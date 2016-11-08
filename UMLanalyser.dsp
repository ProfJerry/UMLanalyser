# Microsoft Developer Studio Project File - Name="UMLanalyser" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=UMLanalyser - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UMLanalyser.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UMLanalyser.mak" CFG="UMLanalyser - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UMLanalyser - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "UMLanalyser - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UMLanalyser - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 msxml2.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "UMLanalyser - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 msxml2.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "UMLanalyser - Win32 Release"
# Name "UMLanalyser - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ADO.cpp
# End Source File
# Begin Source File

SOURCE=.\BmpEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawButton.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UMLanalyser.cpp
# End Source File
# Begin Source File

SOURCE=.\UMLanalyser.rc
# End Source File
# Begin Source File

SOURCE=.\UMLanalyserDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ADO.h
# End Source File
# Begin Source File

SOURCE=.\BmpEdit.h
# End Source File
# Begin Source File

SOURCE=.\DrawButton.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UMLanalyser.h
# End Source File
# Begin Source File

SOURCE=.\UMLanalyserDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\analyse.bmp
# End Source File
# Begin Source File

SOURCE=.\res\analyse_disabled.bmp
# End Source File
# Begin Source File

SOURCE=.\res\analyse_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\analyse_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\background.bmp
# End Source File
# Begin Source File

SOURCE=.\res\close.bmp
# End Source File
# Begin Source File

SOURCE=.\res\close_disabled.bmp
# End Source File
# Begin Source File

SOURCE=.\res\close_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\close_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\edit_background.bmp
# End Source File
# Begin Source File

SOURCE=.\res\edit_small.bmp
# End Source File
# Begin Source File

SOURCE=.\res\log.bmp
# End Source File
# Begin Source File

SOURCE=.\res\log_disabled.bmp
# End Source File
# Begin Source File

SOURCE=.\res\log_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\log_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\open.bmp
# End Source File
# Begin Source File

SOURCE=.\res\open_disabled.bmp
# End Source File
# Begin Source File

SOURCE=.\res\open_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\open_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\return.bmp
# End Source File
# Begin Source File

SOURCE=.\res\return_disabled.bmp
# End Source File
# Begin Source File

SOURCE=.\res\return_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\return_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\txt.bmp
# End Source File
# Begin Source File

SOURCE=.\res\txt_disabled.bmp
# End Source File
# Begin Source File

SOURCE=.\res\txt_down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\txt_hover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\UMLanalyser.ico
# End Source File
# Begin Source File

SOURCE=.\res\UMLanalyser.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\model.mdb
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
