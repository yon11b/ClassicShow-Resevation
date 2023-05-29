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
	DDX_Control(pDX, IDC_LIST_SHOW, m_ListCtrl);
	DDX_Control(pDX, IDC_DATE_START, m_DateStart);
	DDX_Control(pDX, IDC_DATE_FINISH, m_DateFinish);
}


BEGIN_MESSAGE_MAP(CTab1, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SELECTSHOW, &CTab1::OnBnClickedBtnSelectshow)
END_MESSAGE_MAP()


// CTab1 메시지 처리기

BOOL CTab1::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// 표 틀 생성
	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrl.InsertColumn(0, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(1, TEXT("제목"), LVCFMT_CENTER, rt.Width() * 0.3);
	m_ListCtrl.InsertColumn(2, TEXT("연주자"), LVCFMT_CENTER, rt.Width() * 0.25);
	m_ListCtrl.InsertColumn(3, TEXT("작곡가"), LVCFMT_CENTER, rt.Width() * 0.15);
	m_ListCtrl.InsertColumn(4, TEXT("날짜"), LVCFMT_CENTER, rt.Width() * 0.2);

	return TRUE;
}

void CTab1::OnBnClickedBtnSelectshow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	SQLHDBC hDbc;
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	if (DB.db_connect()) {
		MessageBox("DB CONEECT!");


		COleDateTime getStartDate;
		m_DateStart.GetTime(getStartDate);
		COleDateTime startDate(getStartDate.GetYear(), getStartDate.GetMonth(), getStartDate.GetDay(), 0, 0, 0);
		CString strStartDate = startDate.Format(_T("%Y-%m-%d %H:%M:%S"));
		MessageBox(strStartDate);

		COleDateTime getFinishDate;
		m_DateFinish.GetTime(getFinishDate);
		COleDateTime finishDate(getFinishDate.GetYear(), getFinishDate.GetMonth(), getFinishDate.GetDay(), 0, 0, 0);
		CString strFinishDate = finishDate.Format(_T("%Y-%m-%d %H:%M:%S"));

		hDbc = DB.hDbc;
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
		{
			MessageBox("SQL START SELECT");
			sprintf_s((char*)query, 201, "SELECT TITLE, MUSICIAN, COMPOSER, [DATE] FROM SHOW WHERE '%s' <= FORMAT([DATE], 'yyyy-MM-dd HH:mm:ss') AND FORMAT([DATE], 'yyyy-MM-dd HH:mm:ss') <='%s'", strStartDate, strFinishDate);
			SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

			SQLCHAR title[100];
			SQLCHAR musician[100];
			SQLCHAR composer[100];
			SQLCHAR date[100];

			SQLBindCol(hStmt, 1, SQL_C_CHAR, title, 100, NULL);
			SQLBindCol(hStmt, 2, SQL_C_CHAR, musician, 100, NULL);
			SQLBindCol(hStmt, 3, SQL_C_CHAR, composer, 100, NULL);
			SQLBindCol(hStmt, 4, SQL_C_CHAR, date, 100, NULL);

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
			}

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}
		DB.db_disconnect();
	}
	else {
		MessageBox("공연 정보를 불러오는데 실패했습니다.");
	}
}
