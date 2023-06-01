// DeleteTab2.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DeleteTab2.h"
#include "Session.h"


// CDeleteTab2 대화 상자

IMPLEMENT_DYNAMIC(CDeleteTab2, CDialogEx)

CDeleteTab2::CDeleteTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DELETE_DLG2, pParent)
{

}

CDeleteTab2::~CDeleteTab2()
{
}

void CDeleteTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_ReviewNo);
}


BEGIN_MESSAGE_MAP(CDeleteTab2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDeleteTab2::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDeleteTab2 메시지 처리기
BOOL CDeleteTab2::OnInitDialog() {
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
    
    CString userid;
    CString str;
    SQLCHAR reviewno[30];
    SQLCHAR title[100];
    SQLCHAR hallname[100];
    SQLCHAR roomname[100];
    SQLCHAR seatnum[30];
    SQLCHAR sound[30];
    SQLCHAR view[30];
    SQLCHAR total[30]; 
    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[201];

    userid = SESSION.userId;
    if (DB.db_connect()) {

        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 201, "SELECT REVIEWNO, DETAIL, HALLNAME, ROOMNAME, SEATNUM, SOUND, [VIEW], TOTAL FROM REVIEW R, CONCERTHALL C WHERE R.HALLNUM = C.HALLNO AND R.USERID='%s'", userid);
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            SQLBindCol(hStmt, 1, SQL_C_CHAR, reviewno, 30, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, title, 100, NULL);
            SQLBindCol(hStmt, 3, SQL_C_CHAR, hallname, 100, NULL);
            SQLBindCol(hStmt, 4, SQL_C_CHAR, roomname, 100, NULL);
            SQLBindCol(hStmt, 5, SQL_C_CHAR, seatnum, 30, NULL);
            SQLBindCol(hStmt, 6, SQL_C_CHAR, sound, 30, NULL);
            SQLBindCol(hStmt, 7, SQL_C_CHAR, view, 30, NULL);
            SQLBindCol(hStmt, 8, SQL_C_CHAR, total, 30, NULL);

            int num;
            // 공연 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                num = m_ListCtrl.GetItemCount();
                m_ListCtrl.InsertItem(num, (CString)reviewno);
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
        MessageBox("리뷰 정보를 불러오는데 실패했습니다.");
    }

	return TRUE;
}

void CDeleteTab2::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString reviewno;
    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[101];

    if (DB.db_connect()) {
        MessageBox("DB CONEECT!");

        hDbc = DB.hDbc;
        m_ReviewNo.GetWindowText(reviewno);
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            MessageBox("SQL START SELECT");
            sprintf_s((char*)query, 101, "DELETE FROM REVIEW WHERE REVIEWNO='%s'", reviewno);
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }
        DB.db_disconnect();
    }
    else {
        MessageBox("공연 정보를 불러오는데 실패했습니다.");
    }
}
