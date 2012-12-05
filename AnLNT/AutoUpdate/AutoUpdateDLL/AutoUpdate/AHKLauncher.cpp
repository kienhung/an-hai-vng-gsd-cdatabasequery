#include "StdAfx.h"
#include "AHKLauncher.h"
#include "GlobalClass.h"


CAHKLauncher::CAHKLauncher( LPCTSTR strSource, LPCTSTR strAHKLauncher )
:CLauncher(strSource)
{
	m_strGameAlias = strAHKLauncher;
	m_strAHKLauncher.Format(L"%s\\%s", CGlobalClass::GetInstance()->GetExeDirectory(), strAHKLauncher);
	m_iExtraMinute = 3;
}

CAHKLauncher::~CAHKLauncher(void)
{
}

CString CAHKLauncher::GetName()
{
	return m_strGameAlias;
}

BOOL CAHKLauncher::Run()
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	if (FALSE == ::CreateProcess(NULL, m_strAHKLauncher.GetBuffer(), NULL, NULL, FALSE, 0, NULL,NULL, &si, &pi))
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"Unable to start AHK Launcher");
		return FALSE;
	}

	int iWaitInMinute = m_dwLauncherTimeOut/(1000*60) + m_iExtraMinute;
	CGlobalClass::GetInstance()->GetLogWriter()->WriteLogFormat(LOG_TYPE_FYI, L"Beginning waiting for AHK process finished within %d minute(s)", iWaitInMinute);

	int iCount = 0;
	DWORD dwResult = WAIT_FAILED;

	for (iCount = 0; iCount < iWaitInMinute; iCount++)
	{
		dwResult = ::WaitForSingleObject(pi.hProcess, 1000*60);
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLogFormat(LOG_TYPE_FYI, L"Waiting for AHK process finished has started for %d minute(s)", iCount + 1);

		if (WAIT_OBJECT_0 == dwResult)
		{
			break;
		}
	}

	if (dwResult != WAIT_OBJECT_0)
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"Failed to waiting for AHK process finished");
		Clean(pi);

		return FALSE;
	}

	DWORD dwExitCode = 1;
	BOOL bResult = TRUE;

	if (FALSE == GetExitCodeProcess(pi.hProcess, &dwExitCode) || 0 != dwExitCode)
	{
		bResult =  FALSE;
	}

	Clean(pi);
	return bResult;
}

void CAHKLauncher::Clean( PROCESS_INFORMATION &pi )
{
	::CloseHandle(pi.hThread);
	::CloseHandle(pi.hProcess);
}
