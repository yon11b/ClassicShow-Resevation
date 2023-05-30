#pragma once
#include "afxdialogex.h"
#include "UpdateTab1.h"
#include "UpdateTab2.h"
#include "UpdateTab3.h"

class CUpdateTab1;
class CUpdateTab2;
class CUpdateTab3;

// CUpdateDlg 대화 상자

class CUpdateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateDlg)

public:
	CUpdateDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUpdateDlg();
	CUpdateTab1* pDlg1;
	CUpdateTab2* pDlg2;
	CUpdateTab3* pDlg3;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
