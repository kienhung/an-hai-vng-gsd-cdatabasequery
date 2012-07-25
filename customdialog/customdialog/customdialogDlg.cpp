
// customdialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "customdialog.h"
#include "customdialogDlg.h"
using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CcustomdialogDlg dialog




CcustomdialogDlg::CcustomdialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CcustomdialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsPress = false;
	m_Rectangle.SetRectEmpty();
}

void CcustomdialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstCtrlEx);
}

BEGIN_MESSAGE_MAP(CcustomdialogDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCMOUSEHOVER()
END_MESSAGE_MAP()


// CcustomdialogDlg message handlers

BOOL CcustomdialogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	DWORD dwStyle = m_lstCtrlEx.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	m_lstCtrlEx.SetExtendedStyle(dwStyle);
	InitListCtrl();
	InitImageList();
	m_lstCtrlEx.SetRedraw(FALSE);
	InsertItems();
	m_lstCtrlEx.SetRedraw(TRUE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CcustomdialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CcustomdialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
	
		//SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		
		//CDialog::OnPaint();
		if(!m_Rectangle.IsRectEmpty())
		{
			CPaintDC dc(this);
			CDC mdc; // memory DC
			mdc.CreateCompatibleDC(&dc);
			Graphics graphics(dc.m_hDC);
			//DrawItemss(graphics, &m_Rectangle);
			graphics.BeginContainer();
			// create and select a thick, black pen
			DrawItemss(&graphics, &m_Rectangle);
		}
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CcustomdialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CcustomdialogDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnLButtonDown(nFlags, point);
	if(!m_bIsPress)
	{
		m_bIsPress = true;
		m_pOldPoint = point;
		
	}
}

void CcustomdialogDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnLButtonUp(nFlags, point);
	if(m_bIsPress)
	{
		m_bIsPress = false;
		m_pOldPoint.x = -1;
		m_pOldPoint.y = -1;
		m_Rectangle.SetRectEmpty();
	}
}

void CcustomdialogDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//CDialog::OnMouseMove(nFlags, point);

	if(m_pOldPoint != point &&  m_pOldPoint.x >=0 && m_bIsPress)
	{
		if(m_pOldPoint.x <= point.x && m_pOldPoint.y <= point.y)
		{
			m_Rectangle.SetRect(m_pOldPoint, point);
		}else if(m_pOldPoint.x <= point.x && m_pOldPoint.y > point.y)
		{
			m_Rectangle.SetRect(m_pOldPoint.x, point.y, point.x, m_pOldPoint.y);
		}else if(m_pOldPoint.x > point.x && m_pOldPoint.y <= point.y)
		{
			m_Rectangle.SetRect(point.x, m_pOldPoint.y, m_pOldPoint.x, point.y);
		}else
		{
			m_Rectangle.SetRect(point, m_pOldPoint);
		}
		AfxGetMainWnd()->Invalidate();
	}
}
void CcustomdialogDlg::DrawItemss(Graphics* graphics, CRect* rect)
{
	
			//CDC mdc; // memory DC
			//mdc.CreateCompatibleDC(&dc);
			
   CPen penBlack;
			penBlack.CreatePen(PS_SOLID, 3, RGB(100, 255, 0));

			SolidBrush brushBlue(Color(0, 0, 255));
			// get our client rectangle
			//CRect rect;
			//GetClientRect(rect);
			Pen pen(&brushBlue);
		
			
			Rect rectTemp(rect->left, rect->top, rect->Width(), rect->Height());
			graphics->FillRectangles(&brushBlue, &rectTemp, 1);
			
			//graphics.DrawRectangles(&pen, &rect, 1);
}
void CcustomdialogDlg::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	::OutputDebugString(_T("OnncLbuttonUP \n"));
	CDialog::OnNcLButtonUp(nHitTest, point);
}

void CcustomdialogDlg::OnNcMouseHover(UINT nFlags, CPoint point)
{
	// This feature requires Windows 2000 or greater.
	// The symbols _WIN32_WINNT and WINVER must be >= 0x0500.
	// TODO: Add your message handler code here and/or call default
	::OutputDebugString(_T("OnncMouseHover \n"));
	CDialog::OnNcMouseHover(nFlags, point);
}
void CcustomdialogDlg::InitListCtrl()
{
	CRect rect;
	m_lstCtrlEx.GetClientRect(&rect);
	int nColInterval = rect.Width()/2;
	m_lstCtrlEx.InsertColumn(0, _T("Item Name"), LVCFMT_LEFT, nColInterval);
	m_lstCtrlEx.InsertColumn(1, _T("Value"), LVCFMT_LEFT, nColInterval); 
}

BOOL CcustomdialogDlg::InitImageList()
{

	HIMAGELIST hList = ImageList_Create(32,32, ILC_COLOR8 |ILC_MASK , 8, 1);
	m_cImageListNormal.Attach(hList);

	//hList = ImageList_Create(16, 16, ILC_COLOR8 | ILC_MASK, 8, 1);
	//m_cImageListSmall.Attach(hList);


	// Load the large icons
	CBitmap cBmp;
	cBmp.LoadBitmap(IDB_LISTBITMAP_NORMAL);
	m_cImageListNormal.Add(&cBmp, RGB(255,0, 255));
	cBmp.DeleteObject();

	// Load the small icons
	//cBmp.LoadBitmap(IDB_IMAGES_SMALL);
	//m_cImageListSmall.Add(&cBmp, RGB(255,0, 255));

	// Attach them
	m_lstCtrlEx.SetImageList(&m_cImageListNormal, LVSIL_NORMAL);
	//m_lstCtrlEx.SetImageList(&m_cImageListSmall, LVSIL_SMALL);
 	return TRUE;
}

void CcustomdialogDlg::InsertItems()
{
	int count = m_lstCtrlEx.GetItemCount();
	m_lstCtrlEx.DeleteAllItems();

	// Use the LV_ITEM structure to insert the items
	LVITEM lvi;
	CString strItem;
	for (int i = 0; i < 50; i++)
	{
		// Insert the first item
		lvi.mask =  LVIF_IMAGE | LVIF_TEXT;
		strItem.Format(_T("Item %i"), i);
	
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
		lvi.iImage = i%8;
		m_lstCtrlEx.InsertItem(&lvi);

		// Set subitem 1
		strItem.Format(_T("%d"), 10*i);
		lvi.iSubItem =1;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
		m_lstCtrlEx.SetItem(&lvi);

	}
	count = m_lstCtrlEx.GetItemCount();
}