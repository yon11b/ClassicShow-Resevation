// CustomDlg5.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CustomDlg5.h"


// CCustomDlg5 대화 상자

IMPLEMENT_DYNAMIC(CCustomDlg5, CDialogEx)

CCustomDlg5::CCustomDlg5(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_CUSTOM_DLG5, pParent)
{

}

CCustomDlg5::~CCustomDlg5()
{
}

void CCustomDlg5::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
    DDX_Control(pDX, IDC_DATETIMEPICKER5, m_StartDate);
    DDX_Control(pDX, IDC_DATETIMEPICKER4, m_EndDate);
}


BEGIN_MESSAGE_MAP(CCustomDlg5, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CCustomDlg5::OnBnClickedButton1)

END_MESSAGE_MAP()


// CCustomDlg5 메시지 처리기

BOOL CCustomDlg5::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // 표 틀 생성
    CRect rt;
    m_ListCtrl.GetWindowRect(&rt);
    m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_ListCtrl.InsertColumn(0, TEXT("RC"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(1, TEXT("Title"), LVCFMT_CENTER, rt.Width() * 0.3);
    m_ListCtrl.InsertColumn(2, TEXT("Date"), LVCFMT_CENTER, rt.Width() * 0.2);
    m_ListCtrl.InsertColumn(3, TEXT("Musician"), LVCFMT_CENTER, rt.Width() * 0.15);
    m_ListCtrl.InsertColumn(4, TEXT("Composer"), LVCFMT_CENTER, rt.Width() * 0.15);
    m_ListCtrl.InsertColumn(5, TEXT("Genre"), LVCFMT_CENTER, rt.Width() * 0.1);

    return TRUE;
}

void CCustomDlg5::OnBnClickedButton1()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString startdate;
    CString enddate;

    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[501];

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
            sprintf_s((char*)query, 501, "SELECT title, date, musician, composer, Frequency, genre FROM SHOW S \
                JOIN(SELECT TOP 10 SHOWNO, COUNT(SHOWNO) AS Frequency FROM RESERVATE GROUP BY SHOWNO ORDER BY Frequency DESC \
                ) AS T ON S.SHOWNO = T.SHOWNO \
                WHERE '%s' <= FORMAT([DATE], 'yyyy-MM-dd HH:mm:ss') AND FORMAT([DATE], 'yyyy-MM-dd HH:mm:ss') <= '%s' \
                ", strStartDate, strFinishDate);
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            SQLCHAR title[100];
            SQLCHAR date[100];
            SQLCHAR composer[100];
            SQLCHAR musician[100];
            SQLCHAR frequency[10];
            SQLCHAR genre[10];

            SQLBindCol(hStmt, 1, SQL_C_CHAR, title, 100, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, date, 100, NULL);
            SQLBindCol(hStmt, 3, SQL_C_CHAR, musician, 100, NULL);
            SQLBindCol(hStmt, 4, SQL_C_CHAR, composer, 100, NULL);
            SQLBindCol(hStmt, 5, SQL_C_CHAR, frequency, 10, NULL);
            SQLBindCol(hStmt, 6, SQL_C_CHAR, genre, 10, NULL);

            int num;
            CString str;
            // 공연 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                num = m_ListCtrl.GetItemCount();
                str.Format(_T("%d"), num);
                m_ListCtrl.InsertItem(num, (CString)frequency);
                m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)title, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)date, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)musician, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 4, LVIF_TEXT, (CString)composer, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 5, LVIF_TEXT, (CString)genre, NULL, NULL, NULL, NULL);
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