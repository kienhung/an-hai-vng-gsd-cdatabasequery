#pragma once

#define	WM_SOCKET				WM_USER + 1

// define command values
#define		SERVER_MESSAGE				0		// begin server message
#define		CLIENT_MESSAGE				50		// begin client message

#define		VSM_MIN						SERVER_MESSAGE + 1
#define		VSM_MAX						SERVER_MESSAGE + 2000
#define		VCM_MIN						CLIENT_MESSAGE + 1
#define		VCM_MAX						CLIENT_MESSAGE + 3000

// command from Server to Client
#define		VSM_LOGIN_OK				SERVER_MESSAGE + 7
#define		VSM_LOGIN_FAILED			SERVER_MESSAGE + 8	
#define		VSM_LOGOUT					SERVER_MESSAGE + 9

// command from Client to Server
#define		VCM_CLIENTINFO				CLIENT_MESSAGE + 1
#define		VCM_AVAILABLE				CLIENT_MESSAGE + 2
#define		VCM_ONLINE					CLIENT_MESSAGE + 3
#define		VCM_LOGIN					CLIENT_MESSAGE + 4
#define		VCM_PING					CLIENT_MESSAGE + 48
#define		VCM_WEB_HISTORY				CLIENT_MESSAGE + 49


#pragma pack( push, 1)
typedef struct tagMsgHeader
{
	int Command;
	int Param;
	int Reserved;
	int DataLen;

	tagMsgHeader()
	{
		Command = -1;
		Param = 0;
		Reserved = 0;
		DataLen = 0;
	}

	tagMsgHeader(int iCmd, int iParam = 0, int iRsvd = 0, int iDataLen = 0)
	{
		Command = iCmd;
		Param = iParam;
		Reserved = iRsvd;
		DataLen = iDataLen;

		ConvertHTON();
	}

	void ConvertNTOH()
	{
		Command = ntohl(Command);
		Param = ntohl(Param);
		Reserved = ntohl(Reserved);
		DataLen = ntohl(DataLen);
	}

	void ConvertHTON()
	{
		Command = htonl(Command);
		Param = htonl(Param);
		Reserved = htonl(Reserved);
		DataLen = htonl(DataLen);
	}
} MSG_HEADER;
#pragma pack(pop)

class CConnect
{
private:
	SOCKET	m_ConnSock;
	HANDLE	m_hConnThread;
	DWORD	m_dwConnThreadId;
	HANDLE	m_hControlEvent;
	HWND	m_hWnd;
	UINT	m_uiTimerMonitorId;
	BOOL	m_bThreadStart;
	BOOL	m_bConnect;
	CCriticalSection	m_SyncConn;

	static DWORD WINAPI ConnectThreadProc(LPVOID lpPara);

	BOOL SendData(const char *pDataBuf, int iDataLen, int flags = 0, int *piError = NULL);
	BOOL RecvData(char *pDataBuf, int iDataLen, int flags = 0, int *piError = NULL);
	BOOL RecvHeader(char *pDataBuf, int iDataLen, int flags, int *piError);

	BOOL CreateConnection();
	void MonitorConnection();
	void CloseConnection();

public:
	CConnect(void);
	~CConnect(void);

	BOOL Start(HWND hWnd);
	void Stop();

	void	ProcessSocketMsg(LPARAM lParam);
	void	ProcessRead();
	void	ProcessCmd(MSG_HEADER &hdr, LPCTSTR lpData);

	BOOL SendMsgToServer(int iMsgType, int iMsgParam = 0, int iMsgRsvd = 0);
	BOOL SendMsgToServer(int iMsgType, int iMsgParam, LPCTSTR lpData, int iMsgRsvd = 0);
	BOOL SendMsgCLIENTINFO();
	BOOL SendMsgAVAILABLE();
	BOOL SendMsgONLINE();
	BOOL SendMsgLOGIN(const CString &strUserName, const CString &strPassword);
	BOOL SendMsgSENDTIME();
};
