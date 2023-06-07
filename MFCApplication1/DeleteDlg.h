#pragma once
#include "afxdialogex.h"

class CDeleteTab1;
class CDeleteTab2;
class CDeleteTab3;
class CDeleteTab4;

// CDeleteDlg 대화 상자

class CDeleteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteDlg)

public:
	CDeleteDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDeleteDlg();
	
	CDeleteTab1* pDlg1;
	CDeleteTab2* pDlg2;
	CDeleteTab3* pDlg3;
	CDeleteTab4* pDlg4;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
