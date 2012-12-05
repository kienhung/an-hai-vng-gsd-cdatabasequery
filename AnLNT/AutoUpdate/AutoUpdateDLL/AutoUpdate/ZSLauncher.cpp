#include "StdAfx.h"
#include "ZSLauncher.h"
#include "ZSCompare.h"



CZSLauncher::CZSLauncher( LPCTSTR strSource, LPCTSTR strGameAlias )
:CAHKLauncher(strSource, strGameAlias)
{

}

CZSLauncher::~CZSLauncher(void)
{
}

CGameSourceCompare * CZSLauncher::GetComparer( LPCTSTR strNewSource, LPCTSTR strOldSource )
{
	if (m_Comparer != NULL)
	{
		delete m_Comparer;
	}

	m_Comparer = new CZSCompare(strNewSource, strOldSource);
	if (m_Comparer != NULL)
	{
		return m_Comparer;
	}

	return NULL;
}
