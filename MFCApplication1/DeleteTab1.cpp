// DeleteTab1.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "DeleteTab1.h"


// CDeleteTab1 대화 상자

IMPLEMENT_DYNAMIC(CDeleteTab1, CDialogEx)

CDeleteTab1::CDeleteTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DELETE_DLG1, pParent)
{

}

CDeleteTab1::~CDeleteTab1()
{
}

void CDeleteTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_ShowNo);
}


BEGIN_MESSAGE_MAP(CDeleteTab1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CDeleteTab1::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDeleteTab1 메시지 처리기
BOOL CDeleteTab1::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// 표 틀 생성
	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrl.InsertColumn(0, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(1, TEXT("제목"), LVCFMT_CENTER, rt.Width() * 0.3);
	m_ListCtrl.InsertColumn(2, TEXT("연주자"), LVCFMT_CENTER, rt.Width() * 0.25);
	m_ListCtrl.InsertColumn(3, TEXT("작곡가"), LVCFMT_CENTER, rt.Width() * 0.15);
	m_ListCtrl.InsertColumn(4, TEXT("날짜"), LVCFMT_CENTER, rt.Width() * 0.2);

    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[101];
    if (DB.db_connect()) {
        MessageBox("DB CONEECT!");

        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            MessageBox("SQL START SELECT");
            sprintf_s((char*)query, 201, "SELECT TITLE, MUSICIAN, COMPOSER, [DATE] FROM SHOW");
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            SQLCHAR title[100];
            SQLCHAR musician[100];
            SQLCHAR composer[100];
            SQLCHAR date[100];

            SQLBindCol(hStmt, 1, SQL_C_CHAR, title, 100, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, musician, 100, NULL);
            SQLBindCol(hStmt, 3, SQL_C_CHAR, composer, 100, NULL);
            SQLBindCol(hStmt, 4, SQL_C_CHAR, date, 100, NULL);

            int num;
            CString str;
            // 공연 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                num = m_ListCtrl.GetItemCount();
                str.Format(_T("%d"), num);
                m_ListCtrl.InsertItem(num, str);
                m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)title, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)musician, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)composer, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 4, LVIF_TEXT, (CString)date, NULL, NULL, NULL, NULL);
            }

            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }
        DB.db_disconnect();
    }
    else {
        MessageBox("공연 정보를 불러오는데 실패했습니다.");
    }

	return TRUE;
}

void CDeleteTab1::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[101];
    CString showno;
    if (DB.db_connect()) {
        MessageBox("DB CONEECT!");

        hDbc = DB.hDbc;
        m_ShowNo.GetWindowText(showno);
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            MessageBox("SQL START SELECT");
            sprintf_s((char*)query, 101, "DELETE FROM SHOW WHERE SHOWNO='%s'", showno);
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
