#include "StdAfx.h"
#include "ExportFunctions.h"
#include "MyUtils.h"
#include "InputReader.h"



BOOL AutoDetectGameUpdate( LPCTSTR strInput )
{
	
	CInputReader reader(strInput);

	if (FALSE == reader.Read()) {
		return FALSE;
	} else {
		return TRUE;
	}

	return TRUE;
}
