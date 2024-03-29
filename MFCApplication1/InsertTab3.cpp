﻿// InsertTab3.cpp: 구현 파일
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
    ON_BN_CLICKED(IDC_BTN, &CInsertTab3::OnBnClickedBtn)
END_MESSAGE_MAP()


// CInsertTab3 메시지 처리기
BOOL CInsertTab3::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // 표 틀 생성
    CRect rt;
    m_ListCtrl.GetWindowRect(&rt);
    m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_ListCtrl.InsertColumn(1, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.05);
    m_ListCtrl.InsertColumn(2, TEXT("제목"), LVCFMT_CENTER, rt.Width() * 0.15);
    m_ListCtrl.InsertColumn(3, TEXT("날짜"), LVCFMT_CENTER, rt.Width() * 0.15);
    m_ListCtrl.InsertColumn(4, TEXT("연주자"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(5, TEXT("예매 시작"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(6, TEXT("예매 마감"), LVCFMT_CENTER, rt.Width() * 0.1);
    m_ListCtrl.InsertColumn(7, TEXT("작곡가"), LVCFMT_CENTER, rt.Width() * 0.05);
    m_ListCtrl.InsertColumn(8, TEXT("장르"), LVCFMT_CENTER, rt.Width() * 0.05);
    m_ListCtrl.InsertColumn(9, TEXT("좌석R"), LVCFMT_CENTER, rt.Width() * 0.05);
    m_ListCtrl.InsertColumn(10, TEXT("좌석S"), LVCFMT_CENTER, rt.Width() * 0.05);
    m_ListCtrl.InsertColumn(11, TEXT("좌석A"), LVCFMT_CENTER, rt.Width() * 0.05);
    m_ListCtrl.InsertColumn(12, TEXT("좌석B"), LVCFMT_CENTER, rt.Width() * 0.05);

    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[201];
    if (DB.db_connect()) {
        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 201, "SELECT * FROM SHOW");
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            SQLCHAR showno[100];
            SQLCHAR title[100];
            SQLCHAR date[100];
            SQLCHAR musician[100];
            SQLCHAR reserve_starttime[100];
            SQLCHAR reserve_endtime[100];
            SQLCHAR composer[100];
            SQLCHAR genre[100];
            SQLCHAR pricer[100];
            SQLCHAR prices[100];
            SQLCHAR pricea[100];
            SQLCHAR priceb[100];

            SQLBindCol(hStmt, 1, SQL_C_CHAR, showno, 100, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, title, 100, NULL);
            SQLBindCol(hStmt, 3, SQL_C_CHAR, date, 100, NULL);
            SQLBindCol(hStmt, 4, SQL_C_CHAR, musician, 100, NULL);
            SQLBindCol(hStmt, 5, SQL_C_CHAR, reserve_starttime, 100, NULL);
            SQLBindCol(hStmt, 6, SQL_C_CHAR, reserve_endtime, 100, NULL);
            SQLBindCol(hStmt, 7, SQL_C_CHAR, composer, 100, NULL);
            SQLBindCol(hStmt, 8, SQL_C_CHAR, genre, 100, NULL);
            SQLBindCol(hStmt, 9, SQL_C_CHAR, pricer, 100, NULL);
            SQLBindCol(hStmt, 10, SQL_C_CHAR, prices, 100, NULL);
            SQLBindCol(hStmt, 11, SQL_C_CHAR, pricea, 100, NULL);
            SQLBindCol(hStmt, 12, SQL_C_CHAR, priceb, 100, NULL);

            int num;
            CString str;
            // 공연 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                num = m_ListCtrl.GetItemCount();
                str.Format(_T("%d"), num);
                m_ListCtrl.InsertItem(num, (CString)showno);
                m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)title, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)date, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)musician, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 4, LVIF_TEXT, (CString)reserve_starttime, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 5, LVIF_TEXT, (CString)reserve_endtime, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 6, LVIF_TEXT, (CString)composer, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 7, LVIF_TEXT, (CString)genre, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 8, LVIF_TEXT, (CString)pricer, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 9, LVIF_TEXT, (CString)prices, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 10, LVIF_TEXT, (CString)pricea, NULL, NULL, NULL, NULL);
                m_ListCtrl.SetItem(num, 11, LVIF_TEXT, (CString)priceb, NULL, NULL, NULL, NULL);
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

