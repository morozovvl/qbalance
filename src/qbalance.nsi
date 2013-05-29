;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

  ;Name and file
  Name "QBalance"
  OutFile "..\..\qbalance.exe"

  ;Default installation folder
  InstallDir "$LOCALAPPDATA\QBalance"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\QBalance" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel user

;--------------------------------
;Interface Settings
  !define MUI_HEADERIMAGE
;  !define MUI_HEADERIMAGE_BITMAP "src\resources\view.png" ; optional
  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "..\license.gpl"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH
  
  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH  


;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"
  !insertmacro MUI_LANGUAGE "Russian"

  !insertmacro MUI_RESERVEFILE_LANGDLL

;--------------------------------
;Installer Sections

Section "QBalance" SecQBalance

  SetOutPath "$INSTDIR"
  
  ;ADD YOUR OWN FILES HERE...
  File ..\LICENSE.GPL
  File ..\README
  File ..\qbalance.exe
  File ..\psql.exe
  File ..\zip.exe
  File ..\bzip2.dll
  File ..\unzip.exe
  File ..\QtCore4.dll
  File ..\QtGui4.dll
  File ..\QtScript4.dll
  File ..\QtSql4.dll
  File ..\QtXml4.dll
  File ..\QtNetwork4.dll
  File ..\QtOpenGL4.dll
  File ..\QtSvg4.dll
  File ..\QtWebKit4.dll
  File ..\QtXmlPatterns4.dll
  File ..\phonon4.dll
  File ..\mingwm10.dll
;  File ..\comerr32.dll
  File ..\msvcr90.dll
  File ..\msvcrt.dll
  File ..\libpq.dll
;  File ..\gssapi32.dll
;  File ..\k5sprt32.dll
;  File ..\krb5_32.dll
  File ..\libeay32.dll
  File ..\libgcc_s_dw2-1.dll
  File ..\libiconv-2.dll
  File ..\libintl-8.dll
  File ..\ssleay32.dll
  File ..\msjava.dll
  File ..\qt.conf
  File ..\initdb*.sql

  SetOutPath "$INSTDIR\plugins"
  File /r ..\plugins\*.dll
  
  SetOutPath "$INSTDIR\imageformats"
  File /r ..\imageformats\*.dll

  SetOutPath "$INSTDIR\doc"
  File /r ..\doc\*.*
  
  SetOutPath "$INSTDIR\examples"
  File /r ..\examples\*.*

  SetOutPath "$INSTDIR\resources"
  File /r ..\resources\*.*

  ;Store installation folder
  WriteRegStr HKCU "Software\QBalance" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd


Section "source" SecSource

  SetOutPath "$INSTDIR\src"
  
  File *.pri
  File *.bat
  File qbalance.nsi

  SetOutPath "$INSTDIR\src\qbalance"
  
  File /r *.h
  File /r *.cpp
  File /r *.qrc
  File /r *.pro

  SetOutPath "$INSTDIR\src\drvfr"
  
  File /r *.*

  SetOutPath "$INSTDIR\src\qtscriptgenerator"
  
  File /r *.*

SectionEnd


;--------------------------------
;Installer Functions

Function .onInit

  !insertmacro MUI_LANGDLL_DISPLAY

FunctionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_QBalance ${LANG_RUSSIAN} "Основная программа."
  LangString DESC_Source ${LANG_RUSSIAN} "Исходные тексты программы."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecQBalance} $(DESC_QBalance)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecSource} $(DESC_Source)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;ADD YOUR OWN FILES HERE...

  Delete "$INSTDIR\*.*"
  Delete "$INSTDIR\src"

  RMDir "$INSTDIR"

  DeleteRegKey /ifempty HKCU "Software\QBalance"

SectionEnd


;--------------------------------
;Uninstaller Functions

Function un.onInit

  !insertmacro MUI_UNGETLANGUAGE
  
FunctionEnd
