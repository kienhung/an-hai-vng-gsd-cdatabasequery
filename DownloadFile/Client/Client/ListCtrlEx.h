#pragma once


// CListCtrlEx
#define IDC_PROGRESS_LIST WM_USER

class CListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)

	// the array of the Progress Controls in the list control
	CArray<CProgressCtrl*,CProgressCtrl*> m_ProgressList;
	
	
	// the column which should contain the progress bars
	int m_iProgressColumn;
public:
	CListCtrlEx();
	virtual ~CListCtrlEx();
	// initialize the column containing the bars
	
	void CListCtrlEx::OnDestroy();
	void InitProgressColumn(int iColNum = 0);
	void InsertItemDownload(int iIndex, LPCTSTR strFileName, unsigned __int64 iFileSize, int iStatus);
	void UpdateStatusDownload(int iIndex, int iStatus);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};

