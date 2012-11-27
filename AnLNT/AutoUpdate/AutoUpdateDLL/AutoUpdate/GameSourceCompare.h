#pragma once
#include "foldercompare.h"

class CGameSourceCompare :
	public CFolderCompare
{
protected:
	CString m_strResultFilePath;
	BOOL m_bHasUpdate;

protected:
	BOOL Init();
	virtual BOOL IsNeedCompare(LPCTSTR strFileName);
	virtual BOOL ProcessFile(LPCTSTR strFileName);
	virtual BOOL IsUnnecessaryToCheckForAllGames(LPCTSTR strFileName);
public:
	CGameSourceCompare(LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual ~CGameSourceCompare(void);
	virtual BOOL Compare(LPCTSTR strResultFilePath);
	BOOL HasUpdate();
	BOOL DeleteResultFile();
};
