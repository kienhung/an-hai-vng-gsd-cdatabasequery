#pragma once
#include "gamesourcecompare.h"
#include <vector>

using namespace std;

class CHTDCompare :
	public CGameSourceCompare
{
protected:
	
	virtual BOOL IsNeedCompare(LPCTSTR strFileName);
public:
	CHTDCompare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~CHTDCompare(void);
};
