#include "StdAfx.h"
#include "HTDCompare.h"
#include <algorithm>
#include <shlwapi.h>

CHTDCompare::CHTDCompare( LPCTSTR strNewSource, LPCTSTR strOldSource )
:CGameSourceCompare(strNewSource, strOldSource)

{
	LPCTSTR arrFilesNoCheck[] = {L"flist.xml", L"feeling.ini", L"pluginadr.txt", L"config.ini", L"game.ini"};
	int iCount = sizeof(arrFilesNoCheck)/sizeof(arrFilesNoCheck[0]);

	lstFilesNoCheck.assign(arrFilesNoCheck, arrFilesNoCheck + iCount);
}

CHTDCompare::~CHTDCompare(void)
{

}

BOOL CHTDCompare::IsNeedCompare( LPCTSTR strFileName )
{
	CString strSubFileName = ::PathFindFileName(strFileName);
	vector<CString>::iterator it = find (lstFilesNoCheck.begin(), lstFilesNoCheck.end(), strSubFileName);

	if (it != lstFilesNoCheck.end())
	{
		return FALSE;
	}

	return TRUE;
}
