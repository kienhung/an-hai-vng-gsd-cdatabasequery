#pragma once
#include "foldercompare.h"
#include <vector>
using namespace std;

class CGameSourceCompare :
	public CFolderCompare
{
protected:
	vector<CString> lstFilesNoCheck;
	CString m_strResultFilePath;
	BOOL m_bHasUpdate;
	CString m_strGamePatchDirectory;

protected:
	BOOL Init();
	virtual BOOL IsNeedCompare(LPCTSTR strFileName);
	virtual BOOL ProcessFile(LPCTSTR strFileName);
	virtual BOOL IsUnnecessaryToCheckForAllGames(LPCTSTR strFileName);

	BOOL IsFileInListFilesNoCheck(LPCTSTR strFileName);
public:
	CGameSourceCompare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~CGameSourceCompare(void);
	virtual BOOL Compare(LPCTSTR strResultFilePath);
	BOOL HasUpdate();
	BOOL DeleteResultFile();
};
