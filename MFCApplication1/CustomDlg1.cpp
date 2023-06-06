// CustomDlg1.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CustomDlg1.h"
#include "DBConnect.h"


// CCustomDlg1 대화 상자

BOOL CCustomDlg1::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    MessageBox("start");
    SQLHDBC hDbc;
    SQLHSTMT hStmt;	// Statement Handle
    SQLCHAR query[301];
    SQLCHAR showNo[100];
    SQLCHAR titleList[100];
    CString showinfo;
    userid = SESSION.userId;

    if (DB.db_connect())
    {
        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
            sprintf_s((char*)query, 301, "SELECT DISTINCT S.SHOWNO, S.TITLE FROM RESERVATE R, SHOW S WHERE R.USERID='%s' AND R.SHOWNO=S.SHOWNO AND S.DATE < GETDATE()", userid);
            // MessageBox((LPCTSTR)query); // Debugging code
            SQLExecDirect(hStmt, query, SQL_NTS);
            SQLBindCol(hStmt, 1, SQL_C_CHAR, showNo, 100, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, titleList, 100, NULL);

            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                showinfo = (CString)showNo +". " + (CString)titleList;
                m_Show.AddString(showinfo);
            }
        }
        SQLCloseCursor(hStmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        DB.db_disconnect();
    }

    // SOUND COMBO BOX
    m_Sound.AddString("1");
    m_Sound.AddString("2");
    m_Sound.AddString("3");
    m_Sound.AddString("4");
    m_Sound.AddString("5");

    // VIEW COMBO BOX
    m_View.AddString("1");
    m_View.AddString("2");
    m_View.AddString("3");
    m_View.AddString("4");
    m_View.AddString("5");

    // TOTAL COMBO BOX
    m_Total.AddString("1");
    m_Total.AddString("2");
    m_Total.AddString("3");
    m_Total.AddString("4");
    m_Total.AddString("5");

    return TRUE;
}

IMPLEMENT_DYNAMIC(CCustomDlg1, CDialogEx)

CCustomDlg1::CCustomDlg1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOM_DLG1, pParent)
{

}

CCustomDlg1::~CCustomDlg1()
{
}

void CCustomDlg1::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, m_Show);
    DDX_Control(pDX, IDC_COMBO4, m_Sound);
    DDX_Control(pDX, IDC_COMBO5, m_Total);
    DDX_Control(pDX, IDC_COMBO2, m_Seat);
    DDX_Control(pDX, IDC_COMBO3, m_View);
    DDX_Control(pDX, IDC_EDIT2, m_Detail);
}


BEGIN_MESSAGE_MAP(CCustomDlg1, CDialogEx)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CCustomDlg1::OnCbnSelchangeCombo1)
    ON_BN_CLICKED(IDC_BUTTON1, &CCustomDlg1::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCustomDlg1 메시지 처리기

void CCustomDlg1::OnCbnSelchangeCombo1()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    int selIdx = m_Show.GetCurSel();
    CString selText;
    SQLHDBC hDbc;
    SQLHSTMT hStmt1;	// Statement Handle
    SQLCHAR query[501];
    SQLRETURN ret;
    int seatno;

    m_Seat.ResetContent();
    m_Show.GetLBText(selIdx, selText);

    int dotIndex = selText.Find(_T(". "));
    if (dotIndex != -1)
    {
        showno = selText.Left(dotIndex);
    }

    if (DB.db_connect()) {
        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt1) == SQL_SUCCESS) {
            sprintf_s((char*)query, 501, "SELECT S.SEATNO, CLASS, SECTION, [ROW], [COLUMN], S.HALLNO FROM SEAT S, RESERVATE R WHERE USERID='%s' AND R.SHOWNO = '%s' AND R.SEATNO=S.SEATNO AND R.HALLNO=S.HALLNO", userid, showno);
            MessageBox((LPCTSTR)query); // Debugging code
            SQLExecDirect(hStmt1, query, SQL_NTS);

            SQLCHAR seatNo[30];
            SQLCHAR seatClass[30];
            SQLCHAR section[30];
            SQLCHAR row[10];
            SQLCHAR column[10];
            SQLCHAR hallNo[30];
            CString seatinfo;

            SQLBindCol(hStmt1, 1, SQL_C_CHAR, seatNo, 30, NULL);
            SQLBindCol(hStmt1, 2, SQL_C_CHAR, seatClass, 30, NULL);
            SQLBindCol(hStmt1, 3, SQL_C_CHAR, section, 30, NULL);
            SQLBindCol(hStmt1, 4, SQL_C_CHAR, row, 10, NULL);
            SQLBindCol(hStmt1, 5, SQL_C_CHAR, column, 10, NULL);
            SQLBindCol(hStmt1, 6, SQL_C_CHAR, hallNo, 30, NULL);

            while (SQLFetch(hStmt1) == SQL_SUCCESS)
            {
                CString strSeatNo = CString(seatNo);
                CString strSeatClass = CString(seatClass);
                CString strSection = CString(section);
                CString strRow = CString(row);
                CString strColumn = CString(column);
                CString strHallNo = CString(hallNo);

                seatinfo = strHallNo+ "-" + strSeatNo + ". " + strSection + _T("구역") + strRow + _T("열") + strColumn + _T("번째 (") + strSeatClass + _T(")석");
                m_Seat.AddString(seatinfo);
                MessageBox(seatinfo);
            }
        }
        SQLCloseCursor(hStmt1);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt1);
    }
    DB.db_disconnect();
}


void CCustomDlg1::OnBnClickedButton1()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    SQLHDBC hDbc;
    SQLHSTMT hStmt2;	// Statement Handle
    CString selText;
    CString seatno;
    CString hallno;
    CString Info;
    SQLCHAR query[501];

    m_Total.GetWindowText(total);
    int selIdx = m_Seat.GetCurSel();
    m_Seat.GetLBText(selIdx, selText);

    int dotIndex = selText.Find(_T(". "));
    if (dotIndex != -1)
    {
        Info = selText.Left(dotIndex);
    }

    dotIndex = Info.Find(_T("-"));
    if (dotIndex != -1)
    {
        hallno = Info.Left(dotIndex);
        seatno = Info.Right(dotIndex);
    }

    m_Sound.GetWindowText(sound);
    m_View.GetWindowText(view);
    m_Total.GetWindowText(total);
    m_Detail.GetWindowText(detail);

    MessageBox(sound);
    MessageBox(view);
    MessageBox(detail);
    MessageBox(userid);
    MessageBox(hallno);
    MessageBox(seatno);
    MessageBox(total);

    if (DB.db_connect()) {
        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt2) == SQL_SUCCESS) {
            sprintf_s((char*)query, 501, "INSERT INTO REVIEW(SOUND, [VIEW], DETAIL, USERID, HALLNUM, SEATNUM, TOTAL) VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s')", sound, view, detail, userid, hallno, seatno, total);
            MessageBox((char*)query);
            SQLExecDirect(hStmt2, (SQLCHAR*)query, SQL_NTS);
            MessageBox("성공적으로 리뷰를 작성했습니다!");
        }

        else {
            MessageBox("에러났죠");
        }
        SQLCloseCursor(hStmt2);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt2);
        DB.db_disconnect();
    }
    else {
        MessageBox("ERROR");
    }
}
