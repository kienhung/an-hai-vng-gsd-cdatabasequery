#include "StdAfx.h"
#include "DummyManager.h"

CDummyManager::CDummyManager(void)
{
}

CDummyManager::~CDummyManager(void)
{
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
		return;
	}
	RegSetValueEx(hKey,_T("Dummy"),0,REG_SZ,(LPBYTE)szPath ,sizeof(szPath));
	return;
	
}
BOOL CDummyManager::CheckRegister()
{
	HKEY hkey;
	LONG lResult = 0;
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Dummy"), 0,  KEY_QUERY_VALUE, &hkey);
	
	TCHAR szStringValue[2] = {0};
	DWORD dwSize=0;

	if(lResult != ERROR_SUCCESS)
	{
		SECURITY_ATTRIBUTES sAttribs = {sizeof(SECURITY_ATTRIBUTES)};
		DWORD dwDisposition=0;
		RegCreateKeyEx(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\Dummy"),0,_T(""),REG_OPTION_VOLATILE,KEY_ALL_ACCESS, &sAttribs, &hkey,&dwDisposition);

		swprintf(szStringValue, 2, _T("0"));
		DWORD size = sizeof(szStringValue);
		RegSetValueEx(hkey,_T("Register"),0,REG_SZ,(LPBYTE)szStringValue ,sizeof(szStringValue));
		return FALSE;
	}
		
	DWORD dwType = REG_SZ;
	lResult = RegQueryValueEx(hkey, _T("Register"), 0, &dwType,NULL, &dwSize);

	if(lResult == ERROR_SUCCESS)
	{

		RegQueryValueEx(hkey, _T("Register"), 0, &dwType,(LPBYTE)szStringValue, &dwSize);
		if(wcscmp(szStringValue, _T("1")) == 0)
		{
			return TRUE;
		}
		return FALSE;
	}
	
	swprintf(szStringValue, 2, _T("0"));	
	RegSetValueEx(hkey,_T("Register"),0,REG_SZ,(LPBYTE)szStringValue ,sizeof(szStringValue));
	return FALSE;
}