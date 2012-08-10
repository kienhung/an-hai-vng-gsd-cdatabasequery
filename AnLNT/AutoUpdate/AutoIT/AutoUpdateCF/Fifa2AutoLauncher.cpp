#include "StdAfx.h"
#include "Fifa2AutoLauncher.h"

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
	
	if (FALSE == CloseWindow(L"FIFAOnline2Class", L"FIFA Online 2")) {
		return FALSE;
	}

	return TRUE;
}

CString CFifa2AutoLauncher::GetName()
{
	return L"Fifa2Online";
}
