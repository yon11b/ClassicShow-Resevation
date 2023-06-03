// SchemaTab5.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SchemaTab5.h"
#include "DBConnect.h"


// CSchemaTab3 대화 상자

IMPLEMENT_DYNAMIC(CSchemaTab5, CDialogEx)

CSchemaTab5::CSchemaTab5(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_SCHEMA_DLG5, pParent)
{

}

CSchemaTab5::~CSchemaTab5()
{
}

void CSchemaTab5::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CSchemaTab5, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CSchemaTab5::OnBnClickedButton1)
END_MESSAGE_MAP()

// CSchemaTab5 메시지 처리기
BOOL CSchemaTab5::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // 표 틀 생성
    CRect rt;

    m_ListCtrl.GetWindowRect(&rt);
    m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_ListCtrl.InsertColumn(0, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.2);
    m_ListCtrl.InsertColumn(1, TEXT("공연장소"), LVCFMT_CENTER, rt.Width() * 0.4);
    m_ListCtrl.InsertColumn(2, TEXT("홀 이름"), LVCFMT_CENTER, rt.Width() * 0.4);

    return TRUE;
}
void CSchemaTab5::OnBnClickedButton1()
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
            sprintf_s((char*)query, 101, "SELECT * FROM CONCERTHALL");
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            SQLCHAR hallno[10];
            SQLCHAR hallname[100];
            SQLCHAR roomname[100];

            SQLBindCol(hStmt, 1, SQL_C_CHAR, hallno, 10, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, hallname, 100, NULL);
            SQLBindCol(hStmt, 3, SQL_C_CHAR, roomname, 100, NULL);

            int num;
            CString str;
            // 예매 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                num = m_ListCtrl.GetItemCount();
                str.Format(_T("%d"), num);
                m_ListCtrl.InsertItem(num, (CString)hallno);
                m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)hallname, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)roomname, NULL, NULL, NULL, NULL);
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