# Microsoft Developer Studio Project File - Name="Zeus" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Zeus - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Zeus.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Zeus.mak" CFG="Zeus - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Zeus - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Zeus - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Zeus - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/msvc/zeus/release"
# PROP Intermediate_Dir "obj/msvc/zeus/release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib alleg.lib "lib/galib.lib" /nologo /subsystem:windows /machine:I386 /out:"bin/Zeus.exe"

!ELSEIF  "$(CFG)" == "Zeus - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Zeus___Win32_Debug"
# PROP BASE Intermediate_Dir "Zeus___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj/msvc/zeus/debug"
# PROP Intermediate_Dir "obj/msvc/zeus/debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "ZEUS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib alld.lib "lib/galibd.lib" /nologo /subsystem:windows /debug /machine:I386 /out:"bin/Zeus.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Zeus - Win32 Release"
# Name "Zeus - Win32 Debug"
# Begin Group "Cabecalhos"

# PROP Default_Filter "*.h"
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

SOURCE=.\src\zeus\cbotao.h
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

SOURCE=.\src\atena\cconfig.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\cconstrucao.h
# End Source File
# Begin Source File

SOURCE=.\src\zeus\ceditor.h
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

SOURCE=.\src\atena\cladrilho.h
# End Source File
# Begin Source File

SOURCE=.\src\atena\clog.h
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

SOURCE=.\src\zeus\cbotao.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cchefe.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\ccolecao.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cconfig.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\cconstrucao.cpp
# End Source File
# Begin Source File

SOURCE=.\src\zeus\ceditor.cpp
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

SOURCE=.\src\atena\cladrilho.cpp
# End Source File
# Begin Source File

SOURCE=.\src\atena\clog.cpp
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

SOURCE=.\src\atena\funcoes.cpp
# End Source File
# Begin Source File

SOURCE=.\src\zeus\main.cpp
# End Source File
# End Group
# Begin Group "Outros"

# PROP Default_Filter "*.*"
# Begin Source File

SOURCE=.\bin\zeus.ini
# End Source File
# End Group
# Begin Group "Recursos"

# PROP Default_Filter "*.*"
# End Group
# End Target
# End Project
