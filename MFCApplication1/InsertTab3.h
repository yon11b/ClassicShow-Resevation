#pragma once
#include "afxdialogex.h"


// CInsertTab3 대화 상자

class CInsertTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertTab3)

public:
	CInsertTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInsertTab3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERT_DLG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
