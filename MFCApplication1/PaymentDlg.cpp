// CPaymentDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "PaymentDlg.h"
#include "SeatSacDlg.h"
#include "DBConnect.h"


// CPaymentDlg 대화 상자

IMPLEMENT_DYNAMIC(CPaymentDlg, CDialogEx)

CPaymentDlg::CPaymentDlg(CString pShowno, CString pSeatno, CString pHallno, CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_PAYMENT, pParent)
    , ckshowno(pShowno)
    , ckseatno(pSeatno)
    , ckhallno(pHallno)
{

}

CPaymentDlg::~CPaymentDlg()
{
}

void CPaymentDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CK_SEATINFO, m_ChSeatInfo);
    DDX_Control(pDX, IDC_EDIT1, m_InputPw);
}


BEGIN_MESSAGE_MAP(CPaymentDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CPaymentDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CPaymentDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPaymentDlg 메시지 처리기
BOOL CPaymentDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();

    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[201];
    CString seatinfo;
    userid = SESSION.userId;

    if (DB.db_connect()) {
        MessageBox("DB CONEECT!");

        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 201, "SELECT SECTION, [ROW], [COLUMN], PRICE_R, PRICE_S, PRICE_A, PRICE_B FROM SEAT, SHOW WHERE SEATNO = '%s' AND seat.HALLNO='%s' AND SHOWNO='%s'", ckseatno, ckhallno, ckshowno);
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            SQLCHAR section[30];
            SQLCHAR row[10];
            SQLCHAR column[10];
            SQLCHAR price_r[100];
            SQLCHAR price_s[100];
            SQLCHAR price_a[100];
            SQLCHAR price_b[100];

            SQLRETURN ret = SQLFetch(hStmt);

            ret = SQLGetData(hStmt, 1, SQL_C_CHAR, section, 30, NULL);
            ret = SQLGetData(hStmt, 2, SQL_C_CHAR, row, 10, NULL);
            ret = SQLGetData(hStmt, 3, SQL_C_CHAR, column, 10, NULL);
            ret = SQLGetData(hStmt, 4, SQL_C_CHAR, price_r, 100, NULL);
            ret = SQLGetData(hStmt, 5, SQL_C_CHAR, price_s, 100, NULL);
            ret = SQLGetData(hStmt, 6, SQL_C_CHAR, price_a, 100, NULL);
            ret = SQLGetData(hStmt, 7, SQL_C_CHAR, price_b, 100, NULL);
            if ((CString)section == "R"){
                ckprice = (CString)price_r;
            }
            else if ((CString)section == "S") {
                ckprice = (CString)price_s;
            }
            else if ((CString)section == "A") {
                ckprice = (CString)price_a;
            }
            else if ((CString)section == "B") {
                ckprice = (CString)price_b;
            }
            seatinfo = (CString)section + "구역" + (CString)row + "열" + (CString)column + "번째 "+"금액: "+ ckprice;
            MessageBox((CString)section);
            MessageBox(seatinfo);

            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }
        DB.db_disconnect();
    }
    else {
        MessageBox("공연 정보를 불러오는데 실패했습니다.");
    }
    m_ChSeatInfo.SetWindowText(seatinfo);
	return TRUE;
}

// 카드 비밀번호 검증
void CPaymentDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString inputpw;
    CString userpw = SESSION.userPw;
    m_InputPw.GetWindowText(inputpw);
    
    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[101];
    SQLINTEGER count;

    if (DB.db_connect()) {
        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 101, "SELECT COUNT(*) FROM CARD C, [USER] U WHERE U.ID = '%s' U.ID=C.USERID AND C.CARDPW='%s'", userid, inputpw);
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
            MessageBox((char*)query);

            SQLRETURN ret = SQLFetch(hStmt);

            if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
                SQLGetData(hStmt, 1, SQL_C_LONG, &count, sizeof(count), NULL);
                CString message;
                message.Format(_T("%d"), count);

                MessageBox(message);
                if (count==1) {
                    MessageBox("비밀번호 확인 완료");
                }
                else {
                    MessageBox("비밀번호가 일치하지 않습니다.");
                }
            }
            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            DB.db_disconnect();
        }
        else {
            MessageBox("데이터베이스와 연결이 되지 않았습니다.");
        }
    }
}


void CPaymentDlg::OnBnClickedButton2()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query1[201];
    SQLCHAR query2[201];
    if (DB.db_connect()) {
        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            sprintf_s((char*)query1, 201, "INSERT INTO RESERVATE(USERID, SHOWNO, SEATNO, HALLNO, PAYMENT) VALUES('%s','%s','%s','%s','%s')", userid, ckshowno, ckseatno, ckhallno, ckprice);
            SQLExecDirect(hStmt, (SQLCHAR*)query1, SQL_NTS);

            sprintf_s((char*)query2, 201, "UPDATE CARD SET BALANCE=BALANCE-'%s' WHERE USERID='%s'", ckprice, userid);
            SQLExecDirect(hStmt, (SQLCHAR*)query2, SQL_NTS);

            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            DB.db_disconnect();
            MessageBox("예매가 완료되었습니다.");
        }
        else {
            MessageBox("예매가 비정상적으로 종료되었습니다.");
        }
    }
}
