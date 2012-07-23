#pragma once

class AFX_EXT_CLASS CCrypto
{
protected:
	const size_t KEY_LENGTH;
	char *m_pcKey;
	char *m_pcIV;
public:
	CCrypto(void);
	bool SetKey(char *pcKey, size_t uiLength);
	virtual ~CCrypto(void);

	virtual bool ExecuteOneBlock(char *pcBlock, size_t uiSize) = 0;
	virtual bool ExecuteManyBlocks(char *pcBlocks, size_t uiSize) = 0;
	virtual bool ExecuteFile(const TCHAR *ptcInputFileName, const TCHAR *ptcOutputFileName) = 0;

};
