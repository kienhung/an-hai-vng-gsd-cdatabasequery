#pragma once

class CFolderProcesser
{
public:

	CFolderProcesser(void);
	virtual ~CFolderProcesser(void);

protected:
	virtual BOOL Process(LPCTSTR strSourcePath);
	virtual BOOL ProcessFile(LPCTSTR strFileName);
	virtual BOOL ProcessFolder(LPCTSTR strFolderName);
	virtual BOOL PreProcessFoler(LPCTSTR strFolderName);
	virtual BOOL PostProcessFolder(LPCTSTR strFolderName);

	HANDLE GetFindHandle( LPCTSTR strFolderName, WIN32_FIND_DATA *pFindFileData );
};
