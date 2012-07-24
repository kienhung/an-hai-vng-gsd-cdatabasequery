// TestDLL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment (lib, "lib/Cryptography.lib")
#include "Crypto.h"
#include "Encryption.h"
#include "Decryption.h"

// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		TCHAR strInput[] = _T("D:\\input(1).txt");
		TCHAR strOut[] = _T("D:\\output(1).txt");
		CCrypto *pCrypto = new CEncryption();

		//TCHAR strInput[] = _T("D:\\output(1).txt");
		//TCHAR strOut[] = _T("D:\\decryptedOutput(1).txt");
		//CCrypto *pCrypto = new CDecryption();

		try {

			if (pCrypto->ExecuteFile(strInput, strOut) == false) {
				throw 1;
			}
			printf("thanh cong\n");

		} catch (int) {
			printf("Loi\n");
		}

		delete pCrypto;
	}

	return nRetCode;
}
