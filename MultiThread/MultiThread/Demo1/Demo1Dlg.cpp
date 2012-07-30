
// Demo1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo1.h"
#include "Demo1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#define INFO	TRACE("%s (%d): ", __FILE__, __LINE__);
// CDemo1Dlg dialog


CRITICAL_SECTION CriticalSection; 

CDemo1Dlg::CDemo1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemo1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}


CDemo1Dlg::~CDemo1Dlg()
{

}


BEGIN_MESSAGE_MAP(CDemo1Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

END_MESSAGE_MAP()


// CDemo1Dlg message handlers

BOOL CDemo1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);


	m_pList = (CListBox *) GetDlgItem(IDC_LIST);

	ASSERT(m_pList);

	//DWORD dwThreadID;

	HANDLE hThread = ::CreateThread(NULL, 0, CDemo1Dlg::UpdateListThreadFunction, this, 0, NULL);
	ASSERT(hThread);
	::CloseHandle(hThread);

	return TRUE; 
}



void CDemo1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemo1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI CDemo1Dlg::UpdateListThreadFunction( PVOID pvParam )
{

	CDemo1Dlg* pMainDlg = (CDemo1Dlg*)pvParam ;
	ASSERT(pMainDlg);

	const int NUM_THREADS = 3;
	HANDLE arrHThread[NUM_THREADS];

	arrHThread[0] = ::CreateThread(NULL, 0, CDemo1Dlg::SubUpdateListFunction, pMainDlg, 0, NULL);
	arrHThread[1] = ::CreateThread(NULL, 0, CDemo1Dlg::SubUpdateListFunction, pMainDlg, 0, NULL);
	arrHThread[2] = ::CreateThread(NULL, 0, CDemo1Dlg::SubUpdateListFunction, pMainDlg, 0, NULL);

	::WaitForMultipleObjects(NUM_THREADS, arrHThread, TRUE, INFINITE);
	pMainDlg->m_pList->AddString(L"Updating list is complete\n");

	return 0;
}

DWORD WINAPI CDemo1Dlg::SubUpdateListFunction( PVOID pvParam )
{

	CDemo1Dlg* pMainDlg = (CDemo1Dlg*)pvParam;
	pMainDlg->UpdateList();
	return 0;
}

void CDemo1Dlg::UpdateList()
{



	m_csUpdateList.Lock();

	CString strText;
	DWORD dwThreadID = ::GetCurrentThreadId();

	for (int i = 0; i < 10; i++) {
		strText.Format(L"SubUpdateListFunction %u - %d", dwThreadID, i);
		m_pList->AddString(strText);
	}
	m_csUpdateList.Unlock();


}

