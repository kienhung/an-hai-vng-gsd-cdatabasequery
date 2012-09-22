#include "StdAfx.h"
#include "Token.h"

CToken::CToken(void)
{
	m_strDelimit = " ";
	m_bMoreToken = TRUE;
	m_strRemain = "";
}

CToken::CToken(CString strSource, CString strDelimit)
{
	m_strRemain = strSource;
	m_strDelimit = strDelimit;
	m_bMoreToken = TRUE;
}

CToken::~CToken(void)
{

}

void CToken::Init(CString strSource, CString strDelimit)
{
	m_strRemain = strSource;
	m_strDelimit = strDelimit;
	m_bMoreToken = TRUE;
}

CString CToken::GetNextToken()
{
	if (m_bMoreToken == FALSE)
		return _T("");

	int pos = m_strRemain.Find(m_strDelimit, 0);

	if (pos != -1)
	{
		CString strTok;

		strTok = m_strRemain.Left(pos);
		pos += m_strDelimit.GetLength();
		m_strRemain = m_strRemain.Right(m_strRemain.GetLength() - pos);

		return strTok;
	}
	else
	{
		m_bMoreToken = FALSE;
		return m_strRemain;
	}
}
