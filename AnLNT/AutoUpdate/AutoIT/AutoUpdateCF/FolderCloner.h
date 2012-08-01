#pragma once

class CFolderCloner
{
protected:
	CString m_strSource;
	CString m_strDest;
public:

	CFolderCloner(LPCTSTR strSource, LPCTSTR strDest);
	virtual ~CFolderCloner(void);
	BOOL Clone();
};
