#pragma once
#include "TrackingWebApp.h"
#include "vector"
#include <atlbase.h>
#include <comdef.h>
#include <mshtml.h>
#include <UrlHist.h>
#include <afxtempl.h>
#include "WinTabBrowser.h"
using namespace std;


class CTrackingIEBrowser: public CTrackingWebApp
{
private:
	vector<CWinTabBrowser> m_lstWinTab;
	
public:
	
	CTrackingIEBrowser(void);
	~CTrackingIEBrowser(void);
	BOOL GetHistory(vector<STATURL>& lstStatUrl);
	
	//static BOOL CALLBACK enumChildProc(HWND hwnd, LPARAM lParam);
	
	VOID Track();
	
	//static void EnumIETab(const std::wstring &parent_name, HWND hwnd);
	//BOOL CALLBACK EnumWinTabProc(HWND hwnd, LPARAM lParam);

	VOID WriteTrackToFile();
};

