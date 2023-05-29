#pragma once
#include "afxdialogex.h"

class CTab1;
class CTab2;
class CTab3;

// CSelectDlg 대화 상자

class CSelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectDlg)

public:
	CSelectDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSelectDlg();
	CTab1 *pDlg1;
	CTab2 *pDlg2;
	CTab3 *pDlg3;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
