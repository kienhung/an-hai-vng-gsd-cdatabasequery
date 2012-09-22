#pragma once

class CRegistry
{
private:
	HKEY	m_hRootKey;
	CString	m_strSubKey;
public:
	void SetKey(HKEY hRootKey, const TCHAR *pcSubKey);
	BOOL ReadValue(LPCTSTR lpValName, DWORD &dwData);
	BOOL ReadValue(LPCTSTR lpValName, LPTSTR lpBufData, int iBufSize);
	BOOL SaveValue(LPCTSTR lpValName, DWORD &dwData);
	BOOL SaveValue(LPCTSTR lpValName, LPCTSTR lpData);
	CRegistry(void);
	CRegistry(HKEY hRootKey, const TCHAR *pcSubKey);
	~CRegistry(void);

	static BOOL CreateKey(HKEY hRootKey, const TCHAR *pcSubKey);
};
