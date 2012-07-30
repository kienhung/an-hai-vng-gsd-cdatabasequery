#pragma once

class AFX_EXT_CLASS CMyCriticalSection
{
protected:
	CRITICAL_SECTION m_criticalSection;
public:
	CMyCriticalSection(void);
	virtual ~CMyCriticalSection(void);
	void Lock();
	void Unlock();
};
