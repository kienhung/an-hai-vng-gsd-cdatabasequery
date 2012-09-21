#include "StdAfx.h"
#include "Registry.h"

#define REG_PATH_DEFAULT	_T("SOFTWARE\\TekWaveSolutions\\CyberStationManager\\ServerData")

CRegistry::CRegistry(void)
{
	m_hRootKey = HKEY_LOCAL_MACHINE;
	m_strSubKey = REG_PATH_DEFAULT;
}

CRegistry::CRegistry(HKEY hRootKey, const TCHAR *pcSubKey)
{
	m_hRootKey = hRootKey;
	m_strSubKey = pcSubKey;
}

CRegistry::~CRegistry(void)
{
}

void CRegistry::SetKey(HKEY hRootKey, const TCHAR *pcSubKey)
{
	m_hRootKey = hRootKey;
	m_strSubKey = pcSubKey;
}

/****************************************************************************
* Description: Read a DWORD value from the registry 
* Input:	LPCTSTR lpValName:	The name of the registry value
* Output:	DWORD &dwData:		The registry value's data (in DWORD)
* Return:	TRUE if successful; otherwise FALSE
* Revision History:
*		08/14/09	Author: DiepTH 
*****************************************************************************/
BOOL CRegistry::ReadValue(LPCTSTR lpValName, DWORD &dwData)
{
	HKEY	hKey;
	DWORD	dwcbData = sizeof(dwData);

	if (RegOpenKeyEx(m_hRootKey, m_strSubKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		return FALSE;

	if (RegQueryValueEx(hKey, 
						lpValName,
						NULL, NULL,
						(LPBYTE)&dwData, 
						&dwcbData) != ERROR_SUCCESS )
	{
		dwData = -1;
		RegCloseKey(hKey);
		return FALSE;
	}

	RegCloseKey(hKey);

	return TRUE;
}

/****************************************************************************
* Description: Read a String value from the registry 
* Input:	LPCTSTR lpValName:	The name of the registry value
* Output:	LPTSTR lpBufData:	The registry value's data (in String)
*			int iBufSize:		The size of the lpBufData buffer, in TCHARs
* Return:	TRUE if successful; otherwise FALSE
* Revision History:
*		08/14/09	Author: DiepTH 
*****************************************************************************/
BOOL CRegistry::ReadValue(LPCTSTR lpValName, LPTSTR lpBufData, int iBufSize)
{
	HKEY	hKey;
	DWORD	dwcbData = iBufSize * sizeof(TCHAR);

	if (RegOpenKeyEx(m_hRootKey, m_strSubKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		return FALSE;

	if (RegQueryValueEx(hKey, 
						lpValName,
						NULL, NULL,
						(LPBYTE)lpBufData, 
						&dwcbData) != ERROR_SUCCESS )
	{
		RegCloseKey(hKey);
		return FALSE;
	}

	RegCloseKey(hKey);

	return TRUE;
}

/****************************************************************************
* Description: Write a DWORD value to the registry
* Input:	LPCTSTR lpValName:	The name of the registry value
*			DWORD &dwData:		The registry value's data (in DWORD)
* Output:	None
* Return:	TRUE if successful; otherwise FALSE
* Revision History:
*		08/14/09	Author: DiepTH
*****************************************************************************/
BOOL CRegistry::SaveValue(LPCTSTR lpValName, DWORD &dwData)
{
	HKEY hKey;

	if (RegOpenKeyEx(m_hRootKey, m_strSubKey, 0, KEY_WRITE, &hKey) != ERROR_SUCCESS)
		return FALSE;

	if (RegSetValueEx(	hKey,		
						lpValName,		
						NULL,					
						REG_DWORD,				
						(LPBYTE)&dwData,
						sizeof(dwData)) != ERROR_SUCCESS)
	{	
		RegCloseKey(hKey);
		return FALSE;
	}

	RegCloseKey(hKey);
	return TRUE;
}

/****************************************************************************
* Description: Write a String value to the registry 
* Input:	LPCTSTR lpValName:	The name of the registry value
*			LPTSTR lpData:	The registry value's data (in String)
* Output:	None
* Return:	TRUE if successful; otherwise FALSE
* Revision History:
*		08/14/09	Author: DiepTH
*****************************************************************************/
BOOL CRegistry::SaveValue(LPCTSTR lpValName, LPCTSTR lpData)
{
	HKEY hKey;

	if (RegOpenKeyEx(m_hRootKey, m_strSubKey, 0, KEY_WRITE, &hKey) != ERROR_SUCCESS)
		return FALSE;

	if (RegSetValueEx(	hKey,		
						lpValName,		
						NULL,		
						REG_SZ,			
						(LPBYTE)lpData,
						_tcslen(lpData)*sizeof(TCHAR)) != ERROR_SUCCESS)
	{	
		RegCloseKey(hKey);
		return FALSE;
	}

	RegCloseKey(hKey);
	return TRUE;
}

BOOL CRegistry::CreateKey(HKEY hRootKey, const TCHAR *pcSubKey)
{
	HKEY hKey;
	LONG lRet;

	if (RegCreateKeyEx(hRootKey, pcSubKey, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, NULL) == ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return TRUE;
	}

	return FALSE;
}
