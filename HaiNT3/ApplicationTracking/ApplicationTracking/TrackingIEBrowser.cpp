_COM_SMARTPTR_TYPEDEF(IShellWindows, IID_IShellWindows);
_COM_SMARTPTR_TYPEDEF(IWebBrowser2, IID_IWebBrowser2);

#pragma once
#include "StdAfx.h"
#include "WinTabBrowser.h"
#include "TrackingIEBrowser.h"
//#include "ExDisp.h"

////#import <shdocvw.dll>  
////#import <mshtml.tlb>
//#include <atlbase.h>  
//CComModule _Module;       // CComDispatchDriver ATL  
//#include <mshtml.h>       // All IHTMLxxxx interface  
//#include <atlcom.h>  




static IShellWindowsPtr jws_shellwindows(0);


CTrackingIEBrowser::CTrackingIEBrowser()
{
}
CTrackingIEBrowser::~CTrackingIEBrowser()
{

}

BOOL CTrackingIEBrowser::GetHistory(vector<STATURL>& lstStatUrl)
{
	
	STATURL url;
	CString strUrl;

	ULONG uFetched;
	IUrlHistoryStg2* history = NULL;
	
	IEnumSTATURL* enumPtr = NULL;
	
	CoInitialize(NULL);
	if(FAILED(CoCreateInstance(CLSID_CUrlHistory, NULL, CLSCTX_INPROC_SERVER, IID_IUrlHistoryStg2,(void**)&history)))
	{
		return FALSE;
	}

	if(FAILED(history->EnumUrls(&enumPtr)))
		return FALSE;

	while(SUCCEEDED(enumPtr->Next(1,&url,&uFetched)))
	{
		if(uFetched==0)
			break;
		for(int i = 0; i < (int)m_lstTitle.size(); i++)
		{
			
			if(NULL != url.pwcsTitle &&  wcscmp(m_lstTitle[i], url.pwcsTitle) == 0 )
			{
				SYSTEMTIME currentTime;
				::GetLocalTime(&currentTime);
				currentTime.wMinute++;

				FILETIME tempTime;
				SystemTimeToFileTime(&currentTime, &tempTime);

				LARGE_INTEGER lCurrentTime;
				//LARGE_INTEGER lUrlTime;
				
				lCurrentTime.HighPart = tempTime.dwHighDateTime;
				lCurrentTime.LowPart = tempTime.dwLowDateTime;
				
				FileTimeToSystemTime(&url.ftExpires, &currentTime);
				
				STATURL tempUrl = url;
				lstStatUrl.push_back(tempUrl);
				break;
			}
		}
	}
	return TRUE;
}

BOOL CALLBACK CTrackingIEBrowser::enumWindowsProc(HWND hwnd, LPARAM lParam)
{
	vector<CString>* lstTitle = (vector<CString>*)lParam;
	TCHAR strText[250] = {0};
	::GetClassName(hwnd, strText, 250);
	if(wcscmp(strText, _T("TabThumbnailWindow")) == 0)
	{
		wmemset(strText, 0, 250);
		::GetWindowText(hwnd, strText, 250);
		CString strCaption(strText);
		/*int iIndexSub = strCaption.Find(_T("- Windows Internet Explorer"), 0);
		strCaption.Delete(iIndexSub, strCaption.GetLength() - iIndexSub - 1);*/
		strCaption.Replace(_T(" - Windows Internet Explorer"), _T(""));
		lstTitle->push_back(strCaption);
		/*TAB_WEB tabWeb;
		tabWeb.m_strTitle = strCaption;
		lstTabWeb->push_back(tabWeb);*/
	}
	return TRUE;
}



