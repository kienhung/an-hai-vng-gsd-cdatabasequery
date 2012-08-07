#pragma once
#include "FolderProcesser.h"
class CFolderRemoving : public CFolderProcesser
{

public:

	CFolderRemoving(void);
	~CFolderRemoving(void);
	BOOL Remove(const TCHAR strPath[]);
protected:
	virtual BOOL ProcessFile(LPCTSTR strFileName);
	virtual BOOL PostProcessFolder(LPCTSTR strFolderName);
/*
	BOOL IsDirectory(const TCHAR strPath[]);
	BOOL RemoveFile(const TCHAR strPath[]);
	BOOL RemoveFolder(const TCHAR strPath[]);
*/
};
