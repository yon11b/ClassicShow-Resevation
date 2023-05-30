#pragma once
#include "afxdialogex.h"
#include "Session.h"
#include "DBConnect.h"


extern CSESSION SESSION; // 전역 객체 선언
// CInsertTab2 대화 상자

class CInsertTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertTab2)

public:
	CInsertTab2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInsertTab2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERT_DLG2 };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CDBConnect DB;
	CEdit m_Section;
	CEdit m_Sound;
	CEdit m_View;
	CEdit m_Total;
	CComboBox m_ConcertBox;
	CComboBox m_HallBox;
	afx_msg void OnCbnSelchangeCombo1();
	CEdit m_Column;
	CEdit m_Row;
	CEdit m_Detail;
};
