# Microsoft Developer Studio Project File - Name="GALib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=GALib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GALib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GALib.mak" CFG="GALib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GALib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "GALib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GALib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/msvc/galib/release"
# PROP Intermediate_Dir "obj/msvc/galib/release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/galib.lib"

!ELSEIF  "$(CFG)" == "GALib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GALib___Win32_Debug"
# PROP BASE Intermediate_Dir "GALib___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj/msvc/galib/debug"
# PROP Intermediate_Dir "obj/msvc/galib/debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/galibd.lib"

!ENDIF 

# Begin Target

# Name "GALib - Win32 Release"
# Name "GALib - Win32 Debug"
# Begin Group "Cabecalhos"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\src\galib\gaconfig.h
# End Source File
# Begin Source File

SOURCE=.\src\galib\gadados.h
# End Source File
# Begin Source File

SOURCE=.\src\galib\galib.h
# End Source File
# Begin Source File

SOURCE=.\src\galib\gascript.h
# End Source File
# End Group
# Begin Group "Fontes"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\src\galib\gaconfig.cpp
# End Source File
# Begin Source File

SOURCE=.\src\galib\gadados.cpp
# End Source File
# Begin Source File

SOURCE=.\src\galib\gascript.cpp
# End Source File
# End Group
# End Target
# End Project
