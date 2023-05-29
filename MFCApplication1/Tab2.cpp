// Tab2.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "Tab2.h"


// CTab2 대화 상자

IMPLEMENT_DYNAMIC(CTab2, CDialogEx)

CTab2::CTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CTab2::~CTab2()
{
}

void CTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Score);
	DDX_Control(pDX, IDC_LIST_REVIEW, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CTab2, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SHOW, &CTab2::OnLvnItemchangedListctrl2)
	ON_BN_CLICKED(IDC_BTN_SELECTSHOW, &CTab2::OnBnClickedBtnSelectshow)
	ON_BN_CLICKED(IDC_BTN_SELECTREVIEW, &CTab2::OnBnClickedBtnSelectreview)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_REVIEW, &CTab2::OnLvnItemchangedListReview)
END_MESSAGE_MAP()


// CTab2 메시지 처리기
BOOL CTab2::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// 표 틀 생성
	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrl.InsertColumn(0, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(1, TEXT("제목"), LVCFMT_CENTER, rt.Width() * 0.2);
	m_ListCtrl.InsertColumn(2, TEXT("공연장"), LVCFMT_CENTER, rt.Width() * 0.2);
	m_ListCtrl.InsertColumn(3, TEXT("홀"), LVCFMT_CENTER, rt.Width() * 0.2);
	m_ListCtrl.InsertColumn(4, TEXT("좌석"), LVCFMT_CENTER, rt.Width() * 0.2);
	m_ListCtrl.InsertColumn(5, TEXT("시야"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(6, TEXT("소리"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(7, TEXT("좌석총평"), LVCFMT_CENTER, rt.Width() * 0.05);

	return TRUE;
}


void CTab2::OnLvnItemchangedListctrl2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CTab2::OnBnClickedBtnSelectshow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CTab2::OnBnClickedBtnSelectreview()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SQLHDBC hDbc;
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	CString score;

	m_Score.GetWindowText(score);
	
	if (DB.db_connect()) {
		MessageBox("DB CONEECT!");


		hDbc = DB.hDbc;
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
		{
			MessageBox("SQL START SELECT");

			sprintf_s((char*)query, 201, "SELECT TITLE, HALLNAME, ROOMNAME, SEATNUM, SOUND, [VIEW], TOTAL FROM REVIEW, CONCERTHALL WHERE REVIEW.HALLNUM = CONCERTHALL.HALLNO AND REVIEW.TOTAL >= '%s'", score);
			MessageBox((CString)query);
			SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
			CString str;
			SQLCHAR title[100];
			SQLCHAR hallname[100];
			SQLCHAR roomname[100];
			SQLCHAR seatnum[30];
			SQLCHAR sound[30];
			SQLCHAR view[30];
			SQLCHAR total[30];

			SQLBindCol(hStmt, 1, SQL_C_CHAR, title, 100, NULL);
			SQLBindCol(hStmt, 2, SQL_C_CHAR, hallname, 100, NULL);
			SQLBindCol(hStmt, 3, SQL_C_CHAR, roomname, 100, NULL);
			SQLBindCol(hStmt, 4, SQL_C_CHAR, seatnum, 30, NULL);
			SQLBindCol(hStmt, 5, SQL_C_CHAR, sound, 30, NULL);
			SQLBindCol(hStmt, 6, SQL_C_CHAR, view, 30, NULL);
			SQLBindCol(hStmt, 7, SQL_C_CHAR, total, 30, NULL);

			int num;
			// 공연 데이터 나열
			while (SQLFetch(hStmt) != SQL_NO_DATA)
			{
				num = m_ListCtrl.GetItemCount();
				str.Format(_T("%d"), num);
				m_ListCtrl.InsertItem(num, str);
				m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)title, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)hallname, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)roomname, NULL, NULL, NULL, NULL);

				m_ListCtrl.SetItem(num, 4, LVIF_TEXT, (CString)seatnum, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 5, LVIF_TEXT, (CString)sound, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 6, LVIF_TEXT, (CString)view, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 7, LVIF_TEXT, (CString)total, NULL, NULL, NULL, NULL);
			}
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}
		DB.db_disconnect();
	}
	else {
		MessageBox("공연 정보를 불러오는데 실패했습니다.");
	}
	MessageBox("zzz");
}


void CTab2::OnLvnItemchangedListReview(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
