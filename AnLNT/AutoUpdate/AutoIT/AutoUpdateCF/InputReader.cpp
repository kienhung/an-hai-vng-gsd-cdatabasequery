#include "StdAfx.h"
#include "InputReader.h"
#include "AutoUpdateTool.h"
#include "AuditionLauncher.h"
#include "Fifa2Launcher.h"

CInputReader::CInputReader( LPCTSTR strInputFileName )
{

	m_strInput = strInputFileName;

	SYSTEMTIME time;
	GetLocalTime(&time);

	m_strToken.Format(L"%02u-%02u-%u-%02uh%02u", time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute);

}

BOOL CInputReader::Read()
{

	if (FALSE == ReadAudition()) {
		_tprintf(L"Auditon Fail\n");
	}
	
	if (FALSE == ReadCrossfire()) {
		_tprintf(L"Crossfire Fail\n");
	}

	if (FALSE == ReadFifaonline2()) {
		_tprintf(L"Fifaonline2 Fail\n");
	}

	return TRUE;
}



CInputReader::~CInputReader(void)
{
}



BOOL CInputReader::ReadSection( LPCTSTR strSectionName, LPTSTR strSourcePath, LPTSTR strLauncherPath)
{
	
	DWORD dwCount = ::GetPrivateProfileString(strSectionName, L"source", NULL, strSourcePath, MAX_PATH, m_strInput);

	if (dwCount <= 0) {
		return FALSE;
	}

	dwCount = ::GetPrivateProfileString(strSectionName, L"launcher", NULL, strLauncherPath, MAX_PATH, m_strInput);

	if (dwCount <= 0) {
		return FALSE;
	}
	
	return TRUE;
}

BOOL CInputReader::ReadAudition()
{

	TCHAR strSourcePath[MAX_PATH];
	TCHAR strLauncherPath[MAX_PATH];

	if (FALSE == ReadSection(L"Audition", strSourcePath, strLauncherPath)) {
		return FALSE;
	}

	CAutoUpdateTool autoUpdateTool;
	if (FALSE == autoUpdateTool.Create(new CAuditionLauncher(strSourcePath, strLauncherPath), m_strToken)) {
		return FALSE;
	}

	if (FALSE == autoUpdateTool.Update()) {
		return FALSE;
	}

	return TRUE;
}

BOOL CInputReader::ReadCrossfire()
{

	TCHAR strSourcePath[MAX_PATH];
	TCHAR strLauncherPath[MAX_PATH];

	if (FALSE == ReadSection(L"Crossfire", strSourcePath, strLauncherPath)) {
		return FALSE;
	}

	CAutoUpdateTool autoUpdateTool;
	if (FALSE == autoUpdateTool.Create(new CCrossfireLauncher(strSourcePath, strLauncherPath), m_strToken)) {
		return FALSE;
	}

	if (FALSE == autoUpdateTool.Update()) {
		return FALSE;
	}

	return TRUE;
}

BOOL CInputReader::ReadFifaonline2()
{

	TCHAR strSourcePath[MAX_PATH];
	TCHAR strLauncherPath[MAX_PATH];

	if (FALSE == ReadSection(L"Fifaonline2", strSourcePath, strLauncherPath)) {
		return FALSE;
	}

	CAutoUpdateTool autoUpdateTool;
	if (FALSE == autoUpdateTool.Create(new CFifaLauncher2(strSourcePath, strLauncherPath), m_strToken)) {
		return FALSE;
	}

	if (FALSE == autoUpdateTool.Update()) {
		return FALSE;
	}

	return TRUE;
}
