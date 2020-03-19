set PATH=%PATH%;%CD%\..

cd qtscriptgenerator\generator
qmake
mingw32-make release
release\generator.exe
cd ..\qtbindings
qmake
mingw32-make release
cd ..\..

