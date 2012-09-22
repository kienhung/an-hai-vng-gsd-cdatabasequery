#include "StdAfx.h"
#include "Listener.h"
#include "Token.h"
#include "CSMServerSimulator.h"

#define LISTEN_PORT				2345//0xCAF3
#define	MAX_CONN				1000		//allow maximum of 1000 workstations

CListener::CListener(void)
{
	m_ListenSock = INVALID_SOCKET;
}

CListener::~CListener(void)
{
}

BOOL CListener::Initialize()
{
	WSADATA		wsaData = {0};
	SOCKADDR_IN	ServerAddr = {0};

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return FALSE;
	}

	m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_ListenSock == INVALID_SOCKET)
	{
		WSACleanup();
		return FALSE;
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(LISTEN_PORT);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(m_ListenSock, (LPSOCKADDR)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		closesocket(m_ListenSock);
		WSACleanup();
		return FALSE;
	}

	if (listen(m_ListenSock, MAX_CONN) == SOCKET_ERROR)
	{
		closesocket(m_ListenSock);
		WSACleanup();
		return FALSE;
	}

	return TRUE;
}

void CListener::CleanUp()
{	
	if (m_ListenSock != INVALID_SOCKET)
	{
		shutdown(m_ListenSock, SD_BOTH);
		closesocket(m_ListenSock);
		m_ListenSock = INVALID_SOCKET;
	}

	WSACleanup();
}

void CListener::CloseClientConn(LPCLIENT_INFO pClientInfo)
{
	CloseConnection(pClientInfo->ConnSock);
}

void CListener::CloseConnection(SOCKET sock)
{
	shutdown(sock, SD_BOTH);
	closesocket(sock);
}

BOOL CListener::SendData(SOCKET sock, const char *pDataBuf, int iDataLen, int flags, int *piError)
{
	int	iRet, 
		iTotal = 0,
		iRetryCount = 0;

	while (iTotal < iDataLen)
	{
		iRet = send(sock, pDataBuf + iTotal, iDataLen - iTotal, flags);

		if (iRet == 0 || iRet == SOCKET_ERROR)
		{
			int	iError = WSAGetLastError();
			if (iError == WSAEWOULDBLOCK)
			{
				// retry to send
				if (iRetryCount < 5)
				{
					iRetryCount++;
					Sleep(10);
					continue;
				}
			}

			return FALSE;
		}

		iTotal	+= iRet;
		iRetryCount = 0;
	}

	return TRUE;
}

BOOL CListener::RecvData(SOCKET sock, char *pDataBuf, int iDataLen, int flags, int *piError)
{
	int	iRet,
		iTotal = 0,
		iRetryCount = 0;

	while (iTotal < iDataLen)
	{
		iRet = recv(sock, pDataBuf + iTotal, iDataLen - iTotal, flags);

		if (iRet == 0 || iRet == SOCKET_ERROR)
		{
			int	iError = WSAGetLastError();
			if (iError == WSAEWOULDBLOCK)
			{
				// It is a nonfatal error, and the operation should be retried later.
				if (iRetryCount < 5)
				{
					iRetryCount++;
					Sleep(10);
					continue;
				}
				else
				{
					if (piError)
						*piError = iError;
				}
			}
			else if (iError == WSAENOTSOCK || iError == WSAECONNABORTED)
			{
				// Connection have just closed, clear error code
				if (piError)
					*piError = 0;
			}
			else
			{
				if (piError)
					*piError = iError;
			}

			return FALSE;
		}

		iTotal	+= iRet;
		iRetryCount = 0;
	}

	return TRUE;
}

