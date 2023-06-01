// SchemaTab1.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SchemaTab1.h"


// CSchemaTab1 대화 상자

IMPLEMENT_DYNAMIC(CSchemaTab1, CDialogEx)

CSchemaTab1::CSchemaTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCHEMA_DLG1, pParent)
{

}

CSchemaTab1::~CSchemaTab1()
{
}

void CSchemaTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CSchemaTab1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSchemaTab1::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSchemaTab1 메시지 처리기
BOOL CSchemaTab1::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// 표 틀 생성
	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrl.InsertColumn(0, TEXT("id"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(1, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(2, TEXT("제목"), LVCFMT_CENTER, rt.Width() * 0.1);
	m_ListCtrl.InsertColumn(3, TEXT("날짜"), LVCFMT_CENTER, rt.Width() * 0.1);
	m_ListCtrl.InsertColumn(4, TEXT("연주자"), LVCFMT_CENTER, rt.Width() * 0.1);
	m_ListCtrl.InsertColumn(5, TEXT("예매 시작"), LVCFMT_CENTER, rt.Width() * 0.1);
	m_ListCtrl.InsertColumn(6, TEXT("예매 마감"), LVCFMT_CENTER, rt.Width() * 0.1);
	m_ListCtrl.InsertColumn(7, TEXT("작곡가"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(8, TEXT("장르"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(9, TEXT("좌석R"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(10, TEXT("좌석S"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(11, TEXT("좌석A"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(12, TEXT("좌석B"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(13, TEXT("외래키"), LVCFMT_CENTER, rt.Width() * 0.05);

	return TRUE;
}


void CSchemaTab1::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SQLHDBC hDbc;
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	if (DB.db_connect()) {
		MessageBox("DB CONEECT!");

		hDbc = DB.hDbc;
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
		{
			MessageBox("SQL START SELECT");
			sprintf_s((char*)query, 101, "SELECT * FROM SHOW");
			SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

			SQLCHAR showno[100];
			SQLCHAR title[100];
			SQLCHAR date[100];
			SQLCHAR musician[100];
			SQLCHAR reserve_starttime[100];
			SQLCHAR reserve_endtime[100];
			SQLCHAR composer[100];
			SQLCHAR genre[100];
			SQLCHAR pricer[100];
			SQLCHAR prices[100];
			SQLCHAR pricea[100];
			SQLCHAR priceb[100];
			SQLCHAR hallno[100];

			SQLBindCol(hStmt, 1, SQL_C_CHAR, showno, 100, NULL);
			SQLBindCol(hStmt, 2, SQL_C_CHAR, title, 100, NULL);
			SQLBindCol(hStmt, 3, SQL_C_CHAR, date, 100, NULL);
			SQLBindCol(hStmt, 4, SQL_C_CHAR, musician, 100, NULL);
			SQLBindCol(hStmt, 5, SQL_C_CHAR, reserve_starttime, 100, NULL);
			SQLBindCol(hStmt, 6, SQL_C_CHAR, reserve_endtime, 100, NULL);
			SQLBindCol(hStmt, 7, SQL_C_CHAR, composer, 100, NULL);
			SQLBindCol(hStmt, 8, SQL_C_CHAR, genre, 100, NULL);
			SQLBindCol(hStmt, 9, SQL_C_CHAR, pricer, 100, NULL);
			SQLBindCol(hStmt, 10, SQL_C_CHAR, prices, 100, NULL);
			SQLBindCol(hStmt, 11, SQL_C_CHAR, pricea, 100, NULL);
			SQLBindCol(hStmt, 12, SQL_C_CHAR, priceb, 100, NULL);
			SQLBindCol(hStmt, 13, SQL_C_CHAR, hallno, 100, NULL);


			int num;
			CString str;
			// 공연 데이터 나열
			while (SQLFetch(hStmt) != SQL_NO_DATA)
			{
				num = m_ListCtrl.GetItemCount();
				str.Format(_T("%d"), num);
				m_ListCtrl.InsertItem(num, str);
				m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)showno, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)title, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)date, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 4, LVIF_TEXT, (CString)musician, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 5, LVIF_TEXT, (CString)reserve_starttime, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 6, LVIF_TEXT, (CString)reserve_endtime, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 7, LVIF_TEXT, (CString)composer, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 8, LVIF_TEXT, (CString)genre, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 9, LVIF_TEXT, (CString)pricer, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 10, LVIF_TEXT, (CString)prices, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 11, LVIF_TEXT, (CString)pricea, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 12, LVIF_TEXT, (CString)priceb, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 13, LVIF_TEXT, (CString)hallno, NULL, NULL, NULL, NULL);
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
