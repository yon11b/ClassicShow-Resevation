// CustomAll.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CustomAll.h"


// CCustomAll 대화 상자

IMPLEMENT_DYNAMIC(CCustomAll, CDialogEx)

CCustomAll::CCustomAll(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOM_ALL, pParent)
{

}

CCustomAll::~CCustomAll()
{
}

void CCustomAll::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_UserQuery);
}


BEGIN_MESSAGE_MAP(CCustomAll, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCustomAll::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCustomAll 메시지 처리기


void CCustomAll::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString userquery;
    SQLCHAR query[501];
    SQLHDBC hDbc;
    SQLHSTMT hStmt;	// Statement Handle
	m_UserQuery.GetWindowText(userquery);

    if (DB.db_connect())
    {
        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
            sprintf_s((char*)query, 501, userquery);
            SQLExecDirect(hStmt, query, SQL_NTS);
            MessageBox("쿼리가 성공적으로 실행되었습니다!");
        }
        else {
            MessageBox("쿼리에 오류가 있습니다.");
        }
        SQLCloseCursor(hStmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        DB.db_disconnect();
    }
    MessageBox("DB와 연결이 끊어졌습니다.");
}
