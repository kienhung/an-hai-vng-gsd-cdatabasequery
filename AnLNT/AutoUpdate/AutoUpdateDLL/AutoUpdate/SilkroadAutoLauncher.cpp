#include "StdAfx.h"
#include "SilkroadAutoLauncher.h"

CSilkroadAutoLauncher::CSilkroadAutoLauncher(LPCTSTR strSource)
:CLauncher(strSource)
{
	m_StartButtonID = 0x000003E8;
	m_FinishButtonID = 0x000003EA;

	m_strLauncher = strSource + CString(L"\\silkroad.exe");

	m_strLauncherWindowClassName = L"#32770";
	m_strLauncherWindowText = L"Silkroad Online Launcher";
}

CSilkroadAutoLauncher::~CSilkroadAutoLauncher(void)
{

}

CString CSilkroadAutoLauncher::GetName()
{

	return L"Silkroad";
}

BOOL CSilkroadAutoLauncher::Run()
{

	HWND hMainWnd = StartLauncherWindow(m_strLauncherWindowClassName, m_strLauncherWindowText);
	if (NULL == hMainWnd) {
		return FALSE;
	}

	if (FALSE == WaitForComplete()) {
		return FALSE;
	}

	return TRUE;
}

BOOL CSilkroadAutoLauncher::WaitForComplete()
{

	BOOL bIsComplete = FALSE;
	DWORD dwDelayTime = 5000;

	while (FALSE == bIsComplete ) {

		HWND hMainWnd = FindWindow(m_strLauncherWindowClassName, m_strLauncherWindowText);

		if (NULL != hMainWnd) {

			HWND hStartButtonID = ::GetDlgItem(hMainWnd, m_StartButtonID);

			if (TRUE == ::IsWindowVisible(hStartButtonID)) {

				bIsComplete = TRUE;
			
				if (FALSE == ClickButton(hMainWnd, m_FinishButtonID)) {
					return FALSE;
				}

			} 
		}
		::Sleep(dwDelayTime);
	}

	return TRUE;
}
