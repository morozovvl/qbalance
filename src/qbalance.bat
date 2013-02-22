set PATH=%PATH%;%CD%\..

cd qbalance\plugins
del makefile
cd ..\
del makefile
qmake
mingw32-make release

