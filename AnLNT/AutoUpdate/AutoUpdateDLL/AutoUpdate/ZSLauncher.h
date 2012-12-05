#pragma once
#include "AHKLauncher.h"
class CZSLauncher
	: public CAHKLauncher
{
public:
	CZSLauncher(LPCTSTR strSource, LPCTSTR strGameAlias);
	virtual CGameSourceCompare * GetComparer (LPCTSTR strNewSource, LPCTSTR strOldSource);
	~CZSLauncher(void);
};
