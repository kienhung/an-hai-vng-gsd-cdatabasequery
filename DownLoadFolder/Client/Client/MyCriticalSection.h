#pragma once

class CMyCriticalSection
{
	CRITICAL_SECTION m_cs;
public:
	CMyCriticalSection(void);
	~CMyCriticalSection(void);
	void EnterSection();
	void LeaveSection();
};
