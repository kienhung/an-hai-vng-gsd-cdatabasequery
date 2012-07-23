#include "StdAfx.h"
#include "MyMutex.h"

CMyMutex::CMyMutex(TCHAR* strMutexName):m_strMutexName(_T("Default"))
{
	SetMutexName(strMutexName);

}

CMyMutex::~CMyMutex(void)
{
}

void CMyMutex::SetMutexName(TCHAR* strMutexName)
{
	m_strMutexName = strMutexName;
	/*if(m_hMutex != NULL)
	{
		CloseHandle(m_hMutex);

	}*/
	m_hMutex = 	::CreateMutex(NULL, TRUE, m_strMutexName);
}
void CMyMutex::Enter()
{
	
	::WaitForMultipleObjects(LONG_MAX, &m_hMutex, FALSE, INFINITE);
	//::WaitForSingleObject(m_hMutex, INFINITE);
}
void CMyMutex::Release()
{
	::ReleaseMutex(m_hMutex);
}
