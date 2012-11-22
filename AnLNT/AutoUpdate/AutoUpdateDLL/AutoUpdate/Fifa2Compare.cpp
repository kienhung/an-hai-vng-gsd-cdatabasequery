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
	//CString strTemp = strFileName;
	//if (strTemp.Find(L"GameGuard") != -1)
	//{
	//	PTSTR strExtesion = ::PathFindExtension(strFileName);
	//	if (lstrcmpi(strExtesion, L".erl") == 0 || lstrcmpi(strExtesion, L".des") == 0)
	//	{
	//		return FALSE;
	//	}

	//	PTSTR strSub = ::PathFindFileName(strFileName);
	//	if (lstrcmpi(strSub, L"FIFAOnline2VN.ini") == 0)
	//	{
	//		return FALSE;
	//	}
	//}

	if (TRUE == CMyUtils::IsFileInDirectory(strFileName, L"GameGuard"))
	{
		return FALSE;
	}
	return TRUE;
}
