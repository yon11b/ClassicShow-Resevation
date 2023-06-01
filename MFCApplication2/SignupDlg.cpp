// SignupDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SignupDlg.h"
#include <sql.h>
#include <sqlext.h>


// CSignupDlg 대화 상자

IMPLEMENT_DYNAMIC(CSignupDlg, CDialog)

CSignupDlg::CSignupDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SIGNUP, pParent)
{
}

CSignupDlg::~CSignupDlg()
{
}


void CSignupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_USER_NAME, m_UserName);
    DDX_Control(pDX, IDC_USER_ID, m_UserId);
    DDX_Control(pDX, IDC_USER_PW, m_UserPw);
    DDX_Control(pDX, IDC_CARD_NO, m_CardNo);
    DDX_Control(pDX, IDC_CARD_PW, m_CardPw);
    DDX_Control(pDX, IDC_CARD_BAL, m_CardBal);
}


BEGIN_MESSAGE_MAP(CSignupDlg, CDialog)
	ON_BN_CLICKED(IDC_SUBMIT, &CSignupDlg::OnBnClickedSubmit)
    ON_BN_CLICKED(IDC_EXIT, &CSignupDlg::OnBnClickedExit)
END_MESSAGE_MAP()


// CSignupDlg 메시지 처리기

void CSignupDlg::OnBnClickedSubmit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    SQLHDBC hDbc;
    CString cardno;
    CString userid;
    CString userpw;
    CString username;
    CString cardbal;
    CString cardpw;

    SQLHSTMT hStmt;	// Statement Handle
    SQLCHAR query[101];

    m_UserName.GetWindowText(username);
    m_UserId.GetWindowText(userid);
    m_UserPw.GetWindowText(userpw);
    m_CardNo.GetWindowText(cardno);
    m_CardPw.GetWindowText(cardpw);
    m_CardBal.GetWindowText(cardbal);

    hDbc = DB.hDbc;
    if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
    {
        MessageBox("SQL START INSERT");
        MessageBox(userid);
        MessageBox(userpw);
        MessageBox(username);
        MessageBox(cardno);
        MessageBox(cardbal);
        MessageBox(cardpw);

        sprintf_s((char*)query, 101, "INSERT INTO [USER] VALUES('%s','%s','%s')", userid, userpw, username);
        SQLExecDirect(hStmt, query, SQL_NTS);

        sprintf_s((char*)query, 101, "INSERT INTO CARD VALUES('%s','%s',%d, '%s')", cardno, userid, _ttoi(cardbal), cardpw);
        SQLExecDirect(hStmt, query, SQL_NTS);

        SQLCloseCursor(hStmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }
}

void CSignupDlg::OnBnClickedExit()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    CDialog::OnCancel();
}
