#include "StdAfx.h"
#include "TBVAutoLauncher.h"
#include "GlobalClass.h"
#include "TBVCompare.h"
#include "MyUtils.h"

CTBVAutoLauncher::CTBVAutoLauncher( LPCTSTR strSource )
:CLauncherEx(strSource)
{
	m_strRootSource = CString(strSource);
	CreateSourceAndLauncherPath(L"BaVuong1", L"amped_launcher.exe");
	m_dwTimeOutInMinute = 15;
}

CTBVAutoLauncher::~CTBVAutoLauncher(void)
{

}

CString CTBVAutoLauncher::GetName()
{
	return CString(L"TBV");
}

BOOL CTBVAutoLauncher::Run()
{
	if (FALSE == ReadConfig())
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"CTBVAutoLauncher - Falure to read configuration");
		return FALSE;
	}
	
	CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_FYI, L"CTBVAutoLauncher - Start running TBV1 Launcher");
	
	if (FALSE == StartLauncherProcess())
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"CTBVAutoLauncher - Unable to start launcher process");
		return FALSE;
	}

	m_hMainWindow = CLauncherEx::WaitForWindow(m_strBV1WindowClass, m_strBV1WindowTitle, m_dwLauncherTimeOut);
	if (NULL == m_hMainWindow)
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"CTBVAutoLauncher - Waiting for TBV1 Game Window Timeout");
		KillAll();
		return FALSE;
	}

	CMyUtils::KillWindowProcess(m_hMainWindow);

	CreateSourceAndLauncherPath(L"BaVuong2", L"ga2.exe");
	ReleaseProcess();

	CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_FYI, L"CTBVAutoLauncher - Start running TBV2 Launcher");
	m_hMainWindow = StartLauncherWindow(m_strBV2WindowClass, m_strBV2WindowTitle);
	if (NULL == m_hMainWindow)
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"CTBVAutoLauncher - Unable to start launcher process");
		return FALSE;
	}
	CGlobalClass::GetInstance()->GetLogWriter()->WriteLogFormat(LOG_TYPE_FYI, L"CTBVAutoLauncher - Begin sleeping within %u minute(s)", m_dwTimeOutInMinute);
	for (int i = 0; i < m_dwTimeOutInMinute; i++)
	{
		::Sleep(1000*60);
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLogFormat(LOG_TYPE_FYI, L"CTBVAutoLauncher - %d minute(s)", i + 1);
	}
	
	CGlobalClass::GetInstance()->GetLogWriter()->WriteLogFormat(LOG_TYPE_FYI, L"CTBVAutoLauncher - Finish sleeping within %u minute(s)", m_dwTimeOutInMinute);
	CMyUtils::KillWindowProcess(m_hMainWindow);
	
	//::SendMessage(m_hMainWindow, WM_CLOSE, 0, 0);

	return TRUE;
}

void CTBVAutoLauncher::CreateSourceAndLauncherPath( LPCTSTR strGameFolderName, LPCTSTR strGameLauncherName )
{
	m_strLauncher.Format(L"%s\\%s\\%s", m_strRootSource, strGameFolderName, strGameLauncherName);
	m_strSource.Format(L"%s\\%s", m_strRootSource, strGameFolderName);
}

BOOL CTBVAutoLauncher::ReadConfig()
{
	if (!m_ConfigLoadingResult)
	{	
		return FALSE;
	}

	m_dwTimeOutInMinute = m_launcherConfig.child("tbv").child("tbv2_time_out_minute").attribute("value").as_int();
	m_strBV1WindowClass = ExtractStringConfig("tbv", "tbv1", "class");
	m_strBV1WindowTitle = ExtractStringConfig("tbv", "tbv1", "title");
	m_strBV2WindowClass = ExtractStringConfig("tbv", "tbv2", "class");
	m_strBV2WindowTitle = ExtractStringConfig("tbv", "tbv2", "title");

	return TRUE;
}

CGameSourceCompare * CTBVAutoLauncher::GetComparer( LPCTSTR strNewSource, LPCTSTR strOldSource )
{
	if (m_Comparer != NULL)
	{
		delete m_Comparer;
	}

	m_Comparer = new CTBVCompare(strNewSource, strOldSource);

	if (m_Comparer != NULL)
	{
		return m_Comparer;
	}

	return NULL;
}

CString CTBVAutoLauncher::GetSourcePath()
{
	return m_strRootSource;
}
