// PopupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CSMServerSimulator.h"
#include "PopupDlg.h"


// CPopupDlg dialog




CPopupDlg::CPopupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPopupDlg::IDD, pParent)
{

}

CPopupDlg::~CPopupDlg()
{
}

void CPopupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPopupDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON5, &CPopupDlg::OnBnClickedButton5)
END_MESSAGE_MAP()

BOOL CPopupDlg::OnInitDialog()
{

	//RECT popupDialogWindowRect;
	//GetClientRect(&popupDialogWindowRect);

	//int iWidthPopupDialog = popupDialogWindowRect.right - popupDialogWindowRect.left;
	//int iHeightPopupDialog = popupDialogWindowRect.bottom - popupDialogWindowRect.top;

	//CWnd *pMainWnd = theApp.m_pMainWnd;

	//WINDOWPLACEMENT mainDialogPosition;
	//pMainWnd->GetWindowPlacement(&mainDialogPosition);
	//RECT rect;
	//pMainWnd->GetWindowRect(&rect);


	//int iNewXPopupDialog = x + lpwndpos->cx - m_iWidthPopupDialog;
	//int iNewYPopupDialog = y + lpwndpos->cy;

	return TRUE;
}


// CPopupDlg message handlers

void CPopupDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	RECT clientRect;

	GetClientRect(&clientRect);
	::FillRect(dc.m_hDC, &clientRect, (HBRUSH)GetStockObject(GRAY_BRUSH));
}

void CPopupDlg::OnBnClickedButton5()
{
	
}
