
// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "ConnectSocket.h"
#include "Messages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CClientDlg dialog




CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD, &CClientDlg::OnBnClickedBtnDownload)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_edtFolderName = (CEdit*)GetDlgItem(IDC_EDIT_FOLDER_NAME);

	m_uiPort = 11250;
	m_ServerIpAddress = "127.0.0.1";
	m_SavingPath = _T("D:\\Downloads");
	m_edtFolderName->SetWindowText(_T("Demo"));

	return TRUE;
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CClientDlg::OnPaint()
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

HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CClientDlg::OnBnClickedBtnDownload()
{

	SOCKET sClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (INVALID_SOCKET == sClientSocket) {
		throw _T("Unable to create socket");
	}

	SOCKADDR_IN serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(m_uiPort);
	serverAddress.sin_addr.s_addr = inet_addr(m_ServerIpAddress.GetBuffer());

	if (0 != connect(sClientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress))) {
		throw _T("Unable to connect server");
	}

	CConnectSocket *pConnectSocket = new CConnectSocket(sClientSocket, this);
	HANDLE hThread = CreateThread(NULL, 0,  FolderDownloadingThreadFunction, pConnectSocket, CREATE_SUSPENDED, NULL);

	if (NULL != hThread) {

		pConnectSocket->SetThreadHandle(hThread);
		m_lstConnectSockets.push_back(pConnectSocket);
		ResumeThread(hThread);

	} else {
		delete pConnectSocket;
		closesocket(sClientSocket);
	}
}

void CClientDlg::OnDestroy()
{
	CDialog::OnDestroy();

	list<CConnectSocket*>::iterator it;
	for (it = m_lstConnectSockets.begin(); it != m_lstConnectSockets.end(); ++it) {
		delete *it;
	}
	m_lstConnectSockets.clear();
}

void CClientDlg::DestroySocket(CConnectSocket* pConnectSocket) {
	delete pConnectSocket;
	m_lstConnectSockets.remove(pConnectSocket);
}

DWORD WINAPI CClientDlg::FolderDownloadingThreadFunction(LPVOID lpParam ) {

	::OutputDebugStringA("Client: bat dau download thread\n");

	CString strFolderName;

	CConnectSocket *pConnectSocket = (CConnectSocket *)lpParam;
	CClientDlg *pClientDlg = pConnectSocket->GetDlg();

	pClientDlg->m_edtFolderName->GetWindowText(strFolderName);
	pConnectSocket->SendFolderName(strFolderName.GetBuffer());
	
	::OutputDebugStringA("Client: exit download thread\n");

	return 0;
}