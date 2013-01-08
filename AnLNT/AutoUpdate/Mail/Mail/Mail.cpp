// Mail.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Mail.h"
#include "GlobalClass.h"
#include "MyUtils.h"
#include "Include/pugixml.hpp"

#include <iostream>
#include <utility>
#include <string>
#include "MailProjectUtility.h"
#include "LogFinder.h"
#include "Process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
using namespace pugi;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		CString strExeDirectory = CGlobalClass::GetInstance()->GetExeDirectory();

		CString strDataFilePath;
		strDataFilePath.Format(L"%s\\data.xml", strExeDirectory);
		
		CString strIniFileInput;
		strIniFileInput.Format(L"%s\\..\\input.ini", strExeDirectory);

		vector<string> vGames = CMailProjectUtility::GetListGameForMail(strIniFileInput);

		CString strReportFolder;
		strReportFolder.Format(L"%s\\..\\Report", strExeDirectory);

		vector<pair<string, int>> gamesForXml = CMailProjectUtility::PrepareListGameForXml(vGames, strReportFolder);

		CString strLogDirectory;
		strLogDirectory.Format(L"%s\\..\\log", strExeDirectory);
	
		CLogFinder logFinder;
		string logFile = logFinder.GetLastLogFile(strLogDirectory);
		

		string strInit = "<mail><games></games><log path=\"" + logFile + "\"/></mail>";
		
		xml_document doc;
		xml_parse_result result = doc.load(strInit.c_str());
		if (result)
		{
			xml_node games = doc.child("mail").child("games");
			if (games.empty() == false)
			{
				for (int i = 0; i < gamesForXml.size(); i++)
				{
					xml_node game = games.append_child("game");
					if (game.empty() == false)
					{
						xml_attribute id = game.append_attribute("id");
						xml_attribute value = game.append_attribute("value");

						if (id.empty() == false && value.empty() == false)
						{
							id.set_value(gamesForXml[i].first.c_str());
							value.set_value(gamesForXml[i].second);
						}
					}
				}
			}
			xml_node decl = doc.prepend_child(pugi::node_declaration);
			decl.append_attribute("version") = "1.0";
			decl.append_attribute("encoding") = "UTF-8";
			doc.save_file(strDataFilePath);

			//Start Email Helper
			CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_FYI, L"Start Email Helper Process");

			CString strEmailHelperPath;
			strEmailHelperPath.Format(L"%s\\MailHelper.exe", strExeDirectory);

			CProcess process;
			process.SetProcessName(strEmailHelperPath);

			if (FALSE == process.Run())
			{
				CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"Failed to start Email Helper Process");
				return 1;
			}
			process.WaitForExit(INFINITE);
			DWORD dwExitCode = 0;

			if (process.GetExitCode(&dwExitCode))
			{
				if (dwExitCode != 0)
				{
					CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"Email Helper Process Failed");
					return 1;
				}
				CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_FYI, L"Email Helper Process OK");
			}
			else
			{
				CGlobalClass::GetInstance()->GetLogWriter()->WriteLog(LOG_TYPE_ERROR, L"Failed to get exit code of email helper process");
				return 1;
			}
		}

	}

	return nRetCode;
}
