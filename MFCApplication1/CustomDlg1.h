#pragma once
#include "afxdialogex.h"
#include "Session.h"
#include "DBConnect.h"

extern CSESSION SESSION;
// CCustomDlg1 대화 상자

class CCustomDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomDlg1)

public:
	CCustomDlg1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCustomDlg1();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSTOM_DLG1 };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();


	CComboBox m_Show;
	CComboBox m_Sound;
	CComboBox m_Total;
	CComboBox m_Seat;
	CComboBox m_View;
	CEdit m_Detail;
	CDBConnect DB;

	CString showno;
	CString hallno;

	CString userid;

	CString sound;
	CString view;
	CString total;
	CString detail;

	afx_msg void OnBnClickedButton1();
};
