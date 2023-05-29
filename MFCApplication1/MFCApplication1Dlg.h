
// MFCApplication1Dlg.h: 헤더 파일
//

#pragma once
#include "DBConnect.h"
#include "SignupDlg.h"
#include "SelectDlg.h"
#include "MainDlg.h"
#include "Session.h"

// CMFCApplication1Dlg 대화 상자
class CMFCApplication1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CSignupDlg SignupDlg;
	CMainDlg MainDlg;
	afx_msg void OnBnClickedSignup();
	afx_msg void OnBnClickedLogin();

	CDBConnect DB;
	CEdit m_LoginId;
	CEdit m_LoginPw;
	afx_msg void OnBnClickedFin();
	afx_msg void OnStnClickedTitle();
};
