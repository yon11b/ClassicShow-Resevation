﻿#pragma once
#include "afxdialogex.h"
#include "SelectDlg.h"
#include "InsertDlg.h"
#include "UpdateDlg.h"
#include "DeleteDlg.h"
#include "SchemaDlg.h"
#include "CustomDlg.h"

// CMainDlg 대화 상자

class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMainDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSelectDlg SelectDlg;
	CInsertDlg InsertDlg;
	CUpdateDlg UpdateDlg;
	CDeleteDlg DeleteDlg;
	CSchemaDlg SchemaDlg;
	CCustomDlg CustomDlg;
	afx_msg void OnBnClickedSchemaCheck();
	afx_msg void OnBnClickedSelectQuery();
	afx_msg void OnBnClickedInsertQuery();
	afx_msg void OnBnClickedUpdateQuery();
	afx_msg void OnBnClickedDeleteQuery();
	afx_msg void OnBnClickedCustomQuery();
};
