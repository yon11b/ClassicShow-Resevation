#pragma once
#include "afxdialogex.h"


// CSeatLotteDlg 대화 상자

class CSeatLotteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSeatLotteDlg)

public:
	CSeatLotteDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSeatLotteDlg();
	CSeatLotteDlg(CString pShowno, CString pHallno);
	CString showno;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEAT_LOTTE_CONCERT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
