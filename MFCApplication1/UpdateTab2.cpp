// UpdateTab2.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "UpdateTab2.h"


// CUpdateTab2 대화 상자

IMPLEMENT_DYNAMIC(CUpdateTab2, CDialogEx)

CUpdateTab2::CUpdateTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPDATE_DLG2, pParent)
{

}

CUpdateTab2::~CUpdateTab2()
{
}

void CUpdateTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUpdateTab2, CDialogEx)
END_MESSAGE_MAP()


// CUpdateTab2 메시지 처리기
