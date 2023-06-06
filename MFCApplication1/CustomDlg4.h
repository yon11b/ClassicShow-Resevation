#pragma once
#include "afxdialogex.h"


// CCustomDlg4 대화 상자

class CCustomDlg4 : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomDlg4)

public:
	CCustomDlg4(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCustomDlg4();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSTOM_DLG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
