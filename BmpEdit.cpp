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
	memDC.CreateCompatibleDC(pDC);												//�����ڴ��豸������
	memDC.SelectObject(&m_Bitmap);												//��λͼѡ���豸������
	BITMAP m_Bmp;																//����λͼ�ؼ�
	m_Bitmap.GetBitmap(&m_Bmp);													//���λͼ��Ϣ
	int x = m_Bmp.bmWidth;														//��ȡͼƬ���
	int y = m_Bmp.bmHeight;														//��ȡͼƬ�߶�
	CRect rect;																	//���������������
	GetClientRect(rect);														//��ȡ�༭����С���ο�
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,x,y,SRCCOPY);		//��չ����ͼƬ
	memDC.DeleteDC();															//�ͷ��ڴ��豸������
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
	
//	Invalidate();																//ˢ���û�����
	
}

HBRUSH CBmpEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetBkMode(TRANSPARENT);												//�������ֱ���͸��
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
//	CRect rect;
//	GetClientRect(rect);													//��ȡ�ͻ�����
//	InvalidateRect(rect);
	return NULL;
}


void CBmpEdit::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CEdit::OnVScroll(nSBCode, nPos, pScrollBar);								//�жϹ������Ƿ񻬶�
	CRect rect;
	GetClientRect(rect);													//��ȡ�ͻ�����
	InvalidateRect(rect);													//ˢ���û�����																//ˢ���û�����
}

void CBmpEdit::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CEdit::OnHScroll(nSBCode, nPos, pScrollBar);								//�жϹ������Ƿ񻬶�
	CRect rect;
	GetClientRect(rect);													//��ȡ�ͻ�����
	InvalidateRect(rect);													//ˢ���û�����																//ˢ���û�����
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
	if (oldH != newH || oldV != newV)																//�жϹ������Ƿ񻬶�
	{
		CRect rect;
		GetClientRect(rect);													//��ȡ�ͻ�����
		InvalidateRect(rect);													//ˢ���û�����															//ˢ���û�����
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
	if (n1 != n2 || n3 != n4)																//�жϹ������Ƿ񻬶�
	{
		CRect rect;
		GetClientRect(rect);													//��ȡ�ͻ�����
		InvalidateRect(rect);													//ˢ���û�����															//ˢ���û�����
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
	if (n1 != n2 || n3 != n4)																//�жϹ������Ƿ񻬶�
	{
		CRect rect;
		GetClientRect(rect);													//��ȡ�ͻ�����
		InvalidateRect(rect);													//ˢ���û�����															//ˢ���û�����
	}
}
