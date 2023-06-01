// UpdateDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "UpdateDlg.h"
#include "UpdateTab1.h"
#include "UpdateTab2.h"
#include "UpdateTab3.h"

// CUpdateDlg 대화 상자

IMPLEMENT_DYNAMIC(CUpdateDlg, CDialogEx)

CUpdateDlg::CUpdateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPDATE, pParent)
{

}

CUpdateDlg::~CUpdateDlg()
{
}

void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(CUpdateDlg, CDialogEx)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CUpdateDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CUpdateDlg 메시지 처리기
BOOL CUpdateDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();
    m_Tab.InsertItem(0, _T("공연안내"));
    m_Tab.InsertItem(1, _T("공연리뷰"));
    m_Tab.InsertItem(2, _T("예매내역"));
    m_Tab.InsertItem(3, _T("마이페이지"));

    m_Tab.SetCurSel(0);

    CRect rect;
    m_Tab.GetWindowRect(&rect);

    pDlg1 = new CUpdateTab1;
    pDlg1->Create(IDD_UPDATE_DLG1, &m_Tab);
    pDlg1->MoveWindow(0, 25, rect.Width(), rect.Height());
    pDlg1->ShowWindow(SW_SHOW);

    pDlg2 = new CUpdateTab2;
    pDlg2->Create(IDD_UPDATE_DLG2, &m_Tab);
    pDlg2->MoveWindow(0, 25, rect.Width(), rect.Height());
    pDlg2->ShowWindow(SW_HIDE);

    pDlg3 = new CUpdateTab3;
    pDlg3->Create(IDD_UPDATE_DLG3, &m_Tab);
    pDlg3->MoveWindow(0, 25, rect.Width(), rect.Height());
    pDlg3->ShowWindow(SW_HIDE);

    return TRUE;
}

void CUpdateDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
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
