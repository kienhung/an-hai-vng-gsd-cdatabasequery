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
	void InitProgressColumn(int iColNum = 0);
	void InsertItemDownload(int iIndex, LPCTSTR strFileName, LPCTSTR strFileSize, LPCTSTR strStatus);
	void UpdateStatusDownload(int iIndex, LPCTSTR strStatus);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


