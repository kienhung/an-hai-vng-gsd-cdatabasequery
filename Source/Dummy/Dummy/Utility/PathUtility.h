#pragma once

class CPathUtility
{
public:
	CPathUtility(void);
	~CPathUtility(void);

	static CString GetExeDirectory();
	static BOOL IsPathDirectory(LPCTSTR strPath);
};
