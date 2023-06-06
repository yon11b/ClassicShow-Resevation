// CustomDlg3.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CustomDlg3.h"
#include "DBConnect.h"


// CCustomDlg3 대화 상자

IMPLEMENT_DYNAMIC(CCustomDlg3, CDialogEx)

CCustomDlg3::CCustomDlg3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOM_DLG3, pParent)
{

}

CCustomDlg3::~CCustomDlg3()
{
}

void CCustomDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_HallBox);
	DDX_Control(pDX, IDC_COMBO1, m_ConcertBox);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CCustomDlg3, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCustomDlg3::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCustomDlg3::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CCustomDlg3 메시지 처리기

BOOL CCustomDlg3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CDialogEx::OnInitDialog();
	m_ConcertBox.AddString(_T("예술의 전당"));
	m_ConcertBox.AddString(_T("잠실 롯데"));
	m_ConcertBox.AddString(_T("세종문화회관"));

	// 표 틀 생성
	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrl.InsertColumn(0, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.1);
	m_ListCtrl.InsertColumn(1, TEXT("좌석 정보"), LVCFMT_CENTER, rt.Width() * 0.4);
	m_ListCtrl.InsertColumn(2, TEXT("시야 점수"), LVCFMT_CENTER, rt.Width() * 0.15);
	m_ListCtrl.InsertColumn(3, TEXT("음향 점수"), LVCFMT_CENTER, rt.Width() * 0.15);
	m_ListCtrl.InsertColumn(4, TEXT("총 점수"), LVCFMT_CENTER, rt.Width() * 0.2);
	
	return TRUE;
}

void CCustomDlg3::OnBnClickedButton1()
{
	m_ListCtrl.DeleteAllItems();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString concertname;
	CString hallname;
	SQLCHAR query1[201];
	SQLCHAR query2[201];
	SQLCHAR query3[201];
	SQLHDBC hDbc;
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR userhallno[10];

	m_ConcertBox.GetWindowText(concertname);
	m_HallBox.GetWindowText(hallname);
	if (DB.db_connect())
	{
		hDbc = DB.hDbc;
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
			sprintf_s((char*)query1, 201, "SELECT HALLNO FROM CONCERTHALL WHERE HALLNAME='%s' AND ROOMNAME='%s'", concertname, hallname);
			SQLExecDirect(hStmt, query1, SQL_NTS);
			SQLRETURN ret = SQLFetch(hStmt);
			ret = SQLGetData(hStmt, 1, SQL_C_CHAR, userhallno, 10, NULL);
			hallno = (CString)userhallno;
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}
		DB.db_disconnect();
	}

	SQLCHAR Reviewno[10];
	SQLCHAR Title[100];
	SQLCHAR SeatNo[10];
	SQLCHAR View[10];
	SQLCHAR Sound[10];
	SQLCHAR Total[10];

	SQLHSTMT hStmt1; // Statement Handle
	SQLHSTMT hStmt2; // Statement Handle
	CString seatinfo;
	CString str;

	if (DB.db_connect())
	{
		hDbc = DB.hDbc;
		// 사용자가 선택한 공연장 안에 있는 좌석들을 리뷰 테이블에서 찾기
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt1) == SQL_SUCCESS) {
			sprintf_s((char*)query2, 201, "SELECT R.* FROM REVIEW R, CONCERTHALL C WHERE R.HALLNUM = C.HALLNO AND R.HALLNUM = '%s'", hallno);
			MessageBox((LPCTSTR)query2); // Debugging code
			SQLExecDirect(hStmt1, query2, SQL_NTS);

			//get으로 바꾸기 =>>while로 바꾸기. 석이 여러개니까. 
			SQLBindCol(hStmt1, 1, SQL_C_CHAR, Reviewno, 30, NULL);
			SQLBindCol(hStmt1, 2, SQL_C_CHAR, Sound, 30, NULL);
			SQLBindCol(hStmt1, 3, SQL_C_CHAR, View, 10, NULL);
			SQLBindCol(hStmt1, 7, SQL_C_CHAR, SeatNo, 10, NULL);
			SQLBindCol(hStmt1, 8, SQL_C_CHAR, Total, 10, NULL);

			// 공연 데이터 나열
			while (SQLFetch(hStmt1) != SQL_NO_DATA)
			{
				// seat의 detail 정보 구하기
				seatno = (CString)SeatNo;
				MessageBox(seatno);
				if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt2) == SQL_SUCCESS)
				{
					sprintf_s((char*)query3, 201, "SELECT CLASS, SECTION, [ROW], [COLUMN] FROM SEAT WHERE SEATNO = %d AND HALLNO=%d", atoi(seatno), atoi(hallno));
					MessageBox((char*)query3);

					SQLExecDirect(hStmt2, (SQLCHAR*)query3, SQL_NTS);

					SQLRETURN ret2 = SQLFetch(hStmt2);
					SQLCHAR  seatClass[30];
					SQLCHAR  section[30];
					SQLCHAR  row[10];
					SQLCHAR  column[10];

					ret2 = SQLGetData(hStmt2, 1, SQL_C_WCHAR, seatClass, sizeof(seatClass), NULL);
					ret2 = SQLGetData(hStmt2, 2, SQL_C_WCHAR, section, sizeof(section), NULL);
					ret2 = SQLGetData(hStmt2, 3, SQL_C_WCHAR, row, sizeof(row), NULL);
					ret2 = SQLGetData(hStmt2, 4, SQL_C_WCHAR, column, sizeof(column), NULL);

					CString seatClassStr(seatClass);
					CString sectionStr(section);
					CString rowStr(row);
					CString columnStr(column);

					seatinfo = sectionStr + _T("구역 ") + rowStr + _T("열 ") + columnStr + _T("번째");
					MessageBox(seatinfo);
					SQLCloseCursor(hStmt2);
					SQLFreeHandle(SQL_HANDLE_STMT, hStmt2);
				}
				else {
					MessageBox("DB 연결에 실패했습니다.");
				}

				int num;
				num = m_ListCtrl.GetItemCount();
				str.Format(_T("%d"), num);
				m_ListCtrl.InsertItem(num, (CString)Reviewno);
				m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)seatinfo, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)View + "점" , NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)Sound + "점" , NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 4, LVIF_TEXT, (CString)Total + "점" , NULL, NULL, NULL, NULL);
			}
			SQLCloseCursor(hStmt1);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt1);
		}
		DB.db_disconnect();
	}
}

void CCustomDlg3::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int sel = m_ConcertBox.GetCurSel();
	m_HallBox.ResetContent();
	switch (sel) {
	case 0:
		m_HallBox.AddString(_T("콘서트홀"));
		m_HallBox.AddString(_T("IBK챔버"));
		m_HallBox.AddString(_T("리사이틀홀"));
		m_HallBox.AddString(_T("인춘아트홀"));
		m_HallBox.AddString(_T("CJ토월극장"));
		break;
	case 1:
		m_HallBox.AddString(_T("콘서트홀"));
		break;
	case 2:
		m_HallBox.AddString(_T("세종대극장"));
		m_HallBox.AddString(_T("세종M씨어터"));
		m_HallBox.AddString(_T("세종체임버홀"));
		m_HallBox.AddString(_T("세종S씨어터"));
		break;
	}
}
