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
    SQLRETURN ret;
	m_UserQuery.GetWindowText(userquery);

    if (DB.db_connect())
    {
        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
            sprintf_s((char*)query, 501, userquery);
            ret=SQLExecDirect(hStmt, query, SQL_NTS);

            if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
                MessageBox("쿼리가 성공적으로 실행되었습니다!");
            }
            else {
                // 에러가 발생한 경우
                CString sqlState;
                CString message;
                SQLINTEGER nativeError;
                SQLSMALLINT messageLength;

                SQLRETURN diagRet;
                SQLSMALLINT i = 1;
                do {
                    diagRet = SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, i, reinterpret_cast<SQLCHAR*>(sqlState.GetBufferSetLength(6)), &nativeError, reinterpret_cast<SQLCHAR*>(message.GetBufferSetLength(SQL_MAX_MESSAGE_LENGTH)), SQL_MAX_MESSAGE_LENGTH, &messageLength);
                    if (diagRet == SQL_SUCCESS || diagRet == SQL_SUCCESS_WITH_INFO) {
                        // 에러 정보를 처리하거나 출력합니다.
                        // sqlState, nativeError, message 등을 사용할 수 있습니다.
                        // 예를 들어, 에러 메시지를 출력하는 경우:
                        AfxMessageBox(_T("SQLSTATE: " + sqlState));
                        //AfxMessageBox(_T("Native Error: ") + (CString)(nativeError));
                        AfxMessageBox(_T("Message: " + message));
                    }
                    i++;
                } while (diagRet == SQL_SUCCESS || diagRet == SQL_SUCCESS_WITH_INFO);
            }

        }
        else {
            MessageBox("쿼리에 오류가 있습니다.");
        }
        SQLCloseCursor(hStmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        DB.db_disconnect();
    }
    else {
        MessageBox("DB와 연결이 끊어졌습니다.");
    }
}
