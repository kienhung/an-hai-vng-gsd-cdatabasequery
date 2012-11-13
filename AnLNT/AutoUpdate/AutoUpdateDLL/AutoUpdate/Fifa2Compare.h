#pragma once
#include "gamesourcecompare.h"

class CFifa2Compare :
	public CGameSourceCompare
{
protected:
	virtual BOOL IsNeedCompare(LPCTSTR strFileName);

public:
	CFifa2Compare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~CFifa2Compare(void);
};
