// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <shlobj.h>
#include <windows.h>
#include <stdio.h>

#ifdef _MANAGED
#pragma managed(push, off)
#endif

static HINSTANCE	hInstDLL;
static HHOOK	hHook;
static HWND		hMainWnd;
void UnHideAllWindows();

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	hInstDLL = (HINSTANCE) hModule;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


void UnHideAllWindows()
{
	HWND lHwnd = FindWindow(L"Shell_TrayWnd",NULL);
	SendMessage(lHwnd,WM_COMMAND,416,0);
}
LRESULT CALLBACK Xuly(int nCode,   WPARAM wParam, LPARAM lParam)
{
	//if (nCode < 0)  // do not process message 
 //       return CallNextHookEx( hHook, nCode, wParam, lParam );
	//
	//
	//LRESULT RetVal = CallNextHookEx( hHook, nCode, wParam, lParam );
	//return  RetVal;

	if (nCode < 0)  // do not process message 
		return CallNextHookEx( hHook, nCode, wParam, lParam );
	if (!(hMainWnd)) return CallNextHookEx(hHook,nCode,wParam,lParam);
	
	
	/*HWND lHwnd = FindWindow(L"Shell_TrayWnd",NULL);
	SendMessage(lHwnd,WM_COMMAND,419,0);*/

	HWND hWnd = NULL;
	HWND hDesktop = GetDesktopWindow();
	do{
		hWnd = FindWindowEx(hDesktop, hWnd, 0, 0);
		
		if(NULL != hWnd && hMainWnd != hWnd && IsWindowVisible(hWnd) && IsWindow(hWnd))
		{
			SendMessage(hWnd, WM_SHOWWINDOW, FALSE, 0);
			SetWindowPos( hWnd, HWND_BOTTOM,0,0,0,0,SWP_NOACTIVATE|SWP_NOSIZE);
			
		}
	}while(hWnd);
	
	
	/*HWND htop = GetTopWindow(NULL);
	if(htop != hMainWnd && IsWindowVisible(htop))
	{
		ShowWindow(htop, SW_SHOWMINIMIZED);
	}*/


	//DWORD idMyProcess;
	//GetWindowThreadProcessId(hMainWnd,&idMyProcess);
	HWND hForground = GetForegroundWindow();


	
	
	SetForegroundWindow(hMainWnd);
	SetWindowPos( hMainWnd, HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	SendMessage(hMainWnd, WM_MOUSEACTIVATE,(WPARAM)hMainWnd,(LPARAM)NULL );

	
	
	/*if(hForground != hMainWnd)
	{
		
		SendMessage(hMainWnd,WM_ACTIVATE, MAKEWPARAM( WA_ACTIVE, 0), (LPARAM)GetCurrentProcess());
		
		AttachThreadInput(GetWindowThreadProcessId(hForground, NULL), GetCurrentThreadId(), TRUE);
		SetForegroundWindow(hMainWnd);
		SwitchToThisWindow(hMainWnd, TRUE);
		SendMessage(NULL, WM_ACTIVATE, MAKEWPARAM( WA_INACTIVE, 0),(LPARAM)hMainWnd );
		
		BringWindowToTop(hMainWnd);
		SetWindowPos( hMainWnd, hForground,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		AttachThreadInput(GetWindowThreadProcessId(hForground, NULL), GetCurrentThreadId(), FALSE);
	}*/

	
	return CallNextHookEx(hHook,nCode,wParam,lParam);
	
	
}

// Install hook
 __declspec(dllexport) void doSetForegroundGlobalHook(HWND hWnd)
 {
	// Init value for MappedData	
	 hMainWnd = hWnd;
	 hHook = SetWindowsHookEx(WH_FOREGROUNDIDLE, (HOOKPROC)Xuly, hInstDLL, 0);
 }



// Remove hook
 __declspec(dllexport) void doRemoveGlobalHook()
{
	UnHideAllWindows();
	UnhookWindowsHookEx(hHook);
}
#ifdef _MANAGED
#pragma managed(pop)
#endif