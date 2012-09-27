#include "StdAfx.h"
#include "AppUtility.h"
#include "Registry.h"
#pragma warning(disable: 4996)

CAppUtility::CAppUtility(void)
{
}

CAppUtility::~CAppUtility(void)
{
}

VOID CAppUtility::SetStartUp()
{
	TCHAR szPath[MAX_PATH] = {0};
	TCHAR szVale[MAX_PATH] = {0};
	DWORD dwSize=0;
	GetModuleFileName(NULL, szPath, MAX_PATH);
	
	_stprintf(szVale, _T("\"%s\" /autostart"), szPath);
	CRegistry reg(HKEY_LOCAL_MACHINE, REG_STARTUP);
	reg.SaveValue(REG_VALUE_NAME_STARTUP, szVale);
}

BOOL CAppUtility::CheckRegister()
{
	TCHAR strInfo[MAX_PATH] = {0};
	CRegistry reg(HKEY_LOCAL_MACHINE, REG_REGISTER_INFO);
	if(reg.ReadValue(REG_VALUE_NAME_REGINFO, strInfo, MAX_PATH))
	{
		if(wcscmp(_T("1"), strInfo) == 0)
		{
			return TRUE;
		}
	}else
	{
		if(reg.CreateKey(HKEY_LOCAL_MACHINE, REG_REGISTER_INFO))
		{
			reg.SaveValue(REG_VALUE_NAME_REGINFO, _T("0"));
			return FALSE;
		}
	}
	return FALSE;
}
BOOL CAppUtility::CheckCSMExist()
{
	HKEY hKey;
	LONG lResult = 0;
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_PATH_INSTALL, 0,  KEY_ALL_ACCESS, &hKey);
	if(lResult == ERROR_SUCCESS)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CAppUtility::UpdateRegistered(BOOL bIsReg)
{
	TCHAR strInfo[MAX_PATH] = {0};
	swprintf(strInfo, MAX_PATH, _T("%d"), bIsReg);
	CRegistry reg(HKEY_LOCAL_MACHINE, REG_REGISTER_INFO);
	return reg.SaveValue(REG_VALUE_NAME_REGINFO, strInfo);
}