BOOL CListener::RecvHeader(SOCKET sock, char *pDataBuf, int iDataLen, int flags, int *piError)
{
	int	iRet,
		iTotal = 0,
		iRetryCount = 0;

	while (iTotal < iDataLen)
	{
		iRet = recv(sock, pDataBuf + iTotal, iDataLen - iTotal, flags);

		if (iRet <= 0)
		{
			int	iError = WSAGetLastError();
			if (iError == WSAEWOULDBLOCK)
			{
				// It is a nonfatal error, and the operation should be retried later.
				if (iTotal > 0)	// received some data, but now temporarily unavailable -> retry to receive
				{
					if (iRetryCount < 5)
					{
						iRetryCount++;
						Sleep(10);
						continue;
					}
					else
					{
						if (piError)
							*piError = iError;
					}
				}
				else	// have no message, only is a remnants signal -> it isn't error
				{
					if (piError)
						*piError = 0;
				}
			}
			else if (iError == WSAENOTSOCK || iError == WSAECONNABORTED)
			{
				// Connection have just closed, clear error code
				if (piError)
					*piError = 0;
			}
			else
			{
				if (piError)
					*piError = iError;
			}

			return FALSE;
		}

		iTotal += iRet;
		iRetryCount = 0;	// clear this variable
	}

	return TRUE;
}

LPCLIENT_INFO CListener::GetClientInfo(SOCKET sock)
{
	LPCLIENT_INFO	pClientInfo = NULL;
	int	iCount;

	LockCI();
	iCount = m_arrClientInfo.GetCount();
	for (int i = 0; i < iCount; i++)
	{
		if (m_arrClientInfo[i]->ConnSock == sock)
		{
			pClientInfo = m_arrClientInfo[i];
			break;
		}
	}
	UnlockCI();

	return pClientInfo;
}

/****************************************************************************
* Description: check existence or add a client to the connection list (m_arrClientInfo)
* Input:	SOCKET sock:			connected socket
*			LPCTSTR strIP:			client IP address
*			LPCTSTR strHostName:	client host name
*			LPCTSTR strVersion:		client version
*			LPCTSTR strReleaseDate: client release date
* Output:	None
* Return:	LPCLIENT_INFO: pointer to the structure (in m_arrClientInfo) which stores info of the client
* Revision History:
*		08/01/09	Author: DiepTH 
*****************************************************************************/
LPCLIENT_INFO CListener::AddNewClient(SOCKET sock, LPCTSTR strIP, LPCTSTR strHostName, LPCTSTR strVersion, LPCTSTR strReleaseDate)
{
	LPCLIENT_INFO	pClientInfo = NULL;
	int	iCount;

	// check existence of client IP and Name in the connection list
	LockCI();
	iCount = m_arrClientInfo.GetCount();
	for (int i = 0; i < iCount; i++)
	{
		if (m_arrClientInfo[i]->IP.Compare(strIP) == 0)
		{
			if (m_arrClientInfo[i]->Status == AVAILABLE || m_arrClientInfo[i]->Status == ONLINE)
			{
				// It has already existed a connection with this IP 
				// in the connection list and it is active.
				UnlockCI();
				CloseConnection(sock);
				return NULL;
			}
		}

		if (m_arrClientInfo[i]->HostName.CompareNoCase(strHostName) == 0)
		{
			if (m_arrClientInfo[i]->Status == AVAILABLE || m_arrClientInfo[i]->Status == ONLINE)
			{
				// It has already existed a connection with this name (sure from other IP) 
				// in the connection list and it is active.
				UnlockCI();
				CloseConnection(sock);
				return NULL;
			}
			else
			{
				// This client has already existed but it was disconnected. Now re-connect
				pClientInfo = m_arrClientInfo[i];
				break;
			}
		}
	}

	if (pClientInfo == NULL)	// this connection from new client.
	{
//temp
#if 0
		if (m_iClientCount >= g_iMaxClient || m_iClientCount >= MAX_CONN)
		{
			UnlockCI();
#ifdef WRITE_LOG
			g_LogWriter.WriteLogFormat(LOG_TYPE_WARN, _T("Add New Client: Number of connections has reached threshold. So it refuses the connection from %s."), strIP);
#endif			
			CloseConnectionEx(sock);
			return NULL;
		}
#endif

		// Add a new element to the connection list
		pClientInfo = new CLIENT_INFO;
		if (!pClientInfo)
		{
			UnlockCI();
			CloseConnection(sock);
			return NULL;
		}
		m_arrClientInfo.Add(pClientInfo);
	}
	UnlockCI();

	pClientInfo->ConnSock = sock;
	pClientInfo->IP = strIP;
	pClientInfo->HostName = strHostName;
	pClientInfo->Version = strVersion;
	pClientInfo->ReleaseDate = strReleaseDate;

	return pClientInfo;
}

