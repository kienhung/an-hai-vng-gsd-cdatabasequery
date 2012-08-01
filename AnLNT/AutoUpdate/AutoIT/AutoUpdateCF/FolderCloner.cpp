#include "StdAfx.h"
#include "FolderCloner.h"



CFolderCloner::CFolderCloner( LPCTSTR strSource, LPCTSTR strDest )
{

	m_strSource = strSource;
	m_strDest = strDest;
}

CFolderCloner::~CFolderCloner(void)
{
}

BOOL CFolderCloner::Clone()
{

	return TRUE;
}
