#pragma once
#include "afxdialogex.h"


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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
