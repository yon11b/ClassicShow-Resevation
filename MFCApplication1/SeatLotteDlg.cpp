// SeatLotteDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SeatLotteDlg.h"


// CSeatLotteDlg 대화 상자

IMPLEMENT_DYNAMIC(CSeatLotteDlg, CDialogEx)

CSeatLotteDlg::CSeatLotteDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEAT_LOTTE_CONCERT, pParent)
{

}

CSeatLotteDlg::~CSeatLotteDlg()
{
}

void CSeatLotteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSeatLotteDlg, CDialogEx)
END_MESSAGE_MAP()


// CSeatLotteDlg 메시지 처리기
