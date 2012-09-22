#pragma once

#ifdef CSMCTRLS_EXPORTS
#define CSMCTRLS_API __declspec(dllexport)
#else
#define CSMCTRLS_API __declspec(dllimport)
#endif

extern "C"
{
	CSMCTRLS_API int CSMMessageBox(LPCTSTR lpszText, LPCTSTR lpszCaption = NULL, UINT nType = MB_OK, LPCTSTR lpszFontName = NULL);
	CSMCTRLS_API void CSMMsgBoxInit(LPCTSTR lpszLanguage, LPCTSTR lpszFontName = NULL, LPCTSTR lpszDefaultCaption = NULL);
};
	CSMCTRLS_API int CSMMessageBox(HWND hWnd, LPCTSTR lpszText, LPCTSTR lpszCaption = NULL, UINT nType = MB_OK, LPCTSTR lpszFontName = NULL);