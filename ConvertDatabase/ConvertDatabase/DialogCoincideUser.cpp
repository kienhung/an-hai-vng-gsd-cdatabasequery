// DialogCoincideUser.cpp : implementation file
//

#include "stdafx.h"
#include "ConvertDatabase.h"
#include "DialogCoincideUser.h"
#include "UserDAO.h"



// CDialogCoincideUser dialog

IMPLEMENT_DYNAMIC(CDialogCoincideUser, CDialog)

CDialogCoincideUser::CDialogCoincideUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogCoincideUser::IDD, pParent)
{

}
CDialogCoincideUser::CDialogCoincideUser(CWnd* pParent ,  CSM_USER* csm_User, BOOL* optionSave)
	: CDialog(CDialogCoincideUser::IDD, pParent)
{
	m_csmUser = csm_User;
	m_optionSave = optionSave;
}

CDialogCoincideUser::~CDialogCoincideUser()
{
}

void CDialogCoincideUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogCoincideUser, CDialog)
	ON_BN_CLICKED(IDOK, &CDialogCoincideUser::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogCoincideUser message handlers

void CDialogCoincideUser::OnBnClickedOk()
{
	//CUserDAO::m_bUpdateUser = true;
	// TODO: Add your control notification handler code here
	OnOK();
}
