#pragma once

class CMyEvent
{
protected:
	HANDLE m_hEvent;
public:
	CMyEvent(BOOL bManualReset);
	virtual ~CMyEvent(void);
	BOOL SetEvent();
	BOOL ResetEvent();
	DWORD Wait(DWORD dwMilliseconds = INFINITE);
};
