// MainDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "MainDlg.h"
#include "SelectDlg.h"


// CMainDlg 대화 상자

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN, pParent)
{

}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SCHEMA_CHECK, &CMainDlg::OnBnClickedSchemaCheck)
	ON_BN_CLICKED(IDC_SELECT_QUERY, &CMainDlg::OnBnClickedSelectQuery)
END_MESSAGE_MAP()


// CMainDlg 메시지 처리기


void CMainDlg::OnBnClickedSchemaCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMainDlg::OnBnClickedSelectQuery()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SelectDlg.DoModal();
}
