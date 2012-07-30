
// Demo1Dlg.h : header file
//

#pragma once

#include "library/include/MyCriticalSection.h"
#pragma comment (lib, "library/lib/synchronization.lib")

// CDemo1Dlg dialog
class CDemo1Dlg : public CDialog
{

public:
	CDemo1Dlg(CWnd* pParent = NULL);	// standard constructor
	~CDemo1Dlg();

	enum { IDD = IDD_DEMO1_DIALOG };
	static DWORD WINAPI UpdateListThreadFunction(PVOID pvParam);
	static DWORD WINAPI SubUpdateListFunction(PVOID pvParam);
	void UpdateList();

protected:
	HICON m_hIcon;
	CListBox *m_pList;

	CMyCriticalSection m_csUpdateList;
protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
