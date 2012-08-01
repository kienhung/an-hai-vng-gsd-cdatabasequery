#pragma once
class CFolderRemoving
{

public:

	CFolderRemoving(void);
	~CFolderRemoving(void);

	BOOL IsDirectory(const TCHAR strPath[]);
	BOOL RemoveFile(const TCHAR strPath[]);
	BOOL RemoveFolder(const TCHAR strPath[]);

};
