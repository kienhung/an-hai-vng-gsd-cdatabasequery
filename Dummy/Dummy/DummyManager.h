#pragma once
#include "StdAfx.h"
#include "resource.h"
#include "DummyDlg.h"

class CDummyManager
{
private:
	CRegisterInfoDlg* m_pDlgRegInfo;

public:
	CDummyManager(void);
	CDummyManager(CRegisterInfoDlg* pDlgRegInfo);
	~CDummyManager(void);

	VOID Execute();
	VOID StartUp();
	BOOL CheckRegister();
	static VOID UpdateRegistered(BOOL bIsRegistered);
	
};
