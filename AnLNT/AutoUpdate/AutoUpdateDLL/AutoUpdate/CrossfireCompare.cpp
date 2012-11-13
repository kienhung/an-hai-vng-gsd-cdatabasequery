#include "StdAfx.h"
#include "CrossfireCompare.h"
#include <shlwapi.h>
#include "MyUtils.h"

CCrossfireCompare::CCrossfireCompare( LPCTSTR strNewSource, LPCTSTR strOldSource )
:CGameSourceCompare(strNewSource, strOldSource)
{

}

CCrossfireCompare::~CCrossfireCompare(void)
{
}

BOOL CCrossfireCompare::IsNeedCompare( LPCTSTR strFileName )
{
	PTSTR strExtesion = ::PathFindExtension(strFileName);
	if (lstrcmpi(strExtesion, L".slg") == 0 || lstrcmpi(strExtesion, L".log") == 0)
	{
		return FALSE;
	}
	return TRUE;
}
