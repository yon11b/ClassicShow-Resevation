// SchemaTab3.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SchemaTab3.h"
#include "DBConnect.h"


// CSchemaTab3 대화 상자

IMPLEMENT_DYNAMIC(CSchemaTab3, CDialogEx)

CSchemaTab3::CSchemaTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCHEMA_DLG3, pParent)
{

}

CSchemaTab3::~CSchemaTab3()
{
}

void CSchemaTab3::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CSchemaTab3, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CSchemaTab3::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSchemaTab3 메시지 처리기
// CSchemaTab1 메시지 처리기
BOOL CSchemaTab3::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // 표 틀 생성
    CRect rt;

    m_ListCtrl.GetWindowRect(&rt);
    m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_ListCtrl.InsertColumn(0, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.05);
    m_ListCtrl.InsertColumn(1, TEXT("고객이름"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(2, TEXT("공연번호"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(3, TEXT("좌석번호"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(4, TEXT("공연장번호"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(5, TEXT("금액"), LVCFMT_CENTER, rt.Width() * 0.1);

    return TRUE;
}
void CSchemaTab3::OnBnClickedButton1()
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
            sprintf_s((char*)query, 101, "SELECT * FROM RESERVATE");
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            SQLCHAR reserveno[10];
            SQLCHAR userid[10];
            SQLCHAR showno[10];
            SQLCHAR seatno[10];
            SQLCHAR hallno[10];
            SQLCHAR price[10];

            SQLBindCol(hStmt, 1, SQL_C_CHAR, reserveno, 10, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, userid, 10, NULL);
            SQLBindCol(hStmt, 3, SQL_C_CHAR, showno, 10, NULL);
            SQLBindCol(hStmt, 4, SQL_C_CHAR, seatno, 10, NULL);
            SQLBindCol(hStmt, 5, SQL_C_CHAR, hallno, 10, NULL);
            SQLBindCol(hStmt, 6, SQL_C_CHAR, price, 10, NULL);

            int num;
            CString str;
            // 예매 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                num = m_ListCtrl.GetItemCount();
                str.Format(_T("%d"), num);
                m_ListCtrl.InsertItem(num, (CString)reserveno);
                m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)userid, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)showno, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)seatno, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 4, LVIF_TEXT, (CString)hallno, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 5, LVIF_TEXT, (CString)price, NULL, NULL, NULL, NULL);
            }

            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }
        DB.db_disconnect();
    }
    else {
        MessageBox("예매 정보를 불러오는데 실패했습니다.");
    }
}