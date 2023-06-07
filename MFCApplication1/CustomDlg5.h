#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"
#include "Session.h"


// CCustomDlg5 대화 상자

class CCustomDlg5 : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomDlg5)

public:
	CCustomDlg5(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCustomDlg5();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSTOM_DLG5 };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CDBConnect DB;
	CDateTimeCtrl m_StartDate;
	CDateTimeCtrl m_EndDate;
	CListCtrl m_ListCtrl;
};
