#include "StdAfx.h"
#include "ExportFunctions.h"
#include "MyUtils.h"
#include "InputReader.h"
#include "GlobalClass.h"
#include "Process.h"



BOOL AutoDetectGameUpdate( LPCTSTR strInput )
{
	//1. Run launcher
	CInputReader reader(strInput);
	reader.Read();

	
	//2. Run LOL
	CString strLOLAutoLauncher;
	strLOLAutoLauncher.Format(_T("%s\\%s"), CGlobalClass::GetInstance()->GetExeDirectory(), _T("LOL.exe"));

	CProcess process;
	process.SetProcessName(strLOLAutoLauncher);

	if (TRUE == process.Run())
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_FYI, L"LOL dang tu dong chay launcher ...");
		process.WaitForExit();

		DWORD dwExitCode = 0;
		if (TRUE == process.GetExitCode(&dwExitCode))
		{
			if (0 == dwExitCode)
			{
				CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_FYI, L"LOL update hoan tat ...");
			} 
			else if (1 == dwExitCode)
			{
				CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"That bai... Duong truyen bi loi hoac launcher da bi thay doi");
			}
		} 
		else
		{
			CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"Unable to get exit code of LOL AHK Launcher process");
		}
	} 
	else
	{
		CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"Unable to start LOL AHK Launcher");
	}

	//3. Run Email
	CString strEmailProccessPath;
	strEmailProccessPath.Format(L"%s\\Mail\\Mail.exe", CGlobalClass::GetInstance()->GetExeDirectory());
	CProcess emailProcess;
	emailProcess.SetProcessName(strEmailProccessPath);

	CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_FYI, L"Start Mail.exe process");
	if (emailProcess.Run())
	{
		emailProcess.WaitForExit();
		
		DWORD dwExitCode = 0;
		if (TRUE == emailProcess.GetExitCode(&dwExitCode))
		{
			if (0 == dwExitCode)
			{
				CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_FYI, L"Run Mail.exe OK");
			} 
			else
			{
				CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"Run Mail.exe failed");
			}
		} 
		else
		{
			CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"Unable to get exit code of Mail.exe process");
		}
	}

	return TRUE;
}
