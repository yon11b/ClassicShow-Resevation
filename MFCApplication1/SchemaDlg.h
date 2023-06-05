#pragma once
#include "afxdialogex.h"
#include "SchemaTab7.h"

class CSchemaTab1;
class CSchemaTab2;
class CSchemaTab3;
class CSchemaTab4;
class CSchemaTab5;
class CSchemaTab6;
class CSchemaTab7;

// CSchemaDlg 대화 상자

class CSchemaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSchemaDlg)

public:
	CSchemaDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSchemaDlg();
	CSchemaTab1* pDlg1;
	CSchemaTab2* pDlg2;
	CSchemaTab3* pDlg3;
	CSchemaTab4* pDlg4;
	CSchemaTab5* pDlg5;
	CSchemaTab6* pDlg6;
	CSchemaTab7* pDlg7;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCHEMA };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
