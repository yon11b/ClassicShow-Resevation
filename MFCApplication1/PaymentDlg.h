#pragma once
#include "afxdialogex.h"
#include "SeatSacDlg.h"
#include "DBConnect.h"
#include "Session.h"

extern CSESSION SESSION; // 전역 객체 선언
// CPaymentDlg 대화 상자

class CPaymentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPaymentDlg)

public:
	//CPaymentDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CPaymentDlg();
	CString seatno;
	CString hallno;
	CPaymentDlg(CString pShowno, CString pSeatno, CString pHallno, CWnd* pParent = nullptr);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAYMENT };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CDBConnect DB;
	CStatic m_ChSeatInfo; 
	CString userid;
	CString ckshowno;
	CString ckhallno;
	CString ckseatno;
	CString ckprice;
	afx_msg void OnBnClickedButton1();
	CEdit m_InputPw;
	void DoReservation();
	CString ExecuteQuery(SQLHSTMT hStmt, const CString& query);
};
