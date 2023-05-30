#pragma once
#include "afxdialogex.h"

class CInsertTab1;
class CInsertTab2;
class CInsertTab3;

// CInsertDlg 대화 상자

class CInsertDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertDlg)

public:
	CInsertDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInsertDlg();

	CInsertTab1 *pDlg1;
	CInsertTab2* pDlg2;
	CInsertTab3* pDlg3;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ConcertBox;
	CComboBox m_HallBox;
	virtual BOOL OnInitDialog();
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
