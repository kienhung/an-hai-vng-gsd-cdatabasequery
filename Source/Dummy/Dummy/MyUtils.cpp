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
	

	CString strHardwareNumberSerial;
	CDiskId32::getHardDriveID(strHardwareNumberSerial);
	strHardwareNumberSerial.TrimLeft();

	CString strMacSerial;
	CNetCardInfo adapter;
	strMacSerial = adapter.GetMacAddressList();
	if(strLcID.IsEmpty())
	{
		strMacSerial.Empty();
		strMacSerial = adapter.GetMACAddress();
		if(CheckMacAddressValid(strMacSerial, strHardwareNumberSerial, strLcID, strMC))
		{
			return strMC;
		}
	}

	CToken token(strMacSerial, _T(";"));
	CString strItem;
	while (token.MoreTokens())
	{
		strItem = token.GetNextToken();
		if (!strItem.IsEmpty())
		{
			if(CheckMacAddressValid(strItem, strHardwareNumberSerial, strLcID, strMC))
			{
				return strMC;
			}
		}
	}
	return strMC;
}

BOOL CMyUtils::CheckMacAddressValid(const TCHAR* strMacAdd, const TCHAR* strHwSerial,const CString& strLcID, CString& strMC)
{
	CString strTemp;
	strTemp.Format(_T("CCM%sDTS%s"), strMacAdd, strHwSerial);
	CMD5 md5;
	CString strSerial = md5.MDString(strTemp);
	

	CCipher cipher;
	CString strLicense = cipher.Encode(strSerial);
	
	if(strLcID.IsEmpty() || strLcID.Compare(strLicense) == 0)
	{
		strMC = strSerial;
		return TRUE;
	}
	return FALSE;
}

VARIANT CMyUtils::CreateVariantPostData(const CString &strPost)
{
      VARIANT varPostData = {0};

      // convert post data to ASCII string
      USES_CONVERSION;

      LPSTR pszBstrPostData = OLE2A(strPost);
      UINT iElements = strlen( pszBstrPostData );

      LPSAFEARRAY psaPostData =
            SafeArrayCreateVector( VT_UI1, 0, iElements );

      LPSTR pszSafeArrayPostData;
      SafeArrayAccessData( psaPostData, (LPVOID *)&pszSafeArrayPostData );
      memcpy( pszSafeArrayPostData, pszBstrPostData, iElements );
      SafeArrayUnaccessData( psaPostData );

      VariantInit( &varPostData );
      V_VT( &varPostData ) = VT_ARRAY | VT_UI1;
      V_ARRAY( &varPostData ) = psaPostData;

      return varPostData;
}
