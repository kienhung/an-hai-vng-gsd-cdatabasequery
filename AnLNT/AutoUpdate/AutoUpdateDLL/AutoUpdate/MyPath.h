#pragma once

class CMyPath
{
public:
	CMyPath(void);

	CString TransferSourcePath(LPCTSTR strSource, LPCTSTR strDest, LPCTSTR strFileName);
	CString GetExeFilePath();
	CString GetParentPath(LPCTSTR strFileName);
	BOOL IsDirectory(LPCTSTR strPath);
	CString GetShortFileName(const CString &strLongFileName);

	virtual ~CMyPath(void);
};
