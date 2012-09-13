// NetCardInfo.h: interface for the CNetCardInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETCARDINFO_H__639144BF_5085_43EC_92CE_F7BE24D1B5F3__INCLUDED_)
#define AFX_NETCARDINFO_H__639144BF_5085_43EC_92CE_F7BE24D1B5F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNetCardInfo  
{
public:
	
	CString GetErrMsg();
	CString GetMACAddress();
	CString GetMacAddressList();
	
	CNetCardInfo();
	virtual ~CNetCardInfo();

private:
	PIP_ADAPTER_INFO m_pinfo;
	void ParseData();
	void GetInfo();
	CString m_sMACAddr;
	BYTE m_data[4096];
	CString ErrMsg;
	unsigned long len;
	CString m_sMacAddrList;
	void ParseMacAddressList();
};

#endif // !defined(AFX_NETCARDINFO_H__639144BF_5085_43EC_92CE_F7BE24D1B5F3__INCLUDED_)
