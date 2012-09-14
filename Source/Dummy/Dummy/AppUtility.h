#pragma once

class CAppUtility
{
public:
	CAppUtility(void);
	~CAppUtility(void);

	VOID SetStartUp();
	BOOL CheckRegister();
	BOOL CheckCSMExist();
	BOOL UpdateRegistered(BOOL bIsReg);
};
