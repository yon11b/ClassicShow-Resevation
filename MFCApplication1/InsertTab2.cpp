// InsertTab2.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "InsertTab2.h"
#include "DBConnect.h"


// CInsertTab2 대화 상자
BOOL CInsertTab2::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    m_ConcertBox.AddString(_T("예술의 전당"));
    m_ConcertBox.AddString(_T("잠실 롯데"));
    m_ConcertBox.AddString(_T("세종문화회관"));

    return TRUE;
}

IMPLEMENT_DYNAMIC(CInsertTab2, CDialogEx)

CInsertTab2::CInsertTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSERT_DLG2, pParent)
{

}

CInsertTab2::~CInsertTab2()
{
}

void CInsertTab2::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_Section);
    DDX_Control(pDX, IDC_EDIT3, m_Sound);
    DDX_Control(pDX, IDC_EDIT2, m_View);
    DDX_Control(pDX, IDC_EDIT7, m_Total);
    DDX_Control(pDX, IDC_COMBO1, m_ConcertBox);
    DDX_Control(pDX, IDC_COMBO2, m_HallBox);
    DDX_Control(pDX, IDC_EDIT6, m_Column);
    DDX_Control(pDX, IDC_EDIT5, m_Row);
    DDX_Control(pDX, IDC_EDIT4, m_Detail);
}


BEGIN_MESSAGE_MAP(CInsertTab2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CInsertTab2::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CInsertTab2::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CInsertTab2 메시지 처리기

void CInsertTab2::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    int sel = m_ConcertBox.GetCurSel();
    m_HallBox.ResetContent();
    switch (sel) {
    case 0:
        m_HallBox.AddString(_T("콘서트홀"));
        m_HallBox.AddString(_T("IBK챔버"));
        m_HallBox.AddString(_T("리사이틀홀"));
        break;
    case 1:
        m_HallBox.AddString(_T("콘서트홀"));
        break;
    case 2:
        m_HallBox.AddString(_T("세종대극장"));
        m_HallBox.AddString(_T("세종M씨어터"));
        break;
    }
}


void CInsertTab2::OnBnClickedButton1()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString section;
    CString sound;
    CString view;
    CString total;
    CString concert;
    CString hall;
    CString detail;
    CString column;
    CString row;
    CString userid;
    int hallno;
    int seatno;
    int isSeat = 0;

    SQLHDBC hDbc1;
    SQLHSTMT hStmt1;    // Statement Handle
    SQLHDBC hDbc2;
    SQLHSTMT hStmt2;    // Statement Handle
    SQLCHAR query[301];

    userid = SESSION.userId;

    //1. Seat의 Seatno와 Concerthall의 hallno 구하기
    if (DB.db_connect()) {
        m_Section.GetWindowText(section);
        m_Sound.GetWindowText(sound);
        m_View.GetWindowText(view);
        m_Total.GetWindowText(total);
        m_ConcertBox.GetWindowText(concert);
        m_HallBox.GetWindowText(hall);
        m_Detail.GetWindowText(detail);
        m_Column.GetWindowText(column);
        m_Row.GetWindowText(row);
        
        hDbc1 = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc1, &hStmt1) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 201, "SELECT SEATNO, HALLNO FROM SEAT WHERE HALLNO = (SELECT HALLNO FROM CONCERTHALL WHERE HALLNAME ='%s' AND ROOMNAME='%s') AND ([SECTION] ='%s' AND [COLUMN]='%s' AND [ROW]='%s')", concert, hall, section, column, row);
            // MessageBox((LPCTSTR)query); // Debugging code
            SQLExecDirect(hStmt1, query, SQL_NTS);
            SQLBindCol(hStmt1, 1, SQL_C_SLONG, &seatno, sizeof(int), NULL);
            SQLBindCol(hStmt1, 2, SQL_C_SLONG, &hallno, sizeof(int), NULL);

            SQLRETURN ret1 = SQLFetch(hStmt1);
            if (ret1 == SQL_SUCCESS || ret1 == SQL_SUCCESS_WITH_INFO) {
                //MessageBox("Seatno과 Hallno을 구했습니다.");
                isSeat = 1;
            }
            else {
                isSeat = 0;
            }
        }
        SQLCloseCursor(hStmt1);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt1);
        DB.db_disconnect();
    }
    else {
        MessageBox("DB 연결에 실패했습니다.");
    }

    //2. INSERT 실행
    if (isSeat && DB.db_connect()) {
        hDbc2 = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc2, &hStmt2) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 301, "INSERT INTO REVIEW(SOUND, [VIEW], DETAIL, USERID, HALLNUM, \
            SEATNUM, TOTAL) VALUES('%s','%s','%s','%s', %d, %d,'%s')", sound, view, detail, userid, hallno, seatno, total);
            SQLExecDirect(hStmt2, query, SQL_NTS);
            MessageBox("리뷰를 생성하였습니다.");
        }
        SQLCloseCursor(hStmt2);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt2);
        DB.db_disconnect();
    }
    else {
        MessageBox("리뷰 생성에 실패했습니다.");
    }
}