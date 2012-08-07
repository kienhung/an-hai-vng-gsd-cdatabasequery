#pragma once
#include "FolderProcesser.h"


class CFolderCloner : public CFolderProcesser
{
protected:
	CString m_strSource;
	CString m_strDest;
	CString m_strFolderName;
public:

	CFolderCloner(LPCTSTR strSource, LPCTSTR strDest, LPCTSTR strFolderName);
	virtual ~CFolderCloner(void);

	BOOL Clone();
protected:

	virtual BOOL PreProcessFoler(LPCTSTR strFolderName);
	virtual BOOL ProcessFile(LPCTSTR strFileName);

};