void CListener::ProcessRead(SOCKET sock)
{
	MSG_HEADER	hdr;
	int			iError = 0;

	if (!RecvHeader(sock, (char*)&hdr, sizeof (MSG_HEADER), 0, &iError))
	{
		if (iError)
		{
			// check existence of the connection and close	
			CloseConnection(sock);
		}
		else	// nonfatal error -> don't close connection
		{
		}
		return;
	}
	else
	{
		hdr.ConvertNTOH();
	}

	if (hdr.Command < VCM_MIN || hdr.Command > VCM_MAX)
	{
		// invalid command
		// check existence of the connection and close
		CloseConnection(sock);
		return;
	}

	if (hdr.DataLen < 0)
	{
		// check existence of the connection and close
		CloseConnection(sock);
		return;
	}

#ifdef UNICODE
	if (hdr.DataLen % 2 != 0)
	{
		// invalid data (because data is a widechar string, number of bytes must be even)		
		// check existence of the connection and close
		CloseConnection(sock);
	}
#endif

	if (hdr.DataLen > 0)
	{
		int		iNumTChar = hdr.DataLen/sizeof(TCHAR);
		TCHAR	*pData;

		pData = new TCHAR[iNumTChar + 1];
		if (!pData)
		{
			CloseConnection(sock);
			return;
		}

		if (!RecvData(sock, (char*)pData, hdr.DataLen, 0, &iError))
		{
			delete []pData;
			if (iError)
			{
				// check existence of the connection and close
				CloseConnection(sock);
			}
			return;
		}

		pData[iNumTChar] = 0;
		ProcessCmd(hdr, pData, sock);
		delete []pData;
	}
	else
	{
		ProcessCmd(hdr, _T(""), sock);
	}
}

void CListener::ProcessCmd(MSG_HEADER &hdr, LPCTSTR lpData, SOCKET sock)
{
	LPCLIENT_INFO pClientInfo = NULL;

	pClientInfo = GetClientInfo(sock);

	if (hdr.Command == VCM_CLIENTINFO)
	{
		if (pClientInfo != NULL)
		{
			// info from client has existed
			return;
		}

		OnMsgClientInfo(lpData, sock);
	}
	else
	{
		if (pClientInfo == NULL)
		{
			// info from client have not existed yet
			CloseConnection(sock);
			return;
		}

		switch(hdr.Command)
		{
			case VCM_AVAILABLE:
				{
					//OnMsgAvailable(lpData, pClientInfo);
					break;
				}

			case VCM_ONLINE:
				{
					//OnMsgOnline(lpData, pClientInfo);
					break;
				}

			case VCM_LOGIN:
				{
					//OnMsgLogin(lpData, pClientInfo);
					break;
				}
			case VCM_WEB_HISTORY:
				{

					SendMessage(theApp.m_pMainWnd->m_hWnd, VCM_WEB_HISTORY, 0,(LPARAM)lpData);
					break;
				}
			default:
				break;
		}
	}
}

BOOL CListener::Start(HWND hWnd)
{
	if (!Initialize())
	{
		return FALSE;
	}

	if (WSAAsyncSelect(m_ListenSock, hWnd, WM_SOCKET, FD_ACCEPT|FD_READ|FD_CLOSE) == SOCKET_ERROR)
	{
		CleanUp();
		return FALSE;
	}

	// Start some others here

	return TRUE;
}

void CListener::Stop()
{
	// Stop some others here
	
	CleanUp();
}

