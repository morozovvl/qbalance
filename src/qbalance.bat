set PATH=%PATH%;%CD%\..

cd qextserialport
del makefile
qmake
mingw32-make clean
mingw32-make %1

cd ../qbalance/plugins
del makefile
qmake
mingw32-make clean
mingw32-make %1

cd ../../qbalance
del makefile
qmake
mingw32-make clean
mingw32-make %1

