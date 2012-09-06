#include "StdAfx.h"
#include "DummyManager.h"

CDummyManager::CDummyManager(void)
{
}

CDummyManager::~CDummyManager(void)
{
}

BOOL CheckRegister()
{
	HKEY hkey;
	LONG lResult;
	lResult = RegOpenKey(HKEY_LOCAL_MACHINE,_T("Software\\Dummy"),&hkey);

	TCHAR szStringValue[2] = {0};
	DWORD dwSize=2;

	if(lResult != ERROR_SUCCESS)
	{
		
		SECURITY_ATTRIBUTES sAttribs = {sizeof(SECURITY_ATTRIBUTES)};
		DWORD dwDisposition=0;
		RegCreateKeyEx(HKEY_LOCAL_MACHINE,_T("Software\\Dummy"),0,_T(""),REG_OPTION_VOLATILE,KEY_ALL_ACCESS, &sAttribs, &hkey,&dwDisposition);

		swprintf(szStringValue, 2, _T("1"));
		
		RegSetValueEx(hkey,_T("Register"),0,REG_SZ,(LPBYTE)szStringValue ,sizeof(szStringValue));
		return FALSE;
	}
		
	DWORD dwType=REG_SZ;

	lResult = RegQueryValueEx(hkey, TEXT("Register"), NULL, &dwType,(LPBYTE)&szStringValue, &dwSize);
	if(lResult == ERROR_SUCCESS)
	{
		if(wcscmp(szStringValue, _T("1")) == 0)
		{
			return TRUE;
		}
		return FALSE;
	}
	
	swprintf(szStringValue, 2, _T("1"));	
	RegSetValueEx(hkey,_T("Register"),0,REG_SZ,(LPBYTE)szStringValue ,sizeof(szStringValue));
	return FALSE;
}