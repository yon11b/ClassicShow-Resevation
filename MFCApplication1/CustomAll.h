#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"


// CCustomAll 대화 상자

class CCustomAll : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomAll)

public:
	CCustomAll(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCustomAll();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSTOM_ALL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_UserQuery;
	CDBConnect DB;
};
