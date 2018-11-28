import vxi11
import time
import re
from sys import stdout

class device_class():

    def __init__(self, ip):
        self.ip = ip
        self.instrument = vxi11.Instrument(str(self.ip))
        self.name = self.instrument.ask('*IDN?')
        self.name = self.name + " [" + self.ip + "]"
        print "connected to: " + self.name

        self.instrument.timeout = 1
        print "vxi11 timeout: ", self.instrument.timeout

    def reset(self):
        print "resetting " + self.name
        self.instrument.write("*RST")

    def write(self, commandString):
        self.instrument.write(commandString)

        #need a delay in some cases to make sure the command goes
        #through, waiting for an operation response of 1 before
        #exiting write operation
        waitCharacter = ['|', '/', '-','\\']
        waitCharacterIndex = 0

        waitTime = 0.1
        while(self.ask("*OPC?") == None):

            #indicator of waiting for system to be back online
            stdout.write('WAITING on CMD['+commandString+'] (' + waitCharacter[waitCharacterIndex] + ')\r')
            stdout.flush()
            waitCharacterIndex = (waitCharacterIndex + 1) % len(waitCharacter)

            #wait some time before checking system availablility
            time.sleep(waitTime)

            #slowly increment the wait time until 1 second
            waitTime = waitTime + .1
            if(waitTime > 1):
                waitTime= 1

    def ask(self, commandString):
        try:
            response = self.instrument.ask(commandString)
            return response
        except:
            #print "ERROR: command [%s] did not complete" % (commandString)
            return None


        
class fsw_class(device_class):
    def __init__(self, ip):
        device_class.__init__(self, ip)

