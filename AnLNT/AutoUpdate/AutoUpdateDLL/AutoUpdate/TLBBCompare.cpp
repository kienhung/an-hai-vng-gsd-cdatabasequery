#include "StdAfx.h"
#include "TLBBCompare.h"
#include "MyUtils.h"
#include <shlwapi.h>

CTLBBCompare::CTLBBCompare(LPCTSTR strNewSource, LPCTSTR strOldSource)
:CGameSourceCompare(strNewSource, strOldSource)
{
}

CTLBBCompare::~CTLBBCompare(void)
{
}

BOOL CTLBBCompare::IsNeedCompare( LPCTSTR strFileName )
{
	if (TRUE == CMyUtils::IsFileInDirectory(strFileName, L"Patch"))
	{
		PTSTR strExtesion = ::PathFindExtension(strFileName);
		if (lstrcmpi(strExtesion, L".txt") == 0 || lstrcmpi(strExtesion, L".xzip") == 0)
		{
			return FALSE;
		}
	}
	return TRUE;
}
