#include "StdAfx.h"
#include "Encryption.h"
#include "FileServices.h"

CEncryption::CEncryption(void)
{
	m_pcPreviousEncryptedBlock = new char[KEY_LENGTH];
	memcpy(m_pcPreviousEncryptedBlock, m_pcIV, KEY_LENGTH);
}

CEncryption::~CEncryption(void)
{
	if (m_pcPreviousEncryptedBlock != NULL) {
		delete [] m_pcPreviousEncryptedBlock;
	}
}

bool CEncryption::ExecuteOneBlock(char *pcBlock, size_t uiSize) {

	if (uiSize != KEY_LENGTH) {
		return false;
	}
	CCrypto::XorBuffers(pcBlock, pcBlock, m_pcKey, KEY_LENGTH);
	CCrypto::SwapBuffer(pcBlock, pcBlock + uiSize - 1);
	return true;
}

bool CEncryption::ExecuteManyBlocks(char *pcBlocks, size_t uiSize) {

	if (uiSize % KEY_LENGTH != 0) {
		return false;
	}

	for (size_t i = 0; i < uiSize; i += KEY_LENGTH) {

		CCrypto::XorBuffers(pcBlocks + i, pcBlocks + i, m_pcPreviousEncryptedBlock, KEY_LENGTH);
		ExecuteOneBlock(pcBlocks + i, KEY_LENGTH);
			
		memcpy(m_pcPreviousEncryptedBlock, pcBlocks + i, KEY_LENGTH);
	}

	return true;
}

bool CEncryption::ExecuteFile(const TCHAR *ptcInputFileName, const TCHAR *ptcOutputFileName) {

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
	
	size_t uiNumPaddingBytes = 0;
	if (ui64FileSize % KEY_LENGTH != 0) {
		uiNumPaddingBytes = KEY_LENGTH - (ui64FileSize % KEY_LENGTH);
	}

	try {

		DWORD dwBytesWritten = 0;

		if (FALSE == ::WriteFile(hOutputFile, &uiNumPaddingBytes, sizeof(size_t), &dwBytesWritten, NULL)) {
			throw GetLastError();
		}

		TransferPlainToCipher(hInputFile, hOutputFile, uiNumPaddingBytes);
		
	} catch (DWORD) {
		
		CloseHandle(hInputFile);
		CloseHandle(hOutputFile);
		return false;
	}

	CloseHandle(hInputFile);
	CloseHandle(hOutputFile);

	return true;
}

void CEncryption::TransferPlainToCipher(HANDLE hInputFile, HANDLE hOutputFile, size_t uiNumPaddingBytes) {

	if (uiNumPaddingBytes > KEY_LENGTH - 1) {
		throw -1;
	}

	const int BUFFER_LENGTH = 4096;
	char strBuffer[BUFFER_LENGTH] = {0};
	DWORD  dwBytesRead = 0;
	DWORD dwBytesWritten = 0;

	do {

		if (FALSE == ::ReadFile(hInputFile, strBuffer, BUFFER_LENGTH, &dwBytesRead, NULL)) {
			throw GetLastError();
		}

		if (dwBytesRead > 0) {

			while (dwBytesRead % KEY_LENGTH != 0) {
				strBuffer[dwBytesRead] = EOF;
				dwBytesRead++;
			}

			if (false == ExecuteManyBlocks(strBuffer, dwBytesRead)) {
				throw GetLastError();
			}

			if (FALSE == ::WriteFile(hOutputFile, strBuffer, dwBytesRead, &dwBytesWritten, NULL)) {
				throw GetLastError();
			}
		}
		
	} while (dwBytesRead != 0);
}
