#pragma once
#include "afxdialogex.h"
#include"CustomDlg1.h"
#include"CustomDlg2.h"
#include"CustomDlg3.h"
#include"CustomDlg4.h"
#include"CustomDlg5.h"
#include"CustomAll.h"

// CCustomDlg 대화 상자

class CCustomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomDlg)

public:
	CCustomDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCustomDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSTOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();
	CCustomDlg1 CustomDlg1;
	CCustomDlg2 CustomDlg2;
	CCustomDlg3 CustomDlg3;
	CCustomDlg4 CustomDlg4;
	CCustomDlg5 CustomDlg5;
	CCustomAll CustomAll;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};