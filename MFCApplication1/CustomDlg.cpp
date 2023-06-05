// CustomDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CustomDlg.h"


// CCustomDlg 대화 상자

IMPLEMENT_DYNAMIC(CCustomDlg, CDialogEx)

CCustomDlg::CCustomDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOM, pParent)
{

}

CCustomDlg::~CCustomDlg()
{
}

void CCustomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_UserInput);
}


BEGIN_MESSAGE_MAP(CCustomDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCustomDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCustomDlg 메시지 처리기


void CCustomDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString userquery;
	m_UserInput.GetWindowText(userquery);

}
