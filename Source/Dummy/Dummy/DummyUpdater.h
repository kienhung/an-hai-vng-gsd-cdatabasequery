#pragma once

class CDummyUpdater
{
public:
	CDummyUpdater(void);
	~CDummyUpdater(void);

	BOOL IsNeedUpdate();
	BOOL StartUpdate();
protected:
	BOOL DeleteTempFolder();
	void StartProcessDummyLaucher(const TCHAR* strPathLaucher);
protected:

	CString m_strTempFolderPath;
};
