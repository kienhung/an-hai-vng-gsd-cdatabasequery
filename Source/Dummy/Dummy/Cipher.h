// Cipher.h: interface for the CCipher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIPHER_H__9907E863_5A04_41C5_8DFF_79F99A6D0B32__INCLUDED_)
#define AFX_CIPHER_H__9907E863_5A04_41C5_8DFF_79F99A6D0B32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCipher  
{
	
public:
	//chuoi can ma hoa
	CString m_sText;
	//khoa dung de ma hoa
	CString m_sKey;
public:
	void SetKey(CString psKey);
	CString Decode(CString psCode);
	CString Encode(CString psCode);
	CCipher();
	virtual ~CCipher();

protected:
	//bang dung de ma hoa
	TCHAR m_codeTable[127];
	void Xor();
	void Stretch();
	void Shrink();
};

#endif // !defined(AFX_CIPHER_H__9907E863_5A04_41C5_8DFF_79F99A6D0B32__INCLUDED_)
