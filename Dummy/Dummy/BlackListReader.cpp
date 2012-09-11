#include "StdAfx.h"
#include "BlackListReader.h"

CBlackListReader::CBlackListReader(void)
{
}

CBlackListReader::~CBlackListReader(void)
{

}

BOOL CBlackListReader::ProcessItem( LPCTSTR strItemText )
{
	_tprintf(L"%s\n", strItemText);

	return TRUE;
}

BOOL CBlackListReader::Read( LPCTSTR strFilePath )
{
	CStdioFile fileReader;
	CFileException fileException;

	if (FALSE == fileReader.Open(strFilePath, CFile::modeRead | CFile::shareDenyNone , &fileException))
	{
		return FALSE;
	} 

	CString strItemText;
	while (fileReader.ReadString(strItemText))
	{
		if (FALSE == ProcessItem(strItemText))
		{
			return TRUE;
		}
	}
	return TRUE;
}
