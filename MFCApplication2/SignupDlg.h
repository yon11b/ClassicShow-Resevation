#pragma once
#include "afxdialogex.h"
#include <afxdb.h>
#include "DBConnect.h"


// CSignupDlg 대화 상자

class CSignupDlg : public CDialog
{
	DECLARE_DYNAMIC(CSignupDlg)

public:
	CDBConnect DB;
	CEdit m_UserName;
	CEdit m_UserId;
	CEdit m_UserPw;
	CEdit m_CardNo;
	CEdit m_CardBal;
	CEdit m_CardPw;
	CSignupDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSignupDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIGNUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSubmit();
	afx_msg void OnBnClickedExit();
};
