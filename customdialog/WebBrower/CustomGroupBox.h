#pragma once
#include "resource.h"
#include "ie_webbrower.h"

// CCustomGroupBox

class CCustomGroupBox : public CStatic
{
	DECLARE_DYNAMIC(CCustomGroupBox)

public:
	CCustomGroupBox();
	virtual ~CCustomGroupBox();
	static DWORD WINAPI ThreadLoadWebPageChildControl( LPVOID lpParam );
	void LoadWeb();
	void SetWebBrowser(CIe_WebBrower* web);
protected:
	HANDLE m_hThread;
	DECLARE_MESSAGE_MAP()
	
	CIe_WebBrower* m_IeBrowser;
	
};


