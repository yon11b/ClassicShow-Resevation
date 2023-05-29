#pragma once
#include "afxdialogex.h"


// CSeatDlg 대화 상자

class CSeatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSeatDlg)

public:
	CSeatDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSeatDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEAT_SAC_CONCERT };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_SeatGroup;
	CBrush m_brCheck;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton1();
};
