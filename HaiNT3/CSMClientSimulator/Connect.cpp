#include "StdAfx.h"
#include "Connect.h"
#include "CSMClientSimulator.h"

#define MONITOR_TIME_ELAPSE	3000
#define SERVER_PORT			2345//0xCAF3

CConnect::CConnect(void)
{
	m_ConnSock = INVALID_SOCKET;
	m_hConnThread = NULL;
	m_dwConnThreadId = 0;
	m_uiTimerMonitorId = 0;
	m_hControlEvent = NULL;
	m_bThreadStart = FALSE;
	m_bConnect = FALSE;
}

CConnect::~CConnect(void)
{
}

BOOL CConnect::Start(HWND hWnd)
{
	WSADATA		wsaData = {0};

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return FALSE;
	}

	m_hControlEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (!m_hControlEvent)
	{
		WSACleanup();
		return FALSE;
	}

	m_hWnd = hWnd;

	m_hConnThread = CreateThread(NULL, 0, ConnectThreadProc, this, 0, &m_dwConnThreadId);
	if (m_hConnThread == NULL)
	{
		WSACleanup();
		CloseHandle(m_hControlEvent);
		return FALSE;
	}

	WaitForSingleObject(m_hControlEvent, INFINITE);

	if (!m_bThreadStart)
	{
		WSACleanup();
		CloseHandle(m_hControlEvent);
		return FALSE;
	}

	return TRUE;
}

void CConnect::Stop()
{

	DWORD ExitCode;
	if (m_hConnThread)
	{
		PostThreadMessage(m_dwConnThreadId, WM_QUIT, 0, 0);

		if (WaitForSingleObject(m_hConnThread, 5*1000) != WAIT_OBJECT_0)
		{
			if (!GetExitCodeThread(m_hConnThread, &ExitCode) || ExitCode == STILL_ACTIVE)
				TerminateThread(m_hConnThread, -1);
		}
		CloseHandle(m_hConnThread);
		m_hConnThread = NULL;
	}
	
	CloseConnection();
	WSACleanup();
	CloseHandle(m_hControlEvent);
}

void CConnect::ProcessSocketMsg(LPARAM lParam)
{

	if (WSAGETSELECTERROR(lParam))
	{
		// Display the error and close the socket
		CloseConnection();
		return;
	}

	switch(WSAGETSELECTEVENT(lParam))
	{
		case FD_READ:
			{
				// Receive data from the socket in
				// wParam
				ProcessRead();
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
				CloseConnection();
				break;
			}
	}
}

void CConnect::ProcessRead()
{
	MSG_HEADER	hdr;
	int			iError = 0;

	if (!RecvHeader((char*)&hdr, sizeof (MSG_HEADER), 0, &iError))
	{
		if (iError)
		{
			CloseConnection();
		}
		else
		{
		}
		return;
	}
	else
	{
		hdr.ConvertNTOH();
	}

	if (hdr.Command < VSM_MIN || hdr.Command > VSM_MAX)
	{
		// invalid command
		CloseConnection();
		return;
	}

	if (hdr.DataLen < 0)
	{
		CloseConnection();
		return;
	}

#ifdef UNICODE
	if (hdr.DataLen % 2 != 0)
	{
		// invalid data (because data is a widechar string, number of bytes must be even)		
		CloseConnection();
	}
#endif

	if (hdr.DataLen > 0)
	{
		int		iNumTChar = hdr.DataLen/sizeof(TCHAR);
		TCHAR	*pData;

		pData = new TCHAR[iNumTChar + 1];
		if (!pData)
		{
			CloseConnection();
			return;
		}

		if (!RecvData((char*)pData, hdr.DataLen, 0, &iError))
		{
			delete []pData;
			if (iError)
			{
				CloseConnection();
			}
			return;
		}

		pData[iNumTChar] = 0;

		ProcessCmd(hdr, pData);
		delete []pData;
	}
	else
	{
		ProcessCmd(hdr, _T(""));
	}
}

void CConnect::ProcessCmd(MSG_HEADER &hdr, LPCTSTR lpData)
{
	switch(hdr.Command)
	{
		case VSM_LOGIN_OK:	
			{
				break;
			}

		case VSM_LOGIN_FAILED:
			{
				break;
			}

		case VSM_LOGOUT:
			{
				break;
			}
	
		default:
			break;
	}
}

BOOL CConnect::SendData(const char *pDataBuf, int iDataLen, int flags, int *piError)
{
	int	iRet, 
		iOffset = 0,
		iTotal = iDataLen,
		iRetryCount = 0;

	while (iTotal > 0)
	{
		iRet = send(m_ConnSock, pDataBuf + iOffset, iTotal, flags);

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

		iOffset += iRet;
		iTotal	-= iRet;
		iRetryCount = 0;
	}

	return TRUE;
}

