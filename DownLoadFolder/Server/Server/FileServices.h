#pragma once

class CFileServices
{
public:
	CFileServices(void);
	~CFileServices(void);
	unsigned __int64 GetFileSize(HANDLE hFile);
	BOOL IsDirectory(const TCHAR strPath[]);
	BOOL CreateFullPath(TCHAR strFullPath[], size_t uiMaxLength, const TCHAR strRoot[], const TCHAR strName[]);
	BOOL CreateFilesListFilePath(TCHAR strFilesListFilePath[],  size_t uiMaxLength, const TCHAR strRoot[]);
};
