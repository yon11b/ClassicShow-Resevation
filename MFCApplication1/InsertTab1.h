#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"


// CInsertTab1 대화 상자

class CInsertTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertTab1)

public:
	CInsertTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInsertTab1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERT_DLG1 };
#endif

protected:	
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ConcertBox;
	CComboBox m_HallBox;
	afx_msg void OnCbnSelchangeCombo1();
	CDBConnect DB;
	CEdit m_Title;
	CEdit m_Musician;
	CEdit m_Composer;
	CEdit m_Genre;
	CDateTimeCtrl m_Date;
	CDateTimeCtrl m_StartDate;
	CDateTimeCtrl m_EndDate;
	afx_msg void OnBnClickedButton1();
	CEdit m_RSeat;
	CEdit m_SSeat;
	CEdit m_ASeat;
	CEdit m_BSeat;
	CEdit m_Hour;
	CEdit m_Minute;
};
