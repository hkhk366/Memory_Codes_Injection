// gua.h : main header file for the GUA application
//

#if !defined(AFX_GUA_H__0A3C3A74_E97D_4C9D_8194_0724C687F1C4__INCLUDED_)
#define AFX_GUA_H__0A3C3A74_E97D_4C9D_8194_0724C687F1C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGuaApp:
// See gua.cpp for the implementation of this class
//

class CGuaApp : public CWinApp
{
public:
	CGuaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGuaApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUA_H__0A3C3A74_E97D_4C9D_8194_0724C687F1C4__INCLUDED_)
