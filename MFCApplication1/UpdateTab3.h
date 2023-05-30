#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"


// CUpdateTab3 대화 상자

class CUpdateTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateTab3)

public:
	CUpdateTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUpdateTab3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE_DLG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_BeforePw;
	CEdit m_AfterPw;
	CDBConnect DB;
	afx_msg void OnBnClickedButton1();
	CEdit m_AccountNo;
	CEdit m_AccountPw;
	CEdit m_Balance;
	afx_msg void OnBnClickedButton2();
};
