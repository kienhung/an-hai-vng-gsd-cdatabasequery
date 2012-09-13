#pragma once
#include "FolderProcesser.h"
class CFolderDeleter : public CFolderProcesser
{

public:

	CFolderDeleter(void);
	~CFolderDeleter(void);
	BOOL Delete(const TCHAR strPath[]);

protected:
	virtual BOOL ProcessFile(LPCTSTR strFileName);
	virtual BOOL PostProcessFolder(LPCTSTR strFolderName);
};
