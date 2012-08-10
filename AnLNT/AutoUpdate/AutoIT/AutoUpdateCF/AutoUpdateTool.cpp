#include "StdAfx.h"
#include "AutoUpdateTool.h"
#include "FileServices.h"
#include "MyPath.h"
#include "FolderCloner.h"
#include "FolderCompare.h"
#include "FolderRemoving.h"



CAutoUpdateTool::CAutoUpdateTool()
{
	m_pAutoLauncher = NULL;
}

BOOL CAutoUpdateTool::Create( CLauncher *pAutoLauncher, LPCTSTR strToken )
{
	if (NULL == pAutoLauncher) {
		return FALSE;
	}

	m_strSourcePath = pAutoLauncher->GetSourcePath();
	
	m_strToken = strToken;
	m_pAutoLauncher = pAutoLauncher;

	return TRUE;
}

CAutoUpdateTool::~CAutoUpdateTool(void)
{
	if (NULL != m_pAutoLauncher) {
		delete m_pAutoLauncher;
	}
}

BOOL CAutoUpdateTool::Update()
{

	if (NULL == m_pAutoLauncher) {
		return FALSE;
	}

	if (FALSE == CloneSource()) {
		return FALSE;
	}

	if (FALSE == RunAutoLauncher()) {
		return FALSE;
	}

	if (FALSE == Compare()) {
		return FALSE;
	}

	if (FALSE == RemoveTempSource()) {
		return FALSE;
	}

	_tprintf(L"%s update has been complete...\n\n", m_pAutoLauncher->GetName());

	return TRUE;
}

BOOL CAutoUpdateTool::CloneSource()
{

	CMyPath myPath;

	CString strFolderName = myPath.GetShortFileName(m_strSourcePath);
	CString strSource = myPath.GetParentPath(m_strSourcePath);
	CString strDest = myPath.GetExeFilePath();

	CFolderCloner folderCloner(strSource, strDest, strFolderName);

	_tprintf(L"%s is cloning...\n", m_pAutoLauncher->GetName());

	if (FALSE == folderCloner.Clone()) {
		return FALSE;
	}

	m_strTempSourcePath = strDest + CString(L"\\") + strFolderName;

	return TRUE;
}

BOOL CAutoUpdateTool::RunAutoLauncher()
{

	_tprintf(L"%s auto launcher is running ...\n", m_pAutoLauncher->GetName());

	if (FALSE == m_pAutoLauncher->Run()) {
		return FALSE;
	}
	
	return TRUE;
}

BOOL CAutoUpdateTool::Compare()
{

	CFolderCompare folderCompare(m_strSourcePath, m_strTempSourcePath);

	CMyPath myPath;

	CString strReportDirectory = myPath.GetExeFilePath() + L"\\Report";
	if (FALSE == myPath.IsDirectory(strReportDirectory)) {
		::CreateDirectory(strReportDirectory, NULL);
	}

	CString strResultFilePath = strReportDirectory  + L"\\"+ m_strToken + L"_" + m_pAutoLauncher->GetName() + L".txt";

	_tprintf(L"%s is comparing...\n", m_pAutoLauncher->GetName());

	if (FALSE == folderCompare.Compare(strResultFilePath)) {
		return FALSE;
	}
	
	return TRUE;
}

BOOL CAutoUpdateTool::RemoveTempSource()
{

	CFolderRemoving folderRemoving;
	
	_tprintf(L"%s is removing temporary source ...\n", m_pAutoLauncher->GetName());

	if (FALSE == folderRemoving.Remove(m_strTempSourcePath)) {
		return FALSE;
	}
	
	return TRUE;
}

CString CAutoUpdateTool::GetName()
{
	return m_pAutoLauncher->GetName();
}

