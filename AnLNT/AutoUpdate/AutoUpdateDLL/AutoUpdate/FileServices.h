#pragma once

class CFileServices
{
protected:
	TCHAR *m_ptcParentPath;
public:
	CFileServices(void);
	~CFileServices(void);

	unsigned __int64 GetFileSize(HANDLE hFile);
	BOOL IsDirectory(const TCHAR strPath[]);
	BOOL CreateFullPath(TCHAR strFullPath[], size_t uiMaxLength, const TCHAR strRoot[], const TCHAR strName[]);
	BOOL CustomCreateDirectory(const TCHAR *strPath);
	CString GetShortFileName(const CString &strLongFileName);
	const TCHAR * GetParentPath(const TCHAR strPath[]);
};
