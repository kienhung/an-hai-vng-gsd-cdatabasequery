#include "StdAfx.h"

#include "TrackingWebApp.h"

CTrackingWebApp::CTrackingWebApp(void)
{
}

CTrackingWebApp::~CTrackingWebApp(void)
{
	
}
BOOL CALLBACK CTrackingWebApp::enumChildProc(HWND hwnd, LPARAM lParam)
{
	TCHAR strText[250] = {0};
	::GetWindowText(hwnd, strText, 250);
	CString strCopyText(strText);
	if(strCopyText.Find(_T("Windows API")) >= 0)
	{
		AfxMessageBox(_T("found"));
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
	return TRUE;
}

BOOL CALLBACK CTrackingWebApp::enumWindowsProc(HWND hwnd, LPARAM lParam)
{
	TCHAR strText[250] = {0};
	::GetWindowText(hwnd, strText, 250);
	CString strCopyText(strText);
	if(strCopyText.Find(_T("Google Chrome")) > 0)
	{
		EnumChildWindows(hwnd, enumChildProc, 0);
	}
	return TRUE;
}

VOID CTrackingWebApp::Track()
{
	EnumWindows(enumWindowsProc, 0);
}