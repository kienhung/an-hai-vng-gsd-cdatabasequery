#include "StdAfx.h"
#include "Process.h"

CProcess::CProcess(void)
{
	ZeroMemory(&m_processInfo, sizeof(PROCESS_INFORMATION));
	ZeroMemory( &m_startupInfo, sizeof(STARTUPINFO));

	m_startupInfo.cb = sizeof(STARTUPINFO);
}

CProcess::~CProcess(void)
{
	Free();
}

void CProcess::SetProcessName( LPCTSTR strProcessName )
{
	m_strProcessName = CString(strProcessName);
}


BOOL CProcess::GetExitCode( DWORD *pdwExitCode )
{
	if (FALSE == GetExitCodeProcess(m_processInfo.hProcess, pdwExitCode))
	{
		return FALSE;
	}
	return TRUE;
}

void CProcess::Free()
{
	if (m_processInfo.hThread!= NULL)
	{
		::CloseHandle(m_processInfo.hThread);
	}

	if (m_processInfo.hProcess != NULL)
	{
		::CloseHandle(m_processInfo.hProcess);
	}
}

BOOL CProcess::Run( LPCTSTR strWorkingDir /*= NULL*/ )
{
	if (FALSE == ::CreateProcess(NULL, m_strProcessName.GetBuffer(), NULL, NULL, FALSE, 0, NULL, strWorkingDir, &m_startupInfo, &m_processInfo))
	{
		return FALSE;
	}

	return TRUE;
}

DWORD CProcess::WaitForExit( DWORD dwMilliseconds /*= INFINITE*/ )
{
	return ::WaitForSingleObject(m_processInfo.hProcess, dwMilliseconds);
}
