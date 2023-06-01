#pragma once
#include "afxdialogex.h"


// CSchemaTab6 대화 상자

class CSchemaTab6 : public CDialogEx
{
	DECLARE_DYNAMIC(CSchemaTab6)

public:
	CSchemaTab6(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSchemaTab6();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCHEMA_DLG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