void CInsertTab3::OnBnClickedBtn()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString showno;
    SQLHDBC hDbc;
    SQLHSTMT hStmt1; // Statement Handle
    SQLHSTMT hStmt2; // Statement Handle
    SQLCHAR query[401];
    int isValidDate = 0;

    m_ShowNo.GetWindowText(showno);
    if (DB.db_connect()) {
        hDbc = DB.hDbc;
        int count;
        // 예매 가능 날짜 확인
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt1) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 401, "SELECT COUNT(*) FROM SHOW WHERE SHOWNO = '%s' AND GETDATE() >= RESERVE_STARTTIME AND RESERVE_ENDTIME >= GETDATE()", showno);
            SQLExecDirect(hStmt1, (SQLCHAR*)query, SQL_NTS);
            SQLRETURN ret1 = SQLFetch(hStmt1);
            if (ret1 == SQL_SUCCESS || ret1 == SQL_SUCCESS_WITH_INFO) {
                SQLGetData(hStmt1, 1, SQL_C_LONG, &count, sizeof(count), NULL);
                CString cnt;
                cnt.Format(_T("%d"), count);
                if (count == 1) {
                    // COUNT(*) 값이 1인 경우(valid date)
                    isValidDate = 1;             
                }
                else {
                    // COUNT(*) 값이 1인 아닌 경우(예매 가능 기간이 아님)
                    MessageBox("예매 기간이 아닙니다.");
                }
            }
            else {
                MessageBox("예매 기간이 아닙니다.");
            }
            SQLCloseCursor(hStmt1);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt1);
        }


        // 좌석 선택 창으로 이동
        if (isValidDate && SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt2) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 301, "SELECT C.HALLNO, C.HALLNAME FROM CONCERTHALL C WHERE C.HALLNO = (SELECT S.HALLNO FROM SHOW S WHERE S.SHOWNO = '%s')", showno);
            SQLExecDirect(hStmt2, (SQLCHAR*)query, SQL_NTS);

            SQLCHAR hallname[100];
            SQLCHAR hallno[10];
            //SQLBindCol(hStmt, 1, SQL_C_CHAR, hallname, 100, NULL);
            SQLRETURN ret2 = SQLFetch(hStmt2);
            ret2 = SQLGetData(hStmt2, 1, SQL_C_CHAR, hallno, 10, NULL);
            ret2 = SQLGetData(hStmt2, 2, SQL_C_CHAR, hallname, 100, NULL);
    
            if (ret2 == SQL_SUCCESS || ret2 == SQL_SUCCESS_WITH_INFO) {
                // DB 연결 해제
                SQLCloseCursor(hStmt2);
                SQLFreeHandle(SQL_HANDLE_STMT, hStmt2);
                DB.db_disconnect();
                
                // 해당 공연장으로 이동
                CString str_hallname = (CString)hallname;
                CString str_concertno= (CString)hallno;
                if (str_hallname == "예술의 전당") {
                    CSeatSacDlg SeatSac(showno, str_concertno);
                    SeatSac.DoModal();
                }
                else if (str_hallname == "잠실 롯데") {
                    //CSeatLotteDlg SeatLotteDlg(showno, str_concertno);
                    //SeatLotteDlg.DoModal();
                    CSeatSacDlg SeatSac(showno, str_concertno);
                    SeatSac.DoModal();
                }
                else { // "세종문화회관"
                    //SeatSejongDlg.DoModal();
                    CSeatSacDlg SeatSac(showno, str_concertno);
                    SeatSac.DoModal();
                }
            }
            else {
                MessageBox("값이 존재하지 않습니다.");
            }
        }
    }
    else {
        MessageBox("DB 연결에 실패했습니다.");
    }
}