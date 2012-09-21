#include "StdAfx.h"
#include "Registry.h"

#define REG_PATH_DEFAULT	_T("SOFTWARE\\TekWaveSolutions\\CyberStationManager\\Data")

CRegistry::CRegistry(void)
{
	m_hRootKey = HKEY_LOCAL_MACHINE;
	m_strSubKey = REG_PATH_DEFAULT;
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
* Output	DWORD &dwData:		The registry value's data (in DWORD)
* Return value:	TRUE if successful; otherwise FALSE
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
* Output	LPTSTR lpBufData:	The registry value's data (in String)
*			int iBufSize:		The size of the lpBufData buffer, in TCHARs
* Return value:	TRUE if successful; otherwise FALSE
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
* Return value:	TRUE if successful; otherwise FALSE
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
* Output	LPTSTR lpBufData:	The registry value's data (in String)
* Return value:	TRUE if successful; otherwise FALSE
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

BOOL CRegistry::ClearIEHistory()
{
	HKEY hKey;

	if (RegOpenKeyEx(HKEY_CURRENT_USER,
					_T("Software\\Microsoft\\Internet Explorer\\TypedURLs"),
					0,
					KEY_ALL_ACCESS,
					&hKey) == ERROR_SUCCESS)
	{
		TCHAR strValName[1024] = {0};
		DWORD dwValueNameSize = _countof(strValName);
		DWORD dwType;
		LONG lResult;

		lResult = RegEnumValue(	hKey, 0, strValName, &dwValueNameSize,
								0, &dwType, NULL, NULL);

		while (lResult == ERROR_SUCCESS)
		{
			RegDeleteValue(hKey, strValName);

			dwValueNameSize = _countof(strValName);
			ZeroMemory(strValName, dwValueNameSize*sizeof(TCHAR));

			lResult = RegEnumValue(	hKey, 0, strValName, &dwValueNameSize,
									0, &dwType, NULL, NULL);
		}

		RegCloseKey(hKey);

		return TRUE;
	}

	return FALSE;
}