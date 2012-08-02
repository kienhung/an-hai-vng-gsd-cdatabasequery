#pragma once


class CFolderCloner
{
protected:
	CString m_strSource;
	CString m_strDest;
	CString m_strFolderName;
public:

	CFolderCloner(LPCTSTR strSource, LPCTSTR strDest, LPCTSTR m_strFolderName);

	virtual ~CFolderCloner(void);
	BOOL Clone();
protected:

	BOOL RemoveFolderIfExist();
	BOOL RecursivelyCopyFile(LPCTSTR strFileName);
	BOOL CustomCreateDirectory(LPCTSTR strFileName);
	BOOL CustomCopyFile(LPCTSTR strFileName);

	HANDLE GetFindHandle( LPCTSTR strFileName, WIN32_FIND_DATA *pFindFileData );


};
