#include "StdAfx.h"
#include "MyUtility.h"
#include "XUnzip.h"

CMyUtility::CMyUtility(void)
{
}

CMyUtility::~CMyUtility(void)
{
}

BOOL CMyUtility::UnZip( LPCTSTR wcPathIn, LPCTSTR wcExtractObject, LPCTSTR wcPathOut )
{
	HZIP hz;
	int index, numfile;
	ZIPENTRYW ze = {0};
	TCHAR wcFilePath[MAX_PATH] = {0};
	if(!wcPathIn)
		return FALSE;


	hz = OpenZip((void*)wcPathIn, 0, ZIP_FILENAME);
	if (!hz)
		return FALSE;
	GetZipItem(hz, -1, &ze);
	numfile = ze.index;
	for(index = 0; index < numfile; index++)
	{
		GetZipItem(hz, index, &ze);
		if (!wcExtractObject)
		{
			swprintf(wcFilePath, MAX_PATH - 1, _T("%s\\%s"), wcPathOut, ze.name);
			UnzipItem(hz, index, wcFilePath, 0, ZIP_FILENAME);
		}
		else 
		{
			int len = lstrlen(wcExtractObject);
			if (_tcsnicmp(wcExtractObject, ze.name, len) == 0)
			{
				swprintf(wcFilePath, MAX_PATH - 1, _T("%s\\%s"), wcPathOut, ze.name);
				UnzipItem(hz, index, wcFilePath, 0, ZIP_FILENAME);
				//check to know object need to be extracted is file
				if (!(ze.attr & FILE_ATTRIBUTE_DIRECTORY) && len == lstrlen(ze.name))
					break;
			}
		}
	}
	CloseZip(hz);
	return TRUE;

	return TRUE;
}
