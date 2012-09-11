#pragma once

class CRegistryHelper
{
public:
	CRegistryHelper(void);
	~CRegistryHelper(void);

	VOID SetStartUp();
	BOOL CheckRegister();
	VOID UpdateRegistered(BOOL bIsRegistered);
};
