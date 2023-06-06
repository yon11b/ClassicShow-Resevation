// CustomDlg2.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CustomDlg2.h"
#include "DBConnect.h"


// CCustomDlg2 대화 상자

IMPLEMENT_DYNAMIC(CCustomDlg2, CDialogEx)

CCustomDlg2::CCustomDlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOM_DLG2, pParent)
{

}

CCustomDlg2::~CCustomDlg2()
{
}

void CCustomDlg2::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, m_Show);
    DDX_Control(pDX, IDC_COMBO2, m_Seat);
    DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CCustomDlg2, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CCustomDlg2::OnBnClickedButton1)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CCustomDlg2::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CCustomDlg2 메시지 처리기

BOOL CCustomDlg2::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    SQLHDBC hDbc;
    SQLHSTMT hStmt;	// Statement Handle
    SQLCHAR query[301];
    SQLCHAR showNo[10];
    SQLCHAR titleList[100];
    CString showinfo;
    userid = SESSION.userId;

    if (DB.db_connect())
    {
        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
            sprintf_s((char*)query, 301, "SELECT DISTINCT S.SHOWNO, S.TITLE FROM RESERVATE R, SHOW S WHERE R.USERID='%s' AND R.SHOWNO=S.SHOWNO", userid);
            // MessageBox((LPCTSTR)query); // Debugging code
            SQLExecDirect(hStmt, query, SQL_NTS);
            SQLBindCol(hStmt, 1, SQL_C_CHAR, showNo, 10, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, titleList, 100, NULL);
            // 공연 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                showinfo = (CString)showNo + ". " + (CString)titleList;
                m_Show.AddString(showinfo);
            }
        }
        SQLCloseCursor(hStmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        DB.db_disconnect();
    }

    // 표 틀 생성
    CRect rt;
    m_ListCtrl.GetWindowRect(&rt);
    m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_ListCtrl.InsertColumn(0, TEXT("예약번호"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(1, TEXT("사용자"), LVCFMT_CENTER, rt.Width() * 0.3);
    m_ListCtrl.InsertColumn(3, TEXT("좌석번호"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(5, TEXT("가격"), LVCFMT_CENTER, rt.Width() * 0.3);

    return TRUE;
}


void CCustomDlg2::OnBnClickedButton1()
{
    m_ListCtrl.DeleteAllItems();
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString showno;
    CString selText;
    CString seat;
    CString Info;

    int selIdx = m_Show.GetCurSel();
    m_Show.GetLBText(selIdx, selText);
    int dotIndex = selText.Find(_T(". "));
    if (dotIndex != -1)
    {
        showno = selText.Left(dotIndex);
    }

    m_Seat.GetWindowText(seat);
    selIdx = m_Seat.GetCurSel();
    m_Seat.GetLBText(selIdx, selText);

    dotIndex = selText.Find(_T(". "));
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

    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[501];
    SQLCHAR reserveno[10];
    SQLCHAR userIDs[100];
    SQLCHAR seatNos[10];
    SQLCHAR payment[10];
    CString str;

    if (DB.db_connect())
    {
        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
            sprintf_s((char*)query, 501, "SELECT R.* FROM RESERVATE R WHERE \
                R.SHOWNO IN(SELECT R3.SHOWNO FROM RESERVATE R3 WHERE R3.USERID = '%s'\
                    AND SHOWNO = '%s' AND SEATNO = '%s') AND \
                R.SEATNO IN(SELECT S1.SEATNO FROM SEAT S1, SEAT S2 \
                    WHERE S1.PARENT_SEATNO = S2.PARENT_SEATNO AND S1.PARENT_HALLNO = S2.PARENT_HALLNO \
                    AND S2.SEATNO = '%s' AND S2.HALLNO = '%s' \
                )ORDER BY R.SEATNO ASC; ",userid, showno, seatno, seatno, hallno);

            // MessageBox((LPCTSTR)query); // Debugging code
            SQLExecDirect(hStmt, query, SQL_NTS);
            SQLBindCol(hStmt, 1, SQL_C_CHAR, reserveno, 10, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, userIDs, 100, NULL);
            SQLBindCol(hStmt, 4, SQL_C_CHAR, seatNos, 10, NULL);
            SQLBindCol(hStmt, 6, SQL_C_CHAR, payment, 10, NULL);

            int num;
            // 공연 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                num = m_ListCtrl.GetItemCount();
                str.Format(_T("%d"), num);
                m_ListCtrl.InsertItem(num, (CString)reserveno);
                m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)userIDs, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)seatNos, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)payment, NULL, NULL, NULL, NULL);
            }
            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }
        DB.db_disconnect();
    }
}

void CCustomDlg2::OnCbnSelchangeCombo1()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    int selIdx = m_Show.GetCurSel();
    CString selText;
    SQLHDBC hDbc;
    SQLHSTMT hStmt1;	// Statement Handle
    SQLCHAR query[501];
    SQLRETURN ret;
    CString showno;

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

                seatinfo = strHallNo + "-" + strSeatNo + ". " + strSection + _T("구역") + strRow + _T("열") + strColumn + _T("번째 (") + strSeatClass + _T(")석");
                m_Seat.AddString(seatinfo);
                MessageBox(seatinfo);
            }
        }
        SQLCloseCursor(hStmt1);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt1);
    }
    DB.db_disconnect();
}
