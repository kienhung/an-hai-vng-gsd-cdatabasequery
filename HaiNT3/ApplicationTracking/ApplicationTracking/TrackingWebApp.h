#pragma once

class CTrackingWebApp
{
private:

public:

	CTrackingWebApp(void);
	static BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam);
	static BOOL CALLBACK enumChildProc(HWND hwnd, LPARAM lParam);
	virtual VOID Track();
	~CTrackingWebApp(void);
};
