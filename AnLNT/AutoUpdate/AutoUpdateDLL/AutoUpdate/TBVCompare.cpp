#include "StdAfx.h"
#include "TBVCompare.h"
#include <shlwapi.h>
#include "MyUtils.h"



CTBVCompare::CTBVCompare( LPCTSTR strNewSource, LPCTSTR strOldSource )
:CGameSourceCompare(strNewSource, strOldSource)
{

}

CTBVCompare::~CTBVCompare(void)
{
}

BOOL CTBVCompare::IsNeedCompare( LPCTSTR strFileName )
{
	PTSTR strSub = ::PathFindFileName(strFileName);
	if (lstrcmpi(strSub, L"config") == 0 ||
		lstrcmpi(strSub, L"setting.kar") == 0)
	{
		if (TRUE == CMyUtils::IsFileInDirectory(strFileName, L"conf"))
		{
			return FALSE;
		}
	}

	return TRUE;
}
