
// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "ConnectSocket.h"
#include "Messages.h"
#include <strsafe.h>
#include "FileServices.h"
#include "DownloadFileSocket.h"
#include "DuyetFile.h"

#pragma comment (lib, "Crypto/lib/Cryptography.lib")
#include "Crypto/Decryption.h"

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
	//m_Mutex.SetMutexName(_T("UpdateStatusDownload"));
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_DOWNLOAD, m_lstDownload);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD, &CClientDlg::OnBnClickedBtnDownload)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_BROWSE, &CClientDlg::OnBnClickedBtnBrowse)
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
	m_uiPort = 11250;

	m_edtFolderName = (CEdit*)GetDlgItem(IDC_EDIT_FOLDER_NAME);
	m_edtPath = (CEdit*)GetDlgItem(IDC_EDT_PATH);
	
	
	
	CRect rect;
	m_lstDownload.GetClientRect(&rect);
	m_lstDownload.InitProgressColumn(2);
	m_lstDownload.InsertColumn(0,_T("Tên tập tin"), LVCFMT_LEFT, rect.Width()/3, 0);
	m_lstDownload.InsertColumn(1,_T("Kích thước"),LVCFMT_LEFT,rect.Width()/3, 1);
	m_lstDownload.InsertColumn(2,_T("Trạng thái"),LVCFMT_CENTER,rect.Width()/3, 2);
	m_lstDownload.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_UNDERLINECOLD);
	

	

	m_edtFolderName->SetWindowText(_T("Demo"));
	m_edtPath->SetWindowText(_T("D:\\Downloads\\Test"));

	CIPAddressCtrl *pIPAddressCtrlServerAddress = (CIPAddressCtrl*)this->GetDlgItem(IDC_IPADDRESS_SERVER);
	pIPAddressCtrlServerAddress->SetAddress(127, 0, 0, 1);
	
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

HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClientDlg::InsertItemDownload(int iIndex, LPCTSTR strFileName, unsigned __int64 iFileSize, int iStatus)
{
	m_lstDownload.InsertItemDownload(iIndex, strFileName, iFileSize, iStatus);
	
	//CMyCriticalSection cs;
	//m_vtcs.push_back(cs);
	TCHAR strIndex[20];
	StringCchPrintf(strIndex, 20, _T("Mutex%d"), iIndex);
	CMyMutex* myMutex = new CMyMutex(&strIndex[0]);
	
	m_vtMutex.push_back(myMutex);
}
void CClientDlg::OnBnClickedBtnDownload()
{

	try {

		SOCKET sClientSocket = CreateConnectSocket();
		
		CConnectSocket *pConnectSocket = new CConnectSocket(sClientSocket, this);
		HANDLE hThread = CreateThread(NULL, 0,  CClientDlg::FolderDownloadingThreadFunction, pConnectSocket, CREATE_SUSPENDED, NULL);
		

		if (NULL != hThread) {
			pConnectSocket->SetThreadHandle(hThread);
			ResumeThread(hThread);
		} else {
			delete pConnectSocket;
			closesocket(sClientSocket);
		}

	} catch (const TCHAR strMessage[]) {
		AfxMessageBox(strMessage, MB_ICONSTOP);
	}
	
}

void CClientDlg::OnDestroy()
{
	CDialog::OnDestroy();	
}

SOCKET CClientDlg::CreateConnectSocket() {

	SOCKET sClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == sClientSocket) {
		throw _T("Unable to create socket");
	}

	SOCKADDR_IN serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(m_uiPort);

	char strServerIPAddress[16];
	GetIPAddressString(strServerIPAddress, sizeof(strServerIPAddress));
	serverAddress.sin_addr.s_addr = inet_addr(strServerIPAddress);

	if (0 != connect(sClientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress))) {
		throw _T("Unable to connect server");
	}
	return sClientSocket;
}

