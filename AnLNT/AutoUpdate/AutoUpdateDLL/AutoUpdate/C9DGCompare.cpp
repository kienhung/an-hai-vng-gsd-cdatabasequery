#include "StdAfx.h"
#include "C9DGCompare.h"
#include <shlwapi.h>
#include <algorithm>


C9DGCompare::C9DGCompare( LPCTSTR strNewSource, LPCTSTR strOldSource )
:CGameSourceCompare(strNewSource, strOldSource)
{
	LPCTSTR arrFilesNoCheck[] = {L"config.xml", L"ndreg.xrg"};
	int iCount = sizeof(arrFilesNoCheck)/sizeof(arrFilesNoCheck[0]);

	lstFilesNoCheck.assign(arrFilesNoCheck, arrFilesNoCheck + iCount);
}

C9DGCompare::~C9DGCompare(void)
{
}

BOOL C9DGCompare::IsNeedCompare( LPCTSTR strFileName )
{
	if (IsFileInListFilesNoCheck(strFileName))
	{
		return FALSE;
	}

	return TRUE;
}
