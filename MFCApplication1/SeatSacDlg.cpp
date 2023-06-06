// SeatSacDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SeatSacDlg.h"
#include "Resource.h"
#include "DBConnect.h"
#include "PaymentDlg.h"


// CSeatSacDlg 대화 상자

IMPLEMENT_DYNAMIC(CSeatSacDlg, CDialogEx)

CSeatSacDlg::CSeatSacDlg(CString pShowno, CString pHallno, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEAT_SAC_CONCERT, pParent)
	, showno(pShowno)
	, hallno(pHallno)
{

}

CSeatSacDlg::~CSeatSacDlg()
{
}

void CSeatSacDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_SeatNo);
}

BEGIN_MESSAGE_MAP(CSeatSacDlg, CDialogEx)
	ON_WM_DRAWITEM()
	ON_COMMAND_RANGE(IDC_SAC_1, IDC_SAC_148, &CSeatSacDlg::OnBtnClick)
	ON_BN_CLICKED(IDC_BUTTON1, &CSeatSacDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSeatSacDlg 메시지 처리기
BOOL CSeatSacDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	return TRUE;
}

void CSeatSacDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{	
	
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//if (nIDCtl == IDC_BUTTON1)
	int r, g, b;
	if (1252 <= nIDCtl && nIDCtl <= 1283) {
		r = 255;
		g = 000;
		b = 051;
	}
	else if (1284 <= nIDCtl && nIDCtl <= 1323) {
		r = 255;
		g = 255;
		b = 000;
	}
	else if (1324 <= nIDCtl && nIDCtl <= 1349) {
		r = 102;
		g = 255;
		b = 000;
	}
	else if (1350 <= nIDCtl && nIDCtl <= 1399) {
		r = 00;
		g = 102;
		b = 255;
	}
	CDC dc;
	RECT rect;

	dc.Attach(lpDrawItemStruct->hDC);
	rect = lpDrawItemStruct->rcItem;	
	dc.Draw3dRect(&rect, RGB(200, 200, 200), RGB(20, 20, 20));
	dc.FillSolidRect(&rect, RGB(r, g, b));
	UINT state = lpDrawItemStruct->itemState;
	if ((state & ODS_SELECTED))
	{
		dc.DrawEdge(&rect, EDGE_SUNKEN, BF_RECT);
	}
	else
	{
		dc.DrawEdge(&rect, EDGE_RAISED, BF_RECT);
	}
	//dc.SetBkColor(RGB(r, g, b));
	TCHAR buffer[MAX_PATH];

	ZeroMemory(buffer, MAX_PATH);
	::GetWindowText(lpDrawItemStruct->hwndItem, buffer, MAX_PATH);
	dc.DrawText(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc.Detach();		
	
}

void CSeatSacDlg::OnBtnClick(UINT ullD)
{
	
	SQLHDBC hDbc;
	SQLHSTMT hStmt; // Statement Handle
	SQLCHAR query[201];
	if (DB.db_connect()) {
		hDbc = DB.hDbc;
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 201, "SELECT PRICE_R, PRICE_S, PRICE_A, PRICE_B FROM SHOW WHERE SHOWNO = '%s'", showno);
			SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

			SQLCHAR price_r[100];
			SQLCHAR price_s[100];
			SQLCHAR price_a[100];
			SQLCHAR price_b[100];
			SQLRETURN ret = SQLFetch(hStmt);

			int iseatno = (int)ullD - 1251;
			seatno.Format(_T("%d"), iseatno);

			ret = SQLGetData(hStmt, 1, SQL_C_CHAR, price_r, 100, NULL);
			ret = SQLGetData(hStmt, 2, SQL_C_CHAR, price_s, 100, NULL);
			ret = SQLGetData(hStmt, 3, SQL_C_CHAR, price_a, 100, NULL);
			ret = SQLGetData(hStmt, 4, SQL_C_CHAR, price_b, 100, NULL);

			if (1252 <= ullD && ullD <= 1283) {
				seatinfo="좌석번호: "+ seatno + " / 가격 :"+(CString)price_r;
			}
			else if (1284 <= ullD && ullD <= 1323) {
				seatinfo = "좌석번호: " + seatno + " / 가격 :" + (CString)price_s;
			}
			else if (1324 <= ullD && ullD <= 1349) {
				seatinfo = "좌석번호: " + seatno + " / 가격 :" + (CString)price_a;
			}
			else if (1350 <= ullD && ullD <= 1399) {
				seatinfo = "좌석번호: " + seatno + " / 가격 :" + (CString)price_b;
			}
			MessageBox(seatinfo);
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}
		DB.db_disconnect();
	}
	else {
		MessageBox("공연 정보를 불러오는데 실패했습니다.");
	}
}

void CSeatSacDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_SeatNo.GetWindowText(seatno);
	int isSeat;

	// 이미 예매된 좌석인지 검증하기
	SQLHDBC hDbc;
	SQLHSTMT hStmt1; // Statement Handle
	SQLHSTMT hStmt2; // Statement Handle
	SQLCHAR query[201];
	SQLINTEGER count;

	isSeat = 0;

	if (DB.db_connect()) {
		hDbc = DB.hDbc;

		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt1) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 201, "SELECT COUNT(*) FROM SEAT WHERE SEATNO='%s'AND HALLNO='%s'", seatno, hallno);
			SQLExecDirect(hStmt1, (SQLCHAR*)query, SQL_NTS);
			SQLRETURN ret = SQLFetch(hStmt1);

			if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
				SQLGetData(hStmt1, 1, SQL_C_LONG, &count, sizeof(count), NULL);
				if (count == 0) {
					MessageBox("존재하지 않는 좌석입니다");
					isSeat = 0;
				}
				else {
					isSeat = 1;
				}
			}
			else {
				MessageBox("존재하지 않는 좌석입니다");
				isSeat = 0;
			}

			SQLCloseCursor(hStmt1);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt1);
		}

		if (isSeat && SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt2) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 201, "SELECT COUNT(*) FROM RESERVATE WHERE SHOWNO='%s'AND SEATNO='%s'AND HALLNO='%s'", showno, seatno, hallno);
			SQLExecDirect(hStmt2, (SQLCHAR*)query, SQL_NTS);
			SQLRETURN ret = SQLFetch(hStmt2);

			if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
				SQLGetData(hStmt2, 1, SQL_C_LONG, &count, sizeof(count), NULL);
				if (count == 0) {
					// 결제 페이지로 넘어가기
					CPaymentDlg PaymentDlg(showno, seatno, hallno);
					PaymentDlg.DoModal();
				}
				else {
					MessageBox("이미 예매된 좌석입니다.");
				}
			}
			else {
				MessageBox("예기치 못한 오류가 발생했습니다.");
			}
			SQLCloseCursor(hStmt2);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt2);
		}
		else {
			MessageBox("공연 예매에 실패했습니다.");
		}
	}
	DB.db_disconnect();
}