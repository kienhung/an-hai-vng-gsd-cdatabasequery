#pragma once
#include "gamesourcecompare.h"

class CSASEACompare :
	public CGameSourceCompare
{
public:
	CSASEACompare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~CSASEACompare(void);
};
