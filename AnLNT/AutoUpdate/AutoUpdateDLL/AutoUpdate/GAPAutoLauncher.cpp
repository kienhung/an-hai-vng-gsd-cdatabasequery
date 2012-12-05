#include "StdAfx.h"
#include "GAPAutoLauncher.h"
#include "GlobalClass.h"
#include "MyUtils.h"
#include "Include/pugixml.hpp"
#include "WindowFinder.h"
using namespace pugi;
using namespace std;

CGAPAutoLauncher::CGAPAutoLauncher( LPCTSTR strSource )
:CLauncherEx(strSource)
{
	m_strLauncher = strSource + CString(L"\\garenamessenger.exe");
	m_bIsInitSuccessful = Init();
}

CGAPAutoLauncher::~CGAPAutoLauncher(void)
{
}

BOOL CGAPAutoLauncher::Init()
{
	m_bIsStopToFindWindow = FALSE;
	m_bHasUpdate = FALSE;

	if (!m_ConfigLoadingResult)
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"Failure to load launcher config");
		return FALSE;
	}

	char strLauncherName[] = "gap";

	m_iXUpdateOKButton = m_launcherConfig.child(strLauncherName).child("update_ok_button").attribute("x").as_int();
	m_iYUpdateOKBUtton = m_launcherConfig.child(strLauncherName).child("update_ok_button").attribute("y").as_int();
	m_iXExecuteUpdateButton = m_launcherConfig.child(strLauncherName).child("execute_update_button").attribute("x").as_int();
	m_iYExecuteUpdateButton = m_launcherConfig.child(strLauncherName).child("execute_update_button").attribute("y").as_int();

	m_dwWaitForUpdateManagerAppearedTime = m_launcherConfig.child(strLauncherName).child("wait_for_update_manager_appeared").attribute("time_in_second").as_uint();
	m_dwWaitForUpdateManagerAppearedTry = m_launcherConfig.child(strLauncherName).child("wait_for_update_manager_appeared").attribute("try").as_uint();
	m_dwWaitForUpdateManagerDisappearedTime = m_launcherConfig.child(strLauncherName).child("wait_for_update_manager_disappeared").attribute("time_in_second").as_uint();
	m_dwWaitForUpdateManagerDisappearedTry = m_launcherConfig.child(strLauncherName).child("wait_for_update_manager_disappeared").attribute("try").as_uint();

	string strTempUTF8 = m_launcherConfig.child(strLauncherName).child("update_manager_wnd").attribute("class").value();
	TCHAR *pTempWidechar =  CMyUtils::ConvertUTF8ToWideChar(strTempUTF8.c_str());
	if (pTempWidechar != NULL)
	{
		m_strUpdateManagerWndClass = pTempWidechar;
		delete[] pTempWidechar;
	}

	strTempUTF8 = m_launcherConfig.child(strLauncherName).child("update_manager_wnd").attribute("title").value();
	pTempWidechar =  CMyUtils::ConvertUTF8ToWideChar(strTempUTF8.c_str());
	if (pTempWidechar != NULL)
	{
		m_strUpdateManagerWndTitle = pTempWidechar;
		delete[] pTempWidechar;
	}

	strTempUTF8 = m_launcherConfig.child(strLauncherName).child("garena_messenger_wnd").attribute("class").value();
	pTempWidechar =  CMyUtils::ConvertUTF8ToWideChar(strTempUTF8.c_str());
	if (pTempWidechar != NULL)
	{
		m_strGarenaMessengerWndClass = pTempWidechar;
		delete[] pTempWidechar;
	}

	strTempUTF8 = m_launcherConfig.child(strLauncherName).child("garena_messenger_wnd").attribute("title").value();
	pTempWidechar =  CMyUtils::ConvertUTF8ToWideChar(strTempUTF8.c_str());
	if (pTempWidechar != NULL)
	{
		m_strGarenaMessangerWndTitle = pTempWidechar;
		delete[] pTempWidechar;
	}

	int x = 10;

	return TRUE;
}

CString CGAPAutoLauncher::GetName()
{
	return L"GAP";
}

