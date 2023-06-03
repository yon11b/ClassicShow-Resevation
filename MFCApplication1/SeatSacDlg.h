#pragma once
#include "afxdialogex.h"
#include "Session.h"
#include "DBConnect.h"

extern CSESSION SESSION;
// CSeatSacDlg 대화 상자

class CSeatSacDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSeatSacDlg)

public:
	virtual ~CSeatSacDlg();
	CSeatSacDlg(CString pShowno, CString pHallno, CWnd* pParent = nullptr);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEAT_SAC_CONCERT };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CDBConnect DB;
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBtnClick(UINT ullD);
	afx_msg void OnBnClickedButton1();
	CEdit m_SeatNo;
	CString showno;
	CString seatno;
	CString hallno;
	CString payment;
	CString seatinfo;
};
