// guaDlg.h : header file
//

#if !defined(AFX_GUADLG_H__6B5B7422_0C8D_47CD_B46D_7B13EDB6141B__INCLUDED_)
#define AFX_GUADLG_H__6B5B7422_0C8D_47CD_B46D_7B13EDB6141B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGuaDlg dialog

class CGuaDlg : public CDialog
{
// Construction
public:
	CGuaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGuaDlg)
	enum { IDD = IDD_GUA_DIALOG };
	CListCtrl	m_syslist;
	CString	m_wupinming;
	int		m_jiange;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGuaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnCheck1();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUADLG_H__6B5B7422_0C8D_47CD_B46D_7B13EDB6141B__INCLUDED_)
