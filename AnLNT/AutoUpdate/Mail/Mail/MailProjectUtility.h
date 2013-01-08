#pragma once
#include <vector>
#include <string>
#include <utility>

using namespace std;

class CMailProjectUtility
{
protected:
	const static int NUM_GAMES = 100;
public:
	CMailProjectUtility(void);
	~CMailProjectUtility(void);

	static vector<string>					GetListGameForMail(LPCTSTR strFileName);
	static bool								CheckGameHasUpdate(string sAlias, LPCTSTR strReportFolder);
	static vector<pair<string,int>>			PrepareListGameForXml(const vector<string> &vGames, LPCTSTR strReportFolder);
	static BOOL								GetModifyTime(LPCTSTR strFileName, FILETIME &fileTime);
};
