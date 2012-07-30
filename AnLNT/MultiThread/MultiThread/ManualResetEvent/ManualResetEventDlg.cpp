
// ManualResetEventDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManualResetEvent.h"
#include "ManualResetEventDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CManualResetEventDlg dialog




CManualResetEventDlg::CManualResetEventDlg(CWnd* pParent)
	: CDialog(CManualResetEventDlg::IDD, pParent), m_myEvent(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	ASSERT(m_hEvent);
}

BEGIN_MESSAGE_MAP(CManualResetEventDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CManualResetEventDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CManualResetEventDlg message handlers

BOOL CManualResetEventDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon





	return TRUE;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CManualResetEventDlg::OnPaint()
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
HCURSOR CManualResetEventDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI CManualResetEventDlg::UpdateListThreadFunction( PVOID pvParam )
{

	CManualResetEventDlg *pMainDlg = (CManualResetEventDlg*)pvParam;
	ASSERT(pMainDlg);


	HANDLE hHouseBuyingThread = ::CreateThread(NULL, 0, CManualResetEventDlg::HouseBuyingThreadFunction, pMainDlg, 0, NULL);
	ASSERT(hHouseBuyingThread);
	::CloseHandle(hHouseBuyingThread);

	HANDLE hCarBuyingThread = ::CreateThread(NULL, 0, CManualResetEventDlg::CarBuyingThreadFunction, pMainDlg, 0, NULL);
	ASSERT(hHouseBuyingThread);
	::CloseHandle(hCarBuyingThread);

	CString strText;

	for (int i = 0; i < 10; i++) {

		strText.Format(L"vay tien %d", i);
		pMainDlg->m_list->AddString(strText);
	}

	(pMainDlg->m_myEvent).SetEvent();
	return 0;
}

DWORD WINAPI CManualResetEventDlg::HouseBuyingThreadFunction( PVOID pvParam )
{

	CManualResetEventDlg *pMainDlg = (CManualResetEventDlg*)pvParam;
	ASSERT(pMainDlg);

	(pMainDlg->m_myEvent).Wait();

	CString strText;

	for (int i = 0; i < 10; i++) {
		strText.Format(L"Mua nha %d", i);
		pMainDlg->m_list->AddString(strText);
	}

	return 0;
}

DWORD WINAPI CManualResetEventDlg::CarBuyingThreadFunction( PVOID pvParam )
{

	CManualResetEventDlg *pMainDlg = (CManualResetEventDlg*)pvParam;
	ASSERT(*pMainDlg);


	(pMainDlg->m_myEvent).Wait();

	CString strText;

	for (int i = 0; i < 10; i++) {
		strText.Format(L"Mua xe %d", i);
		pMainDlg->m_list->AddString(strText);
	}

	return 0;
}


void CManualResetEventDlg::OnBnClickedButton1()
{

	m_list = (CListBox *) GetDlgItem(IDC_LIST);
	ASSERT(m_list);

	m_list->ResetContent();
	m_myEvent.ResetEvent();

	HANDLE hThread = ::CreateThread(NULL, 0, CManualResetEventDlg::UpdateListThreadFunction, this, 0, NULL);
	ASSERT(hThread);

	::CloseHandle(hThread);
}
