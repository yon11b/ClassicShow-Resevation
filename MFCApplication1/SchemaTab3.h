#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"

// CSchemaTab3 대화 상자

class CSchemaTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CSchemaTab3)

public:
	CSchemaTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSchemaTab3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCHEMA_DLG3 };
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
