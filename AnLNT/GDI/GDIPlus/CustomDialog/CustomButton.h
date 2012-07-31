#pragma once


// CCustomButton

class CCustomButton : public CButton
{
	DECLARE_DYNAMIC(CCustomButton)

public:

	CCustomButton();
	virtual ~CCustomButton();
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnPaint( );
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);


	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct );

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseHover(WPARAM,LPARAM);
	afx_msg LRESULT OnMouseLeave(WPARAM,LPARAM);

protected:
	int m_isInClient;
	DECLARE_MESSAGE_MAP()
};


