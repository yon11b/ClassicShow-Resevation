#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"


// CDeleteTab1 대화 상자

class CDeleteTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteTab1)

public:
	CDeleteTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDeleteTab1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE_DLG1 };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	CEdit m_ShowNo;
	CDBConnect DB;
	afx_msg void OnBnClickedButton2();
};
