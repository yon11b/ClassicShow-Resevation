// CustomDlg2.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CustomDlg2.h"
#include "DBConnect.h"


// CCustomDlg2 대화 상자

IMPLEMENT_DYNAMIC(CCustomDlg2, CDialogEx)

CCustomDlg2::CCustomDlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOM_DLG2, pParent)
{

}

CCustomDlg2::~CCustomDlg2()
{
}

void CCustomDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCustomDlg2, CDialogEx)
END_MESSAGE_MAP()


// CCustomDlg2 메시지 처리기

BOOL CCustomDlg2::OnInitDialog()
{
	CDialogEx::OnInitDialog();
    SQLHDBC hDbc;
    SQLHSTMT hStmt;	// Statement Handle
    SQLCHAR query[301];
    SQLCHAR showNo[100];
    SQLCHAR titleList[100];
    CString showinfo;
    userid = SESSION.userId;

    if (DB.db_connect())
    {
        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
            sprintf_s((char*)query, 301, "SELECT DISTINCT S.SHOWNO, S.TITLE FROM RESERVATE R, SHOW S WHERE R.USERID='%s' AND R.SHOWNO=S.SHOWNO", userid);
            // MessageBox((LPCTSTR)query); // Debugging code
            SQLExecDirect(hStmt, query, SQL_NTS);
            SQLBindCol(hStmt, 1, SQL_C_CHAR, showNo, 100, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, titleList, 100, NULL);
            // 공연 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                showinfo = (CString)showNo + ". " + (CString)titleList;
                m_Show.AddString(showinfo);
            }
        }
        SQLCloseCursor(hStmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        DB.db_disconnect();
	return TRUE;
}
