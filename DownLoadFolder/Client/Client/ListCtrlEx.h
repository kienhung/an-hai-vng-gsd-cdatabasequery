#pragma once
#include <vector>
using namespace std;

#if !defined(AFX_PROLISTCTRL_H__81C51345_D304_48FE_AE90_1A71500AB2E9__INCLUDED_)
#define AFX_PROLISTCTRL_H__81C51345_D304_48FE_AE90_1A71500AB2E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif
// CListCtrlEx
#define IDC_PROGRESS_LIST WM_USER

class CListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)

	// the array of the Progress Controls in the list control
	
	//vector<CProgressCtrl*> m_ProgressList;
	
	// the column which should contain the progress bars
	int m_iProgressColumn;
	vector<__int64> m_vtFileSize;
	vector<__int64> m_vtSumSizeDownload;
	
public:
	CListCtrlEx();
	virtual ~CListCtrlEx();
	// initialize the column containing the bars
	
	void InitProgressColumn(int iColNum = 0);
	void InsertItemDownload(int iIndex, LPCTSTR strFileName, unsigned __int64 iFileSize, int iStatus);
	void UpdateStatusDownload(int iIndex, int iStatus);
	void InsertProgresCtrl(int iIndex, int iAddStatus);
	void InvalidateProgressCtrls();
protected:
	
	
	afx_msg void OnCustomDraw( NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
public:
	
};



#endif