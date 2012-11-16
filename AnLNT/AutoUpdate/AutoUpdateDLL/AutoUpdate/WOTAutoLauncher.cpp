#include "StdAfx.h"
#include "WOTAutoLauncher.h"
#include "MyUtils.h"
#include "WOTCompare.h"

CWOTAutoLauncher::CWOTAutoLauncher(LPCTSTR strSource)
:CLauncher(strSource)
{
	m_strLauncher = strSource + CString(L"\\WOTLauncher.exe");
	m_strConfigFilePath = strSource + CString(L"\\WOTLauncher.cfg");
	m_strLogFilePath = strSource + CString(L"\\WOTLauncher.log");
	m_strTempUpdateDirectoryPath = strSource + CString(L"\\Updates");

	m_iDelayTime = 10000;
	m_bIsFailed = FALSE;
}

CWOTAutoLauncher::~CWOTAutoLauncher(void)
{
}

CString CWOTAutoLauncher::GetName()
{

	return L"WOT";
}

BOOL CWOTAutoLauncher::Run()
{
	if (TRUE == CMyUtils::FileExists(m_strTempUpdateDirectoryPath))
	{
		if (FALSE == CMyUtils::DeleteDir(m_strTempUpdateDirectoryPath))
		{
			CMyUtils::WriteErrorLog(L"WOT fails to remove the update directory");
			return FALSE;
		}
	}

	if (FALSE == GetConfigFileLastWriteTime()) {
		CMyUtils::WriteErrorLog(L"WOTLauncher.cfg not found");
		return FALSE;
	}

	if (FALSE == StartLauncherProcess()) {
		CMyUtils::WriteErrorLog(L"Unable to start WOTLauncher.exe");
		return FALSE;
	}

	if (FALSE == WaitForUpdateBeginning()) {
		CMyUtils::WriteErrorLog(L"WaitForUpdateBeginning failed");
		return FALSE;
	}

	if (FALSE == WaitForComplate()) {
		CMyUtils::WriteErrorLog(L"WaitForComplate failed");
		return FALSE;
	}
	
	if (TRUE == m_bIsFailed)
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL CWOTAutoLauncher::StartLauncherProcess()
{

	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	if (FALSE == ::CreateProcess(m_strLauncher, NULL, NULL, NULL, FALSE, 0, NULL, m_strSource, &si, &pi)) {
		return FALSE;
	}

	m_hProcess = pi.hProcess;

	return TRUE;
}

BOOL CWOTAutoLauncher::GetConfigFileLastWriteTime()
{

	WIN32_FIND_DATA FindFileData;

	HANDLE hFind = FindFirstFile(m_strConfigFilePath, &FindFileData);

	if (INVALID_HANDLE_VALUE == hFind) {
		return FALSE;
	}

	m_ftConfigFileLastWriteTime = FindFileData.ftLastWriteTime;

	::FindClose(hFind);
	return TRUE;
}

BOOL CWOTAutoLauncher::WaitForUpdateBeginning()
{

	WIN32_FIND_DATA FindFileData;

	while (true) {
		
		HANDLE hFind = ::FindFirstFile(m_strConfigFilePath, &FindFileData);

		if (INVALID_HANDLE_VALUE == hFind) {
			return FALSE;
		}

		::FindClose(hFind);

		if (::CompareFileTime(&m_ftConfigFileLastWriteTime, &FindFileData.ftLastWriteTime) != 0) {
			return TRUE;
		}
	}

	return TRUE;
}

BOOL CWOTAutoLauncher::WaitForComplate()
{

	CStdioFile readFile;
	CFileException fileException;

	if (readFile.Open(m_strLogFilePath, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone   , &fileException)) {

		BOOL bIsComplete = FALSE;

		DWORD ullStartTime = GetTickCount ();

		while (FALSE == bIsComplete) {

			DWORD ullEndTime = GetTickCount () - ullStartTime ;

			if (ullEndTime > m_dwLauncherTimeOut)
			{
				CMyUtils::WriteErrorLog(L"WOTLauncher Timeout");
				ProcessError();
				return TRUE;
			}

			CString strPrevious = L"Nothing";
			CString strCurrent;

			while (readFile.ReadString(strCurrent)) {

				if (strCurrent.Find(L"ERROR") != -1) {
					ProcessError();
					return TRUE;
				}

				if (strCurrent.Find(L"Update complete") != -1 && strPrevious.Find(L"Clear old/temp files") != -1) {
					bIsComplete = TRUE;	
				}

				strPrevious = strCurrent;
			}

			readFile.Seek(0, CFile::begin);
			::Sleep(m_iDelayTime);
		}

		return ProcessComplete();

	}

	return FALSE;
}

BOOL CWOTAutoLauncher::ProcessError()
{
	m_bIsFailed = TRUE;
	if (FALSE == KillProcess()) {
		return FALSE;
	}

	return TRUE;
}

BOOL CWOTAutoLauncher::ProcessComplete()
{
	if (FALSE == KillProcess()) {
		return FALSE;
	}
	
	return TRUE;
}

BOOL CWOTAutoLauncher::KillProcess()
{
	if (FALSE == ::TerminateProcess(m_hProcess, 0)) {
		return FALSE;
	}

	::WaitForSingleObject(m_hProcess, INFINITE);
	::CloseHandle(m_hProcess);

	DWORD dwWait = 5000;
	::Sleep(dwWait);
	return TRUE;
}

CGameSourceCompare * CWOTAutoLauncher::GetComparer( LPCTSTR strNewSource, LPCTSTR strOldSource )
{
	if (m_Comparer != NULL)
	{
		delete m_Comparer;
	}

	m_Comparer = new CWOTCompare(strNewSource, strOldSource);

	if (m_Comparer != NULL)
	{
		return m_Comparer;
	}

	return NULL;
}
