// UIThreadDialog.cpp : implementation file
//

#include "stdafx.h"
#include "WebBrowser.h"
#include "UIThreadDialog.h"


// CUIThreadDialog dialog

IMPLEMENT_DYNAMIC(CUIThreadDialog, CDialog)

CUIThreadDialog::CUIThreadDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CUIThreadDialog::IDD, pParent)
{

}

CUIThreadDialog::~CUIThreadDialog()
{
}

void CUIThreadDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_explorer);
}


BEGIN_MESSAGE_MAP(CUIThreadDialog, CDialog)
END_MESSAGE_MAP()

BOOL CUIThreadDialog::OnInitDialog()
{
	m_explorer.Navigate(L"asus.com", NULL, NULL, NULL, NULL);
	return TRUE;
}


// CUIThreadDialog message handlers