static void jws_enum_ie_tabs(const std::wstring &parent_name, HWND hwnd)
{
	CoInitialize(NULL);
	CComPtr<IShellWindows> spShellWin;  

	HRESULT hr = spShellWin.CoCreateInstance(CLSID_ShellWindows);  
	if ( FAILED ( hr ) )  
	{  
		return;  
	}  

	long nCount = 0;          
	spShellWin->get_Count( &nCount );// Get the count of IE instanceExplorer   
									 //and IExplorer  
	if( 0 == nCount )  
	{  
		return;  
	}  

	for(int i=0; i<nCount; i++)  
	{  
		CComPtr< IDispatch > spDispIE;  
		hr=spShellWin->Item(CComVariant( (long)i ), &spDispIE );  
		if (FAILED(hr))    
			continue;  

		CComQIPtr<IWebBrowser2> spBrowser = spDispIE;  
		if (!spBrowser)       
			continue;  


		/*HWND browser_hwnd;
		if(S_OK != (spBrowser->get_HWND((SHANDLE_PTR *)&browser_hwnd) ) || browser_hwnd != hwnd)
		continue;*/

		CComPtr < IDispatch > spDispDoc;  
		hr = spBrowser->get_Document( &spDispDoc );//check instance  
													//object is or no IE  
		if (FAILED(hr))    
			continue;
	
		CComQIPtr< IHTMLDocument2 > spDocument2 = spDispDoc;
		if (!spDocument2)     continue;
		
		_bstr_t title, uri;
		BSTR title_b, uri_b;
		
		spBrowser->get_LocationURL(&uri_b);
		//spBrowser->get_Name(&title_b);
		if(S_OK != spBrowser->get_LocationName(&title_b))
			title = _bstr_t(L"");
		else
		title.Attach(title_b);
		CString s(title_b);
		CString t(uri_b);
		s.AppendFormat(_T("\n%s"), t);
		AfxMessageBox(s);
	} 
	CoUninitialize();//release COM  


#pragma region
  //VARIANT v;
  //V_VT(&v) = VT_I4;
  //IDispatchPtr disp(0);
  //HRESULT hrt;
  //
  //for(V_I4(&v) = 0; S_OK == (hr = jws_shellwindows->Item(v, &disp)); V_I4(&v)++)
  //{
  //  // Cast to IWebBrowser2
  //  IWebBrowser2Ptr browser(0);
	
  //  if(S_OK != disp->QueryInterface(IID_IWebBrowser2, (void **)&browser))
  //    continue;
  //  // Verify if it is inside the desired window
  //  HWND browser_hwnd;
  //  if(S_OK != (browser->get_HWND((SHANDLE_PTR *)&browser_hwnd) ) || browser_hwnd != hwnd)
  //    continue;
  //  
  //  // OK, we got a TAB from this browser

  //  // Get the tab's HWND, it will be used to determine if the table is active
  //  IServiceProviderPtr servProv(0);
  //  IOleWindowPtr oleWnd(0);
  //  HWND tab_hwnd;
  //  _bstr_t title, uri;
  //  BSTR title_b, uri_b;
  //  if(S_OK != browser->QueryInterface(IID_IServiceProvider, (void **)&servProv))
  //    continue;
  //  if(S_OK != servProv->QueryService(SID_SShellBrowser, IID_IOleWindow, (void **)&oleWnd))
  //    continue;
  //  if(S_OK != oleWnd->GetWindow(&tab_hwnd))
  //    continue;

  //  // Add to the window list
  //  if(S_OK != browser->get_LocationName(&title_b))
  //    title = _bstr_t(L"");
  //  else
  //    title.Attach(title_b);
  //  if(S_OK != browser->get_LocationURL(&uri_b))
  //    uri = _bstr_t(L"");
  //  else
  //    uri.Attach(uri_b);

    //jws_windows.push_back(JWS_WINDOW_DATA(parent_name, hwnd, tab_hwnd, hicon, title, uri, browser));
#pragma endregion
  
}
static BOOL CALLBACK WindowsProc(HWND hwnd, LPARAM lParam)
{
	wchar_t title[512];

  DWORD dwStyle = GetWindowLongPtr(hwnd, GWL_STYLE);
  if(!(dwStyle & WS_VISIBLE))
    return TRUE;
  GetWindowText(hwnd, title, _countof(title));
  if(!title[0])
    return TRUE;
  LONG exstyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
  if(exstyle & WS_EX_TOOLWINDOW)
    return TRUE;
  
  //jws_windows.push_back(JWS_WINDOW_DATA(hwnd, hicon, title));

  wchar_t className[512];
  if(GetClassName(hwnd, className, _countof(className)))
  {
	  if(!(wcscmp(className, L"IEFrame")))
      jws_enum_ie_tabs(title, hwnd);
  }
	return TRUE;
}


VOID CTrackingIEBrowser::Track()
{
	EnumWindows(WindowsProc, NULL);
	/*EnumWindows(enumWindowsProc, (LPARAM)&m_lstTitle);
	vector<STATURL> lstStatURL;
	GetHistory(lstStatURL);*/


}