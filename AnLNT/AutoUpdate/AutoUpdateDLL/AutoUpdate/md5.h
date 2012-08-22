//http://people.csail.mit.edu/rivest/Md5.c
/*
 **********************************************************************
 ** md5.h -- Header file for implementation of MD5                   **
 ** RSA Data Security, Inc. MD5 Message Digest Algorithm             **
 ** Created: 2/17/90 RLR                                             **
 ** Revised: 12/27/90 SRD,AJ,BSK,JT Reference C version              **
 ** Revised (for MD5): RLR 4/27/91                                   **
 **   -- G modified to have y&~z instead of y&z                      **
 **   -- FF, GG, HH modified to add in last register done            **
 **   -- Access pattern: round 2 works mod 5, round 3 works mod 3    **
 **   -- distinct additive constant for each step                    **
 **   -- round 4 added, working mod 7                                **
 **********************************************************************
 */

/*
 **********************************************************************
 ** Copyright (C) 1990, RSA Data Security, Inc. All rights reserved. **
 **                                                                  **
 ** License to copy and use this software is granted provided that   **
 ** it is identified as the "RSA Data Security, Inc. MD5 Message     **
 ** Digest Algorithm" in all material mentioning or referencing this **
 ** software or this function.                                       **
 **                                                                  **
 ** License is also granted to make and use derivative works         **
 ** provided that such works are identified as "derived from the RSA **
 ** Data Security, Inc. MD5 Message Digest Algorithm" in all         **
 ** material mentioning or referencing the derived work.             **
 **                                                                  **
 ** RSA Data Security, Inc. makes no representations concerning      **
 ** either the merchantability of this software or the suitability   **
 ** of this software for any particular purpose.  It is provided "as **
 ** is" without express or implied warranty of any kind.             **
 **                                                                  **
 ** These notices must be retained in any copies of any part of this **
 ** documentation and/or software.                                   **
 **********************************************************************
 */


/*
void MD5Init (MD5_CTX *mdContext);
void MD5Update (MD5_CTX *mdContext,unsigned char *inBuf,unsigned int inLen);
void MD5Final (MD5_CTX *mdContext);
*/
/*
 **********************************************************************
 ** End of md5.h                                                     **
 ******************************* (cut) ********************************
 */


// md5.h : main header file
//

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CMD5
// See md5.cpp for the implementation of this class
//
class CMD5
{
	/* typedef a 32 bit type */
	typedef unsigned long int UINT4;

	/* Data structure for MD5 (Message Digest) computation */
	typedef struct {
	  UINT4 i[2];                   /* number of _bits_ handled mod 2^64 */
	  UINT4 buf[4];                                    /* scratch buffer */
	  unsigned char in[64];                              /* input buffer */
	  unsigned char digest[16];     /* actual digest after MD5Final call */
	} MD5_CTX;
public:
	CString MDFile (LPCTSTR filename);
	CString MDString (CString inString);
	CMD5();
	virtual ~CMD5();
private:
	void Transform (UINT4 *buf, UINT4 *in);
	void MD5Init (MD5_CTX *mdContext);
	void MD5Update (MD5_CTX *mdContext,unsigned char *inBuf,unsigned int inLen);
	void MD5Final (MD5_CTX *mdContext);
protected:
	CString MDPrint (MD5_CTX *mdContext);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
