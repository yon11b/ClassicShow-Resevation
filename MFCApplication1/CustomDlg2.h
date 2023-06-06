#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"



extern CSESSION SESSION;
// CCustomDlg2 대화 상자

class CCustomDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomDlg2)

public:
	CCustomDlg2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCustomDlg2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSTOM_DLG2 };
#endif

protected:
	virtual BOOL OnInitDialog();
	CDBConnect DB;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
