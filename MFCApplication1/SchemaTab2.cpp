// SchemaTab2.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SchemaTab2.h"


// CSchemaTab2 대화 상자

IMPLEMENT_DYNAMIC(CSchemaTab2, CDialogEx)

CSchemaTab2::CSchemaTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCHEMA_DLG2, pParent)
{

}

CSchemaTab2::~CSchemaTab2()
{
}

void CSchemaTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSchemaTab2, CDialogEx)
END_MESSAGE_MAP()


// CSchemaTab2 메시지 처리기
