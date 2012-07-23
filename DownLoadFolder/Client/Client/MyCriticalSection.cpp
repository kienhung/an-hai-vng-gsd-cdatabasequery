#include "StdAfx.h"
#include "MyCriticalSection.h"

CMyCriticalSection::CMyCriticalSection(void)
{
	InitializeCriticalSection(&m_cs);
}

CMyCriticalSection::~CMyCriticalSection(void)
{
	DeleteCriticalSection(&m_cs);
}

void CMyCriticalSection::EnterSection()
{
	
	EnterCriticalSection(&m_cs);
}
void CMyCriticalSection::LeaveSection()
{
	LeaveCriticalSection(&m_cs);
}