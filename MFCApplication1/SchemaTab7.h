#pragma once
#include "afxdialogex.h"


// CSchemaTab7 대화 상자

class CSchemaTab7 : public CDialogEx
{
	DECLARE_DYNAMIC(CSchemaTab7)

public:
	CSchemaTab7(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSchemaTab7();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCHEMA_DLG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
