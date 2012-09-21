#pragma once

class CToken
{
public:
	CToken(void);
	CToken(CString strSource, CString strDelimit = _T(";"));
	~CToken(void);

	void		Init(CString strSource, CString strDelimit = _T(";"));
	void		SetToken(CString strDelimit) {m_strDelimit = strDelimit;};
	CString		GetNextToken();	// Returns the next token
	BOOL		MoreTokens(){return m_bMoreToken;};	// Do we have any more tokens to retrieve
	CString		Remain(){return m_strRemain;};

private:
	CString		m_strRemain;	// The string we have left after taking tokens out
	CString		m_strDelimit;	// The delimiter string
	BOOL		m_bMoreToken;
};
