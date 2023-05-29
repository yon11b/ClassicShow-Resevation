#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"
#include "Session.h"


extern CSESSION SESSION; // 전역 객체 선언

// CTab3 대화 상자

class CTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab3)

public:
	CTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CDBConnect DB;
	afx_msg void OnBnClickedBtnSelectasc();
	afx_msg void OnBnClickedBtnSelectdesc();
	CListCtrl m_ListCtrl;
};
