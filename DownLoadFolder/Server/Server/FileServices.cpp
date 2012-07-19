#include "StdAfx.h"
#include "FileServices.h"

CFileServices::CFileServices(void)
{
}

CFileServices::~CFileServices(void)
{
}

unsigned __int64 CFileServices::GetFileSize(HANDLE hFile) {

	if (INVALID_HANDLE_VALUE != hFile) {

		LARGE_INTEGER bigIntFileSize;
		if (FALSE == ::GetFileSizeEx(hFile, &bigIntFileSize)) {
			return 0;
		}
		return bigIntFileSize.QuadPart;
	}
	return 0;
}
