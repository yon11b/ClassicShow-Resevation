// Tab3.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "Tab3.h"

// CTab3 대화 상자

IMPLEMENT_DYNAMIC(CTab3, CDialogEx)

CTab3::CTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CTab3::~CTab3()
{
}

void CTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RESERVE, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CTab3, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SELECTASC, &CTab3::OnBnClickedBtnSelectasc)
	ON_BN_CLICKED(IDC_BTN_SELECTDESC, &CTab3::OnBnClickedBtnSelectdesc)
END_MESSAGE_MAP()


// CTab3 메시지 처리기
BOOL CTab3::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// 표 틀 생성
	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrl.InsertColumn(0, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.1);
	m_ListCtrl.InsertColumn(1, TEXT("공연명"), LVCFMT_CENTER, rt.Width() * 0.3);
	m_ListCtrl.InsertColumn(2, TEXT("관람일시"), LVCFMT_CENTER, rt.Width() * 0.3);
	m_ListCtrl.InsertColumn(3, TEXT("취소가능일시"), LVCFMT_CENTER, rt.Width() * 0.3);

	return TRUE;
}


void CTab3::OnBnClickedBtnSelectasc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SQLHDBC hDbc;
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];
	CString score;
	CString userid = SESSION.userId;

	if (DB.db_connect()) {

		hDbc = DB.hDbc;
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 201, "SELECT TITLE, [DATE], RESERVE_ENDTIME FROM RESERVATE R, SHOW S WHERE R.USERID='%s' AND R.SHOWNO=S.SHOWNO", userid);			
			SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
			CString str;
			SQLCHAR title[100];
			SQLCHAR date[50];
			SQLCHAR canceldate[50];

			SQLBindCol(hStmt, 1, SQL_C_CHAR, title, 100, NULL);
			SQLBindCol(hStmt, 2, SQL_C_CHAR, date, 50, NULL);
			SQLBindCol(hStmt, 3, SQL_C_CHAR, canceldate, 50, NULL);

			int num;
			// 공연 데이터 나열
			while (SQLFetch(hStmt) != SQL_NO_DATA)
			{
				num = m_ListCtrl.GetItemCount();
				str.Format(_T("%d"), num);
				m_ListCtrl.InsertItem(num, str);
				m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)title, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)date, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)canceldate, NULL, NULL, NULL, NULL);				
			}
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}
		DB.db_disconnect();
	}
	else {
		MessageBox("예매 내역을 불러오는데 실패했습니다.");
	}
}


void CTab3::OnBnClickedBtnSelectdesc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SQLHDBC hDbc;
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];
	CString score;
	CString userid = SESSION.userId;

	m_ListCtrl.DeleteAllItems();
	if (DB.db_connect()) {
		hDbc = DB.hDbc;
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 201, "SELECT TITLE, [DATE], RESERVE_ENDTIME FROM RESERVATE R, SHOW S WHERE R.USERID='%s' AND R.SHOWNO=S.SHOWNO ORDER BY [DATE] DESC", userid);			
			SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
			CString str;
			SQLCHAR title[100];
			SQLCHAR date[50];
			SQLCHAR canceldate[50];

			SQLBindCol(hStmt, 1, SQL_C_CHAR, title, 100, NULL);
			SQLBindCol(hStmt, 2, SQL_C_CHAR, date, 50, NULL);
			SQLBindCol(hStmt, 3, SQL_C_CHAR, canceldate, 50, NULL);			

			int num;
			// 공연 데이터 나열
			while (SQLFetch(hStmt) != SQL_NO_DATA)
			{
				num = m_ListCtrl.GetItemCount();
				str.Format(_T("%d"), num);
				m_ListCtrl.InsertItem(num, str);
				m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)title, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)date, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)canceldate, NULL, NULL, NULL, NULL);								
			}
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}
		DB.db_disconnect();
	}
	else {
		MessageBox("예매 내역을 불러오는데 실패했습니다.");
	}
}