#from Tkinter import *
#import os
#
#root = Tk()
#termf = Frame(root, height=400, width=500)
#
#termf.pack(fill=BOTH, expand=YES)
#wid = termf.winfo_id()
#os.system('xterm -into %d -geometry 400x200 -sb &' % wid)
#
#root.mainloop()

#!/usr/bin/python
from Tkinter import *
import ttk
import os

main = Tk()
main.title('Notebook Demo')
main.geometry('800x600')

# gives weight to the cells in the grid
rows = 0
while rows < 50:
    main.rowconfigure(rows, weight=1)
    main.columnconfigure(rows, weight=1)
    rows += 1

# Defines and places the notebook widget
nb = ttk.Notebook(main)
nb.grid(row=1, column=0, columnspan=50, rowspan=49, sticky='NESW')


XTENSA_CORE="D106_micro_be_ecc"
XTENSA_BUILD_PLATFORM_PATH="RD-2012.5-linux"
XTENSA_TOOL_INSTALL_PATH="/opt/xtensa/XtDevTools/install"
core_specific_file="/sw/agarcha/home/projects/cronus/sit/feature_dev/full/dev/Firmware/build/build_asic_Latest/bin/cpu_h"

terminal_program="xterm"

# Adds tab 1 of the notebook
page1 = ttk.Frame(nb)
nb.add(page1, text='Tab1')
#cmd="${terminal_program} -into %d -geometry 400x200 -sb -e \"${XTENSA_TOOL_INSTALL_PATH}/tools/${XTENSA_BUILD_PLATFORM_PATH}/XtensaTools/bin/xt-gdb --xtensa -core=${XTENSA_CORE} -x ${core_specific_file}\"&" % page1.winfo_id()

xterm_cmd = XTENSA_TOOL_INSTALL_PATH + "/tools/"+XTENSA_BUILD_PLATFORM_PATH+"/XtensaTools/bin/xt-gdb --xtensa-core=" + XTENSA_CORE +" -x " + core_specific_file
cmd = terminal_program + " -into "+str(page1.winfo_id())+" -geometry 400x200 -sb -e \""  + xterm_cmd + "\"&" 
print "CMD:  " + cmd
os.system(cmd)

# Adds tab 2 of the notebook
page2 = ttk.Frame(nb)
nb.add(page2, text='Tab2')


main.mainloop()
