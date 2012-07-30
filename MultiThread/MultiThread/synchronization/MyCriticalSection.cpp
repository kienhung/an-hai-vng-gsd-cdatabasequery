#include "StdAfx.h"
#include "MyCriticalSection.h"

CMyCriticalSection::CMyCriticalSection(void)
{
	::InitializeCriticalSection(&m_criticalSection);
}

CMyCriticalSection::~CMyCriticalSection(void)
{
	::DeleteCriticalSection(&m_criticalSection);
}

void CMyCriticalSection::Lock()
{
	::EnterCriticalSection(&m_criticalSection);
}

void CMyCriticalSection::Unlock()
{

	::LeaveCriticalSection(&m_criticalSection);
}
