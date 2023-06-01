// InsertTab3.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "InsertTab3.h"
#include "DBConnect.h"
#include "SeatSacDlg.h"
#include "SeatLotteDlg.h"
#include "SeatSejongDlg.h"

// CInsertTab3 대화 상자

IMPLEMENT_DYNAMIC(CInsertTab3, CDialogEx)

CInsertTab3::CInsertTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSERT_DLG3, pParent)
{

}

CInsertTab3::~CInsertTab3()
{
}

void CInsertTab3::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_SHOW, m_ListCtrl);
    DDX_Control(pDX, IDC_EDIT1, m_ShowNo);
}


BEGIN_MESSAGE_MAP(CInsertTab3, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CInsertTab3::OnEnChangeEdit1)
    ON_BN_CLICKED(IDC_BTN, &CInsertTab3::OnBnClickedBtn)
END_MESSAGE_MAP()


// CInsertTab3 메시지 처리기
BOOL CInsertTab3::OnInitDialog() {
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
    SQLCHAR query[201];
    if (DB.db_connect()) {
        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 201, "SELECT SHOWNO, TITLE, MUSICIAN, COMPOSER, [DATE] FROM SHOW");
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            SQLCHAR showno[30];
            SQLCHAR title[100];
            SQLCHAR musician[100];
            SQLCHAR composer[100];
            SQLCHAR date[100];

            SQLBindCol(hStmt, 1, SQL_C_CHAR, showno, 30, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, title, 100, NULL);
            SQLBindCol(hStmt, 3, SQL_C_CHAR, musician, 100, NULL);
            SQLBindCol(hStmt, 4, SQL_C_CHAR, composer, 100, NULL);
            SQLBindCol(hStmt, 5, SQL_C_CHAR, date, 100, NULL);
            int num;
            CString str;
            // 공연 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                num = m_ListCtrl.GetItemCount();
                m_ListCtrl.InsertItem(num, (CString)showno);
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


void CInsertTab3::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CInsertTab3::OnBnClickedBtn()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString showno;
    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[301];

    m_ShowNo.GetWindowText(showno);
    int ishowno = _ttoi(showno);
    SESSION.showNo = ishowno;
    if (DB.db_connect()) {
        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 301, "SELECT C.HALLNAME FROM CONCERTHALL C WHERE C.HALLNO = (SELECT S.HALLNO FROM SHOW S WHERE S.SHOWNO = %d)", ishowno);
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            SQLCHAR hallname[100];
            //SQLBindCol(hStmt, 1, SQL_C_CHAR, hallname, 100, NULL);
            SQLRETURN ret = SQLFetch(hStmt);
            ret = SQLGetData(hStmt, 1, SQL_C_CHAR, hallname, 100, NULL);

            if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
                MessageBox("값이 존재합니다.");
                CString hall = (CString)hallname;
                MessageBox(hall);
                if (hall == "예술의 전당") {
                    MessageBox("11111");
                    SeatSacDlg.DoModal();
                }
                else if (hall == "잠실 롯데") {
                    MessageBox("22222");
                    SeatLotteDlg.DoModal();
                }
                else { // "세종문화회관"
                    MessageBox("333333");
                    SeatSejongDlg.DoModal();
                }
            }
            else {
                MessageBox("값이 존재하지 않습니다.");
            }
            SQLCloseCursor(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        }
        DB.db_disconnect();
    }
    else {
        MessageBox("공연 정보를 불러오는데 실패했습니다.");
    }
}
