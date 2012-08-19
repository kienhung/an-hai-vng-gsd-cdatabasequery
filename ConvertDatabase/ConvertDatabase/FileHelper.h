#pragma once

class CFileHelper
{
public:
	CFileHelper(void);
	~CFileHelper(void);

	static BOOL CopyAndRenameFolder(const TCHAR* strSourceDir, const TCHAR* strDestDir, const TCHAR* strNewFolderName);
	static BOOL CopyFolder(const TCHAR* strSourceDir, const TCHAR* strDestDir);
	static BOOL CopyFolderProcess(const TCHAR* strSourceDir, const TCHAR* strDestDir);
	static BOOL DeleteFolder(const TCHAR* strFilePath);
};
