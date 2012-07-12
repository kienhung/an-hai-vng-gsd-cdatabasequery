// KetNoiDlg.cpp : implementation file
//
#pragma once
#include "stdafx.h"
#include "QuanLy.h"
#include "KetNoiDlg.h"
#pragma warning(disable: 4996)

// CKetNoiDlg dialog

IMPLEMENT_DYNAMIC(CKetNoiDlg, CDialog)

CKetNoiDlg::CKetNoiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKetNoiDlg::IDD, pParent)
{

}

CKetNoiDlg::~CKetNoiDlg()
{
}

void CKetNoiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_USERNAME, m_strUsername);
	DDV_MaxChars(pDX, m_strUsername, MAX_LENGTH);

	DDX_Text(pDX, IDC_EDT_PASSWORD, m_strPassword);
	DDV_MaxChars(pDX, m_strPassword, MAX_LENGTH);

	DDX_Text(pDX, IDC_EDT_SERVERADDRESS, m_strServerAddress);
	DDV_MaxChars(pDX, m_strServerAddress, MAX_LENGTH);

	DDX_Text(pDX, IDC_EDT_DATABASENAME, m_strDatabaseName);
	DDV_MaxChars(pDX, m_strDatabaseName, MAX_LENGTH);

}


BEGIN_MESSAGE_MAP(CKetNoiDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CKetNoiDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CKetNoiDlg message handlers

void CKetNoiDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UpdateConnectData();
	OnOK();	
}
void CKetNoiDlg::UpdateConnectData()
{
	CQuanLyApp* pApp = static_cast <CQuanLyApp*> ( AfxGetApp());
	
	strcpy(pApp->ConnectString.m_strUsername, CStringToArrChar(m_strUsername));
	strcpy(pApp->ConnectString.m_strPasssword, CStringToArrChar(m_strPassword));
	strcpy(pApp->ConnectString.m_strServerAddress, CStringToArrChar(m_strServerAddress));
	strcpy(pApp->ConnectString.m_strDatabaseName, CStringToArrChar(m_strDatabaseName));
}
char* CKetNoiDlg::CStringToArrChar(CString cStrSource)
{
	char* arrDest;
	TCHAR* warrTemp = cStrSource.GetBuffer();
	arrDest = new char[wcslen(warrTemp) + 1];
	wcstombs( arrDest, warrTemp, wcslen(warrTemp));
	arrDest[wcslen(warrTemp)] = '\0';
	return arrDest;
}