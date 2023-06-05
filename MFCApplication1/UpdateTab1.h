#pragma once
#include "afxdialogex.h"
#include "DBConnect.h"


// CUpdateTab1 대화 상자

class CUpdateTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateTab1)

public:
	CUpdateTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUpdateTab1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE_DLG1 };
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
