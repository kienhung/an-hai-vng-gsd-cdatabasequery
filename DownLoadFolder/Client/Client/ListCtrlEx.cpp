// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CListCtrlEx

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)
CListCtrlEx::CListCtrlEx() : m_iProgressColumn(0)
{
}

CListCtrlEx::~CListCtrlEx()
{
	/*int Count = (int) m_ProgressList.size();
	for(int i = Count - 1; i >= 0; i--)
	{
		CProgressCtrl* pControl = m_ProgressList[i];
		m_ProgressList.pop_back();
		pControl->DestroyWindow();
		delete pControl;
	}*/
	m_vtFileSize.clear();
	m_vtSumSizeDownload.clear();
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CListCtrlEx message handlers


void CListCtrlEx::InitProgressColumn(int iColNum/*=0*/)
{
	m_iProgressColumn = iColNum;
}

void CListCtrlEx::InsertItemDownload(int iIndex, LPCTSTR strFileName,unsigned __int64 iFileSize, int iStatus )
{
	/*LPCTSTR strFileSize, LPCTSTR strStatus*/

	LVITEM lvItemDownload;
	lvItemDownload.mask = LVIF_TEXT | LVIF_STATE;
	lvItemDownload.state = LVIS_OVERLAYMASK;
	lvItemDownload.stateMask = LVIS_SELECTED;
	lvItemDownload.iItem = iIndex;

	
	// Insert file name.
	lvItemDownload.iSubItem = 0;
	lvItemDownload.pszText = (LPTSTR)(LPCTSTR)(strFileName);
	InsertItem(&lvItemDownload);

	CString strFileSize;
	strFileSize.Format(_T("%I64u"), iFileSize);
	

	// Insert file size.
	lvItemDownload.iSubItem = 1;
	lvItemDownload.pszText = (LPTSTR)(LPCTSTR)(strFileSize.GetBuffer());
	SetItem(&lvItemDownload);
	
	m_vtFileSize.push_back(iFileSize);
	m_vtSumSizeDownload.push_back(0);

	//CString strStatus;
	//strStatus.Format(_T("%d"), iStatus);

	// Insert status download.
	//lvItemDownload.iSubItem = 2;
	//lvItemDownload.pszText = (LPTSTR)(LPCTSTR)(strStatus);
	
	//SetItem(&lvItemDownload);
	

	//InsertProgresCtrl(iIndex, iStatus);
		
	
}
void CListCtrlEx::InsertProgresCtrl(int iIndex, int iStatus)
{
	CHeaderCtrl* pHeader = GetHeaderCtrl();
	
	CRect ColRt;
	pHeader->GetItemRect(m_iProgressColumn, &ColRt);
	 //get the rect
	CRect rt;
	GetItemRect(iIndex, &rt, LVIR_LABEL);
	rt.top += 1;
	rt.bottom -= 1;
	rt.left += ColRt.left;
	int Width = ColRt.Width();
	rt.right = rt.left + Width - 4;
	
	rt.left = ColRt.left+1;
	rt.right = ColRt.right-1;

	CProgressCtrl *pControl = new CProgressCtrl;
	pControl->Create(WS_CHILD|WS_VISIBLE, rt, this, IDC_PROGRESS_LIST + iIndex);
	pControl->SetRange(0, 100);
	pControl->SetPos(iStatus);
	pControl->ShowWindow(SW_SHOWNOACTIVATE);
	
	 //add them to the list
	//m_ProgressList.push_back(pControl);
	
}

void CListCtrlEx::UpdateStatusDownload(int iIndex, int iAddStatus)
{
	//CString strStatus;
	//strStatus.Format(_T("%d%%"), iStatus);

	/*m_ProgressList[iIndex]->SetWindowText(strStatus.GetBuffer());
	m_ProgressList[iIndex]->SetMarquee(false, 1);
	m_ProgressList[iIndex]->SetPos(iStatus);
	m_ProgressList[iIndex]->Invalidate(TRUE);*/
	///__int64 iSizeFile = _wtoi64(GetItemText(iIndex, 1));
	
	
	CProgressCtrl* pCtrl;
	pCtrl = (CProgressCtrl*)this->GetItemData(iIndex);
	if(NULL != pCtrl)
	{
		m_vtSumSizeDownload[iIndex] += iAddStatus;
		int iPer = (int)( (double)m_vtSumSizeDownload[iIndex]*100.0 / (double)m_vtFileSize[iIndex]);
		pCtrl->SetPos(iPer);
	}
	/*CHeaderCtrl* pHeader = GetHeaderCtrl();
	CRect ColRt;
	pHeader->GetItemRect(m_iProgressColumn,&ColRt);
	CRect rt;
	GetItemRect(iIndex, &rt, LVIR_LABEL);
	rt.top += 1;
	rt.bottom -= 1;
	rt.left += ColRt.left;
	int Width = ColRt.Width();
	rt.right = rt.left + Width - 4;
	rt.left = ColRt.left +1 ;
	rt.right = ColRt.right-1;

	m_ProgressList[iIndex]->MoveWindow(&rt, TRUE);*/
}

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
		if (m_iProgressColumn != nSubItem)
			return;
		
		CRect rcSubItem;
		this->GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rcSubItem);
		
		CProgressCtrl* pCtrl = (CProgressCtrl*)this->GetItemData(nItem);
		if (NULL == pCtrl)
		{
			pCtrl = new CProgressCtrl;
			//if (rcSubItem.Width() > 100)
			//	rcSubItem.right = rcSubItem.left + 100;

			pCtrl->Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH, rcSubItem, 
							   this, 0x1000 + nItem);
			ASSERT(pCtrl->GetSafeHwnd());
			
			pCtrl->SetPos( nItem*10 % 100 );
			this->SetItemData(nItem, (DWORD)pCtrl);
		}
			
		//if (rcSubItem.Width() > 100)
		//	rcSubItem.right = rcSubItem.left + 100;
		pCtrl->MoveWindow(rcSubItem);
		
		pCtrl->ShowWindow(SW_SHOW);
		*pResult = CDRF_SKIPDEFAULT;
		return;
	}
}

