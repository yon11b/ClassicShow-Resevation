// InsertTab1.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "InsertTab1.h"
#include "DBConnect.h"


// CInsertTab1 대화 상자

BOOL CInsertTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_ConcertBox.AddString(_T("예술의 전당"));
	m_ConcertBox.AddString(_T("잠실 롯데"));
	m_ConcertBox.AddString(_T("세종문화회관"));

	return TRUE;
}

IMPLEMENT_DYNAMIC(CInsertTab1, CDialogEx)

CInsertTab1::CInsertTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSERT_DLG1, pParent)
{

}

CInsertTab1::~CInsertTab1()
{
}

void CInsertTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ConcertBox);
	DDX_Control(pDX, IDC_COMBO2, m_HallBox);
	DDX_Control(pDX, IDC_EDIT1, m_Title);
	DDX_Control(pDX, IDC_EDIT3, m_Musician);
	DDX_Control(pDX, IDC_EDIT2, m_Composer);
	DDX_Control(pDX, IDC_EDIT4, m_Genre);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_Date);
	DDX_Control(pDX, IDC_DATETIMEPICKER5, m_StartDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_EndDate);
	DDX_Control(pDX, IDC_EDIT5, m_RSeat);
	DDX_Control(pDX, IDC_EDIT8, m_SSeat);
	DDX_Control(pDX, IDC_EDIT7, m_ASeat);
	DDX_Control(pDX, IDC_EDIT6, m_BSeat);
	DDX_Control(pDX, IDC_EDIT9, m_Hour);
	DDX_Control(pDX, IDC_EDIT10, m_Minute);
}


BEGIN_MESSAGE_MAP(CInsertTab1, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CInsertTab1::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CInsertTab1::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CInsertTab1::OnBnClickedOk)
END_MESSAGE_MAP()


// CInsertTab1 메시지 처리기


void CInsertTab1::OnCbnSelchangeCombo1()
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


void CInsertTab1::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString title;
	CString musician;
	CString composer;
	CString genre;
	CString concert;
	CString hall;
	CString rseat;
	CString sseat;
	CString aseat;
	CString bseat;
	CString hour;
	CString minute;
	int hallno;

	SQLHDBC hDbc1;
	SQLHSTMT hStmt1;	// Statement Handle
	SQLHDBC hDbc2;
	SQLHSTMT hStmt2;	// Statement Handle
	SQLCHAR query[301];
	SQLLEN result;
	if (DB.db_connect()) {
		MessageBox("DB CONEECT!");
		m_Title.GetWindowText(title);
		m_Musician.GetWindowText(musician);
		m_Composer.GetWindowText(composer);
		m_Genre.GetWindowText(genre);
		m_ConcertBox.GetWindowText(concert);
		m_HallBox.GetWindowText(hall);
		m_RSeat.GetWindowText(rseat);
		m_SSeat.GetWindowText(sseat);
		m_ASeat.GetWindowText(aseat);
		m_BSeat.GetWindowText(bseat);
		m_Hour.GetWindowText(hour);
		m_Minute.GetWindowText(minute);

		MessageBox(rseat);

		// show의 외래키로 들어갈 hallno 구하기
		hDbc1 = DB.hDbc;
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc1, &hStmt1) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 101, "SELECT HALLNO FROM CONCERTHALL WHERE HALLNAME ='%s' AND ROOMNAME='%s'", concert, hall);
			SQLExecDirect(hStmt1, query, SQL_NTS);
			SQLBindCol(hStmt1, 1, SQL_C_SLONG, &hallno, sizeof(int), NULL);

			SQLRETURN ret1 = SQLFetch(hStmt1);
			if (ret1 == SQL_SUCCESS || ret1 == SQL_SUCCESS_WITH_INFO) {
				MessageBox("Hallno를 구했습니다.");
			}
		}
		SQLCloseCursor(hStmt1);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt1);
		DB.db_disconnect();
	}
	else {
		MessageBox("hallno를 구하지 못했습니다.");
	}
	if (DB.db_connect()) {
		// 사용자로부터 입력받은 date를 DB에 넣을 수 있는 형태로 변환
		// 1. 시간
		
		// 2. 날짜
		COleDateTime getDate;
		m_Date.GetTime(getDate);
		m_Hour.GetWindowText(hour);
		m_Minute.GetWindowText(minute);
		
		// 3. 날짜 + 시간
		COleDateTime date(getDate.GetYear(), getDate.GetMonth(), getDate.GetDay(), _ttoi(hour), _ttoi(minute), 0);
		CString strDate = date.Format(_T("%Y-%m-%d %H:%M:%S"));
		MessageBox(strDate);

		COleDateTime getStartDate;
		m_StartDate.GetTime(getStartDate);
		COleDateTime startDate(getStartDate.GetYear(), getStartDate.GetMonth(), getStartDate.GetDay(), 0, 0, 0);
		CString strStartDate = startDate.Format(_T("%Y-%m-%d %H:%M:%S"));
		MessageBox(strStartDate);

		COleDateTime getFinishDate;
		m_EndDate.GetTime(getFinishDate);
		COleDateTime finishDate(getFinishDate.GetYear(), getFinishDate.GetMonth(), getFinishDate.GetDay(), 0, 0, 0);
		CString strFinishDate = finishDate.Format(_T("%Y-%m-%d %H:%M:%S"));
		MessageBox(strFinishDate);

		hDbc2 = DB.hDbc;
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc2, &hStmt2) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "INSERT INTO SHOW(TITLE,[DATE],MUSICIAN,RESERVE_STARTTIME,RESERVE_ENDTIME,\
				COMPOSER, GENRE, PRICE_R, PRICE_S, PRICE_A, PRICE_B, HALLNO) VALUES('%s','%s','%s','%s','%s','%s',\
				'%s','%s','%s','%s','%s',%d)", title, strDate, musician, strStartDate, strFinishDate, composer, genre, rseat, sseat, aseat, bseat,hallno);
			SQLExecDirect(hStmt2, query, SQL_NTS);
			MessageBox((LPCTSTR)query);
		}
		else {
			MessageBox("ERORR");
		}
		SQLCloseCursor(hStmt2);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt2);
		DB.db_disconnect();
	}
	else {
		MessageBox("에러가 발생했습니다.");
	}
}


void CInsertTab1::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
