// SeatSejongDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SeatSejongDlg.h"


// CSeatSejongDlg 대화 상자

IMPLEMENT_DYNAMIC(CSeatSejongDlg, CDialogEx)

CSeatSejongDlg::CSeatSejongDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEAT_SEJONG_CONCERT, pParent)
{

}

CSeatSejongDlg::~CSeatSejongDlg()
{
}

void CSeatSejongDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSeatSejongDlg, CDialogEx)
END_MESSAGE_MAP()


// CSeatSejongDlg 메시지 처리기
