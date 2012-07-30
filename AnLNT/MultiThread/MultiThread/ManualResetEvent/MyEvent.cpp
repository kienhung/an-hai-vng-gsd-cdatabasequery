#include "StdAfx.h"
#include "MyEvent.h"

CMyEvent::CMyEvent(BOOL bManualReset) 
{
	m_hEvent = ::CreateEvent(NULL, bManualReset, FALSE, NULL);
}

CMyEvent::~CMyEvent(void)
{
	if (NULL != m_hEvent) {
		::CloseHandle(m_hEvent);	
	}
}

BOOL CMyEvent::SetEvent() {

	if (NULL != m_hEvent) {
		return ::SetEvent(m_hEvent);
	}
	return FALSE;
}

BOOL CMyEvent::ResetEvent() {

	if (NULL != m_hEvent) {
		return ::ResetEvent(m_hEvent);
	}

	return FALSE;
}

DWORD CMyEvent::Wait(DWORD dwMilliseconds) {

	if (NULL != m_hEvent) {
		return ::WaitForSingleObject(m_hEvent, dwMilliseconds);
	}

	return WAIT_FAILED;
}
