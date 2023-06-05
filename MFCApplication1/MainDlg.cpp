// MainDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "MainDlg.h"
#include "SelectDlg.h"
#include "InsertDlg.h"
#include "UpdateDlg.h"
#include "DeleteDlg.h"
#include "SchemaDlg.h"


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
	ON_BN_CLICKED(IDC_INSERT_QUERY, &CMainDlg::OnBnClickedInsertQuery)
	ON_BN_CLICKED(IDC_UPDATE_QUERY, &CMainDlg::OnBnClickedUpdateQuery)
	ON_BN_CLICKED(IDC_DELETE_QUERY, &CMainDlg::OnBnClickedDeleteQuery)
	ON_BN_CLICKED(IDC_CUSTOM_QUERY, &CMainDlg::OnBnClickedCustomQuery)
END_MESSAGE_MAP()


// CMainDlg 메시지 처리기


void CMainDlg::OnBnClickedSchemaCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SchemaDlg.DoModal();
}


void CMainDlg::OnBnClickedSelectQuery()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SelectDlg.DoModal();
}


void CMainDlg::OnBnClickedInsertQuery()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InsertDlg.DoModal();
}


void CMainDlg::OnBnClickedUpdateQuery()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateDlg.DoModal();
}


void CMainDlg::OnBnClickedDeleteQuery()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DeleteDlg.DoModal();
}

void CMainDlg::OnBnClickedCustomQuery()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CustomDlg.DoModal();
}
