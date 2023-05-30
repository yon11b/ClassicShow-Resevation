// DeleteTab2.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DeleteTab2.h"


// CDeleteTab2 대화 상자

IMPLEMENT_DYNAMIC(CDeleteTab2, CDialogEx)

CDeleteTab2::CDeleteTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DELETE_DLG2, pParent)
{

}

CDeleteTab2::~CDeleteTab2()
{
}

void CDeleteTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeleteTab2, CDialogEx)
END_MESSAGE_MAP()


// CDeleteTab2 메시지 처리기
