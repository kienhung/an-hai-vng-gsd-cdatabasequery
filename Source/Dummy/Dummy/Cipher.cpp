// Cipher.cpp: implementation of the CCipher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Cipher.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCipher::CCipher()
{
	this->m_sText = _T("");

	SetKey(_T("ddmsys"));
}

//Purpose : Gan key 
//Passed  : Khoa can cho chuoi ma hoa
//Call Frm: 
//Returns : 
//===============================================================================
//User                  Ref   Date          Comments
//===================== ===== ============= =====================================
//HungTran              1.0   10 Feb 2003   Created
//===================================================================
void CCipher::SetKey(CString psKey)
{
	this->m_sKey  = psKey;
	int liLen = psKey.GetLength();

	if (!liLen)
		return;

	for (int i=0;i<127;i++)
		m_codeTable[i] = this->m_sKey.GetAt(i%liLen);
}

CCipher::~CCipher()
{
	
}
//Purpose : Ma hoa du lieu
//Passed  : Chuoi can ma hoa
//Call Frm: 
//Returns : Chuoi duoc ma hoa
//===============================================================================
//User                  Ref   Date          Comments
//===================== ===== ============= =====================================
//HungTran              1.0   10 Feb 2003   Created
//===================================================================
CString CCipher::Encode(CString psCode)
{
	this->m_sText = psCode;
	
	Shrink();
	Xor();
	
	//SAU KHI MA HOA ,BIEN DOI CHUOI MA HOA VE DANG CHUOI SO,KY TU DOC DUOC.

	int liLen =  this->m_sText.GetLength();
	//Get all of the chars and convert to the number by it ascii and concat all together
	CString lsNo;
	CString lsResult=_T("");
	
	//muc dich dung de giam kich thuoc cua chuoi can ma hoa
	bool lOdd = 0;
	int i;
	long lCount=0;//tong gia tri cua chuoi

	//muc dich: khi thay doi mot ky tu nao do cua chuoi can ma hoa
	//thi hau nhu toan bo chuoi duoc ma hoa se thay doi 
	//lCount: TONG GIA TRI CUA TOAN BO KY TU TRONG CHUOI DA MA HOA
	for (i=0;i<liLen;i++)
		lCount+=(unsigned short)m_sText.GetAt(i);
	
	for (i=0;i<liLen;i++)
	{
		//Lay gia tri ky tu thu i trong chuoi da ma hoa
		unsigned int lC = (unsigned short) this->m_sText.GetAt(i);

		//NEU KHONG PHAI LA KY TU DOC DUOC:
		if ((lC < 'a' || lC > 'z')&&(lC < 'A' || lC > 'Z'))
		{
			//gia tri lC cong them PHAN DU lCount CHIA CHO 256.//dieu
			//nay se lam thay doi hau nhu toan bo chuoi ma hoa 
			//neu nhu co su thay doi 1 ktu trong chuoi can ma hoa
			lC+= lCount%256;

			//dinh dang lC ve dang chuoi HEXA
			lsNo.Format(_T("%X"),lC);

			lOdd = !lOdd;

			//MUC DICH RUT NGAN CHUOI MA HOA.//bo
			//NEU LE
			//if (lOdd)//chi lay ktu cuoi trong chuoi HEXA vua roi
			//	lsResult+=lsNo.GetAt(lsNo.GetLength()-1);
			//NEU CHAN
			//else// lay toan bo HEXA
			lsResult+=lsNo;
		}
		//Neu lC la ktu doc duoc
		else
		{
			wchar_t ch = lC;
			lsResult+=ch;
		}
		
		
	}

	//ket qua sau khi bien doi chuoi ma hoa 
	this->m_sText = lsResult;
	//this->m_sText:la chuoi duoc ma hoa.
	return this->m_sText;
}
//Purpose : Giai ma,tam thoi chua giai ma duoc
//Passed  : Chuoi can giai ma
//Call Frm: 
//Returns : Chuoi duoc giai ma
//===============================================================================
//User                  Ref   Date          Comments
//===================== ===== ============= =====================================
//HungTran              1.0   10 Jan 2003   Created
//===================================================================
CString CCipher::Decode(CString psCode)
{
	this->m_sText = psCode;
	
	return this->m_sText;
}

