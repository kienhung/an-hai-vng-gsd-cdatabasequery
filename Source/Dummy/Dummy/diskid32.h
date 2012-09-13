// diskid32.h : main header file
//

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CDiskId32App
// See DiskId32.cpp for the implementation of this class
//
class CDiskId32
{
public:
	static long getHardDriveID(CString& psHardDriveComputerID);
	CDiskId32();
	virtual ~CDiskId32();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