void CListener::ProcessSocketMsg(WPARAM wParam, LPARAM lParam)
{

	if (WSAGETSELECTERROR(lParam))
	{
		// Display the error and close the socket
		CloseConnection(wParam);
		return;
	}

	switch(WSAGETSELECTEVENT(lParam))
	{
		case FD_ACCEPT:
			{
				SOCKADDR_IN ClientAddr = {0};
				int	iLen = sizeof(ClientAddr);
				accept(wParam, (LPSOCKADDR)&ClientAddr, &iLen);
				break;
			}
		case FD_READ:
			{
				// Receive data from the socket in
				// wParam
				ProcessRead(wParam);
				break;
			}

		case FD_WRITE:
			{
				// The socket in wParam is ready
				// for sending data
				break;
			}

		case FD_CLOSE:
			{
				// The connection is now closed	
				CloseConnection(wParam);
				break;
			}
	}
}

BOOL CListener::SendMsgToClient(LPCLIENT_INFO pClientInfo, int iMsgType, int iMsgParam, int iMsgRsvd)
{
	MSG_HEADER	hdr(iMsgType, iMsgParam, iMsgRsvd);
	BOOL		bRet;

	pClientInfo->SyncConn.Lock();
	bRet = SendData(pClientInfo->ConnSock, (char*)&hdr, sizeof(hdr), 0);
	pClientInfo->SyncConn.Unlock();

	if (!bRet)
		CloseClientConn(pClientInfo);

	return bRet;
}

BOOL CListener::SendMsgToClient(LPCLIENT_INFO pClientInfo, int iMsgType, int iMsgParam, LPCTSTR lpData, int iMsgRsvd)
{
	EX_MSG	msg(iMsgType, iMsgParam, lpData, iMsgRsvd);

	if (msg.Content)
	{
		BOOL	bRet;

		pClientInfo->SyncConn.Lock();
		bRet = SendData(pClientInfo->ConnSock, msg.Content, msg.ContentLen, 0);
		pClientInfo->SyncConn.Unlock();

		if (!bRet)
			CloseClientConn(pClientInfo);

		return bRet;	
	}

	return FALSE;
}

/****************************************************************************
* Description: Process the VCM_CLIENTINFO message from a client.
* Input:	LPCTSTR lpData:	The data string from client.
*			SOCKET sock:	client connected socket.
* Output:	None.
* Return:	None.
* Revision History:
*		08/03/09	Author: DiepTH
*****************************************************************************/
void CListener::OnMsgClientInfo(LPCTSTR lpData, SOCKET sock)
{
	SOCKADDR_IN	ClientAddr = {0};
	int			iNameLen;
	CToken		token(lpData);
	CString		strIP,
				strHostName,
				strVersion,
				strReleaseDate;
	BOOL		bExistIP = FALSE;
	DWORD		dwThreadId;
	LPCLIENT_INFO pClientInfo;

	iNameLen = sizeof(ClientAddr);
	if (getpeername(sock, (LPSOCKADDR)&ClientAddr, &iNameLen) == SOCKET_ERROR)
	{
		CloseConnection(sock);
		return;
	}

	strIP.Format(_T("%d.%d.%d.%d"),
					ClientAddr.sin_addr.S_un.S_un_b.s_b1,
					ClientAddr.sin_addr.S_un.S_un_b.s_b2,
					ClientAddr.sin_addr.S_un.S_un_b.s_b3,
					ClientAddr.sin_addr.S_un.S_un_b.s_b4);

	// parse the received data
	// lpData: <Host_Name>;<Client_Version>;<Release_Date>;
	token.SetToken(_T(";"));
	strHostName	= token.GetNextToken();
	strHostName.MakeUpper();
	strVersion = token.GetNextToken();
	strReleaseDate = token.GetNextToken();

	// check existence or add a client (IP and Name) in the connection list
	pClientInfo = AddNewClient(sock, strIP, strHostName, strVersion, strReleaseDate);
	if (!pClientInfo)
		return;

}
