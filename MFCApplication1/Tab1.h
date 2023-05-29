#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"


// CTab1 대화 상자

class CTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab1)

public:
	CTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CDBConnect DB;
	CListCtrl m_ListCtrl;
	CDateTimeCtrl m_DateStart;
	CDateTimeCtrl m_DateFinish;
	afx_msg void OnBnClickedBtnSelectshow();
};
