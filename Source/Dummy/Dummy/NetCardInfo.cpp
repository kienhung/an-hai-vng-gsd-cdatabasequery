// NetCardInfo.cpp: implementation of the CNetCardInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dummy.h"
#include "NetCardInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetCardInfo::CNetCardInfo()
{
	ErrMsg = _T( "" );

	m_sMACAddr= _T( "" );

	ZeroMemory( m_data,4096 );
	len = 0;
	m_pinfo = ( PIP_ADAPTER_INFO )m_data;

	GetInfo();
}

CNetCardInfo::~CNetCardInfo()
{

}

CString CNetCardInfo::GetMACAddress()
{
	return m_sMACAddr;
}

CString CNetCardInfo::GetErrMsg()
{
	return ErrMsg;
}

void CNetCardInfo::GetInfo()
{
	ErrMsg = _T( "Success!" );

	unsigned long nError;

	nError = GetAdaptersInfo( m_pinfo,&len );
	switch( nError ) {
		case ERROR_SUCCESS:
			ParseData();
			break;
		case ERROR_NO_DATA:
			ErrMsg = _T( "No net device information!" );
			break;
		case ERROR_NOT_SUPPORTED:
			ErrMsg = _T( "The system not support GetAdaptersInfo API function!" );
			break;
		case ERROR_BUFFER_OVERFLOW:
			nError = GetAdaptersInfo( m_pinfo,&len );
			if( nError == 0 )
			{
				ParseData();
				ParseMacAddressList();
			}
			else ErrMsg = _T("Unknow error!");
			break;
	}
}

void CNetCardInfo::ParseData()
{
	m_sMACAddr.Format( _T("%02X%02X%02X%02X%02X%02X"),m_pinfo->Address[0],m_pinfo->Address[1],m_pinfo->Address[2],m_pinfo->Address[3],m_pinfo->Address[4],m_pinfo->Address[5] );
}

CString CNetCardInfo::GetMacAddressList()
{
	return m_sMacAddrList;
}


void CNetCardInfo::ParseMacAddressList()
{
	m_sMacAddrList = _T("");
	CString strAddress;
	PIP_ADAPTER_INFO pItem = m_pinfo;
	
	m_sMacAddrList.Format(_T("%02X%02X%02X%02X%02X%02X"),
		pItem->Address[0],
		pItem->Address[1],
		pItem->Address[2],
		pItem->Address[3],
		pItem->Address[4],
		pItem->Address[5]);
	
	pItem = pItem->Next;
	
	while (pItem != NULL)
	{
		
		strAddress.Format(_T("%02X%02X%02X%02X%02X%02X"),
			pItem->Address[0],
			pItem->Address[1],
			pItem->Address[2],
			pItem->Address[3],
			pItem->Address[4],
			pItem->Address[5]);
		
		m_sMacAddrList = m_sMacAddrList + _T(";") + strAddress;
		pItem = pItem->Next;
	}
	
}
