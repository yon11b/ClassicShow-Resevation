// DeleteDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DeleteDlg.h"
#include "DeleteTab1.h"
#include "DeleteTab2.h"
#include "DeleteTab3.h"
#include "DeleteTab4.h"

// CDeleteDlg 대화 상자

IMPLEMENT_DYNAMIC(CDeleteDlg, CDialogEx)

CDeleteDlg::CDeleteDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DELETE, pParent)
{

}

CDeleteDlg::~CDeleteDlg()
{
}

void CDeleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(CDeleteDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDeleteDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CDeleteDlg 메시지 처리기
BOOL CDeleteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Tab.InsertItem(0, _T("공연 정보(관리자)"));
	m_Tab.InsertItem(1, _T("내 리뷰"));
	m_Tab.InsertItem(2, _T("공연장(관리자)"));
	m_Tab.InsertItem(3, _T("전체 리뷰(관리자)"));

	m_Tab.SetCurSel(0);

	CRect rect;
	m_Tab.GetWindowRect(&rect);

	pDlg1 = new CDeleteTab1;
	pDlg1->Create(IDD_DELETE_DLG1, &m_Tab);
	pDlg1->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg1->ShowWindow(SW_SHOW);

	pDlg2 = new CDeleteTab2;
	pDlg2->Create(IDD_DELETE_DLG2, &m_Tab);
	pDlg2->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg2->ShowWindow(SW_HIDE);

	pDlg3 = new CDeleteTab3;
	pDlg3->Create(IDD_DELETE_DLG3, &m_Tab);
	pDlg3->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg3->ShowWindow(SW_HIDE);

	pDlg4 = new CDeleteTab3;
	pDlg4->Create(IDD_DELETE_DLG3, &m_Tab);
	pDlg4->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg4->ShowWindow(SW_HIDE);

	return TRUE;
}

void CDeleteDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = m_Tab.GetCurSel();
	switch (sel) {
	case 0:
		pDlg1->ShowWindow(SW_SHOW);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_HIDE);
		pDlg4->ShowWindow(SW_HIDE);
		break;
	case 1:
		pDlg1->ShowWindow(SW_HIDE);
		pDlg2->ShowWindow(SW_SHOW);
		pDlg3->ShowWindow(SW_HIDE);
		pDlg4->ShowWindow(SW_HIDE);
		break;
	case 2:
		pDlg1->ShowWindow(SW_HIDE);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_SHOW);
		pDlg4->ShowWindow(SW_HIDE);
		break;
	case 3:
		pDlg1->ShowWindow(SW_HIDE);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_HIDE);
		pDlg4->ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}
