// UpdateTab2.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "UpdateTab2.h"


// CUpdateTab2 대화 상자

IMPLEMENT_DYNAMIC(CUpdateTab2, CDialogEx)

CUpdateTab2::CUpdateTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPDATE_DLG2, pParent)
{

}

CUpdateTab2::~CUpdateTab2()
{
}

void CUpdateTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CUpdateTab2, CDialogEx)

END_MESSAGE_MAP()


// CUpdateTab2 메시지 처리기
BOOL CUpdateTab2::OnInitDialog() {
	CDialogEx::OnInitDialog();

	m_ListCtrl.DeleteAllItems();
	// 표 틀 생성
	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrl.InsertColumn(0, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(1, TEXT("제목"), LVCFMT_CENTER, rt.Width() * 0.4);
	m_ListCtrl.InsertColumn(2, TEXT("공연장"), LVCFMT_CENTER, rt.Width() * 0.1);
	m_ListCtrl.InsertColumn(3, TEXT("홀"), LVCFMT_CENTER, rt.Width() * 0.1);
	m_ListCtrl.InsertColumn(4, TEXT("좌석"), LVCFMT_CENTER, rt.Width() * 0.2);
	m_ListCtrl.InsertColumn(5, TEXT("시야"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(6, TEXT("소리"), LVCFMT_CENTER, rt.Width() * 0.05);
	m_ListCtrl.InsertColumn(7, TEXT("좌석총평"), LVCFMT_CENTER, rt.Width() * 0.05);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SQLHDBC hDbc;
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[201];
	CString score;
	CString seat;

	if (DB.db_connect()) {
		hDbc = DB.hDbc;
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 201, "SELECT DETAIL, HALLNAME, ROOMNAME, SEATNUM, SOUND, [VIEW], TOTAL FROM REVIEW R, CONCERTHALL C WHERE R.HALLNUM = C.HALLNO AND R.TOTAL >= '%s'", score);
			SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
			CString str;
			SQLCHAR title[100];
			SQLCHAR hallname[100];
			SQLCHAR roomname[100];
			SQLCHAR seatnum[30];
			SQLCHAR sound[30];
			SQLCHAR view[30];
			SQLCHAR total[30];

			SQLBindCol(hStmt, 1, SQL_C_CHAR, title, 100, NULL);
			SQLBindCol(hStmt, 2, SQL_C_CHAR, hallname, 100, NULL);
			SQLBindCol(hStmt, 3, SQL_C_CHAR, roomname, 100, NULL);
			SQLBindCol(hStmt, 4, SQL_C_CHAR, seatnum, 30, NULL);
			SQLBindCol(hStmt, 5, SQL_C_CHAR, sound, 30, NULL);
			SQLBindCol(hStmt, 6, SQL_C_CHAR, view, 30, NULL);
			SQLBindCol(hStmt, 7, SQL_C_CHAR, total, 30, NULL);

			int num;
			// 공연 데이터 나열
			while (SQLFetch(hStmt) != SQL_NO_DATA)
			{
				num = m_ListCtrl.GetItemCount();
				str.Format(_T("%d"), num);
				m_ListCtrl.InsertItem(num, str);
				m_ListCtrl.SetItem(num, 1, LVIF_TEXT, (CString)title, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 2, LVIF_TEXT, (CString)hallname, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 3, LVIF_TEXT, (CString)roomname, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 4, LVIF_TEXT, (CString)seatnum, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 5, LVIF_TEXT, (CString)sound, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 6, LVIF_TEXT, (CString)view, NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(num, 7, LVIF_TEXT, (CString)total, NULL, NULL, NULL, NULL);
			}
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}
		DB.db_disconnect();
	}
	else {
		MessageBox("리뷰 정보를 불러오는데 실패했습니다.");
	}

	return TRUE;
}
CString CUpdateTab2::GetColumnName(int columnIndex)
{
	CString columnName;

	switch (columnIndex)
	{
	case 0:
		columnName = _T("ID");
		break;
	case 1:
		columnName = _T("TITLE");
		break;
	case 2:
		columnName = _T("MUSICIAN");
		break;
	case 3:
		columnName = _T("COMPOSER");
		break;
	case 4:
		columnName = _T("DATE");
		break;
	default:
		break;
	}
	return columnName;
}

void CUpdateTab2::OnNMDblclkList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	iSavedItem = pNMItemActivate->iItem;
	iSavedSubitem = pNMItemActivate->iSubItem;

	if (pNMItemActivate->iItem != -1)
	{
		CRect rect;

		if (pNMItemActivate->iSubItem == 0)
		{
			m_ListCtrl.GetItemRect(pNMItemActivate->iItem, rect, LVIR_BOUNDS);
			rect.right = rect.left + m_ListCtrl.GetColumnWidth(0);
		}
		else
		{
			m_ListCtrl.GetSubItemRect(pNMItemActivate->iItem, pNMItemActivate->iSubItem, LVIR_BOUNDS, rect);
		}
		m_ListCtrl.ClientToScreen(rect);
		this->ScreenToClient(rect);
		GetDlgItem(IDC_EDIT1)->SetWindowText(m_ListCtrl.GetItemText(pNMItemActivate->iItem, pNMItemActivate->iSubItem));
		GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
		GetDlgItem(IDC_EDIT1)->SetFocus();
	}
	*pResult = 0;
}

BOOL CUpdateTab2::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RETURN) {
			if (pMsg->hwnd == GetDlgItem(IDC_EDIT1)->GetSafeHwnd())
			{
				CString str;
				GetDlgItemText(IDC_EDIT1, str);
				m_ListCtrl.SetItemText(iSavedItem, iSavedSubitem, str);

				// 수정된 값을 데이터베이스에 반영
				CString columnName = GetColumnName(iSavedSubitem); // 열 이름 가져오기
				CString newValue = str; // 새로운 값
				CString primaryKey = m_ListCtrl.GetItemText(iSavedItem, 0); // 선택된 항목의 기본 키 값 (ID)

				// TODO: 데이터베이스 업데이트 쿼리 실행
				// 예시: UPDATE 문을 사용하여 업데이트 쿼리 실행
				SQLHDBC hDbc;
				SQLHSTMT hStmt;
				SQLCHAR query[200];
				int showno;

				if (DB.db_connect())
				{
					hDbc = DB.hDbc;
					if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
					{
						showno = _ttoi(primaryKey) + 1;
						sprintf_s((char*)query, 200, "UPDATE SHOW SET %s = '%s' WHERE SHOWNO = %d",
							columnName, newValue, showno);
						MessageBox((char*)query);
						if (SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS) == SQL_SUCCESS)
						{
							MessageBox(_T("데이터베이스 업데이트 성공"));
						}
						else
						{
							MessageBox(_T("데이터베이스 업데이트 실패"));
						}
						SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
					}
					DB.db_disconnect();
				}
				else
				{
					MessageBox(_T("데이터베이스 연결 실패"));
				}
				GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
			}
			return TRUE;
		}

		if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

