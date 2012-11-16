// dllmain.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxwin.h>
#include <afxdllx.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static AFX_EXTENSION_MODULE AutoUpdateDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{


		TRACE0("AutoUpdate.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(AutoUpdateDLL, hInstance))
			return 0;

		new CDynLinkLibrary(AutoUpdateDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("AutoUpdate.DLL Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(AutoUpdateDLL);
	}
	return 1;   // ok
}

