#pragma once

class CMyMutex
{
	HANDLE m_hMutex;
	TCHAR* m_strMutexName;
public:
	CMyMutex(TCHAR* strMutexName = _T("Default"));
	~CMyMutex(void);
	void Enter();
	void Release();
	void SetMutexName(TCHAR* strMutexName);
};
