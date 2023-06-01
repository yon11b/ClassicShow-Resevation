#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"
#include "SeatSacDlg.h"
#include "SeatLotteDlg.h"
#include "SeatSejongDlg.h"
#include "Session.h"

extern CSESSION SESSION;
// CInsertTab3 대화 상자

class CInsertTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertTab3)

public:
	CInsertTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInsertTab3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERT_DLG3 };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl; 
	CDBConnect DB;
	CSeatSacDlg SeatSacDlg;
	CSeatLotteDlg SeatLotteDlg;
	CSeatSejongDlg SeatSejongDlg;

	afx_msg void OnEnChangeEdit1();
	CEdit m_ShowNo;
	afx_msg void OnBnClickedBtn();
};
