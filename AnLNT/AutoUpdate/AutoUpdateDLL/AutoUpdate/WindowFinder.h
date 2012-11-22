#pragma once

#include <vector>
using namespace std;

class CWindowFinder
{
protected:
	CString m_strWindowName;
	CString m_strClassName;
	vector<HWND> m_vResultWnd;

public:
	CWindowFinder(void);
	virtual ~CWindowFinder(void);

	vector<HWND> GetListWindow(LPCTSTR strClassName, LPCTSTR strWindowName);
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
};
