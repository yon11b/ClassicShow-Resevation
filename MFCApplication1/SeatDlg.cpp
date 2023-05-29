// SeatDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SeatDlg.h"


// CSeatDlg 대화 상자

IMPLEMENT_DYNAMIC(CSeatDlg, CDialogEx)

CSeatDlg::CSeatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEAT_SAC_CONCERT, pParent)
{

}

CSeatDlg::~CSeatDlg()
{
}

void CSeatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEAT_GROUP, m_SeatGroup);
}


BEGIN_MESSAGE_MAP(CSeatDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CSeatDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSeatDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSeatDlg 메시지 처리기

BOOL CSeatDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	
	return TRUE;
}

void CSeatDlg::OnBnClickedCheck1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CSeatDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
