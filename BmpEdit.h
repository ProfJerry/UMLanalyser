#if !defined(AFX_BmpEdit_H__445FE7AE_1FB1_4019_9CA6_F3C773D85DAF__INCLUDED_)
#define AFX_BmpEdit_H__445FE7AE_1FB1_4019_9CA6_F3C773D85DAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BmpEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBmpEdit window

class CBmpEdit : public CEdit
{
// Construction
public:
	CBmpEdit();
	CBitmap m_Bitmap;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	int oldV;
	int oldH;
	virtual ~CBmpEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBmpEdit)
	afx_msg void OnChange();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BmpEdit_H__445FE7AE_1FB1_4019_9CA6_F3C773D85DAF__INCLUDED_)
