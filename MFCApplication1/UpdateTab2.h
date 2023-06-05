#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"

// CUpdateTab2 대화 상자

class CUpdateTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateTab2)

public:
	CUpdateTab2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUpdateTab2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE_DLG2 };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CDBConnect DB;
	CListCtrl m_ListCtrl;
	CString GetColumnName(int columnIndex);
	int iSavedItem, iSavedSubitem;
	afx_msg void OnNMDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	BOOL PreTranslateMessage(MSG* pMsg);
};
