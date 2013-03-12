set PATH=%PATH%;%CD%\..

cd qbalance\plugins
del makefile
qmake
mingw32-make clean
mingw32-make release
cd ..\
del makefile
qmake
mingw32-make clean
mingw32-make release

