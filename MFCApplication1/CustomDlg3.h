#pragma once
#include "afxdialogex.h"
#include "Session.h"
#include "DBConnect.h"


// CCustomDlg3 대화 상자

class CCustomDlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomDlg3)

public:
	CCustomDlg3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCustomDlg3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSTOM_DLG3 };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CComboBox m_HallBox;
	CComboBox m_ConcertBox;
	afx_msg void OnCbnSelchangeCombo1();
	CListCtrl m_ListCtrl;
};
