// UpdateTab3.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "UpdateTab3.h"
#include "DBConnect.h"
#include "Session.h"

// CUpdateTab3 대화 상자

IMPLEMENT_DYNAMIC(CUpdateTab3, CDialogEx)

CUpdateTab3::CUpdateTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPDATE_DLG3, pParent)
{

}

CUpdateTab3::~CUpdateTab3()
{
}

void CUpdateTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_BeforePw);
	DDX_Control(pDX, IDC_EDIT2, m_AfterPw);
	DDX_Control(pDX, IDC_EDIT3, m_AccountNo);
	DDX_Control(pDX, IDC_EDIT4, m_AccountPw);
	DDX_Control(pDX, IDC_EDIT6, m_Balance);
}


BEGIN_MESSAGE_MAP(CUpdateTab3, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CUpdateTab3::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUpdateTab3::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUpdateTab3 메시지 처리기


void CUpdateTab3::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString beforepw;
	CString afterpw;	
	SQLHDBC hDbc;
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];

	m_BeforePw.GetWindowText(beforepw);
	m_AfterPw.GetWindowText(afterpw);
	if (SESSION.userPw == beforepw) {
		if (DB.db_connect()) {
			hDbc = DB.hDbc;
			if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
			{
				sprintf_s((char*)query, 101, "UPDATE [USER] SET PW='%s' WHERE ID='%s'", afterpw, SESSION.userId);
				SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
			}
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			DB.db_disconnect();
		}
	}
	else {
		MessageBox("기존 비밀번호가 틀렸습니다!");
	}
}


void CUpdateTab3::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString accountno;
	CString accountpw;
	CString balance;
	SQLHDBC hDbc;
	SQLHSTMT hStmt; // Statement Handle
	SQLCHAR query[101];

	m_AccountNo.GetWindowText(accountno);
	m_AccountPw.GetWindowText(accountpw);
	m_Balance.GetWindowText(balance);
	if (DB.db_connect()) {
		
		hDbc = DB.hDbc;
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 101, "UPDATE CARD SET ACCOUNTNO='%s', CARDPW='%s', BALANCE='%s' WHERE USERID='%s'", accountno, accountpw, balance, SESSION.userId);
			SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
		}
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		DB.db_disconnect();
	}

	else {
		MessageBox("DB연결에 실패했습니다.");
	}
}
