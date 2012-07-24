#pragma once
#include "crypto.h"

class AFX_EXT_CLASS CDecryption :
	public CCrypto
{
protected:
	char *m_pcPreviousDecryptedBlock;
	char *m_pcSavePreviousDecryptedBlock;
public:
	CDecryption(void);
	virtual ~CDecryption(void);
	virtual bool ExecuteOneBlock(char *pcBlock, size_t uiSize);
	virtual bool ExecuteManyBlocks(char *pcBlocks, size_t uiSize);
	virtual bool ExecuteFile(const TCHAR *ptcInputFileName, const TCHAR *ptcOutputFileName);
protected:
	void TransferCipherToPlain(HANDLE hInputFile, HANDLE hOutputFile, unsigned __int64 ui64NumBlocks, size_t uiNumPaddingBytes);
};
