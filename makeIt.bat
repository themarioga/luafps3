@echo off
set PATH=C:/PSDK3/mingw/bin;C:/PSDK3/mingw/msys/1.0/bin;C:/PSDK3/mingw/python27;%PATH%
set PS3DEV=/c/PSDK3/ps3dev
set PSL1GHT=/c/PSDK3/psl1ght
set PORTLIBS=/c/PSDK3/portlibs

make
make pkg
pause