BOOL CGAPAutoLauncher::Run()
{
	if (FALSE == m_bIsInitSuccessful)
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"Failure to start GAP Launcher");
		return FALSE;
	}

	if (FALSE == StartLauncherProcess())
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"CGAPLaucher: Unable to start launcher process");
		return FALSE;
	}

	HWND hUpdateWindow = NULL;
	//HARD_CODE
	//for (int i = 0; i < 2; i++)
	//{
	//	hUpdateWindow = CLauncherEx::WaitForWindow(m_strUpdateManagerWndClass, m_strUpdateManagerWndTitle, m_dwWaitForUpdateManagerAppearedTime*1000, m_dwWaitForUpdateManagerAppearedTry);
	//	if (NULL != hUpdateWindow)
	//	{
	//		break;
	//	}
	//	if (0 == i)
	//	{
	//		CWindowFinder windowFinder;
	//		vector<HWND> listMainWnd = windowFinder.GetListWindow(m_strGarenaMessengerWndClass, m_strGarenaMessangerWndTitle);
	//		if (listMainWnd.size() > 0)
	//		{
	//			CMyUtils::SimulateLeftMouseClick(listMainWnd, 213, 483);
	//		}
	//	}
	//}
	
	//printf("NO Update\n");
	//CMyUtils::KillWindowProcessEx(m_strGarenaMessengerWndClass, m_strGarenaMessangerWndTitle);
	//return TRUE;
	
	//TEST
			CWindowFinder windowFinder;
			vector<HWND> listMainWnd = windowFinder.GetListWindow(m_strGarenaMessengerWndClass, m_strGarenaMessangerWndTitle);
			if (listMainWnd.size() > 0)
			{
				CMyUtils::SimulateLeftMouseClick(listMainWnd, 222, 478);
			}	
	//END_TEST

	DWORD iTry = 0;
	printf("window: %x\n", hUpdateWindow);
	while (iTry < m_dwWaitForUpdateManagerDisappearedTry)
	{
		CMyUtils::SimulateLeftMouseClick(hUpdateWindow, m_iXUpdateOKButton, m_iYUpdateOKBUtton);
		//HARD_CODE
		printf("Try: %d. MaxTry: %d\n", iTry, m_dwWaitForUpdateManagerDisappearedTry);
		if (TRUE == CLauncherEx::WaitForWindowDisappeared(hUpdateWindow, m_dwWaitForUpdateManagerDisappearedTime*1000))
		{
			break;
		}
		iTry++;
	}
	printf("End: Try: %d. MaxTry: %d\n", iTry, m_dwWaitForUpdateManagerDisappearedTry);
	if (iTry < m_dwWaitForUpdateManagerDisappearedTry)
	{
		printf("NO UPDATE\n");
		return FALSE;
	}
	printf("Has Update\n");
	CMyUtils::SimulateLeftMouseClick(hUpdateWindow, m_iXExecuteUpdateButton, m_iYExecuteUpdateButton);

	//const DWORD dwNumThreads = 2;
	//HANDLE arrFindWindowThreadHandles[dwNumThreads] = {NULL};
	//int iFindUpdateManagerThreadIndex = 0;
	//int iFindGarenaMessengerThreadIndex = 1;

	//arrFindWindowThreadHandles[iFindUpdateManagerThreadIndex] = ::CreateThread(NULL, 0, FindUpdateManagerThreadFunction, this, 0, NULL);
	//arrFindWindowThreadHandles[iFindGarenaMessengerThreadIndex ] = ::CreateThread(NULL, 0, FindGarenaMessengerThreadFunction, this, 0, NULL);

	//if (NULL == arrFindWindowThreadHandles[iFindUpdateManagerThreadIndex] || NULL == arrFindWindowThreadHandles[iFindGarenaMessengerThreadIndex])
	//{
	//	CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"CGAPLaucher: Unable to create threads to find windows");
	//	return FALSE;
	//}

	//DWORD dwResult = ::WaitForMultipleObjects(dwNumThreads, arrFindWindowThreadHandles, FALSE, 3*60*1000);
	//if (WAIT_TIMEOUT == dwResult)
	//{
	//	CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"CGAPLaucher: Find Window Timeout");
	//	return FALSE;
	//}

	//if (WAIT_FAILED == dwResult)
	//{
	//	CGlobalClass::GetInstance()->GetLogWriter()->WriteLogFormat(LOG_TYPE_ERROR, L"CGAPLaucher: Failure to wait for threads with last error %u", GetLastError());
	//	return FALSE;
	//}

	//for (DWORD i = 0; i < dwNumThreads; i++)
	//{
	//	::CloseHandle(arrFindWindowThreadHandles[i]);
	//}

	//if (TRUE == m_bHasUpdate)
	//{
	//	printf("Has Update\n");
	//}
	//else
	//{
	//	printf("No Update\n");
	//}
	return TRUE;
}

//DWORD WINAPI CGAPAutoLauncher::FindUpdateManagerThreadFunction( PVOID pvParam )
//{
//	CGAPAutoLauncher *pLauncher = (CGAPAutoLauncher*)pvParam;
//	while (FALSE == pLauncher->m_bIsStopToFindWindow)
//	{
//		pLauncher->m_hMainWindow = CLauncherEx::WaitForWindow(pLauncher->m_strUpdateManagerWndClass, pLauncher->m_strUpdateManagerWndTitle, 1000*60);
//
//		if (pLauncher->m_hMainWindow != NULL)
//		{
//			pLauncher->m_bIsStopToFindWindow = TRUE;
//			pLauncher->m_bHasUpdate = TRUE;
//		}
//	}
//	return TRUE;
//}

//DWORD WINAPI CGAPAutoLauncher::FindGarenaMessengerThreadFunction( PVOID pvParam )
//{
//	CGAPAutoLauncher *pLauncher = (CGAPAutoLauncher*)pvParam;
//	while (FALSE == pLauncher->m_bIsStopToFindWindow)
//	{
//		pLauncher->m_hMainWindow = CLauncherEx::WaitForWindow(pLauncher->m_strGarenaMessengerWndClass, pLauncher->m_strGarenaMessangerWndTitle, 1000*60);
//
//		if (pLauncher->m_hMainWindow != NULL)
//		{
//			pLauncher->m_bIsStopToFindWindow = TRUE;
//			pLauncher->m_bHasUpdate = FALSE;
//		}
//	}
//	return TRUE;
//}
