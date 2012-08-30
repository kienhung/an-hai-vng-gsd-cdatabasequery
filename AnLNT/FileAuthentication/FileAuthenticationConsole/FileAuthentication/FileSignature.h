#pragma once

class CFileSignature
{

protected:

	static const int KEY_LENGTH = 8;

	char m_cHeadBytes[KEY_LENGTH];
	char m_cMiddleBytes[KEY_LENGTH];
	char m_cTailBytes[KEY_LENGTH];
	char m_cKey[KEY_LENGTH];
	char m_cSignature[KEY_LENGTH];

	unsigned __int64 m_ui64RealFileSize;

	HANDLE m_hFile;

public:
	CFileSignature(void);
	virtual ~CFileSignature(void);

	BOOL Sign(LPCTSTR strFilePath);
	BOOL VerifySignature(LPCTSTR strFilePath);

protected:

	BOOL ReadThreeByteArrays();
	BOOL ReadOneByteArray(HANDLE hFile, LARGE_INTEGER *pliIndex, char* pcBuffer);
	void GenerateSignature();

	void XorTwoByteArray(char *pcFirstBuffer, char *pcSecondBuffer);
	BOOL WriteSignature();
	BOOL CompareSignature();
};
