#pragma once

class CFileUtility
{
public:
	CFileUtility(void);
	~CFileUtility(void);

	BOOL GetFileSize(LPCTSTR strFileName, unsigned __int64 *pui64FileSize);
	BOOL GetFileSize(HANDLE hFile, unsigned __int64 *pui64FileSize );

};
