// CustomButton.cpp : implementation file
//

#include "stdafx.h"
#include "CustomDialog.h"
#include "CustomButton.h"


// CCustomButton

IMPLEMENT_DYNAMIC(CCustomButton, CButton)

CCustomButton::CCustomButton()
{
	m_isInClient = 0;
}

CCustomButton::~CCustomButton()
{
}


BEGIN_MESSAGE_MAP(CCustomButton, CButton)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_CREATE()
END_MESSAGE_MAP()


void CCustomButton::OnPaint( ) {

	CPaintDC dc(this);
}

BOOL CCustomButton::OnEraseBkgnd(CDC* pDC) {
	
	return true;
}


void CCustomButton::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct) {

	
	Graphics graphics(lpDrawItemStruct->hDC);
	RECT rect = lpDrawItemStruct->rcItem;

	if (lpDrawItemStruct->itemState & ODS_SELECTED) {

		Point pointStart ((rect.right - rect.left)/2, rect.top);
		Point pointEnd ((rect.right - rect.left)/2, rect.bottom);

		LinearGradientBrush linGrBrush(pointStart, pointEnd, Color(255, 255, 255, 0), Color(255, 219, 219, 219));
		graphics.FillRectangle(&linGrBrush,	0, 0, rect.right - rect.left, rect.bottom - rect.top);
	

	} else if (~(lpDrawItemStruct->itemState & ODS_SELECTED)) {

		SolidBrush brush(Color(255, 0, 0, 0));
		graphics.FillRectangle(&brush, 	0, 0, rect.right - rect.left, rect.bottom - rect.top);

	}

}


void CCustomButton::OnMouseMove(UINT nFlags, CPoint point) {

	CButton::OnMouseMove(nFlags, point);

	
	if (!m_isInClient) {

		Graphics graphics(GetDC()->m_hDC);

		CRect rect;
		GetClientRect(&rect);

		SolidBrush brush(Color(255, 255, 0, 0));
		graphics.FillRectangle(&brush, 	0, 0, rect.right - rect.left, rect.bottom - rect.top);

		TRACKMOUSEEVENT tme = { sizeof(tme) };
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = GetSafeHwnd();
		TrackMouseEvent(&tme);
		m_isInClient = 1;

	}
	
}


LRESULT CCustomButton::OnMouseLeave(WPARAM wParam,LPARAM lParam)
{
	
	m_isInClient = 0;

	Graphics graphics(GetDC()->m_hDC);
	SolidBrush brush(Color(255, 0, 0, 0));

	CRect rect;
	GetClientRect(&rect);

	graphics.FillRectangle(&brush, 	0, 0, rect.right - rect.left, rect.bottom - rect.top);
	
	return 0;
}

LRESULT CCustomButton::OnMouseHover(WPARAM,LPARAM) {

	Graphics graphics(GetDC()->m_hDC);
	SolidBrush brush(Color(255, 255, 0, 0));

	CRect rect;
	GetClientRect(&rect);
	graphics.FillEllipse(&brush, rect.left, rect.top, rect.right, rect.bottom);

	return 0;
}

int CCustomButton::OnCreate(LPCREATESTRUCT lpCreateStruct ) {


	return CButton::OnCreate(lpCreateStruct);
}