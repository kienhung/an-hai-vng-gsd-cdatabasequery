#pragma once
#include <vector>

using namespace std;

class CLogFileInfo
{

protected:

	CString m_strFileName;
	FILETIME m_ftWriteTime;

	vector<CLogFileInfo> m_vFileInfo;

public:
	CLogFileInfo(void);
	virtual ~CLogFileInfo(void);

	//static vector<CLogFileInfo> ListAll(LPCTSTR strDirectory);

protected:
	void Init();
	const static int NUM_FILES = 100;
};
