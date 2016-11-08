// DrawButton.cpp : implementation file
//

#include "stdafx.h"
#include "UMLanalyser.h"
#include "DrawButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawButton

CDrawButton::CDrawButton()
{
	m_isInRect = FALSE;					
	m_isPressed = FALSE;
	isFirst = TRUE;
}

CDrawButton::~CDrawButton()
{
}


BEGIN_MESSAGE_MAP(CDrawButton, CButton)
	//{{AFX_MSG_MAP(CDrawButton)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
//	ON_WM_PAINT()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawButton message handlers

void CDrawButton::SetCBitmap(CBitmap * bNormal, CBitmap * bHower, CBitmap * bDown, CBitmap * bDisabled)
{
	m_bNormal.Attach (* bNormal);
	m_bHower.Attach (* bHower);
	m_bDown.Attach (* bDown);
	m_bDisabled.Attach (* bDisabled);
}

void CDrawButton::PreSubclassWindow() 
{
	SetTimer (1, 50, NULL);					//定时检测按钮状态并绘制
	
	CButton::PreSubclassWindow();
}

//**************************************************//
//函数功能：定时 更新位图按钮的状态					//
//**************************************************//
void CDrawButton::OnTimer(UINT nIDEvent) 
{
	CPoint point;
	GetCursorPos (& point);
	CRect rcWnd;
	GetWindowRect (& rcWnd);

	//判断鼠标位置
	if (rcWnd.PtInRect (point))
	{
		if (m_isInRect != TRUE)
		{
			m_isInRect = TRUE;
			Invalidate ();
		}
		else
			goto END;
	}
	else
	{
		if (m_isInRect == TRUE)			//在按钮内
		{
			Invalidate ();
			m_isInRect = FALSE;
		}
		else if (m_isPressed == TRUE)	//按钮按下
		{
			Invalidate ();
			m_isPressed = FALSE;
		}
		else
			goto END;
	}
	
END:CButton::OnTimer(nIDEvent);
}

//**************************************************//
//函数功能：鼠标左键按下处理						//
//**************************************************//
void CDrawButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_isPressed = TRUE;					//按钮被按下
	
	CButton::OnLButtonDown(nFlags, point);
}

//**************************************************//
//函数功能：鼠标左键恢复处理						//
//**************************************************//
void CDrawButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_isPressed = FALSE;				//按钮被放开
	
	CButton::OnLButtonUp(nFlags, point);
}


//**************************************************//
//函数功能：绘制为图按钮							//
//**************************************************//
void CDrawButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (isFirst)
	{
		CBitmap bNormal;
		CBitmap bHower;
		CBitmap bDown;
		CBitmap bDisabled;

		long ID = GetWindowLong (m_hWnd ,GWL_ID);

		if (ID == IDC_BUTTON_OPEN)
		{
			bNormal.LoadBitmap (IDB_BITMAP_OPEN);
			bHower.LoadBitmap (IDB_BITMAP_OPEN_HOVER);
			bDown.LoadBitmap (IDB_BITMAP_OPEN_DOWN);
			bDisabled.LoadBitmap (IDB_BITMAP_OPEN_DISABLED);
		}
		else if (ID == IDC_BUTTON_ANALYSE)
		{
			bNormal.LoadBitmap (IDB_BITMAP_ANALYSE);
			bHower.LoadBitmap (IDB_BITMAP_ANALYSE_HOVER);
			bDown.LoadBitmap (IDB_BITMAP_ANALYSE_DOWN);
			bDisabled.LoadBitmap (IDB_BITMAP_ANALYSE_DISABLED);
		}
		else if (ID == IDC_BUTTON_LOG)
		{
			bNormal.LoadBitmap (IDB_BITMAP_LOG);
			bHower.LoadBitmap (IDB_BITMAP_LOG_HOVER);
			bDown.LoadBitmap (IDB_BITMAP_LOG_DOWN);
			bDisabled.LoadBitmap (IDB_BITMAP_LOG_DISABLED);
		}
		else if (ID == IDC_BUTTON_TXT)
		{
			bNormal.LoadBitmap (IDB_BITMAP_TXT);
			bHower.LoadBitmap (IDB_BITMAP_TXT_HOVER);
			bDown.LoadBitmap (IDB_BITMAP_TXT_DOWN);
			bDisabled.LoadBitmap (IDB_BITMAP_TXT_DISABLED);
		}
		else if (ID == IDCANCEL)
		{
			bNormal.LoadBitmap (IDB_BITMAP_CLOSE);
			bHower.LoadBitmap (IDB_BITMAP_CLOSE_HOVER);
			bDown.LoadBitmap (IDB_BITMAP_CLOSE_DOWN);
			bDisabled.LoadBitmap (IDB_BITMAP_CLOSE_DISABLED);
		}
		else if (ID == IDC_BUTTON_LOGCANCEL || IDC_BUTTON_TXTCANCEL)
		{
			bNormal.LoadBitmap (IDB_BITMAP_RETURN);
			bHower.LoadBitmap (IDB_BITMAP_RETURN_HOVER);
			bDown.LoadBitmap (IDB_BITMAP_RETURN_DOWN);
			bDisabled.LoadBitmap (IDB_BITMAP_RETURN_DISABLED);
		}
		
		SetCBitmap (& bNormal, & bHower, & bDown, & bDisabled);
		bNormal.Detach ();
		bHower.Detach ();
		bDown.Detach ();
		bDisabled.Detach ();
		isFirst = FALSE;
	}

	//创建兼容设备上下文
	CDC dc;
	dc.Attach (lpDrawItemStruct->hDC);
	UINT state = lpDrawItemStruct->itemState;
	CRect rect;
	GetClientRect (rect);
	CDC memDC;
	memDC.CreateCompatibleDC (& dc);
	BITMAP m_bmp;
	if (! IsWindowEnabled())			//按钮不可用
	{
		memDC.SelectObject (& m_bDisabled);	
		m_bDisabled.GetBitmap (& m_bmp);
	}
	else if (m_isPressed == TRUE)		//按钮被按下
	{
		memDC.SelectObject (& m_bDown);	
		m_bDown.GetBitmap (& m_bmp);
	}
	else if (m_isInRect == TRUE)		//按钮高亮
	{
		memDC.SelectObject (& m_bHower);	
		m_bHower.GetBitmap (& m_bmp);
	}
	else								//正常按钮
	{
		memDC.SelectObject (& m_bNormal);	
		m_bNormal.GetBitmap (& m_bmp);
	}
	int x = m_bmp.bmWidth;
	int y = m_bmp.bmHeight;

	//绘制位图
	dc.StretchBlt (0, 0, rect.Width (), rect.Height (), & memDC, 0, 0, x, y, SRCCOPY);
	memDC.DeleteDC ();

	//绘制按钮标题
	CString str;
	GetWindowText (str);
	dc.DrawText (str, CRect (0, 0, rect.right, rect.bottom), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc.DeleteDC ();	
}
