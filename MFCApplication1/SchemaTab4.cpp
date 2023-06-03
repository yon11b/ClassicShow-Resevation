// SchemaTab4.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SchemaTab4.h"
#include "DBConnect.h"


// CSchemaTab4 대화 상자

IMPLEMENT_DYNAMIC(CSchemaTab4, CDialogEx)

CSchemaTab4::CSchemaTab4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCHEMA_DLG4, pParent)
{

}

CSchemaTab4::~CSchemaTab4()
{
}

void CSchemaTab4::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CSchemaTab4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSchemaTab4::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSchemaTab4 메시지 처리기
BOOL CSchemaTab4::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // 표 틀 생성
    CRect rt;

    m_ListCtrl.GetWindowRect(&rt);
    m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_ListCtrl.InsertColumn(0, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(1, TEXT("좌석번호"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(2, TEXT("공연장번호"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(3, TEXT("좌석등급"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(4, TEXT("좌석구역"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(5, TEXT("좌석 열"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(6, TEXT("좌석 행"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(7, TEXT("부모 좌석번호"), LVCFMT_CENTER, rt.Width() * 0.15);
    m_ListCtrl.InsertColumn(8, TEXT("부모 공연장 번호"), LVCFMT_CENTER, rt.Width() * 0.15);

    return TRUE;
}

void CSchemaTab4::OnBnClickedButton1()
{
    m_ListCtrl.DeleteAllItems();
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[101];
    if (DB.db_connect()) {

        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 101, "SELECT * FROM SEAT");
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            SQLCHAR seatno[10];
            SQLCHAR hallno[10];
            SQLCHAR classname[10];
            SQLCHAR section[10];
            SQLCHAR row[10];
            SQLCHAR column[10];
            SQLCHAR parent_seatno[10];
            SQLCHAR parent_hallno[10];

            SQLBindCol(hStmt, 1, SQL_C_CHAR, seatno, 10, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, hallno, 10, NULL);
            SQLBindCol(hStmt, 3, SQL_C_CHAR, classname, 10, NULL);
            SQLBindCol(hStmt, 4, SQL_C_CHAR, section, 10, NULL);
            SQLBindCol(hStmt, 5, SQL_C_CHAR, row, 10, NULL);
            SQLBindCol(hStmt, 6, SQL_C_CHAR, column, 10, NULL);
            SQLBindCol(hStmt, 7, SQL_C_CHAR, parent_seatno, 10, NULL);
            SQLBindCol(hStmt, 8, SQL_C_CHAR, parent_hallno, 10, NULL);

            int num;
            CString str;
            // 좌석 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                num = m_ListCtrl.GetItemCount();
                str.Format(_T("%d"), num);
                m_ListCtrl.InsertItem(num, str);
                m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)seatno, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)hallno, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)classname, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 4, LVIF_TEXT, (CString)section, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 5, LVIF_TEXT, (CString)row, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 6, LVIF_TEXT, (CString)column, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 7, LVIF_TEXT, (CString)parent_seatno, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 8, LVIF_TEXT, (CString)parent_hallno, NULL, NULL, NULL, NULL);
            }

            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }
        DB.db_disconnect();
    }
    else {
        MessageBox("좌석 정보를 불러오는데 실패했습니다.");
    }
}