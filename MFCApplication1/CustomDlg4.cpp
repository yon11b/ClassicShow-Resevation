// CustomDlg4.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CustomDlg4.h"


// CCustomDlg4 대화 상자

IMPLEMENT_DYNAMIC(CCustomDlg4, CDialogEx)

CCustomDlg4::CCustomDlg4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOM_DLG4, pParent)
{

}

CCustomDlg4::~CCustomDlg4()
{
}

void CCustomDlg4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCustomDlg4, CDialogEx)
END_MESSAGE_MAP()


// CCustomDlg4 메시지 처리기
