// SchemaTab2.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SchemaTab2.h"


// CSchemaTab2 대화 상자

IMPLEMENT_DYNAMIC(CSchemaTab2, CDialogEx)

CSchemaTab2::CSchemaTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCHEMA_DLG2, pParent)
{

}

CSchemaTab2::~CSchemaTab2()
{
}

void CSchemaTab2::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CSchemaTab2, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CSchemaTab2::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSchemaTab2 메시지 처리기
BOOL CSchemaTab2::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // 표 틀 생성
    CRect rt;
    m_ListCtrl.GetWindowRect(&rt);
    m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_ListCtrl.InsertColumn(0, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.05);
    m_ListCtrl.InsertColumn(1, TEXT("제목"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(2, TEXT("작성자"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(3, TEXT("공연장번호"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(4, TEXT("좌석번호"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(5, TEXT("음향 평가"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(6, TEXT("시야 평가"), LVCFMT_CENTER, rt.Width() * 0.05);
    m_ListCtrl.InsertColumn(7, TEXT("총 평가"), LVCFMT_CENTER, rt.Width() * 0.05);

    return TRUE;
}


void CSchemaTab2::OnBnClickedButton1()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[101];
    if (DB.db_connect()) {

        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 101, "SELECT * FROM REVIEW");
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            SQLCHAR reviewno[100];
            SQLCHAR sound[10];
            SQLCHAR view[10];
            SQLCHAR detail[1000];
            SQLCHAR userid[100];
            SQLCHAR hallno[100];
            SQLCHAR seatno[100];
            SQLCHAR total[100];

            SQLBindCol(hStmt, 1, SQL_C_CHAR, reviewno, 100, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, sound, 10, NULL);
            SQLBindCol(hStmt, 3, SQL_C_CHAR, view, 100, NULL);
            SQLBindCol(hStmt, 4, SQL_C_CHAR, detail, 1000, NULL);
            SQLBindCol(hStmt, 5, SQL_C_CHAR, userid, 100, NULL);
            SQLBindCol(hStmt, 6, SQL_C_CHAR, hallno, 10, NULL);
            SQLBindCol(hStmt, 7, SQL_C_CHAR, seatno, 10, NULL);
            SQLBindCol(hStmt, 8, SQL_C_CHAR, total, 10, NULL);

            int num;
            CString str;
            // 공연 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                num = m_ListCtrl.GetItemCount();
                str.Format(_T("%d"), num);
                m_ListCtrl.InsertItem(num, (CString)reviewno);
                m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)detail, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)userid, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)hallno, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 4, LVIF_TEXT, (CString)seatno, NULL, NULL, NULL, NULL);
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
        MessageBox("공연 정보를 불러오는데 실패했습니다.");
    }
}
