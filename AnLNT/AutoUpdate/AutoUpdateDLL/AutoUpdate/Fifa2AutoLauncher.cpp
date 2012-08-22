#include "StdAfx.h"
#include "Fifa2AutoLauncher.h"
#include <tlhelp32.h>

CFifa2AutoLauncher::CFifa2AutoLauncher(LPCTSTR strSource)
	:CLauncher(strSource)
{
	m_strLauncher = strSource + CString(L"\\GameLoader.exe");

	iAcceptCheckboxID = 0x00000426;
	iZone1RadioButtonID = 0x000007D1;
	iStartButtonID = 0x000003E9;
}

CFifa2AutoLauncher::~CFifa2AutoLauncher(void)
{

}

BOOL CFifa2AutoLauncher::Run()
{
	HWND hMainWnd = StartLauncherWindow(L"#32770", L"GameLoader");
	if (NULL == hMainWnd) {
		return FALSE;
	}

	if (FALSE == CheckButton(iAcceptCheckboxID)) {
		return FALSE;
	}

	if (FALSE == CheckButton(iZone1RadioButtonID)) {
		return FALSE;
	}

	HWND hStartButton = ::GetDlgItem(hMainWnd, iStartButtonID);

	while (hStartButton != NULL) {
		if (FALSE == ClickButton(iStartButtonID)) {
			return FALSE;
		}
		hStartButton = ::GetDlgItem(hMainWnd, iStartButtonID);
	}
	
	if (FALSE == WaitForComplete()) {
		return FALSE;
	}

	return TRUE;
}

CString CFifa2AutoLauncher::GetName()
{
	return L"Fifa Online 2";
}

BOOL CFifa2AutoLauncher::WaitForComplete()
{

	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0);

	if (INVALID_HANDLE_VALUE == hProcessSnap) {
		return FALSE;
	}

	while (true) {

		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if( !::Process32First( hProcessSnap, &pe32 ) ) {
			::CloseHandle( hProcessSnap );  
			return FALSE ;
		}

		do {
			if (lstrcmp(pe32.szExeFile, L"FF2Client.exe") == 0) {

				HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);

				if (hProcess == NULL) {
					_tprintf(L"Open process is failed. Error: %d\n", GetLastError());
				}

				if (FALSE == ::TerminateProcess(hProcess, 0)) {
					_tprintf(L"Termiate process crossfire.dat that bai. Error: %d\n", GetLastError());
				} 

				::CloseHandle(hProcess);
				::CloseHandle( hProcessSnap );

				return TRUE;
			}

		} while (::Process32Next( hProcessSnap, &pe32 ));
	}
	
	return FALSE;
}
