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

	CMyPath myPath;

	m_strLogFilePath = myPath.GetExeFilePath() + CString(L"\\log") + m_strToken + CString(L".txt");
	return TRUE;
}

BOOL CAutoUpdateTool::Create( CLauncher *pAutoLauncher, LPCTSTR strToken, LPCTSTR strCCSource )
{
	m_strTempSourcePath = strCCSource;
	return Create(pAutoLauncher, strToken);
}


CAutoUpdateTool::~CAutoUpdateTool(void)
{
	if (NULL != m_pAutoLauncher) {
		delete m_pAutoLauncher;
	}
}

BOOL CAutoUpdateTool::Update()
{
	CString strLog;

	if (NULL == m_pAutoLauncher) {

		strLog = L"Creating auto launcher is failed...";
		WriteLog(strLog);
		WriteLog(L"");

		return FALSE;
	}

	if (FALSE ==  RunAutoLauncher()) {
		WriteLog(L"Running auto launcher is failed. There are some problems on the network connection or the auto launcher tool is out of date");
	}

	if (FALSE == Compare()) {
		WriteLog(L"Comparing folder is failed");
	}

	strLog = m_pAutoLauncher->GetName() + L" update is complete...";
	WriteLog(strLog);
	WriteLog(L"");

	return TRUE;

}

BOOL CAutoUpdateTool::CloneSource()
{
	return TRUE;
}

BOOL CAutoUpdateTool::RunAutoLauncher()
{
	CString strLog = m_pAutoLauncher->GetName() + L" auto launcher is running ...";
	WriteLog(strLog);

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

	CString strLog = m_pAutoLauncher->GetName() + L" is comparing...";
	WriteLog(strLog);

	if (FALSE == folderCompare.Compare(strResultFilePath)) {
		return FALSE;
	}
	
	return TRUE;
}

BOOL CAutoUpdateTool::RemoveTempSource()
{
	return TRUE;
}

CString CAutoUpdateTool::GetName()
{
	if (NULL == m_pAutoLauncher) {
		return L"";
	}
	return m_pAutoLauncher->GetName();
}

void CAutoUpdateTool::WriteLog( const CString &strLog )
{
	_tprintf(strLog + L"\n");

	CStdioFile fileWriter;
	CFileException fileException;

	if (fileWriter.Open(m_strLogFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeBinary , &fileException)) {

		fileWriter.SeekToEnd();

		fileWriter.WriteString(strLog + L"\r\n");
	
		fileWriter.Close();
	} 
}
