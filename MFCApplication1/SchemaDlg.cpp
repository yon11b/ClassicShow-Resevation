// SchemaDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SchemaDlg.h"
#include "SchemaTab1.h"
#include "SchemaTab2.h"
#include "SchemaTab3.h"
#include "SchemaTab4.h"
#include "SchemaTab5.h"
#include "SchemaTab6.h"
#include "SchemaTab7.h"

// CSchemaDlg 대화 상자

IMPLEMENT_DYNAMIC(CSchemaDlg, CDialogEx)

CSchemaDlg::CSchemaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCHEMA, pParent)
{

}

CSchemaDlg::~CSchemaDlg()
{
}

void CSchemaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(CSchemaDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CSchemaDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CSchemaDlg 메시지 처리기
BOOL CSchemaDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	m_Tab.InsertItem(0, _T("공연"));
	m_Tab.InsertItem(1, _T("리뷰"));
	m_Tab.InsertItem(2, _T("예매내역"));
	m_Tab.InsertItem(3, _T("좌석"));
	m_Tab.InsertItem(4, _T("공연장."));
	m_Tab.InsertItem(5, _T("사용자"));
	m_Tab.InsertItem(6, _T("카드"));

	m_Tab.SetCurSel(0);

	CRect rect;
	m_Tab.GetWindowRect(&rect);

	pDlg1 = new CSchemaTab1;
	pDlg1->Create(IDD_SCHEMA_DLG1, &m_Tab);
	pDlg1->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg1->ShowWindow(SW_SHOW);

	pDlg2 = new CSchemaTab2;
	pDlg2->Create(IDD_SCHEMA_DLG2, &m_Tab);
	pDlg2->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg2->ShowWindow(SW_HIDE);

	pDlg3 = new CSchemaTab3;
	pDlg3->Create(IDD_SCHEMA_DLG3, &m_Tab);
	pDlg3->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg3->ShowWindow(SW_HIDE);

	pDlg4 = new CSchemaTab4;
	pDlg4->Create(IDD_SCHEMA_DLG4, &m_Tab);
	pDlg4->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg4->ShowWindow(SW_HIDE);

	pDlg5 = new CSchemaTab5;
	pDlg5->Create(IDD_SCHEMA_DLG5, &m_Tab);
	pDlg5->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg5->ShowWindow(SW_HIDE);

	pDlg6 = new CSchemaTab6;
	pDlg6->Create(IDD_SCHEMA_DLG6, &m_Tab);
	pDlg6->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg6->ShowWindow(SW_HIDE);

	pDlg7 = new CSchemaTab7;
	pDlg7->Create(IDD_SCHEMA_DLG7, &m_Tab);
	pDlg7->MoveWindow(0, 25, rect.Width(), rect.Height());
	pDlg7->ShowWindow(SW_HIDE);
	return TRUE;
}

void CSchemaDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = m_Tab.GetCurSel();
	switch (sel) {
	case 0:
		pDlg1->ShowWindow(SW_SHOW);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_HIDE);
		pDlg4->ShowWindow(SW_HIDE);
		pDlg5->ShowWindow(SW_HIDE);
		pDlg6->ShowWindow(SW_HIDE);
		pDlg7->ShowWindow(SW_HIDE);
		break;
	case 1:
		pDlg1->ShowWindow(SW_HIDE);
		pDlg2->ShowWindow(SW_SHOW);
		pDlg3->ShowWindow(SW_HIDE);
		pDlg4->ShowWindow(SW_HIDE);
		pDlg5->ShowWindow(SW_HIDE);
		pDlg6->ShowWindow(SW_HIDE);
		pDlg7->ShowWindow(SW_HIDE);
		break;
	case 2:
		pDlg1->ShowWindow(SW_HIDE);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_SHOW);
		pDlg4->ShowWindow(SW_HIDE);
		pDlg5->ShowWindow(SW_HIDE);
		pDlg6->ShowWindow(SW_HIDE);
		pDlg7->ShowWindow(SW_HIDE);
		break;

	case 3:
		pDlg1->ShowWindow(SW_HIDE);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_HIDE);
		pDlg4->ShowWindow(SW_SHOW);
		pDlg5->ShowWindow(SW_HIDE);
		pDlg6->ShowWindow(SW_HIDE);
		pDlg7->ShowWindow(SW_HIDE);
		break;

	case 4:
		pDlg1->ShowWindow(SW_HIDE);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_HIDE);
		pDlg4->ShowWindow(SW_HIDE);
		pDlg5->ShowWindow(SW_SHOW);
		pDlg6->ShowWindow(SW_HIDE);
		pDlg7->ShowWindow(SW_HIDE);
		break;

	case 5:
		pDlg1->ShowWindow(SW_HIDE);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_HIDE);
		pDlg4->ShowWindow(SW_HIDE);
		pDlg5->ShowWindow(SW_HIDE);
		pDlg6->ShowWindow(SW_SHOW);
		pDlg7->ShowWindow(SW_HIDE);
		break;

	case 6:
		pDlg1->ShowWindow(SW_SHOW);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_HIDE);
		pDlg4->ShowWindow(SW_HIDE);
		pDlg5->ShowWindow(SW_HIDE);
		pDlg6->ShowWindow(SW_HIDE);
		pDlg7->ShowWindow(SW_SHOW);
		break;

	}
	*pResult = 0;
}
