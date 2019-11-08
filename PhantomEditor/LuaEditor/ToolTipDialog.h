/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once


// CToolTipDialog �Ի���

class CToolTipDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CToolTipDialog)

public:
	CToolTipDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CToolTipDialog();

// �Ի�������
	enum { IDD = 0 };

	VOID		ShowToolTip(CWnd* wnd, const wchar_t* szText, const POINT& pos, int nTimeMillisecond = 5000);	//
	//
	HWND		m_tipWindow;
	CString		m_strToolTip;
	INT			m_nTimeMillisecond;
	CImage		m_backImage;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};