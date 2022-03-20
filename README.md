This is the Debug Project
Contributor : Chutzpa William YEUMO BARKWENDE

How to use :
-Make sure that your CWD is */ProjetPOSIX
-Use : make to compile the program
-use : ./debug + <./yourexecutable>
-Have fun catching different types of error signals and look at the elf map of the binary

Functions role explained in the .h
Elf lines will give us what functions are used in the executable and the libs called however it's bloated, but we use the SHT_SYMTAB to get only the things we want

