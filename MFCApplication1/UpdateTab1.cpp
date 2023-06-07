// UpdateTab1.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "UpdateTab1.h"


// CUpdateTab1 대화 상자
IMPLEMENT_DYNAMIC(CUpdateTab1, CDialogEx)

CUpdateTab1::CUpdateTab1(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_UPDATE_DLG1, pParent)
{

}

CUpdateTab1::~CUpdateTab1()
{
}

void CUpdateTab1::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST2, m_ListCtrl);
    DDX_Control(pDX, IDC_EDIT1, m_edit);
}

BEGIN_MESSAGE_MAP(CUpdateTab1, CDialogEx)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CUpdateTab1::OnNMDblclkList2)
END_MESSAGE_MAP()


// CUpdateTab1 메시지 처리기
BOOL CUpdateTab1::OnInitDialog() {
    CDialogEx::OnInitDialog();

    m_edit.ShowWindow(SW_HIDE);

    // 표 틀 생성
    CRect rt;
    m_ListCtrl.GetWindowRect(&rt);
    m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_ListCtrl.InsertColumn(0, TEXT("번호"), LVCFMT_CENTER, rt.Width() * 0.05);
    m_ListCtrl.InsertColumn(1, TEXT("제목"), LVCFMT_CENTER, rt.Width() * 0.3);
    m_ListCtrl.InsertColumn(2, TEXT("연주자"), LVCFMT_CENTER, rt.Width() * 0.25);
    m_ListCtrl.InsertColumn(3, TEXT("작곡가"), LVCFMT_CENTER, rt.Width() * 0.15);
    m_ListCtrl.InsertColumn(4, TEXT("날짜"), LVCFMT_CENTER, rt.Width() * 0.2);

    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[101];
    if (DB.db_connect()) {

        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            sprintf_s((char*)query, 101, "SELECT SHOWNO, TITLE, MUSICIAN, COMPOSER, [DATE] FROM SHOW");
            SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            SQLCHAR showno[10];
            SQLCHAR title[100];
            SQLCHAR musician[100];
            SQLCHAR composer[100];
            SQLCHAR date[100];

            SQLBindCol(hStmt, 1, SQL_C_CHAR, showno, 10, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, title, 100, NULL);
            SQLBindCol(hStmt, 3, SQL_C_CHAR, musician, 100, NULL);
            SQLBindCol(hStmt, 4, SQL_C_CHAR, composer, 100, NULL);
            SQLBindCol(hStmt, 5, SQL_C_CHAR, date, 100, NULL);

            int num;
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

CString CUpdateTab1::GetColumnName(int columnIndex)
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

void CUpdateTab1::OnNMDblclkList2(NMHDR* pNMHDR, LRESULT* pResult)
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

BOOL CUpdateTab1::PreTranslateMessage(MSG* pMsg)
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
                        showno = _ttoi(primaryKey);
                        sprintf_s((char*)query, 200, "UPDATE SHOW SET %s = '%s' WHERE SHOWNO = %d",
                            columnName, newValue, showno);                        
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