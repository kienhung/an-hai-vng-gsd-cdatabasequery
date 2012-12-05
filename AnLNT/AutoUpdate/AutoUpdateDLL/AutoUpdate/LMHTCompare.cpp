#include "StdAfx.h"
#include "LMHTCompare.h"
#include <shlwapi.h>
#include "MyUtils.h"


CLMHTCompare::CLMHTCompare( LPCTSTR strNewSource, LPCTSTR strOldSource )
:CGameSourceCompare(strNewSource, strOldSource)
{

}

CLMHTCompare::~CLMHTCompare(void)
{
}

BOOL CLMHTCompare::IsNeedCompare( LPCTSTR strFileName )
{
	PTSTR strExtesion = ::PathFindExtension(strFileName);
	if (lstrcmpi(strExtesion, L".log") == 0)
	{
		return FALSE;
	}

	PTSTR strSub = ::PathFindFileName(strFileName);
	if (lstrcmpi(strSub, L"lol.properties") == 0 ||
		lstrcmpi(strSub, L"locale.properties") == 0 ||
		lstrcmpi(strSub, L"locale.cfg") == 0)
	{
		return FALSE;
	}

	if (lstrcmpi(strExtesion, L".properties") == 0 )
	{
		if (TRUE == CMyUtils::IsFileInDirectory(strFileName, L"preferences")
			|| TRUE == CMyUtils::IsFileInDirectory(strFileName, L"global"))	
		{
			return FALSE;
		}
	}

	return TRUE;
}