BOOL CConnect::RecvData(char *pDataBuf, int iDataLen, int flags, int *piError)
{
	int	iRet,
		iTotal = 0,
		iRetryCount = 0;

	while (iTotal < iDataLen)
	{
		iRet = recv(m_ConnSock, pDataBuf + iTotal, iDataLen - iTotal, flags);

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

BOOL CConnect::RecvHeader(char *pDataBuf, int iDataLen, int flags, int *piError)
{
	int	iRet,
		iTotal = 0,
		iRetryCount = 0;

	while (iTotal < iDataLen)
	{
		iRet = recv(m_ConnSock, pDataBuf + iTotal, iDataLen - iTotal, flags);

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

BOOL CConnect::CreateConnection()
{
	if (m_ConnSock == INVALID_SOCKET)
	{
		m_ConnSock = socket(AF_INET, SOCK_STREAM, 0);
		if (m_ConnSock == INVALID_SOCKET)
		{
			return FALSE;
		}
	}

	SOCKADDR_IN	ServerAddr = {0};
	ULONG		ulServerIP = inet_addr(g_strServerIP);

	if (ulServerIP == INADDR_NONE || ulServerIP == INADDR_ANY)
	{
		return FALSE;
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(SERVER_PORT);
	ServerAddr.sin_addr.s_addr = ulServerIP;

	if (connect(m_ConnSock, (sockaddr*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		return FALSE;
	}

	if (WSAAsyncSelect(m_ConnSock, m_hWnd, WM_SOCKET, FD_CONNECT|FD_WRITE|FD_READ|FD_CLOSE) == SOCKET_ERROR)
	{
		shutdown(m_ConnSock, SD_BOTH);
		closesocket(m_ConnSock);
		m_ConnSock = INVALID_SOCKET;
		return FALSE;
	}
	m_bConnect = TRUE;
	return TRUE;	
}

void CConnect::MonitorConnection()
{
	if (m_bConnect)
	{
		SendMsgToServer(VCM_PING);
	}

	if (!m_bConnect)
	{
		CreateConnection();

		if (!m_bConnect)
			return;

		if (!SendMsgCLIENTINFO())
			return;

//temp
#if 0

		if (!SendMsgSENDTIME())
			return;
		else
		{
			// Send to Underground clear TimeUsed
			g_UDPClient.SendMsgTo(UCM_WRITE_REG_TIMEUSED, 0);
		}

		if (m_bOnline)	
		{
			// Client is ONLINE
			SendMsgONLINE();
		}
		else
		{	
			// Client is WAITING
			SendMsgAVAILABLE();
		}
#endif
	}
}

void CConnect::CloseConnection()
{
	shutdown(m_ConnSock, SD_BOTH);
	closesocket(m_ConnSock);
	m_ConnSock = INVALID_SOCKET;
	m_bConnect = FALSE;
}

DWORD WINAPI CConnect::ConnectThreadProc(LPVOID lpPara)
{
	CConnect	*p = (CConnect*)lpPara;

	p->m_uiTimerMonitorId = SetTimer(NULL, 0, MONITOR_TIME_ELAPSE, NULL);
	if (p->m_uiTimerMonitorId == 0)
	{
		SetEvent(p->m_hControlEvent);
		return -1;
	}

	MSG msg;

	// Call PeekMessage for creating Thread's message queue
	// Before call PostThreadMessage function
	PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);

	p->m_bThreadStart = TRUE;
	SetEvent(p->m_hControlEvent);

	// run first time
	p->MonitorConnection();

	while (GetMessage(&msg, NULL, 0, 0))
	{
		switch(msg.message)	
		{
		case WM_TIMER:
			{
				if (msg.wParam == p->m_uiTimerMonitorId)
				{
					p->MonitorConnection();
				}
				break;
			}

		default:
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	KillTimer(NULL, p->m_uiTimerMonitorId);

	return 1;
}

BOOL CConnect::SendMsgToServer(int iMsgType, int iMsgParam, int iMsgRsvd)
{
	MSG_HEADER	hdr(iMsgType, iMsgParam, iMsgRsvd)	;
	BOOL		bRet;

	m_SyncConn.Lock();	// lock socket: multi-thread call send
	bRet = SendData((char*)&hdr, sizeof(hdr), 0);
	m_SyncConn.Unlock();

	if (!bRet)
	{
		CloseConnection();
		return FALSE;
	}

	return TRUE;
}

BOOL CConnect::SendMsgToServer(int iMsgType, int iMsgParam, LPCTSTR lpData, int iMsgRsvd)
{
	MSG_HEADER	hdr;
	char		*pBuf;
	int			iHeaderLen,
				iDataLen,
				iBufLen;
	BOOL		bRet;

	iHeaderLen = sizeof(MSG_HEADER);
	iDataLen = _tcslen(lpData)* sizeof(TCHAR);
	iBufLen = iHeaderLen + iDataLen;

	hdr.Command = iMsgType;
	hdr.Param = iMsgParam;
	hdr.Reserved = iMsgRsvd;
	hdr.DataLen = iDataLen;
	hdr.ConvertHTON();

	pBuf = new char[iBufLen];
	if (!pBuf)
	{
		CloseConnection();
		return FALSE;
	}

	memcpy(pBuf, &hdr, iHeaderLen);
	memcpy(pBuf + iHeaderLen, lpData, iDataLen);

	m_SyncConn.Lock();	// lock socket: multi-thread call send
	bRet = SendData(pBuf, iBufLen, 0);
	m_SyncConn.Unlock();
	
	if (!bRet)
	{
		delete []pBuf;
		CloseConnection();
		return FALSE;
	}

	delete []pBuf;
	return TRUE;
}

BOOL CConnect::SendMsgCLIENTINFO()
{
	TCHAR			strComputerName[128] = {0};
	DWORD			dwSize;

	dwSize = _countof(strComputerName);
	if (!GetComputerName(strComputerName, &dwSize))
	{
		CloseConnection();
		return FALSE;
	}
	_tcsupr(strComputerName);

	CString		strData;	
	strData.Format(_T("%s;%s;%s"), strComputerName, g_strVersion, g_strReleaseDate);

	return SendMsgToServer(VCM_CLIENTINFO, 0, strData);
}
