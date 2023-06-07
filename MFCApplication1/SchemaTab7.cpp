// SchemaTab7.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SchemaTab7.h"
#include "DBConnect.h"

// CSchemaTab7 대화 상자

IMPLEMENT_DYNAMIC(CSchemaTab7, CDialogEx)

CSchemaTab7::CSchemaTab7(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_SCHEMA_DLG7, pParent)
{

}

CSchemaTab7::~CSchemaTab7()
{
}

void CSchemaTab7::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CSchemaTab7, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CSchemaTab7::OnBnClickedButton1)
END_MESSAGE_MAP()

// CSchemaTab7 메시지 처리기
BOOL CSchemaTab7::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // 표 틀 생성
    CRect rt;

    m_ListCtrl.GetWindowRect(&rt);
    m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_ListCtrl.InsertColumn(0, TEXT("계좌번호"), LVCFMT_CENTER, rt.Width() * 0.2);
    m_ListCtrl.InsertColumn(1, TEXT("사용자"), LVCFMT_CENTER, rt.Width() * 0.3);
    m_ListCtrl.InsertColumn(2, TEXT("잔액"), LVCFMT_CENTER, rt.Width() * 0.2);
    m_ListCtrl.InsertColumn(3, TEXT("비밀번호"), LVCFMT_CENTER, rt.Width() * 0.3);

    return TRUE;
}
void CSchemaTab7::OnBnClickedButton1()
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
            sprintf_s((char*)query, 101, "SELECT * FROM CARD");
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            SQLCHAR accountno[10];
            SQLCHAR userid[100];
            SQLCHAR balance[100];
            SQLCHAR cardpw[100];

            SQLBindCol(hStmt, 1, SQL_C_CHAR, accountno, 10, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, userid, 100, NULL);
            SQLBindCol(hStmt, 3, SQL_C_CHAR, balance, 100, NULL);
            SQLBindCol(hStmt, 4, SQL_C_CHAR, cardpw, 100, NULL);

            int num;
            CString str;
            // 예매 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                num = m_ListCtrl.GetItemCount();
                str.Format(_T("%d"), num);
                m_ListCtrl.InsertItem(num, (CString)accountno);
                m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)userid, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)balance, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)cardpw, NULL, NULL, NULL, NULL);
            }

            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }
        DB.db_disconnect();
    }
    else {
        MessageBox("카드 정보를 불러오는데 실패했습니다.");
    }
}
