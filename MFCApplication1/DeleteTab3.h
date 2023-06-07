#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"


// CDeleteTab3 대화 상자

class CDeleteTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteTab3)

public:
	CDeleteTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDeleteTab3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE_DLG3 };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	CDBConnect DB;
	afx_msg void OnBnClickedButton1();
	CEdit m_ShowNo;
};
