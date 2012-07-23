#pragma once
#include "crypto.h"


class AFX_EXT_CLASS CEncryption :
	public CCrypto
{
protected:
	char *m_pcPreviousEncryptedBlock;
public:
	CEncryption(void);
	virtual ~CEncryption(void);
	virtual bool ExecuteOneBlock(char *pcBlock, size_t uiSize);
	virtual bool ExecuteManyBlocks(char *pcBlocks, size_t uiSize);
	virtual bool ExecuteFile(const TCHAR *ptcInputFileName, const TCHAR *ptcOutputFileName);
};
