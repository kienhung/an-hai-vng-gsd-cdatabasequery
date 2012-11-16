#pragma once

#define LOG_TYPE_FATAL			0x0
#define LOG_TYPE_ERROR			0x1
#define LOG_TYPE_WARN			0x2				
#define LOG_TYPE_FYI			0x3
#define LOG_TYPE_DEBUG			0x4	

#define	DEF_LOG_FILESIZE	200
#define	DEF_LIFETIME		30

typedef struct __tagLOG_CONFIG
{
	BOOL	bEnable;
	BOOL	bAutoClean;
	BYTE	byLogLevel;
	SHORT	nMaxSize;
	SHORT	nLifeTime;
	__tagLOG_CONFIG()
	{
		bEnable		= TRUE;
		bAutoClean	= FALSE;
		byLogLevel	= (BYTE)LOG_TYPE_FYI;
		nMaxSize	= DEF_LOG_FILESIZE;
		nLifeTime	= DEF_LIFETIME;
	}
} LOG_CONFIG;

class CLogWriter
{
private:
	CRITICAL_SECTION	m_csLockWriter;

	TCHAR				m_szLogDir[MAX_PATH];
	HANDLE				m_hLogFile;
	DWORD				m_maxSize;

	BOOL	Open();
	void	Close();
	void	GetFileName(LPTSTR filename);
	void	CheckOpenNewFile();
	BOOL	CreateDir(LPCTSTR strDir);
public:
	CLogWriter(void);
	~CLogWriter(void);

	BOOL	Initialize(LPCTSTR lpszLogDir = NULL);
	BOOL	WriteLog(char type, LPCTSTR msg);
	BOOL	WriteLogFormat(char type, LPCTSTR msg, ...);
};
