#include "StdAfx.h"
#include "WOTAutoLauncher.h"

CWOTAutoLauncher::CWOTAutoLauncher(LPCTSTR strSource)
:CLauncher(strSource)
{
	m_strLauncher = strSource + CString(L"\\WOTLauncher.exe");
	m_strConfigFilePath = strSource + CString(L"\\WOTLauncher.cfg");
	m_strLogFilePath = strSource + CString(L"\\WOTLauncher.log");

	m_iDelayTime = 10000;

}

CWOTAutoLauncher::~CWOTAutoLauncher(void)
{
}

CString CWOTAutoLauncher::GetName()
{

	return L"World of Tank";
}

BOOL CWOTAutoLauncher::Run()
{

	if (FALSE == GetConfigFileLastWriteTime()) {
		return FALSE;
	}

	if (FALSE == StartLauncherProcess()) {
		return FALSE;
	}

	if (FALSE == WaitForUpdateBeginning()) {
		return FALSE;
	}

	if (FALSE == WaitForComplate()) {
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

		while (FALSE == bIsComplete) {

			CString strPrevious = L"Nothing";
			CString strCurrent;

			while (readFile.ReadString(strCurrent)) {

				if (strCurrent.Find(L"ERROR") != -1) {
					ProcessError();
					return FALSE;
				}

				if (strCurrent.Find(L"update complete") != -1 && strPrevious.Find(L"initialize clear process") != -1) {
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

	return TRUE;
}
