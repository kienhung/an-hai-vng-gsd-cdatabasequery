
// ServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "ConnectSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerDlg dialog




CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_uiPort = 11250;
	m_sListener = INVALID_SOCKET;
	m_hListenThread = NULL;
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CServerDlg message handlers

BOOL CServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	InitListener();
	m_strRootFolder = _T("D:\\Public");
	return TRUE; 
}


void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CServerDlg::InitListener() {

	m_sListener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_sListener) {
		AfxMessageBox(_T("Unable to create socket"));
		return FALSE;
	}

	SOCKADDR_IN serverAddress;

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(m_uiPort);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	if (SOCKET_ERROR == bind(m_sListener, (SOCKADDR*)&serverAddress, sizeof(serverAddress))) {
		AfxMessageBox(_T("Unable to bind"));
		return FALSE;
	}

	if (SOCKET_ERROR == listen(m_sListener, 5)) {
		AfxMessageBox(_T("Unable to listen"));
		return FALSE;
	}

	DWORD dwThreadID = 0;
	m_hListenThread = ::CreateThread(NULL, 0, SocketListeningThreadFunction, this, NULL, &dwThreadID);

	if (0 == m_hListenThread) {
		AfxMessageBox(_T("Unable to listen imcoming connection"), MB_ICONSTOP);
	} 
	return TRUE;
}
void CServerDlg::OnDestroy()
{
	CDialog::OnDestroy();

	if (m_sListener != INVALID_SOCKET) {
		closesocket(m_sListener);
		m_sListener = INVALID_SOCKET;
	}

	if (m_hListenThread != NULL) {
		CloseHandle(m_hListenThread);
	}
}

DWORD WINAPI CServerDlg::SocketListeningThreadFunction(LPVOID lpParam ) {

	::OutputDebugStringA("Nhay vao thread listen\n");
	CServerDlg *pServerDlg = (CServerDlg *)lpParam;

	while (pServerDlg->m_sListener != INVALID_SOCKET) {

		::OutputDebugStringA("cho ket noi\n");
		SOCKET sConnectSocket = INVALID_SOCKET;
		sConnectSocket = accept(pServerDlg->m_sListener, NULL, NULL);
		

		if (INVALID_SOCKET != sConnectSocket) {
			
			::OutputDebugStringA("co mot ket noi\n");

			CConnectSocket *pConnectSocket = new CConnectSocket(sConnectSocket, pServerDlg);
			::OutputDebugStringA("Tao thread\n");
			HANDLE hThread = CreateThread(NULL, 0,  FolderDownloadingThreadFunction, pConnectSocket, CREATE_SUSPENDED, NULL);

			if (NULL != hThread) {

				pConnectSocket->SetThreadHandle(hThread);
				::OutputDebugStringA("cap nhat du lieu cho thread\n");
				ResumeThread(hThread);

			} else {
				delete pConnectSocket;
			}
		}
	}
	::OutputDebugStringA("thoat ra thread listen\n");
	return 0;
}

DWORD WINAPI CServerDlg::FolderDownloadingThreadFunction(LPVOID lpParam ) {

	::OutputDebugStringA("nhay vao thread download\n");

	CConnectSocket *pConnectSocket = (CConnectSocket *)lpParam;
	CServerDlg *pServerDlg = pConnectSocket->GetDlg();

	int iMessageType;
	int uiLength;

	::OutputDebugStringA("cho nhan header\n");
	if (pConnectSocket->GetMessageHeader(&iMessageType, &uiLength) == FALSE) {
		return pConnectSocket->Destroy();
	}

	::OutputDebugStringA("da nhan duoc header header\n");
	switch (iMessageType) {
		case FILE_LIST_REQUEST:

			::OutputDebugStringA("process file list resuqest\n");
			pServerDlg ->ProcessFileListRequest(pConnectSocket, uiLength);
			break;

		case DOWNLOAD_FILE:
			::OutputDebugStringA("download file\n");
			break;
	}

	::OutputDebugStringA("thoat thread download\n");

	
	return pConnectSocket->Destroy();
}



int CServerDlg::ProcessFileListRequest( CConnectSocket* pConnectSocket, int uiLength )
{

	::OutputDebugStringA("nha vao ProcessFileListRequest \n");
	const TCHAR * strFolderName = pConnectSocket->RecevieFolderName(uiLength);
	if (strFolderName != NULL) {
		::OutputDebugString(strFolderName);
		::OutputDebugStringA("\n");
	}

	//MESSAGE_HEADER messageHeader;
	
	return 1;
}

