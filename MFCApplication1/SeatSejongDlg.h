#pragma once
#include "afxdialogex.h"


// CSeatSejongDlg 대화 상자

class CSeatSejongDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSeatSejongDlg)

public:
	CSeatSejongDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSeatSejongDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEAT_SEJONG_CONCERT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