//Purpose : Thuc hien phep XOR dung de ma hoa
//Passed  : Chuoi can giai ma
//Call Frm: 
//Returns : Chuoi duoc giai ma
//===============================================================================
//User                  Ref   Date          Comments
//===================== ===== ============= =====================================
//HungTran              1.0   10 Jan 2003   Created
//===================================================================
void CCipher::Xor()
{
	//thuat toan cua ham nay tac gia cung chua hieu.
	//moi thac mac xin lien he voi Boss.
	TCHAR lngC=0;
    TCHAR intB =0;
    int lngN =0;
	unsigned char ch;
	long len = this->m_sText.GetLength();

    for (lngN = 0 ; lngN<len ; lngN++)
	{
        lngC = this->m_sText.GetAt(lngN);
        intB = this->m_codeTable[lngN%127];
		ch = lngC^intB;
        this->m_sText.SetAt(lngN,ch);
    }
}

//Convert any string to a printable, displayable string
//Temporary is not used
//thuat toan cua ham nay tac gia cung chua hieu.
//moi thac mac xin lien he voi Boss.
void CCipher::Stretch()
{
	int lngC=0;
    int lngN=0;
    int lngJ=0;
    int lngK=0;
    int lngA=0;
    CString strB ;
	wchar_t	ch;
    lngA = this->m_sText.GetLength();
	int lngB = lngA + (lngA + 2) / 3;
    //strB = Space(lngB)
	for (int i=0;i<lngB;i++)
	{	
		ch = 32;
		strB += ch;
	}

	
    //For lngN = 1 To lngA
	for (lngN = 0;lngN<lngA;lngN++)
	{
        lngC = this->m_sText.GetAt(lngN);
        lngJ = lngJ + 1;
		if (lngJ>=lngA) break;
        strB.SetAt(lngJ,(lngC & 63) + 59);
        switch (lngN%3)
		{
        case 1:
            lngK = lngK | ((lngC / 64) * 16);
			break;
        case 2:
            lngK = lngK | ((lngC / 64) * 4);
			break;

		case 0:
            lngK = lngK | (lngC / 64);
            lngJ = lngJ + 1;
			if (lngJ>=lngA) lngJ = lngJ - 1;;
            strB.SetAt(lngJ,lngK + 59);
            lngK = 0;
			break;
		}
    }
    if (lngA % 3 )
	{
        lngJ = lngJ + 1;

		if (lngJ>=lngA) lngJ = lngJ - 1;;

        strB.SetAt(lngJ,lngK + 59);
    }
    this->m_sText = strB;
}
//thuat toan cua ham nay tac gia cung chua hieu.
//moi thac mac xin lien he voi Boss.
void CCipher::Shrink()
{

	int lngC =0;
    int lngD =0;
    int lngE =0;
    int lngA =0;
    int lngB =0;
    int lngN =0;
    int lngJ =0;
    int lngK =0;
    CString strB ;
	wchar_t	ch;
	unsigned char ch1;
    lngA = this->m_sText.GetLength();

	if (!lngA ) return ;

    lngB = lngA - 1 - (lngA - 1) / 4;
	
	if (lngB==0) lngB = 1;

	//strB = Space(lngB)
	for (int i=0;i<lngB;i++)
	{
		ch = 32;
		strB += ch;
	}

    //For lngN = 1 To lngB
	for (lngN = 0; lngN< lngB;lngN++)
	{
        lngJ = lngJ + 1;
        //lngC = Asc(Mid(mstrText, lngJ, 1)) - 59
		if (lngJ>=lngA) lngJ = lngA - 1 ;
		
		lngC = this->m_sText.GetAt(lngJ) - 59;

        //Select Case lngN Mod 3
        //Case 1
          //  lngK = lngK + 4
            //If lngK > lngA Then lngK = lngA
            //lngE = Asc(Mid(mstrText, lngK, 1)) - 59
            //lngD = ((lngE \ 16) And 3) * 64
        //Case 2
          //  lngD = ((lngE \ 4) And 3) * 64
        //Case 0
          //  lngD = (lngE And 3) * 64
           // lngJ = lngJ + 1
        //End Select
		switch(lngN % 3)
		{
		case 1:
			lngK = lngK + 4;
			if (lngK >= lngA)  lngK = lngA-1;
			lngE = this->m_sText.GetAt(lngK) - 59;
			lngD = ((lngE / 16) & 3) * 64;

			break;
		case 2:
			lngD = ( (lngE / 4)  &  3 ) * 64;
			break;
		case 0:
			  lngD = (lngE & 3) * 64;
			  lngJ = lngJ + 1;
			break;
			
		}
        //strB, lngN, 1) = Chr(lngC Or lngD)
		ch1 = lngC | lngD;
		strB.SetAt(lngN,ch1);
    }
    this->m_sText = strB;

}

