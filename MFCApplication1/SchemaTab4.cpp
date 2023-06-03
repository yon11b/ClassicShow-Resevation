// SchemaTab4.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SchemaTab4.h"


// CSchemaTab4 대화 상자

IMPLEMENT_DYNAMIC(CSchemaTab4, CDialogEx)

CSchemaTab4::CSchemaTab4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCHEMA_DLG4, pParent)
{

}

CSchemaTab4::~CSchemaTab4()
{
}

void CSchemaTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSchemaTab4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSchemaTab4::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSchemaTab4 메시지 처리기


void CSchemaTab4::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}
