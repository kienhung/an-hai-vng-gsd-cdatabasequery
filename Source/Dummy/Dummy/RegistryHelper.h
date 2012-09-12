#pragma once

class CRegistryHelper
{
public:
	CRegistryHelper(void);
	~CRegistryHelper(void);

	VOID SetStartUp();
	BOOL CheckRegister();
	VOID UpdateRegistered(BOOL bIsRegistered);
	TCHAR* GetValueRegistry(const TCHAR* strSubKey, const TCHAR* strKeyName);
	BOOL SetValueRegistry(const TCHAR* strSubKey, const TCHAR* strKeyName, const TCHAR* strValue);
	BOOL SetValueRegistryEx(const TCHAR* strSubKey, const TCHAR* strKeyName, const TCHAR* strValue);

};
