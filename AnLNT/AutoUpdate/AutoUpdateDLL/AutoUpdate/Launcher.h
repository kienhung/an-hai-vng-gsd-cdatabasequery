#pragma once

//class AFX_EXT_CLASS CLauncher
class CGameSourceCompare;

class CLauncher
{
protected:

	CString m_strSource;
	CString m_strLauncher;

	int m_iTimeoutCount;
	int m_iTimeoutSeconds;

	HWND m_hMainWindow;
	DWORD m_dwLauncherTimeOut;
	//09/11/2012
	CGameSourceCompare *m_Comparer;
public:

	CLauncher(LPCTSTR strSource);

	virtual BOOL Run() = 0;
	virtual CString GetName() = 0;
	CString GetSourcePath();

	virtual ~CLauncher(void);

	virtual CGameSourceCompare * GetComparer (LPCTSTR strNewSource, LPCTSTR strOldSource);
protected:
	virtual BOOL StartLauncherProcess();
	virtual HWND StartLauncherWindow(LPCTSTR strClassName, LPCTSTR strWindowName);

	virtual BOOL CloseWindow(LPCTSTR strClassName, LPCTSTR strWindowName);

	virtual BOOL ClickButton(int iButtonID);
	virtual BOOL ClickButton(HWND hParent, int iButtonID);

	virtual BOOL CheckButton(int iButtonID, WORD wState = BST_CHECKED);
	virtual BOOL CheckButton(HWND hParent, int iButtonID,  WORD wState = BST_CHECKED);

};
