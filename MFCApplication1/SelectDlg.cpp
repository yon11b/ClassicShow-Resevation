// SelectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SelectDlg.h"
#include "Tab1.h"
#include "Tab2.h"
#include "Tab3.h"

// CSelectDlg 대화 상자

IMPLEMENT_DYNAMIC(CSelectDlg, CDialogEx)

CSelectDlg::CSelectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SELECT, pParent)
{

}

CSelectDlg::~CSelectDlg()
{
}


// CSelectDlg 메시지 처리기

BOOL CSelectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Tab.InsertItem(0, _T("공연안내"));
	m_Tab.InsertItem(0, _T("공연리뷰"));
	m_Tab.InsertItem(0, _T("예매내역"));
	m_Tab.InsertItem(0, _T("마이페이지"));

	m_Tab.SetCurSel(0);

	CRect rect;
	m_Tab.GetWindowRect(&rect);

	pDlg1 = new CTab1;
	pDlg1->Create(IDD_DIALOG1, &m_Tab);
	pDlg1->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg1->ShowWindow(SW_SHOW);

	pDlg2 = new CTab2;
	pDlg2->Create(IDD_DIALOG2, &m_Tab);
	pDlg2->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg2->ShowWindow(SW_SHOW);

	pDlg3 = new CTab3;
	pDlg3->Create(IDD_DIALOG3, &m_Tab);
	pDlg3->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg3->ShowWindow(SW_SHOW);

	return TRUE;
}

void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(CSelectDlg, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LISTCTRL, &CSelectDlg::OnLbnSelchangeList1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CSelectDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CSelectDlg 메시지 처리기


void CSelectDlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CSelectDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = m_Tab.GetCurSel();
	switch (sel) {
	case 0:
		pDlg1->ShowWindow(SW_SHOW);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_HIDE);
		break;
	case 1:
		pDlg1->ShowWindow(SW_HIDE);
		pDlg2->ShowWindow(SW_SHOW);
		pDlg3->ShowWindow(SW_HIDE);
		break;
	case 2:
		pDlg1->ShowWindow(SW_HIDE);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}
