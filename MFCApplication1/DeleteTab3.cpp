// DeleteTab3.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DeleteTab3.h"
#include "DBConnect.h"


// CDeleteTab3 대화 상자

IMPLEMENT_DYNAMIC(CDeleteTab3, CDialogEx)

CDeleteTab3::CDeleteTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DELETE_DLG3, pParent)
{

}

CDeleteTab3::~CDeleteTab3()
{
}

void CDeleteTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_ShowNo);
}


BEGIN_MESSAGE_MAP(CDeleteTab3, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON1, &CDeleteTab3::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDeleteTab3 메시지 처리기

BOOL CDeleteTab3::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // 표 틀 생성
    CRect rt;

    m_ListCtrl.GetWindowRect(&rt);
    m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_ListCtrl.InsertColumn(0, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.2);
    m_ListCtrl.InsertColumn(1, TEXT("공연장소"), LVCFMT_CENTER, rt.Width() * 0.4);
    m_ListCtrl.InsertColumn(2, TEXT("홀 이름"), LVCFMT_CENTER, rt.Width() * 0.4);

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
        MessageBox("공연장 정보를 불러오는데 실패했습니다.");
    }

    return TRUE;
}

void CDeleteTab3::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString showno;
    m_ShowNo.GetWindowTextA(showno);

    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[101];

    if (DB.db_connect()) {
        hDbc = DB.hDbc;
        m_ShowNo.GetWindowText(showno);
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 101, "DELETE FROM CONCERTHALL WHERE HALLNO='%s'", showno);

            SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            // 에러 메시지 처리
            if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
                MessageBox("해당 공연장을 사용하고 있어서 삭제가 불가능합니다.");
            }
            else {
                MessageBox("성공적으로 공연장을 삭제했습니다.");
            }

            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

        }
        DB.db_disconnect();
    }
    else {
        MessageBox("공연장 삭제에 실패했습니다.");
    }
}
