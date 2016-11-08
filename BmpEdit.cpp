// BmpEdit.cpp : implementation file

#include "stdafx.h"
#include "UMLanalyser.h"
#include "BmpEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpEdit

CBmpEdit::CBmpEdit()
{
	m_Bitmap.LoadBitmap(IDB_BITMAP_EDIT);
}

CBmpEdit::~CBmpEdit()
{
}


BEGIN_MESSAGE_MAP(CBmpEdit, CEdit)
	//{{AFX_MSG_MAP(CBmpEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_DROPFILES()
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpEdit message handlers

BOOL CBmpEdit::OnEraseBkgnd(CDC* pDC) 
{
/*	CDC memDC;
	memDC.CreateCompatibleDC(pDC);												//创建内存设备上下文
	memDC.SelectObject(&m_Bitmap);												//将位图选入设备上下文
	BITMAP m_Bmp;																//声明位图控件
	m_Bitmap.GetBitmap(&m_Bmp);													//获得位图信息
	int x = m_Bmp.bmWidth;														//获取图片宽度
	int y = m_Bmp.bmHeight;														//获取图片高度
	CRect rect;																	//声明矩形区域对象
	GetClientRect(rect);														//获取编辑区大小矩形框
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,x,y,SRCCOPY);		//伸展铺上图片
	memDC.DeleteDC();															//释放内存设备上下文
	return TRUE;
*/
	CBrush hbr, * phbrOld;
	CRect rect;
	hbr.CreatePatternBrush (&m_Bitmap);
	phbrOld= pDC->SelectObject(&hbr);
	GetClientRect(&rect);
	pDC->FillRect(&rect,&hbr);
	pDC->SelectObject(phbrOld);
	hbr.DeleteObject();
	return TRUE; 
	//return CEdit::OnEraseBkgnd(pDC);
}

void CBmpEdit::OnChange() 
{
	// send this notification unless you override the CEdit::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
//	Invalidate();																//刷新用户界面
	
}

HBRUSH CBmpEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetBkMode(TRANSPARENT);												//设置文字背景透明
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
//	CRect rect;
//	GetClientRect(rect);													//获取客户区域
//	InvalidateRect(rect);
	return NULL;
}


void CBmpEdit::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CEdit::OnVScroll(nSBCode, nPos, pScrollBar);								//判断滚动条是否滑动
	CRect rect;
	GetClientRect(rect);													//获取客户区域
	InvalidateRect(rect);													//刷新用户界面																//刷新用户界面
}

void CBmpEdit::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CEdit::OnHScroll(nSBCode, nPos, pScrollBar);								//判断滚动条是否滑动
	CRect rect;
	GetClientRect(rect);													//获取客户区域
	InvalidateRect(rect);													//刷新用户界面																//刷新用户界面
}


void CBmpEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	oldH = GetScrollPos (SB_HORZ);
	oldV = GetScrollPos (SB_VERT);
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CBmpEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
	int newH = GetScrollPos (SB_HORZ);
	int newV = GetScrollPos (SB_VERT);
	if (oldH != newH || oldV != newV)																//判断滚动条是否滑动
	{
		CRect rect;
		GetClientRect(rect);													//获取客户区域
		InvalidateRect(rect);													//刷新用户界面															//刷新用户界面
	}
}


BOOL CBmpEdit::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	int n1,n2,n3,n4;
	n1 = GetScrollPos (SB_VERT);	
	n3= GetScrollPos (SB_HORZ);
	BOOL editS = CEdit::OnMouseWheel(nFlags, zDelta, pt);
	n2 = GetScrollPos (SB_VERT);
	n4 = GetScrollPos (SB_HORZ);
	if (n1 != n2 || n3 != n4)																//判断滚动条是否滑动
	{
		CRect rect;
		GetClientRect(rect);													//获取客户区域
		InvalidateRect(rect);													//刷新用户界面															//刷新用户界面
	}

	return editS;
}

void CBmpEdit::OnMouseMove(UINT nFlags, CPoint point) 
{
	int n1,n2,n3,n4;
	n1 = GetScrollPos (SB_VERT);	
	n3= GetScrollPos (SB_HORZ);
	CEdit::OnMouseMove(nFlags, point);
	n2 = GetScrollPos (SB_VERT);
	n4 = GetScrollPos (SB_HORZ);
	if (n1 != n2 || n3 != n4)																//判断滚动条是否滑动
	{
		CRect rect;
		GetClientRect(rect);													//获取客户区域
		InvalidateRect(rect);													//刷新用户界面															//刷新用户界面
	}
}
