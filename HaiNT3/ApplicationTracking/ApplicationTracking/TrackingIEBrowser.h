#pragma once
#include "TrackingWebApp.h"
#include "vector"
#include <atlbase.h>
#include <comdef.h>
#include <mshtml.h>
#include <UrlHist.h>
#include <afxtempl.h>
using namespace std;


class CTrackingIEBrowser: public CTrackingWebApp
{
private:
	vector<TAB_WEB> m_lstTabWeb;
	vector<CString> m_lstTitle;
	
public:
	
	CTrackingIEBrowser(void);
	~CTrackingIEBrowser(void);
	BOOL GetHistory(vector<STATURL>& lstStatUrl);
	static BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam);
	//static BOOL CALLBACK enumChildProc(HWND hwnd, LPARAM lParam);
	
	VOID Track();
};

