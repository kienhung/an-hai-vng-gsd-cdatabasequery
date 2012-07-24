#include "StdAfx.h"
#include "Crypto.h"

CCrypto::CCrypto(void) : KEY_LENGTH(8)
{
	m_pcKey = new char[KEY_LENGTH];
	m_pcKey[0] = 21;

	for (size_t i = 1; i < KEY_LENGTH; i++) {
		m_pcKey[i] = 3*i - 2* m_pcKey[i - 1] + 4;
	}

	m_pcIV = new char[KEY_LENGTH];
	m_pcIV[0] = -30;

	for (size_t i = 1; i < KEY_LENGTH; i++) {
		m_pcIV[i] = 2*i + 3*m_pcIV[i - 1] - 4;	
	}
}

CCrypto::~CCrypto(void)
{
	if (m_pcKey != NULL) {
		delete[] m_pcKey;
	}
	if (m_pcIV != NULL) {
		delete[] m_pcIV;
	}
}
bool CCrypto::SetKey(char *pcKey, size_t uiLength) {

	if (uiLength != KEY_LENGTH) {
		return false;
	}

	memcpy(m_pcKey, pcKey, KEY_LENGTH);
	return true;
}

void CCrypto::XorBuffers(char *pcDest, char *pcFirstSource, char *pcSecondSource, size_t uiSize) {

	for (size_t i = 0; i < uiSize; i++) {
		pcDest[i] = pcFirstSource[i] ^ pcSecondSource[i];
	}
}

void CCrypto::SwapBuffer(char *pcBegin, char *pcEnd) {

	while (pcBegin < pcEnd) {
		(*pcBegin) = (*pcBegin) ^ (*pcEnd);
		(*pcEnd) = (*pcEnd) ^ (*pcBegin);
		(*pcBegin) = (*pcBegin) ^ (*pcEnd);

		pcBegin++;
		pcEnd--;
	}
}