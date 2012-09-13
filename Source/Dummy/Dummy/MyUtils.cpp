#include "StdAfx.h"
#include "MyUtils.h"
#include "NetCardInfo.h"
#include "Token.h"
#include "diskid32.h"
#include "md5.h"
#include "Cipher.h"
#include "IntOptionDAO.h"


CMyUtils::CMyUtils(void)
{
}

CMyUtils::~CMyUtils(void)
{
}
CString CMyUtils::GetLicenseID()
{
	CString strLCID;
	strLCID.Empty();
	CIntOptionDAO intOptionDAO;
	strLCID = intOptionDAO.GetLicesenID();
	return strLCID;
}
CString CMyUtils::GetMachineCode()
{
	CString strMC;
	CString strLcID = GetLicenseID();

	CString sHardwareNumberSerial;
	CDiskId32::getHardDriveID(sHardwareNumberSerial);
	sHardwareNumberSerial.TrimLeft();

	CString strMacSerial;
	CNetCardInfo adapter;
	strMacSerial = adapter.GetMacAddressList();


	CToken token(strMacSerial, _T(";"));
	CString strItem;
	while (token.MoreTokens())
	{
		strItem = token.GetNextToken();
		if (!strItem.IsEmpty())
		{
			if(CheckMacAddressValid(strItem, sHardwareNumberSerial, strLcID, strMC))
			{
				return strMC;
			}
		}
	}
	return strMC;
}

BOOL CMyUtils::CheckMacAddressValid(const TCHAR* strMacAdd, const TCHAR* strHwSerial, CString strLcID, CString& strMC)
{
	CString strTemp;
	strTemp.Format(_T("CCM%sDTS%s"), strMacAdd, strHwSerial);
	CMD5 cipher;
	CString strSerial = cipher.MDString(strTemp);
	

	CCipher cp;
	CString strLicense = cp.Encode(strSerial);
	
	if(strLcID.Compare(strLicense) == 0)
	{
		strMC = strSerial;
		return TRUE;
	}
	return FALSE;
}
