#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"


// CSchemaTab4 대화 상자

class CSchemaTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CSchemaTab4)

public:
	CSchemaTab4(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSchemaTab4();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCHEMA_DLG4 };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CDBConnect DB;
	afx_msg void OnBnClickedButton1();
	CListCtrl m_ListCtrl;
};
