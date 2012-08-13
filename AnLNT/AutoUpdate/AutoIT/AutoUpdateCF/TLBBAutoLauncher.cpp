#include "StdAfx.h"
#include "TLBBAutoLauncher.h"

CTLBBAutoLauncher::CTLBBAutoLauncher(LPCTSTR strSource)
:CLauncher(strSource)
{
	m_strLauncher = strSource + CString(L"\\Launch.exe");

	m_CloseButtonID = 1027;
	m_iDelayTime = 5000;
}

CTLBBAutoLauncher::~CTLBBAutoLauncher(void)
{
}

CString CTLBBAutoLauncher::GetName()
{

	return L"Thien Long Bat Bo";
}

BOOL CTLBBAutoLauncher::Run()
{
	HWND hMainWnd = StartLauncherWindow(L"#32770", L"TLBB2");

	if (NULL == hMainWnd) {
		return FALSE;
	}

	if (FALSE == GetLoginServerFileWriteTime(&m_LoginServerFileLowWriteTime, &m_LoginServerFileHighWriteTime)) {
		return FALSE;
	}

	if (FALSE == WaitForComplete()) {
		return FALSE;
	}

	if (FALSE == ClickButton(m_hMainWindow, m_CloseButtonID)) {
		return FALSE;
	}

	return TRUE;
}

BOOL CTLBBAutoLauncher::GetLoginServerFileWriteTime( DWORD *pLowWriteTime, DWORD *pHighWriteTime )
{

	CString strLoginServerFilePath = m_strSource + L"\\Patch\\LoginServer.txt";

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = ::FindFirstFile(strLoginServerFilePath, &FindFileData);

	if (INVALID_HANDLE_VALUE == hFind) {
		return FALSE;
	}

	*pLowWriteTime = FindFileData.ftLastWriteTime.dwLowDateTime;
	*pHighWriteTime = FindFileData.ftLastWriteTime.dwHighDateTime;

	::FindClose(hFind);

	return TRUE;
}

BOOL CTLBBAutoLauncher::WaitForComplete()
{

	DWORD dwNewLoginServerFileLowWriteTime;
	DWORD dwNewLoginServerFileHighWriteTime;

	BOOL isComplete = FALSE;

	while (FALSE == isComplete) {

		if (FALSE == GetLoginServerFileWriteTime(&dwNewLoginServerFileLowWriteTime, &dwNewLoginServerFileHighWriteTime)) {
			return FALSE;
		}

		if (m_LoginServerFileLowWriteTime != dwNewLoginServerFileLowWriteTime || m_LoginServerFileHighWriteTime != dwNewLoginServerFileHighWriteTime) {
			isComplete = TRUE;
		}

		::Sleep(m_iDelayTime);
	}

	return TRUE;
}
