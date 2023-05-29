// Tab1.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "Tab1.h"


// CTab1 대화 상자

IMPLEMENT_DYNAMIC(CTab1, CDialogEx)

CTab1::CTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CTab1::~CTab1()
{
}

void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTCTRL, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CTab1, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL, &CTab1::OnLvnItemchangedListctrl)
END_MESSAGE_MAP()


// CTab1 메시지 처리기

BOOL CTab1::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// 표 틀 생성
	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrl.InsertColumn(0, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.1);
	m_ListCtrl.InsertColumn(1, TEXT("제목"), LVCFMT_CENTER, rt.Width() * 0.2);
	m_ListCtrl.InsertColumn(2, TEXT("연주자"), LVCFMT_CENTER, rt.Width() * 0.2);
	m_ListCtrl.InsertColumn(3, TEXT("작곡가"), LVCFMT_CENTER, rt.Width() * 0.2);
	m_ListCtrl.InsertColumn(4, TEXT("날짜"), LVCFMT_CENTER, rt.Width() * 0.2);
	m_ListCtrl.InsertColumn(5, TEXT("예매"), LVCFMT_CENTER, rt.Width() * 0.1);
	
	SQLHDBC hDbc;
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];

	if (DB.db_connect()) {
		MessageBox("DB CONEECT!");
	}
	else {
		MessageBox("ERROR!");
	}
	hDbc = DB.hDbc;
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
	{
		MessageBox("SQL START SELECT");

		sprintf_s((char*)query, 101, "SELECT TITLE, MUSICIAN, COMPOSER, [DATE] FROM SHOW");
		SQLExecDirect(hStmt, query, SQL_NTS);

		SQLCHAR title[30];
		SQLCHAR musician[30];
		SQLCHAR composer[30];
		SQLCHAR date[30];

		SQLBindCol(hStmt, 1, SQL_C_CHAR, title, 30, NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, musician, 30, NULL);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, composer, 30, NULL);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, date, 30, NULL);

		int num;
		CString str;
		// 공연 데이터 나열
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			num = m_ListCtrl.GetItemCount();
			str.Format(_T("%d"), num);
			m_ListCtrl.InsertItem(num, str);
			m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)title, NULL, NULL, NULL, NULL);
			m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)musician, NULL, NULL, NULL, NULL);
			m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)composer, NULL, NULL, NULL, NULL);
			m_ListCtrl.SetItem(num, 4, LVIF_TEXT, (CString)date, NULL, NULL, NULL, NULL);
			m_ListCtrl.SetItem(num, 5, LVIF_TEXT, TEXT("예매"), NULL, NULL, NULL, NULL);

		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		DB.db_disconnect();
	}

	else {
		MessageBox("공연 정보를 불러오는데 실패했습니다.");
	}
	return TRUE;
}

void CTab1::OnLvnItemchangedListctrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.



	*pResult = 0;
}
