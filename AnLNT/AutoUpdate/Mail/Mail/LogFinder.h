#pragma once
#include <FolderProcesser.h>
#include <string>
#include <vector>
using namespace std;

class CLogFinder
	:public CFolderProcesser
{
public:
	CLogFinder(void);
	~CLogFinder(void);
	string GetLastLogFile(LPCTSTR strLogDirectory);

protected:
	virtual BOOL ProcessFile(LPCTSTR strFileName);
protected:
	string m_strLastLog;
	vector<CString> lstLog;
	FILETIME m_ftMaxWriteName;
};
