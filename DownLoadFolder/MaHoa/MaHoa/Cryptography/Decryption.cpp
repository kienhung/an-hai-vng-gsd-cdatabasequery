#include "StdAfx.h"
#include "Decryption.h"
#include "FileServices.h"

CDecryption::CDecryption(void)
{
	m_pcPreviousDecryptedBlock = new char[KEY_LENGTH];
	memcpy(m_pcPreviousDecryptedBlock, m_pcIV, KEY_LENGTH);

	m_pcSavePreviousDecryptedBlock = new char[KEY_LENGTH];
}

CDecryption::~CDecryption(void)
{
	if (m_pcPreviousDecryptedBlock != NULL) {
		delete [] m_pcPreviousDecryptedBlock;
	}

	if (m_pcSavePreviousDecryptedBlock != NULL) {
		delete [] m_pcSavePreviousDecryptedBlock;
	}	
}

bool CDecryption::ExecuteOneBlock(char *pcBlock, size_t uiSize) {

	if (uiSize != KEY_LENGTH) {
		return false;
	}

	CCrypto::SwapBuffer(pcBlock, pcBlock + uiSize - 1);
	CCrypto::XorBuffers(pcBlock, pcBlock, m_pcKey, KEY_LENGTH);
	return true;
}

bool CDecryption::ExecuteManyBlocks(char *pcBlocks, size_t uiSize) {

	if (uiSize % KEY_LENGTH != 0) {
		return false;
	}

	for (size_t i = 0; i < uiSize; i += KEY_LENGTH) {

		memcpy(m_pcSavePreviousDecryptedBlock, pcBlocks + i, KEY_LENGTH);

		ExecuteOneBlock(pcBlocks + i, KEY_LENGTH);
		CCrypto::XorBuffers(pcBlocks + i, pcBlocks + i, m_pcPreviousDecryptedBlock, KEY_LENGTH);

		memcpy(m_pcPreviousDecryptedBlock, m_pcSavePreviousDecryptedBlock, KEY_LENGTH);
	}

	return true;
}

bool CDecryption::ExecuteFile(const TCHAR *ptcInputFileName, const TCHAR *ptcOutputFileName) {

	HANDLE hInputFile = ::CreateFile(ptcInputFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hInputFile) {
		return false;
	}

	HANDLE hOutputFile = ::CreateFile(ptcOutputFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hOutputFile) {
		CloseHandle(hInputFile);
		return false;
	}

	CFileServices fileServices;
	unsigned __int64 ui64FileSize = fileServices.GetFileSize(hInputFile);

	try {

		if ((ui64FileSize - sizeof(size_t)) % KEY_LENGTH != 0) {
			throw GetLastError();
		}

		size_t uiNumPaddingBytes = 0;
		DWORD dwBytesRead = 0;

		if (FALSE == ::ReadFile(hInputFile, &uiNumPaddingBytes, sizeof(size_t), &dwBytesRead, NULL)) {
			throw GetLastError();
		}

		unsigned __int64 ui64NumBlocks = (ui64FileSize - sizeof(size_t))/KEY_LENGTH;
		TransferCipherToPlain(hInputFile, hOutputFile, ui64NumBlocks, uiNumPaddingBytes);

	} catch (DWORD) {
		CloseHandle(hInputFile);
		CloseHandle(hOutputFile);
		return false;
	}
	
	CloseHandle(hInputFile);
	CloseHandle(hOutputFile);

	return true;
}


void CDecryption::TransferCipherToPlain(HANDLE hInputFile, HANDLE hOutputFile, unsigned __int64 ui64NumBlocks, size_t uiNumPaddingBytes) {

	if (uiNumPaddingBytes > KEY_LENGTH - 1) {
		throw -1;
	}

	const int BUFFER_LENGTH = 4096;
	char strBuffer[BUFFER_LENGTH] = {0};
	DWORD  dwBytesRead = 0;
	DWORD dwBytesWritten = 0;

	unsigned __int64 ui64BlockCount = 0;
	
	do {

		if (FALSE == ::ReadFile(hInputFile, strBuffer, BUFFER_LENGTH, &dwBytesRead, NULL)) {
			throw GetLastError();
		}

		if (dwBytesRead > 0) {

			if (false == ExecuteManyBlocks(strBuffer, dwBytesRead)) {
				throw GetLastError();
			}

			ui64BlockCount += dwBytesRead/KEY_LENGTH;

			if (ui64BlockCount == ui64NumBlocks) {
				dwBytesRead -= uiNumPaddingBytes;
			}

			if (FALSE == ::WriteFile(hOutputFile, strBuffer, dwBytesRead, &dwBytesWritten, NULL)) {
				throw GetLastError();
			}
		}

	} while (dwBytesRead != 0);
}