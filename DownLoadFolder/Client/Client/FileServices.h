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
	BOOL CreateFilesListFilePath(TCHAR strFilesListFilePath[],  size_t uiMaxLength, const TCHAR strRoot[]);
	BOOL CustomCreateDirectory(const TCHAR *strPath);
	const TCHAR * GetParentPath(const TCHAR strPath[]);
};