void CListCtrlEx::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
	InvalidateProgressCtrls();
}

void CListCtrlEx::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
	InvalidateProgressCtrls();
}

void CListCtrlEx::OnDestroy()
{
	int nCount = this->GetItemCount();
	CProgressCtrl* pCtrl;
	for(int i = 0; i < nCount; i++)
	{
		pCtrl = (CProgressCtrl*)this->GetItemData(i);
		if (NULL != pCtrl)
			delete pCtrl;
		this->SetItemData(i, 0);
	}
}

void CListCtrlEx::InvalidateProgressCtrls()
{
	int nFirst = GetTopIndex();
	int nLast = nFirst + GetCountPerPage();

	//Hide the other items.
	int nCount = this->GetItemCount();
	CProgressCtrl* pCtrl;
	for(int i = 0; i < nFirst; i++)
	{
		pCtrl = (CProgressCtrl*)this->GetItemData(i);
		if (NULL != pCtrl)
			pCtrl->ShowWindow(SW_HIDE);		
	}

	for(int i = nLast; i < nCount; i++)
	{
		pCtrl = (CProgressCtrl*)this->GetItemData(i);
		if (NULL != pCtrl)
			pCtrl->ShowWindow(SW_HIDE);	
	}

	//Invalidate
	CRect rc(0,0,0,0);
	CRect rcSubItem;
	for(; nFirst < nLast; nFirst++)
	{
		GetSubItemRect(nFirst, 2, LVIR_BOUNDS, rcSubItem);
		VERIFY( rc.UnionRect(rc, rcSubItem) );
	}

	InvalidateRect(rc);
}