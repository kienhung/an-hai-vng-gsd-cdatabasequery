#pragma once

class AFX_EXT_CLASS CMyEvent
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
