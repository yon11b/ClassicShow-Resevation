﻿#pragma once
#include "afxdialogex.h"


// CSeatSacDlg 대화 상자

class CSeatSacDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSeatSacDlg)

public:
	CSeatSacDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSeatSacDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEAT_SAC_CONCERT };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_Seat1;
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBnClickedButton1();
};
