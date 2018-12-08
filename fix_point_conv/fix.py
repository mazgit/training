import math

def floatToFix(val, numFracBits):
    floatVal = float(val)
    totalbits = 32

    decVal = floatVal - math.floor(floatVal)
    intVal = floatVal - decVal

    #print "floatVal[%f] intVal[%f] decVal[%f] " % (floatVal, intVal, decVal)

    searchVal = 0
    fracBits = 0
    for fracCount in range(1,numFracBits+1):

        additionVal = 1.0/(2**fracCount)

        if((searchVal + additionVal) <= decVal):
            searchVal = searchVal + additionVal
            fracBits = fracBits | (1<<(numFracBits-fracCount))
            #print "bit[%d] searchVal[%f] addition[%f]" % (fracCount, searchVal, additionVal)
        #else:
        #    print "skip bit[%d]" % (fracCount)

    #print(bin(fracBits))
    #print(bin(int(intVal)))
    fixedPointVal = (int(intVal) << numFracBits) | fracBits
    #print(bin(fixedPointVal), " // ", hex(fixedPointVal) )
    return fixedPointVal

val = 21.85123
frac = 15
print hex(floatToFix(val, frac))
print hex(int(val * 2**(frac)))
