// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__DCB85894_D6AB_4B5B_836B_40678D35E1FB__INCLUDED_)
#define AFX_STDAFX_H__DCB85894_D6AB_4B5B_836B_40678D35E1FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include "MsXml2.h"  
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace\
 rename("EOF","adoEOF")rename("BOF","adoBOF") //导入ADO动态链接库


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__DCB85894_D6AB_4B5B_836B_40678D35E1FB__INCLUDED_)