class docsis31_instrument_class(fsw_class):
    def __init__(self, ip):
        fsw_class.__init__(self, ip)

        #setup instrument for docsis 3.1
        self.write("INST:SEL DOCS")

    def reset(self):
        fsw_class.reset(self)

        #after reset profile A is present - must delete this to make
        #sure adding new profile data is valid
        self.write('CONF:DS:CHAN:PCON:SEL A')
        self.write('CONF:DS:CHAN1:PCON:DEL')
        self.write('CONFigure:DS:CHANnel:NCP:PCONfig1:DELete')
        
        #setting default sweep time
        self.acquisition_config()

        #set input power to auto
        self.write('CONFigure:POWer:AUTO ON')
        

    def acquisition_config(self, sweepTimeInSec=.050):
        self.write('SWEep:TIME ' + str(sweepTimeInSec))
        
    def ocd_config(self,
                   centerFreqInHz=1e9,
                   fftMode='4K',
                   cyclicPrefix='auto',
                   rollOff='auto',
                   interleavingDepth=1,
                   plcStartIndex=1,
                   ncpQamMod=16):

        print "User settings:"
        print " - centerFreq[%d]Hz" %         (centerFreqInHz    )
        print " - fftMode[%s]" %              (fftMode           )
        print " - cyclicPrefix[%s]" %         (str(cyclicPrefix) )
        print " - rollOff[%s]" %              (str(rollOff)      )
        print " - interleavingDepth[%d]" %    (interleavingDepth )
        print " - plcStartIndex[%s]" %        (str(plcStartIndex))
        print " - ncpQamMod[%d]" %            (ncpQamMod         )

        #Set the center frequency
        self.write('FREQ:CENT ' + str(centerFreqInHz/1e9) + 'Ghz')
        
        #Nfft mode is 4K
        self.write("CONF:CHAN:NFFT FFT"+fftMode)

        #Configure the cyclic prefix
        cyclicPrefixObj = re.match(' *(?:([Aa][Uu][Tt][Oo])|([0-9]+)) *', str(cyclicPrefix))
        if(cyclicPrefixObj):
            #if auto is detected
            if(cyclicPrefixObj.group(1)):
                print "Cyclic Prefix [AUTO]"
                self.write("CONF:CHAN:CP AUTO")

            #if an number value is detected
            elif(cyclicPrefixObj.group(2)):
                self.write("CONF:CHAN:CP S"+cyclicPrefixObj.group(2))
        else:
            print("ERROR: CP is invalid [" + str(cyclicPrefix) + "]")

        #Configure roll-off factor of 64 samples


        #Configure the roll off
        rollOffObj = re.match(' *(?:([Aa][Uu][Tt][Oo])|([0-9]+)) *', str(rollOff))
        if(rollOffObj):
            #if auto is detected
            if(rollOffObj.group(1)):
                print "Rolloff [AUTO]"
                self.write("CONF:CHAN:ROFF AUTO")

            #if an number value is detected
            elif(rollOffObj.group(2)):
                self.write("CONF:CHAN:ROFF S"+rollOffObj.group(2))

        else:
            print("ERROR: CP is invalid [" + str(rollOff) + "]")



        #Time-interleaving depth is 16
        self.write('CONF:DS:CHAN:TIDepth '+str(interleavingDepth))

        #setup PLC index value or set to auto detect
        plcStartIndexObj = re.match(' *(?:([Aa][Uu][Tt][Oo])|([0-9]+)) *', str(plcStartIndex))

        if(plcStartIndexObj):

            #if auto is detected
            if(plcStartIndexObj.group(1)):
                print "PLC Index [AUTO]"
                self.write('CONFigure:DS:CHANnel:PLC:INDex:AUTO ON')

            #if an index value is detected
            elif(plcStartIndexObj.group(2)):
                #turn off plc index auto detect
                print "Turning off PLC Index to AUTO Detect"
                self.write('CONFigure:DS:CHANnel:PLC:INDex:AUTO OFF')
                print "PLC Index [%s]" % (plcStartIndexObj.group(2).strip())


                #set plc index value
                self.write('CONFigure:DS:CHANnel:PLC:INDex '+plcStartIndexObj.group(2))

        else:
            print("ERROR: PLC start index is invalid [" + str(plcStartIndex) + "]")
        
        #NCP configuration
        if(ncpQamMod == 2):
            self.write('CONF:DS:CHAN:NCP:MOD QPSK')
        else:
            ncpQamMod = 2**ncpQamMod
            self.write('CONF:DS:CHAN:NCP:MOD QAM' + str(ncpQamMod))

            
    def continuousPilots(self, subcarrierList):
        #convert list to string
        subcarrierListString =  str(subcarrierList)[1:-1]

        print "Continuous Pilots [%s]" % (subcarrierListString)

        #specify entry for continuous pilots
        self.write('CONF:DS:CHAN:CPES2:SUBC:TYPE CPIL')

        #write in list of subcarriers to entry
        self.write('CONF:DS:CHAN:CPES2:SUBC:SET '+ subcarrierListString)

    def excludedSubcarriers(self, subcarrierList):
        #convert list to string
        subcarrierListString =  str(subcarrierList)[1:-1]

        print "Excluded subcarriers [%s]" %( subcarrierListString)

        #specify entry for excluded subcarriers
        self.write('CONF:DS:CHAN:CPES3:SUBC:TYPE ESUB')

        #write in list of subcarriers to entry
        self.write('CONF:DS:CHAN:CPES3:SUBC:SET '+ subcarrierListString)

    def profile_config(self, profileId, qamMod, subcarrierStart, subcarrierStop, ncp=False, subcarrierIncrement=1):

        #determine if profile is for NCP or not
        if(True == ncp):
            ncpSelect="NCP:"
            print "Profile[NCP]:"
            
        else:
            ncpSelect=""
            
            #determinine which profile based off of number Id, need to
            #convert to alphabetic Id

            profileId = ord('A') + profileId
            profileId = chr(profileId)

            self.write('CONF:DS:CHAN:PCON:SEL '+profileId)
            print "Profile[%c]: " % (profileId)
            
        profileConfigurationId = int(self.ask('CONF:DS:CHAN:'+ncpSelect+'PCON:COUN?')) + 1
        print" - configuration[%d] qam[%d] start[%d] stop[%d]" % (profileConfigurationId, qamMod, subcarrierStart, subcarrierStop)

        self.write('CONF:DS:CHAN:'+ncpSelect+'PCON'+ str(profileConfigurationId) +':SUBC:STAR '+str(subcarrierStart))
        self.write('CONF:DS:CHAN:'+ncpSelect+'PCON'+ str(profileConfigurationId) +':SUBC:STOP '+str(subcarrierStop))
        self.write('CONF:DS:CHAN:'+ncpSelect+'PCON'+ str(profileConfigurationId) +':SUBC:INCR '+str(subcarrierIncrement))

        if(qamMod == 0):
            self.write('CONF:DS:CHAN:'+ncpSelect+'PCON'+ str(profileConfigurationId) +':SUBC:MOD ZERobit')
        elif(qamMod == 2):
            self.write('CONF:DS:CHAN:'+ncpSelect+'PCON'+ str(profileConfigurationId) +':SUBC:MOD QPSK')
        else:
            qamMod = 2**qamMod
            self.write('CONF:DS:CHAN:'+ncpSelect+'PCON'+ str(profileConfigurationId) +':SUBC:MOD QAM' + str(qamMod))

    def capture(self, captureTimeInMs=50):

        #adjust aquisition time
        self.acquisition_config(sweepTimeInSec=(captureTimeInMs/1000.0))

        #---------- Performing the Measurements -----
        #Select single sweep mode.
        print "turning off continuous sweep"
        self.write('INIT:CONT OFF')

        #capture as many frames as sweep time allows
        #Evaluation Range > Frame Statistic Count > OFF
        self.write("FRAMe:COUNt:STATe OFF")
        
        #Initiate a new measurement and prevent new commands until
        #process is complete (*WAI)
        print "initiate and waiting for capture...."
        self.write('INITiate;*WAI')

        #there is no command to determine number of frames stored in
        #capture buffer... will have to keep pulling out data and use
        #the fact that when there are no more frames the return data
        #is always matching ... TS MB should prevent replication in
        #captured data, so this algorithm should be safe
        self.write('UNIT:BITS BYTE')

        #allow for frames to be selected individually
        self.write('FRAM:SEL:STAT ON')
        
        frameCounter = 0
        frames=[]
        while(1):

            self.write('SENS:FRAM:SEL '+str(frameCounter))

            # note: the retruned data will look like:
            #<CW_Index>,<Object>,<Modulation>,<NoBits>,<NoEntries>,<Bits>,
            currentFrame = self.ask('FETC:BITS:ALL?')

            #if we are repeating frames then we are done
            if(len(frames) > 0):
                if(currentFrame == frames[-1]):
                    break
                
            frames.append(currentFrame)
            print "saved frame: " + str(frameCounter)
            frameCounter = frameCounter + 1
            
        print "total frames saved: " + str(len(frames))
        return frames
    
    def display_config(self):
        #---------- Configuring the result displays ------------
        # Activate following result displays:
        # 1: Signal Content Detailed (bottom)
        # 2: Bitstream (bottom right)
        # 3: Power Spectrum (default, upper right)
        # 4: Constellation (default, lower right)
        
        self.write("LAY:REPL '1',SCD")
        self.write("LAY:REPL '2',BITS")
        self.write("LAY:REPL '3',PSP")
        self.write("LAY:REPL '4',CONS")
        
