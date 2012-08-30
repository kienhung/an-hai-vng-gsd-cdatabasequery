#pragma once

class CPathUtility
{
public:
	CPathUtility(void);
	virtual ~CPathUtility(void);

	CString GetExeFilePath();
	CString GetParentPath(LPCTSTR strFileName);
	CString GetShortFileName(const CString &strLongFileName);

	BOOL IsDirectory(LPCTSTR strFileName);
	BOOL IsFileExist(LPCTSTR strFileName);
};
