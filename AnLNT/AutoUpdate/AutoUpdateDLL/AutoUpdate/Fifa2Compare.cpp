#include "StdAfx.h"
#include "Fifa2Compare.h"
#include <shlwapi.h>
#include "MyUtils.h"


CFifa2Compare::CFifa2Compare( LPCTSTR strNewSource, LPCTSTR strOldSource )
:CGameSourceCompare(strNewSource, strOldSource)
{
	
}

CFifa2Compare::~CFifa2Compare(void)
{
}

BOOL CFifa2Compare::IsNeedCompare( LPCTSTR strFileName )
{
	if (TRUE == CMyUtils::IsFileInDirectory(strFileName, L"GameGuard"))
	{
		return FALSE;
	}
	return TRUE;
}