fsw_ds31 = docsis31_instrument_class('10.23.45.89')
fsw_ds31.reset()
fsw_ds31.display_config()

fsw_ds31.ocd_config(centerFreqInHz = 204e6,
                    fftMode='8K',
                    cyclicPrefix='auto',
                    rollOff='auto',
                    interleavingDepth=1,
                    plcStartIndex='auto',
                    ncpQamMod=2)

fsw_ds31.continuousPilots((374, 531, 680, 830, 982, 1138, 1288, 1447, 1597, 1749, 1909, 2061, 2213, 2364, 2521, 2672, 2830, 2984, 3130, 3281, 3444, 3596, 3746, 3894, 4052, 4207, 4354, 4410, 4434, 4456, 4474, 4549, 4567, 4589, 4613, 4758, 4904, 5064, 5218, 5368, 5524, 5671, 5828, 5983, 6135, 6289, 6436, 6598, 6748, 6904, 7052, 7202, 7354, 7518, 7665, 7823))
##fsw_ds31.excludedSubcarriers((6,7,8,9,10))

fsw_ds31.profile_config(profileId=0, qamMod=4, subcarrierStart=296, subcarrierStop=7895)
fsw_ds31.profile_config(profileId=0, qamMod=2, subcarrierStart=296, subcarrierStop=7895, ncp=True)

capturedBitstream = fsw_ds31.capture(captureTimeInMs=50)
print "\n_Bitstream:_\n" + str(capturedBitstream)

