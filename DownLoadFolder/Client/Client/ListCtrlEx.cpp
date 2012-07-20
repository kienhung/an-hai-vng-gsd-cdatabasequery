// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlEx.h"


// CListCtrlEx

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)
CListCtrlEx::CListCtrlEx() : m_iProgressColumn(0)
{
}

CListCtrlEx::~CListCtrlEx()
{
	int Count = (int) m_ProgressList.size();
	for(int i = Count - 1; i >= 0; i--)
	{
		CProgressCtrl* pControl = m_ProgressList[i];
		m_ProgressList.pop_back();
		pControl->DestroyWindow();
		delete pControl;
	}
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CListCtrlEx message handlers


void CListCtrlEx::OnPaint()
{
	// TODO: Add your message handler code here
	// Do not call CListCtrl::OnPaint() for painting messages
	CListCtrl::OnPaint();
	
}

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
	
	CString strStatus;
	strStatus.Format(_T("%d"), iStatus);

	// Insert status download.
	lvItemDownload.iSubItem = 2;
	lvItemDownload.pszText = (LPTSTR)(LPCTSTR)(strStatus);
	
	SetItem(&lvItemDownload);
	

	InsertProgresCtrl(iIndex, iStatus);
		
	
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
	m_ProgressList.push_back(pControl);
}

void CListCtrlEx::UpdateStatusDownload(int iIndex, int iStatus)
{
	CString strStatus;
	strStatus.Format(_T("%d%%"), iStatus);
	m_ProgressList[iIndex]->SetWindowText(strStatus.GetBuffer());
	m_ProgressList[iIndex]->SetMarquee(false, 1);
	m_ProgressList[iIndex]->SetPos(iStatus);
	m_ProgressList[iIndex]->Invalidate(TRUE);
	if(iStatus >= 100)
	{
		SetItemText(iIndex, 2, strStatus);
	}
	

	CHeaderCtrl* pHeader=GetHeaderCtrl();
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
	
	m_ProgressList[iIndex]->MoveWindow(&rt, TRUE);
		
	
}