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
	~CDummyManager(void);

	BOOL CheckRegister();
	
};
