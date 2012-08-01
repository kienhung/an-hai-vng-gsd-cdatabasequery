/**************************************************************
 * MakewWindowTransparent.cpp
 * Copyright 2003, East Coast Toolworks LLC.
 *
 * by Mike Schaeffer
 * mschaef@mschaef.com
 *
 * Permission is freely granted to make use of this code as you
 * see fit. Nothing is guaranteed about this code and no warranties
 * are provided about suitability for any purpose.
 */

#include "stdafx.h"
#include "MakeWindowTransparent.h"

/**************************************************************
 * MakeWindowTrasparent(window, factor)
 *
 * A function that will try to make a window transparent
 * (layered) under versions of Windows that support that kind
 * of thing. Gracefully fails on versions of Windows that
 * don't.
 *
 * Returns FALSE if the operation fails.
 */

typedef DWORD (WINAPI *PSLWA)(HWND, DWORD, BYTE, DWORD);

static PSLWA pSetLayeredWindowAttributes = NULL;
static BOOL initialized = FALSE;

bool MakeWindowTransparent(HWND hWnd, unsigned char factor)
{
	/* First, see if we can get the API call we need. If we've tried
	 * once, we don't need to try again. */
	if (!initialized)
	{
		HMODULE hDLL = LoadLibrary (_T("user32"));

		pSetLayeredWindowAttributes = 
			(PSLWA) GetProcAddress(hDLL, "SetLayeredWindowAttributes");

		initialized = TRUE;
	}

	if (pSetLayeredWindowAttributes == NULL) 
		return FALSE;

	/* Windows need to be layered to be made transparent. This is done
		* by modifying the extended style bits to contain WS_EX_LAYARED. */
	SetLastError(0);

	SetWindowLong(hWnd, 
				GWL_EXSTYLE , 
				GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	if (GetLastError())
		return FALSE;

	/* Now, we need to set the 'layered window attributes'. This
	* is where the alpha values get set. */
	return pSetLayeredWindowAttributes (hWnd, 
                                        RGB(255,255,255), 
                                        factor,
                                        LWA_COLORKEY|LWA_ALPHA);
}

bool MakeWindowTransparent(CWnd *w, unsigned char factor)
{
	HWND wnd = w->GetSafeHwnd();

	ASSERT(wnd);

	return MakeWindowTransparent(wnd, factor);
}