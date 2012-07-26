// CustomGroupBox.cpp : implementation file
//

#include "stdafx.h"
#include "WebBrower.h"
#include "CustomGroupBox.h"


// CCustomGroupBox

IMPLEMENT_DYNAMIC(CCustomGroupBox, CStatic)

CCustomGroupBox::CCustomGroupBox()
{
}

CCustomGroupBox::~CCustomGroupBox()
{
}


BEGIN_MESSAGE_MAP(CCustomGroupBox, CStatic)
END_MESSAGE_MAP()



// CCustomGroupBox message handlers

void CCustomGroupBox::SetWebBrowser(CIe_WebBrower* web)
{
	m_IeBrowser = web;
}
void CCustomGroupBox::LoadWeb()
{
	
	//CIe_WebBrower* temp =  (CIe_WebBrower*)GetDlgItem(IDC_IE_WEBBROWER);
	m_hThread = CreateThread( NULL, 0, ThreadLoadWebPageChildControl, m_IeBrowser, 0, NULL);
}

DWORD WINAPI CCustomGroupBox::ThreadLoadWebPageChildControl( LPVOID lpParam )
{
	CIe_WebBrower* e = (CIe_WebBrower*)lpParam;
	e->Navigate(_T("http://www.asus.com/"), NULL, NULL, NULL, NULL);
	return 0;
}