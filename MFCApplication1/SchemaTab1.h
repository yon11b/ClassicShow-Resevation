﻿#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"


// CSchemaTab1 대화 상자

class CSchemaTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CSchemaTab1)

public:
	CSchemaTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSchemaTab1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCHEMA_DLG1 };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;	
	CDBConnect DB;
	afx_msg void OnBnClickedButton1();
};
