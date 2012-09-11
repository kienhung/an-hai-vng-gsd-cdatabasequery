#pragma once
#include "StdAfx.h"
#include "DummyManager.h"

CDummyManager::CDummyManager(void)
{
}

CDummyManager::CDummyManager(CDummyDlg* pDlgRegInfo)
{
	m_pDlgRegInfo = pDlgRegInfo;
}

CDummyManager::~CDummyManager(void)
{
}

VOID CDummyManager::Execute()
{
	if(NULL == m_pDlgRegInfo)
		return;

	StartUp();
	INT_PTR nResponse = 0;
	m_pDlgRegInfo->SetRegistered(CheckRegister());
	nResponse = m_pDlgRegInfo->DoModal();
	

	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
}

VOID CDummyManager::StartUp()
{
	HKEY hKey;
	LONG lResult = 0;
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0,  KEY_ALL_ACCESS, &hKey);
	
	if(lResult != ERROR_SUCCESS)
	{
		return;
	}
	
	TCHAR szPath[MAX_PATH] = {0};
	TCHAR szStringValue[MAX_PATH] = {0};
	DWORD dwSize=0;
	GetModuleFileName(NULL, szPath, MAX_PATH);
	
	DWORD dwType = REG_SZ;
	lResult = RegQueryValueEx(hKey, _T("Dummy"), 0, &dwType, NULL, &dwSize);
	if(lResult == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, _T("Dummy"), 0, &dwType,(LPBYTE)szStringValue, &dwSize);
		if(wcscmp(szPath, szStringValue) != 0)
		{
			RegSetValueEx(hKey,_T("Dummy"),0,REG_SZ,(LPBYTE)szPath ,sizeof(szPath));
		}
		RegCloseKey(hKey);
		return;
	}
	RegSetValueEx(hKey,_T("Dummy"),0,REG_SZ,(LPBYTE)szPath ,sizeof(szPath));
	RegCloseKey(hKey);
	return;
	
}
BOOL CDummyManager::CheckRegister()
{
	HKEY hKey;
	LONG lResult = 0;
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Dummy"), 0,  KEY_ALL_ACCESS, &hKey);
	
	TCHAR szStringValue[2] = {0};
	DWORD dwSize=0;

	if(lResult != ERROR_SUCCESS)
	{
		SECURITY_ATTRIBUTES sAttribs = {sizeof(SECURITY_ATTRIBUTES)};
		DWORD dwDisposition=0;
		RegCreateKeyEx(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\Dummy"),0,_T(""),REG_OPTION_VOLATILE,KEY_ALL_ACCESS, &sAttribs, &hKey,&dwDisposition);

		swprintf(szStringValue, 2, _T("0"));
		RegSetValueEx(hKey,_T("Registered"),0,REG_SZ,(LPBYTE)szStringValue ,sizeof(szStringValue));
		RegCloseKey(hKey);
		return FALSE;
	}
		
	DWORD dwType = REG_SZ;
	lResult = RegQueryValueEx(hKey, _T("Registered"), 0, &dwType,NULL, &dwSize);

	if(lResult == ERROR_SUCCESS)
	{

		RegQueryValueEx(hKey, _T("Registered"), 0, &dwType,(LPBYTE)szStringValue, &dwSize);
		RegCloseKey(hKey);
		if(wcscmp(szStringValue, _T("1")) == 0)
		{
			return TRUE;
		}
		return FALSE;
	}
	
	swprintf(szStringValue, 2, _T("0"));	
	RegSetValueEx(hKey,_T("Registered"),0,REG_SZ,(LPBYTE)szStringValue ,sizeof(szStringValue));
	RegCloseKey(hKey);
	return FALSE;
}

VOID CDummyManager::UpdateRegistered(BOOL bIsRegistered)
{
	HKEY hKey;
	LONG lResult = 0;
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Dummy"), 0,  KEY_ALL_ACCESS, &hKey);
	
	TCHAR szStringValue[2] = {0};
	DWORD dwSize=0;

	if(lResult != ERROR_SUCCESS)
	{
		SECURITY_ATTRIBUTES sAttribs = {sizeof(SECURITY_ATTRIBUTES)};
		DWORD dwDisposition=0;
		RegCreateKeyEx(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\Dummy"),0,_T(""),REG_OPTION_VOLATILE,KEY_ALL_ACCESS, &sAttribs, &hKey,&dwDisposition);
	}

	if(bIsRegistered)
	{
		swprintf(szStringValue, 2, _T("1"));
	}
	else
		swprintf(szStringValue, 2, _T("0"));

	RegSetValueEx(hKey,_T("Registered"),0,REG_SZ,(LPBYTE)szStringValue ,sizeof(szStringValue));
}