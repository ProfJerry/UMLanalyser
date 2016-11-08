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
	void SetCBitmap (CBitmap * bNormal, CBitmap * bHower, CBitmap * bDown, CBitmap * bDisabled);	//����ÿ��״̬ͼƬ
	BOOL m_isInRect;						//����Ƿ��ڰ�ť�ڲ�					
	BOOL m_isPressed;						//��ť�Ƿ񱻰���
	CBitmap m_bDown;						//λͼ����ť����
	CBitmap m_bHower;						//λͼ����ť����
	CBitmap m_bNormal;						//λͼ����ͨ��ť
	CBitmap m_bDisabled;					//λͼ����ť������
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


