#include "StdAfx.h"
#include "AppUtility.h"
#include "Registry.h"
#include "MyDefine.h"

CAppUtility::CAppUtility(void)
{
}

CAppUtility::~CAppUtility(void)
{
}

VOID CAppUtility::SetStartUp()
{
	TCHAR szPath[MAX_PATH] = {0};
	DWORD dwSize=0;
	GetModuleFileName(NULL, szPath, MAX_PATH);
	
	CRegistry reg(HKEY_LOCAL_MACHINE, REG_STARTUP);
	reg.SaveValue(REG_VALUE_NAME_STARTUP, szPath);
}

BOOL CAppUtility::CheckRegister()
{
	return FALSE;
}