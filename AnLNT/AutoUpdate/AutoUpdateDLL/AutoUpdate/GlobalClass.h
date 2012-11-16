#pragma once
#include "Include/LogWriter.h"

class CMyCriticalSection
{
protected:
	CRITICAL_SECTION m_criticalSection;
public:
	CMyCriticalSection()
	{
		::InitializeCriticalSection(&m_criticalSection);
	}
	virtual ~CMyCriticalSection()
	{
		::DeleteCriticalSection(&m_criticalSection);
	}
	void Lock()
	{	
		::EnterCriticalSection(&m_criticalSection);
	}
	void Unlock()
	{
		::LeaveCriticalSection(&m_criticalSection);
	}
};


class CGlobalClass
{

public:

	virtual ~CGlobalClass(void);
	static CGlobalClass* GetInstance();

	CLogWriter *GetLogWriter();

protected:

	CGlobalClass(void);
	CLogWriter m_logWriter;

	static CMyCriticalSection m_sCrriticalSection;
};
