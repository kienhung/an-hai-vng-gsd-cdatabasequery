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
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CListCtrlEx message handlers


void CListCtrlEx::OnPaint()
{
	// TODO: Add your message handler code here
	// Do not call CListCtrl::OnPaint() for painting messages

	int Top = GetTopIndex();
	int Total = GetItemCount();
	int PerPage = GetCountPerPage();
	int LastItem = ((Top+PerPage)>Total)?Total:Top+PerPage;

	//Remove all progressbar to add it back
	int Count = (int)m_ProgressList.GetCount();
	for(int i = 0; i < Count; i++)
	{
		CProgressCtrl* pControl = m_ProgressList.GetAt(0);
		pControl->DestroyWindow();
		m_ProgressList.RemoveAt(0);
	}

	CHeaderCtrl* pHeader = GetHeaderCtrl();
	for(int i = Top; i < LastItem; i++)
	{
		CRect ColRt;
		pHeader->GetItemRect(m_iProgressColumn, &ColRt);
		// get the rect
		CRect rt;
		GetItemRect(i, &rt, LVIR_LABEL);
		rt.top += 1;
		rt.bottom -= 1;
		rt.left += ColRt.left;
		int Width = ColRt.Width();
		rt.right = rt.left + Width - 4;
		
		rt.left = ColRt.left+1;
		rt.right = ColRt.right-1;

		// create the progress control and set their position
		CProgressCtrl* pControl = new CProgressCtrl();
		pControl->Create(NULL, rt, this, IDC_PROGRESS_LIST + i);

		CString Data = GetItemText(i, 2);
		int Percent = _wtoi(Data);

		// set the position on the control
		pControl->SetPos(Percent);
		pControl->ShowWindow(SW_SHOWNORMAL);

		// add them to the list
		m_ProgressList.Add(pControl);
	}

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

}

void CListCtrlEx::UpdateStatusDownload(int iIndex, LPCTSTR strStatus)
{
	SetItemText(iIndex, 2, strStatus);
}