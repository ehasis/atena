# Microsoft Developer Studio Project File - Name="Atena" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Atena - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Atena.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Atena.mak" CFG="Atena - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Atena - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Atena - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Atena - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/msvc/atena/release"
# PROP Intermediate_Dir "obj/msvc/atena/release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /Ox /Ot /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib alleg.lib "lib/galib.lib" "lib/alfont.lib" /nologo /subsystem:windows /machine:I386 /out:"bin/Atena.exe"

!ELSEIF  "$(CFG)" == "Atena - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj/msvc/atena/debug"
# PROP Intermediate_Dir "obj/msvc/atena/debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib alld.lib "lib/galibd.lib" "lib/alfontd.lib" /nologo /subsystem:windows /debug /machine:I386 /out:"bin/Atenad.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Atena - Win32 Release"
# Name "Atena - Win32 Debug"
# Begin Group "Cabecalhos"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\src\atena\arquivos.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\calien.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\callegro.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\carma.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cbonus.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\ccenario.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cchefe.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\ccolecao.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\ccolecaoavancada.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cconstrucao.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cexplosao.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cfase.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cfilme.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cfundo.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cinimigo.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cjogo.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cladrilho.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cmenu.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cnave.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cobjeto.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\construcoes.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\ctela.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\ctiro.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cveiculo.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\erro.h
# End Source File
# Begin Source File

SOURCE=.\src\galib\galib.h
# End Source File
# End Group
# Begin Group "Fontes"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\src\atena\calien.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\carma.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cbonus.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\ccenario.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cchefe.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\ccolecao.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cconstrucao.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cexplosao.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cfase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cfilme.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cfundo.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cinimigo.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cjogo.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cladrilho.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cmenu.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cnave.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cobjeto.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\ctela.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\ctiro.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cveiculo.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\erro.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\main.cpp
# End Source File
# End Group
# Begin Group "Outros"

# PROP Default_Filter "*.*"
# Begin Source File

SOURCE=.\bin\atena.ini
# End Source File
# End Group
# Begin Group "Recursos"

# PROP Default_Filter "*.rc"
# Begin Source File

SOURCE=.\src\atena\rc\atena.ico
# End Source File
# Begin Source File

SOURCE=.\src\atena\rc\Atena.rc
# End Source File
# Begin Source File

SOURCE=.\src\atena\rc\atena1.ico
# End Source File
# End Group
# End Target
# End Project
