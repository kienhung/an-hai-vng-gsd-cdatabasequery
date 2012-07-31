
// CustomDialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CustomDialog.h"
#include "CustomDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCustomDialogDlg dialog




CCustomDialogDlg::CCustomDialogDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCustomDialogDlg::IDD, pParent), m_image(L"D:\\vng.png")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_imageX = 60;
	m_imageY = 100;	
	m_bIsPress = false;
}

void CCustomDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCustomDialogDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CCustomDialogDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_MYBUTTON, &CCustomDialogDlg::OnBnClickedMyButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


BOOL CCustomDialogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	m_myButton.Create(_T("My button"),  WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_OWNERDRAW, CRect(10, 5, 30, 20), this, IDC_BTN_MYBUTTON);

	return TRUE;  
}



void CCustomDialogDlg::OnPaint()
{

	CPaintDC dc(this);
	Graphics graphics(dc.m_hDC);

	
	CRect rect;
	GetClientRect(&rect);

	Bitmap bitmap(rect.Width(), rect.Height(), &graphics);
	Graphics tempGraph(&bitmap);

	Point pointStart (rect.left, rect.top);
	Point pointEnd (rect.right, rect.bottom);

	LinearGradientBrush linGrBrush(pointStart, pointEnd, Color(255, 200, 200, 200), Color(255, 219, 219, 219));
	tempGraph.FillRectangle(&linGrBrush, rect.left, rect.top, rect.right, rect.bottom);

	SolidBrush brush(Color(255, 120, 120, 120));
	tempGraph.FillRectangle(&brush, 0, 0, m_iTitleBarWidth, m_iTitleBarHeigth);

	Pen pen(Color(255, 120, 120, 120), 1);
	pen.SetAlignment(PenAlignmentInset);
	tempGraph.DrawRectangle(&pen, rect.left, rect.top, rect.right - 1, rect.bottom - 1);

	RectF dest((float)m_imageX, (float)m_imageY, (float)m_image.GetWidth(), (float)m_image.GetHeight());
	tempGraph.DrawImage(&m_image, dest, 0, 0, (float)m_image.GetWidth(), (float)m_image.GetHeight(), UnitPixel, NULL);
	

	graphics.DrawImage(&bitmap, rect.left, rect.top);
}


HCURSOR CCustomDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCustomDialogDlg::OnLButtonDown(UINT nFlags, CPoint point)
{

	CDialog::OnLButtonDown(nFlags, point);
	
	if (point.x > 0 
		&& point.x < m_iTitleBarWidth 
		&& point.y > 0
		&& point.y < m_iTitleBarHeigth) {
		
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, NULL);
	} else {

	}

	if (point.x > m_imageX 	&& point.x < m_imageX + (int)m_image.GetWidth()
		&&  point.y > m_imageY 	&& point.y < m_imageY + (int)m_image.GetHeight()) {

			m_bIsPress = true;
			SetCapture();
	}
}	

void CCustomDialogDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	m_iTitleBarWidth = cx;
	m_iTitleBarHeigth = 30;
}

void CCustomDialogDlg::OnBnClickedButton1()
{
	DestroyWindow();
}


void CCustomDialogDlg::OnBnClickedMyButton(){

	DestroyWindow();
}
BOOL CCustomDialogDlg::OnEraseBkgnd(CDC* pDC) {

	return TRUE;
}
void CCustomDialogDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (true == m_bIsPress) {

		CRect rect;
		GetClientRect(&rect);

		
		m_imageX = point.x;
		m_imageY = point.y;
	
		this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	}

	CDialog::OnMouseMove(nFlags, point);
}

void CCustomDialogDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	

	m_bIsPress = false;
	ReleaseCapture();

	CRect rect;
	GetClientRect(&rect);

	if (m_imageX < rect.left) {
		m_imageX = rect.left;
	}

	if (m_imageX > rect.right - (int) m_image.GetWidth()) {
		m_imageX = rect.right - (int) m_image.GetWidth();
	}

	if (m_imageY < rect.top) {
		m_imageY = rect.top;
	}

	if (m_imageY > rect.bottom - (int)m_image.GetHeight()) {
		m_imageY = rect.bottom - (int)m_image.GetHeight();
	}

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	
	CDialog::OnLButtonUp(nFlags, point);
}

