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

typedef struct tagExMsg
{
	char *Content;
	int	 ContentLen;

	tagExMsg()
	{
		Content = NULL;
		ContentLen = -1;
	}

	tagExMsg(int iCmd, int iParam, LPCTSTR lpData, int iRsvd = 0)
	{
		int		iHeaderLen,
			iDataLen;

		iHeaderLen = sizeof(MSG_HEADER);
		iDataLen = _tcslen(lpData) * sizeof(TCHAR);
		ContentLen = iHeaderLen + iDataLen;

		Content = new char[ContentLen];
		if (Content)
		{
			MSG_HEADER	hdr(iCmd, iParam, iRsvd, iDataLen);
			memcpy(Content, &hdr, iHeaderLen);
			memcpy(Content + iHeaderLen, lpData, iDataLen);
		}
	}
	~tagExMsg()
	{
		if (Content)
			delete []Content;
	}

} EX_MSG;

typedef struct tagClientInfo
{
	SOCKET		ConnSock;		// Connection socket
	CString		IP;				// Client IP Address
	CString		IPGateway;		// Client IP Gateway
	CString		HostName;		// Client Host Name
	CString		Version;		// Current Client Version
	CString		ReleaseDate;	// Release date
	BYTE		Status;			// AVAILABLE - ONLINE - DISCONNECT - WARNING		
#define INIT_INFO			0 
#define AVAILABLE			1 
#define DISCONNECT			2
#define ONLINE				3
#define WARNING				4
#define	ACTIVE				5	// AVAILABLE or ONLINE

	DWORD		FlagMask;		// Mask for set some flags
#define USER_UNDER18		0x00000001	// user under 18 years old
#define SERVICE_ORDER		0x00000002	// services are ordered (have not accepted)
#define SERVICE_ACCEPT		0x00000004	// services are accepted (have not payed out)
#define HAVE_NOT_PAID		0x00000008	// the machine has not paid yet
#define CLIENT_PAUSE		0x00000010	// the workstation pause 

	BYTE		DFStatus;		// Deepfreeze status
#define DF_NOT_EXIST				0
#define DF_STATUS_FROZEN			1
#define DF_STATUS_THAW				2
#define DF_WRONG_PASS				3
#define DF_AVAILABLE_UPDATE			4

	BYTE		DPStatus;		// Disk protection status
#define DP_UNPROTECT				0
#define DP_PROTECT					1
#define DP_AVAILABLE_UPDATE			2

	BOOL		Pause;			// Flag to check Client Pause or not
	ULONG		UserId;			// UserId in usertb table
#define INVALID_ID				(ULONG)(~0)	// Su dung gia tri nay de gan cho UserId khi may AVAILABLE
	// Ta khong the dung UserId=0 khi AVAILABLE, vi UserId=0 la cho TH ADMIN ONLINE
	ULONG		AnonymId;
	ULONG		SystemLogId;	// SystemLogId in systemlogtb	
	ULONG		UserGroupId;	// PriceId in pricelisttb
	int			UserGroupType;	// ANONYM, MEMBER, ADMIN, STAFF
	BOOL		PrePaid;		// ANONYM: prepaid or pay later 
	ULONG		MachineGroupId;

	DWORD		WrkThreadId;
	CCriticalSection	SyncConn;

	tagClientInfo()
	{
		ConnSock = INVALID_SOCKET;
		IP = _T("");
		IPGateway = _T("");
		HostName = _T("");
		Version = _T("");
		ReleaseDate = _T("");
		Status = INIT_INFO;
		FlagMask = 0;
		DFStatus = DF_NOT_EXIST;
		DPStatus = DP_UNPROTECT;
		Pause = FALSE;
		UserId = INVALID_ID;
		AnonymId = 0;
		SystemLogId = 0;
		UserGroupId = 0;
		UserGroupType = 0;	// NONE_GROUP
		PrePaid = FALSE;
		MachineGroupId = 0;
		WrkThreadId = 0;
	}
} CLIENT_INFO, *LPCLIENT_INFO;

typedef CArray<LPCLIENT_INFO>		CArrayClientInfo;

class CListener
{
private:
	SOCKET			m_ListenSock;
	CArrayClientInfo	m_arrClientInfo;
	CCriticalSection	m_SyncCI;

private:
	BOOL Initialize();
	void CleanUp();
	inline void LockCI(){m_SyncCI.Lock();}
	inline void UnlockCI(){m_SyncCI.Unlock();}
	void CloseClientConn(LPCLIENT_INFO pClientInfo);
	void CloseConnection(SOCKET sock);

	BOOL	SendData(SOCKET sock, const char *pDataBuf, int iDataLen, int flags = 0, int *piError = NULL);
	BOOL	RecvData(SOCKET sock, char *pDataBuf, int iDataLen, int flags = 0, int *piError = NULL);
	BOOL	RecvHeader(SOCKET sock, char *pDataBuf, int iDataLen, int flags, int *piError);

	void	ProcessRead(SOCKET sock);
	void	ProcessCmd(MSG_HEADER &hdr, LPCTSTR lpData, SOCKET sock);
	LPCLIENT_INFO	GetClientInfo(SOCKET sock);
	LPCLIENT_INFO	AddNewClient(SOCKET sock, LPCTSTR strIP, LPCTSTR strHostName, LPCTSTR strVersion, LPCTSTR strReleaseDate);

public:
	CListener(void);
	~CListener(void);

	BOOL	Start(HWND hWnd);
	void	Stop();

	void	ProcessSocketMsg(WPARAM wParam, LPARAM lParam);
	BOOL	SendMsgToClient(LPCLIENT_INFO pClientInfo, int iMsgType, int iMsgParam = 0, int iMsgRsvd = 0);
	BOOL	SendMsgToClient(LPCLIENT_INFO pClientInfo, int iMsgType, int iMsgParam, LPCTSTR lpData, int iMsgRsvd = 0);

	// Process commands
	void	OnMsgClientInfo(LPCTSTR lpData, SOCKET sock);
};
