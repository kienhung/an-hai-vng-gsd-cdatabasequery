#include "StdAfx.h"
#include "RegistryHelper.h"

CRegistryHelper::CRegistryHelper(void)
{
}

CRegistryHelper::~CRegistryHelper(void)
{
}


TCHAR* CRegistryHelper::GetValueRegistry(const TCHAR* strSubKey, const TCHAR* strKeyName)
{
	TCHAR* pstrValue = NULL;
	
	HKEY hKey;
	LONG lResult = 0;
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, strSubKey, 0,  KEY_ALL_ACCESS, &hKey);

	if(lResult != ERROR_SUCCESS)
	{
		return NULL;
	}
	DWORD dwSize=0;
	DWORD dwType = REG_SZ;
	lResult = RegQueryValueEx(hKey, strKeyName, 0, &dwType, NULL, &dwSize);
	
	if(lResult == ERROR_SUCCESS)
	{
		pstrValue = new TCHAR[dwSize];
		RegQueryValueEx(hKey, strKeyName, 0, &dwType,(LPBYTE)pstrValue, &dwSize);
		RegCloseKey(hKey);
		return pstrValue;
	}
	return pstrValue;
}

BOOL CRegistryHelper::SetValueRegistry(const TCHAR* strSubKey, const TCHAR* strKeyName, const TCHAR* strValue)
{
	HKEY hKey;
	LONG lResult = 0;
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, strSubKey, 0,  KEY_ALL_ACCESS, &hKey);

	if(lResult != ERROR_SUCCESS)
	{
		return FALSE;
	}
	RegSetValueEx(hKey,strKeyName,0,REG_SZ,(LPBYTE)strValue ,sizeof(TCHAR) * wcslen(strValue));
	RegCloseKey(hKey);
	return TRUE;
}

BOOL CRegistryHelper::SetValueRegistryEx(const TCHAR* strSubKey, const TCHAR* strKeyName, const TCHAR* strValue)
{
	HKEY hKey;
	LONG lResult = 0;
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, strSubKey, 0,  KEY_ALL_ACCESS, &hKey);

	if(lResult != ERROR_SUCCESS)
	{
		SECURITY_ATTRIBUTES sAttribs = {sizeof(SECURITY_ATTRIBUTES)};
		DWORD dwDisposition=0;
		lResult = RegCreateKeyEx(HKEY_LOCAL_MACHINE, strSubKey, 0, _T(""),REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &sAttribs, &hKey,&dwDisposition);
		if(lResult != ERROR_SUCCESS)
			return FALSE;
	}
	RegSetValueEx(hKey,strKeyName,0,REG_SZ,(LPBYTE)strValue ,sizeof(TCHAR) * wcslen(strValue));
	RegCloseKey(hKey);
	return TRUE;
}


VOID CRegistryHelper::SetStartUp()
{	
	TCHAR szPath[MAX_PATH] = {0};
	TCHAR* szStringValue = NULL;
	DWORD dwSize=0;
	GetModuleFileName(NULL, szPath, MAX_PATH);
	
	szStringValue = GetValueRegistry(TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), _T("Dummy"));
	if(NULL == szStringValue || wcscmp(szPath, szStringValue) != 0)
	{
		SetValueRegistry(TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), _T("Dummy"), szPath);
	}
	if(NULL != szStringValue)
	{
		delete szStringValue;
	}
	return;
}

BOOL CRegistryHelper::CheckRegister()
{
	
	
	HKEY hKey;
	LONG lResult = 0;
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Dummy\\Data"), 0,  KEY_ALL_ACCESS, &hKey);
	
	TCHAR szStringValue[2] = {0};
	DWORD dwSize=0;

	if(lResult != ERROR_SUCCESS)
	{
		SECURITY_ATTRIBUTES sAttribs = {sizeof(SECURITY_ATTRIBUTES)};
		DWORD dwDisposition=0;
		RegCreateKeyEx(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\Dummy\\Data"),0,_T(""),REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &sAttribs, &hKey,&dwDisposition);

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

VOID CRegistryHelper::UpdateRegistered(BOOL bIsRegistered)
{
	TCHAR szStringValue[2] = {0};
	if(bIsRegistered)
	{
		swprintf(szStringValue, 2, _T("1"));
	}
	else
		swprintf(szStringValue, 2, _T("0"));

	SetValueRegistryEx(_T("SOFTWARE\\Dummy\\Data"), _T("Registered"), szStringValue);
}