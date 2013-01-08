#pragma once

class CProcess
{
protected:

	PROCESS_INFORMATION				m_processInfo;
	CString							m_strProcessName;
	STARTUPINFO						m_startupInfo;

public:

	CProcess(void);
	virtual ~CProcess(void);


	void							SetProcessName(LPCTSTR strProcessName);
	void							Free();
	BOOL							GetExitCode(DWORD *pdwExitCode);
	BOOL							Run(LPCTSTR strWorkingDir = NULL);
	DWORD							WaitForExit(DWORD dwMilliseconds = INFINITE);
};
