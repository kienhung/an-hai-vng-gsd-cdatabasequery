#pragma once
#include "StdAfx.h"

typedef struct
{
	CString m_strURL;
	CString m_strTitle;
}TAB_WEB;


class CTrackingWebApp
{
private:

public:

	CTrackingWebApp(void);
	
	virtual VOID Track();
	~CTrackingWebApp(void);
};
