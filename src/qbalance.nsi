;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

ShowInstDetails show
ShowUninstDetails show

!include "FileFunc.nsh"
!insertmacro un.GetTime


  ;Name and file
  !DEFINE APPNAME "QBalance"
  !DEFINE COMPANYNAME "QBalance"
  OutFile "..\..\qbalance.exe"


  ;Default installation folder
  InstallDir "$LOCALAPPDATA\QBalance"
  
  ;Get installation folder from registry if available
;  InstallDirRegKey HKCU "Software\QBalance" ""

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
    !define MUI_FINISHPAGE_NOAUTOCLOSE
    !define MUI_FINISHPAGE_RUN
    !define MUI_FINISHPAGE_RUN_NOTCHECKED
    !define MUI_FINISHPAGE_RUN_TEXT "Запустить программу"
    !define MUI_FINISHPAGE_RUN_FUNCTION "LaunchLink"
;    !define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED
;    !define MUI_FINISHPAGE_SHOWREADME $INSTDIR\README
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

  createDirectory "$SMPROGRAMS\${COMPANYNAME}"
  createShortCut "$SMPROGRAMS\${COMPANYNAME}\uninstall.lnk" "$INSTDIR\uninstall.exe" ""
  createShortCut "$SMPROGRAMS\${COMPANYNAME}\${APPNAME}.lnk" "$INSTDIR\${APPNAME}.exe" "" "$INSTDIR\resources\${APPNAME}.ico"
  CreateShortCut "$DESKTOP\${APPNAME}.lnk" "$INSTDIR\${APPNAME}.exe" ""

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
  File ..\qextserialport1.dll

  SetOutPath "$INSTDIR\plugins\platforms"
  File /r ..\plugins\platforms\qminimal.dll
  File /r ..\plugins\platforms\qoffscreen.dll
  File /r ..\plugins\platforms\qwindows.dll

  SetOutPath "$INSTDIR\plugins\imageformats"
  File /r ..\plugins\imageformats\qjpeg4.dll

  SetOutPath "$INSTDIR\plugins\sqldrivers"
  File /r ..\plugins\sqldrivers\qsqlpsql4.dll

  SetOutPath "$INSTDIR\plugins\designer"
  File /r ..\plugins\designer\plugins.dll
  File /r ..\plugins\designer\plugins.dll

  SetOutPath "$INSTDIR\plugins\script"
  File /r ..\plugins\script\*.dll
 
 ; SetOutPath "$INSTDIR\examples"
 ; File /r ..\examples\*.*

  SetOutPath "$INSTDIR\resources"
  File /r ..\resources\*.*

  ;Store installation folder
  WriteRegStr HKCU "Software\QBalance" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd


Section /o "source" SecSource

  SetOutPath "$INSTDIR\src"
  
  File *.pri
  File *.bat
  File qbalance.nsi
  File /r *.*

SectionEnd


Section /o "doc" SecDoc

  SetOutPath "$INSTDIR\doc"
  File /r ..\doc\*.*

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
  LangString DESC_Doc ${LANG_RUSSIAN} "Документация к программе."
  LangString DESC_RunProgram ${LANG_RUSSIAN} "Запустить программу"

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SecQBalance} $(DESC_QBalance)
  !insertmacro MUI_DESCRIPTION_TEXT ${SecSource} $(DESC_Source)
  !insertmacro MUI_DESCRIPTION_TEXT ${SecDoc} $(DESC_Doc)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"
  
  DeleteRegKey /ifempty HKCU "Software\QBalance"
  RMDir /r "$INSTDIR"
  RMDir /r "$SMPROGRAMS\${COMPANYNAME}"
  Delete "$DESKTOP\${APPNAME}.lnk"

SectionEnd


;--------------------------------
;Uninstaller Functions

Function un.onInit

  !insertmacro MUI_UNGETLANGUAGE
  
FunctionEnd


Function LaunchLink
;  MessageBox MB_OK "Reached LaunchLink $\r$\n \
;                   SMPROGRAMS: $SMPROGRAMS  $\r$\n \
;                   Start Menu Folder: $STARTMENU_FOLDER $\r$\n \
;                   InstallDirectory: $INSTDIR "
  ExecShell "" "$DESKTOP\${APPNAME}.lnk"
FunctionEnd
