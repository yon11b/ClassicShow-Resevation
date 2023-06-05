// Tab4.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "Tab4.h"
#include "DBConnect.h"


// CTab4 대화 상자
IMPLEMENT_DYNAMIC(CTab4, CDialogEx)

CTab4::CTab4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

CTab4::~CTab4()
{
}

void CTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_ShowNo);
}

BEGIN_MESSAGE_MAP(CTab4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTab4::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTab4 메시지 처리기
BOOL CTab4::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // 표 틀 생성
    CRect rt;
    m_ListCtrl.GetWindowRect(&rt);
    m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_ListCtrl.InsertColumn(0, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.4);
    m_ListCtrl.InsertColumn(1, TEXT("사용자 아이디"), LVCFMT_CENTER, rt.Width() * 0.6);
    return TRUE;
}

void CTab4::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString showno;
	m_ShowNo.GetWindowText(showno);
	
    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[201];
    CString score;
    CString seat;

    m_ListCtrl.DeleteAllItems();
    if (DB.db_connect()) {
        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 201, "SELECT USERID FROM RESERVATE WHERE SHOWNO = '%s'", showno);
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
            SQLCHAR userid[50];
            CString str;

            SQLBindCol(hStmt, 1, SQL_C_CHAR, userid, 50, NULL);
            int num;
            // 공연 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                num = m_ListCtrl.GetItemCount();
                str.Format(_T("%d"), num);
                m_ListCtrl.InsertItem(num, str);
                m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)userid, NULL, NULL, NULL, NULL);
            }
            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }
        DB.db_disconnect();
    }
    else {
        MessageBox("사용자 정보를 불러오는데 실패했습니다.");
    }
}