#if !defined(AFX_DRAWBUTTON_H__B8248E43_169C_4C56_A517_B152E0739764__INCLUDED_)
#define AFX_DRAWBUTTON_H__B8248E43_169C_4C56_A517_B152E0739764__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawButton.h : header file

#include "DrawButton.h"
//

/////////////////////////////////////////////////////////////////////////////
// CDrawButton window

class CDrawButton : public CButton
{
// Construction
public:
	CDrawButton();
//	CDrawButton(int NL, int HR, int DN, int DD);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL isFirst;
	void SetCBitmap (CBitmap * bNormal, CBitmap * bHower, CBitmap * bDown, CBitmap * bDisabled);	//设置每个状态图片
	BOOL m_isInRect;						//鼠标是否在按钮内部					
	BOOL m_isPressed;						//按钮是否被按下
	CBitmap m_bDown;						//位图：按钮按下
	CBitmap m_bHower;						//位图：按钮高亮
	CBitmap m_bNormal;						//位图：普通按钮
	CBitmap m_bDisabled;					//位图：按钮不可用
	virtual ~CDrawButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawButton)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWBUTTON_H__B8248E43_169C_4C56_A517_B152E0739764__INCLUDED_)


