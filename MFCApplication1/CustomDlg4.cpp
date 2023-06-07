// CustomDlg4.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CustomDlg4.h"


// CCustomDlg4 대화 상자

IMPLEMENT_DYNAMIC(CCustomDlg4, CDialogEx)

CCustomDlg4::CCustomDlg4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOM_DLG4, pParent)
{

}

CCustomDlg4::~CCustomDlg4()
{
}

void CCustomDlg4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER5, m_StartDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_EndDate);
}


BEGIN_MESSAGE_MAP(CCustomDlg4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCustomDlg4::OnBnClickedButton1)
	
END_MESSAGE_MAP()


// CCustomDlg4 메시지 처리기

BOOL CCustomDlg4::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// 표 틀 생성
	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrl.InsertColumn(0, TEXT("Id"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(1, TEXT("Title"), LVCFMT_CENTER, rt.Width() * 0.35);
	m_ListCtrl.InsertColumn(2, TEXT("Date"), LVCFMT_CENTER, rt.Width() * 0.2);
	m_ListCtrl.InsertColumn(3, TEXT("Musician"), LVCFMT_CENTER, rt.Width() * 0.1);
	m_ListCtrl.InsertColumn(4, TEXT("Composer"), LVCFMT_CENTER, rt.Width() * 0.1);
	m_ListCtrl.InsertColumn(5, TEXT("Genre"), LVCFMT_CENTER, rt.Width() * 0.1);
	m_ListCtrl.InsertColumn(6, TEXT("Price_R"), LVCFMT_CENTER, rt.Width() * 0.1);

	return TRUE;
}

void CCustomDlg4::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString startdate;
	CString enddate;

	SQLHDBC hDbc;
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[401];

	m_ListCtrl.DeleteAllItems();
	if (DB.db_connect()) {
		COleDateTime getStartDate;
		m_StartDate.GetTime(getStartDate);
		COleDateTime startDate(getStartDate.GetYear(), getStartDate.GetMonth(), getStartDate.GetDay(), 0, 0, 0);
		CString strStartDate = startDate.Format(_T("%Y-%m-%d %H:%M:%S"));

		COleDateTime getFinishDate;
		m_EndDate.GetTime(getFinishDate);
		COleDateTime finishDate(getFinishDate.GetYear(), getFinishDate.GetMonth(), getFinishDate.GetDay(), 0, 0, 0);
		CString strFinishDate = finishDate.Format(_T("%Y-%m-%d %H:%M:%S"));

		hDbc = DB.hDbc;
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 401, "SELECT TITLE, [DATE], MUSICIAN, COMPOSER, GENRE, PRICE_R FROM SHOW \
						WHERE '%s' <= FORMAT([DATE], 'yyyy-MM-dd HH:mm:ss') AND FORMAT([DATE], 'yyyy-MM-dd HH:mm:ss') <='%s' \
						ORDER BY PRICE_R DESC;", strStartDate, strFinishDate);
			SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

			SQLCHAR title[100];
			SQLCHAR date[100];
			SQLCHAR musician[100];
			SQLCHAR composer[100];
			SQLCHAR genre[100];
			SQLCHAR price_r[10];

			SQLBindCol(hStmt, 1, SQL_C_CHAR, title, 100, NULL);
			SQLBindCol(hStmt, 2, SQL_C_CHAR, date, 100, NULL);
			SQLBindCol(hStmt, 3, SQL_C_CHAR, musician, 100, NULL);
			SQLBindCol(hStmt, 4, SQL_C_CHAR, composer, 100, NULL);
			SQLBindCol(hStmt, 5, SQL_C_CHAR, genre, 100, NULL);
			SQLBindCol(hStmt, 6, SQL_C_CHAR, price_r, 10, NULL);

			int num;
			CString str;
			// 공연 데이터 나열
			while (SQLFetch(hStmt) != SQL_NO_DATA)
			{
				num = m_ListCtrl.GetItemCount();
				str.Format(_T("%d"), num);
				m_ListCtrl.InsertItem(num, str);
				m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)title, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)date, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)musician, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 4, LVIF_TEXT, (CString)composer, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 5, LVIF_TEXT, (CString)genre, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 6, LVIF_TEXT, (CString)price_r, NULL, NULL, NULL, NULL);
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