DWORD WINAPI CClientDlg::FolderDownloadingThreadFunction(LPVOID lpParam ) {

	CConnectSocket *pConnectSocket = (CConnectSocket *)lpParam;
	CClientDlg *pClientDlg = pConnectSocket->GetDlg();


	CString cstrFolderName;
	pClientDlg->m_edtFolderName->GetWindowText(cstrFolderName);
	CString cstrSavingPath;
	pClientDlg->m_edtPath->GetWindowText(cstrSavingPath);


	TCHAR strFullSavingFolderPath[MAX_PATH];
	CFileServices fileServices;
	fileServices.CreateFullPath(strFullSavingFolderPath, MAX_PATH, cstrSavingPath.GetBuffer(), cstrFolderName.GetBuffer());

	if (FALSE == fileServices.CustomCreateDirectory(strFullSavingFolderPath)) {
		AfxMessageBox(_T("Try another folder to save"), MB_ICONSTOP);
		return pConnectSocket->Destroy();
	}

	if (pConnectSocket->SendFileName(cstrFolderName.GetBuffer(), FILE_LIST_REQUEST) == FALSE) {
		return pConnectSocket->Destroy();
	}

	TCHAR strDanhSachFilePath[MAX_PATH];

	StringCchPrintf(strDanhSachFilePath, MAX_PATH, _T("%s\\%s"), strFullSavingFolderPath,  _T("danhsach.ini"));
	BOOL bResult = pConnectSocket->ReceiveFile(strDanhSachFilePath);

	if (FALSE == bResult) {
		pConnectSocket->Destroy();
		return FALSE;
	}

	TCHAR strDecryptedDanhSachFilePath[MAX_PATH];
	StringCchPrintf(strDecryptedDanhSachFilePath, MAX_PATH, _T("%s\\%s"), strFullSavingFolderPath,  _T("DecryptedDanhSach.ini"));
	
	CDecryption decryption;
	if (decryption.ExecuteFile(strDanhSachFilePath, strDecryptedDanhSachFilePath) == false) {
		return pConnectSocket->Destroy();
	}

	CDuyetFile duyetFile;
	duyetFile.ApproveFolderToDownload(pClientDlg, cstrSavingPath.GetBuffer(), strDecryptedDanhSachFilePath);

	::DeleteFile( strDecryptedDanhSachFilePath);
	::DeleteFile(strDanhSachFilePath);
	return pConnectSocket->Destroy();
}


DWORD WINAPI CClientDlg::FileDownloadingThreadFunction(LPVOID lpParam ) {


	CDownloadFileSocket *pConnectSocket = (CDownloadFileSocket *)lpParam;
	CClientDlg *pClientDlg = pConnectSocket->GetDlg();
	
	if (FALSE == pConnectSocket->Request()) {
		return pConnectSocket->Destroy();
	}

	if (FALSE == pConnectSocket->Receive()) {
		return pConnectSocket->Destroy();
	}

	return pConnectSocket->Destroy();
}

BOOL CClientDlg::GetIPAddressString(char *pcBuffer, size_t stMaxLength) {

	if (stMaxLength < 16) {
		return false;
	}

	BYTE nField0;
	BYTE nField1;
	BYTE nField2;
	BYTE nField3;
	
	CIPAddressCtrl *pIPAddressCtrlServerAddress = (CIPAddressCtrl*)this->GetDlgItem(IDC_IPADDRESS_SERVER);
	int nNonBlankFieldsCount = pIPAddressCtrlServerAddress->GetAddress(nField0, nField1, nField2, nField3);
	if (nNonBlankFieldsCount < 4) {
		throw _T("Not to be allowed to leave any fields be blank");
	}
	sprintf_s(pcBuffer, stMaxLength, "%d.%d.%d.%d", nField0, nField1, nField2, nField3);
	return TRUE;
}
void CClientDlg::OnBnClickedBtnBrowse()
{
	BROWSEINFO browseInfo;
	ZeroMemory(&browseInfo, sizeof(BROWSEINFO));

	TCHAR strTitle[] = _T("Choosing a folder to save your file");
	browseInfo.lpszTitle = strTitle;

	LPITEMIDLIST pItemIDList = ::SHBrowseForFolder(&browseInfo);

	if (NULL != pItemIDList) {

		TCHAR strPATH[MAX_PATH] = {0};

		if (FALSE != ::SHGetPathFromIDList(pItemIDList, strPATH)) {

			m_edtPath->SetWindowText(strPATH);

		}

		::CoTaskMemFree(pItemIDList);
	}
}
int CClientDlg::GetCountItemDownload()
{
	return m_lstDownload.GetItemCount();
}
void CClientDlg::UpdateStateItemDownload(const int *iIndex,const int *iPosition)
{
	m_vtMutex[*iIndex]->Enter();
	m_lstDownload.UpdateStatusDownload(*iIndex, *iPosition);
	m_vtMutex[*iIndex]->Release();
	
	
}

CString CClientDlg::GetFolderDownload()
{
	CString strFolder;
	m_edtFolderName->GetWindowTextW(strFolder);
	return strFolder;
}