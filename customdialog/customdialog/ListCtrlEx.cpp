// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "customdialog.h"
#include "ListCtrlEx.h"


// CListCtrlEx

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

CListCtrlEx::CListCtrlEx()
{

}

CListCtrlEx::~CListCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	
END_MESSAGE_MAP()



void CListCtrlEx::OnCustomDraw( NMHDR* pNMHDR, LRESULT* pResult)
{
		NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

	*pResult = CDRF_DODEFAULT;

	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	}else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		return;
	}else if ( (CDDS_SUBITEM | CDDS_ITEMPREPAINT) == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYPOSTPAINT;
		return;
	}else if ( (CDDS_SUBITEM | CDDS_ITEMPOSTPAINT) == pLVCD->nmcd.dwDrawStage )
	{
		int nItem = pLVCD->nmcd.dwItemSpec;
		int nSubItem = pLVCD->iSubItem;
		
		return;
	}
}

void CListCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	AfxMessageBox(_T("Left button down"));
	CListCtrl::OnLButtonDown(nFlags, point);
}
void CListCtrlEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	CListCtrl::OnLButtonUp(nFlags, point);
}
void CListCtrlEx::OnMouseMove(UINT nFlags, CPoint point)
{
	//AfxMessageBox(_T("Mouse move"));
	/*TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(tme);
    tme.hwndTrack = m_hWnd;
    tme.dwFlags = TME_LEAVE|TME_HOVER;
    tme.dwHoverTime = 1;
    TrackMouseEvent(&tme);*/
}
void CListCtrlEx::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CListCtrl::OnMouseHover(nFlags, point);
	AfxMessageBox(_T("mouse hover"));
}
