#include "StdAfx.h"
#include "AHKLauncher.h"
#include "GlobalClass.h"


CAHKLauncher::CAHKLauncher( LPCTSTR strSource, LPCTSTR strGameAlias )
:CLauncher(strSource)
{
	m_strGameAlias = strGameAlias;
	m_strAHKLauncher.Format(L"%s\\%s", CGlobalClass::GetInstance()->GetExeDirectory(), strGameAlias);
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
	if (PrepareForAll() == FALSE)
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"Failed to call prepareForAll method");
		return FALSE;
	}

	if (BeforeRun() == FALSE)
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"Failed to call BeforeRun method");
		return FALSE;
	}

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
	m_bResult = TRUE;

	if (FALSE == GetExitCodeProcess(pi.hProcess, &dwExitCode) || 0 != dwExitCode)
	{
		m_bResult =  FALSE;
	}

	Clean(pi);
	AfterRun();
	return m_bResult;
}

void CAHKLauncher::Clean( PROCESS_INFORMATION &pi )
{
	::CloseHandle(pi.hThread);
	::CloseHandle(pi.hProcess);
}

BOOL CAHKLauncher::PrepareForAll()
{
	return TRUE;
}

BOOL CAHKLauncher::BeforeRun()
{
	return TRUE;
}

BOOL CAHKLauncher::AfterRun()
{
	return TRUE;
}
