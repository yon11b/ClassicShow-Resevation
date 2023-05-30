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
}


BEGIN_MESSAGE_MAP(CUpdateTab1, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CUpdateTab1::OnBnClickedButton1)
    ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST2, &CUpdateTab1::OnLvnEndlabeleditList2)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CUpdateTab1::OnLvnItemchangedList2)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CUpdateTab1::OnNMDblclkList2)
END_MESSAGE_MAP()


// CUpdateTab1 메시지 처리기

BOOL CUpdateTab1::OnInitDialog() {
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
    
    return TRUE;
}

void CUpdateTab1::OnBnClickedButton1()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    SQLHDBC hDbc;
    SQLHSTMT hStmt; // Statement Handle
    SQLCHAR query[101];
    if (DB.db_connect()) {
        MessageBox("DB CONEECT!");

        hDbc = DB.hDbc;
        if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
        {
            MessageBox("SQL START SELECT");
            sprintf_s((char*)query, 101, "SELECT TITLE, MUSICIAN, COMPOSER, [DATE] FROM SHOW");
                SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);

            SQLCHAR title[100];
            SQLCHAR musician[100];
            SQLCHAR composer[100];
            SQLCHAR date[100];

            SQLBindCol(hStmt, 1, SQL_C_CHAR, title, 100, NULL);
            SQLBindCol(hStmt, 2, SQL_C_CHAR, musician, 100, NULL);
            SQLBindCol(hStmt, 3, SQL_C_CHAR, composer, 100, NULL);
            SQLBindCol(hStmt, 4, SQL_C_CHAR, date, 100, NULL);

            int num;
            CString str;
            // 공연 데이터 나열
            while (SQLFetch(hStmt) != SQL_NO_DATA)
            {
                num = m_ListCtrl.GetItemCount();
                str.Format(_T("%d"), num);
                m_ListCtrl.InsertItem(num, str);
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
}

void CUpdateTab1::OnLvnEndlabeleditList2(NMHDR* pNMHDR, LRESULT* pResult)
{
    NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


    *pResult = 0;
}

void CUpdateTab1::OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    *pResult = 0;
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
    // TODO: Add your specialized code here and/or call the base class
    if (pMsg->message == WM_KEYDOWN) {
        if (pMsg->wParam == VK_RETURN) {

            if (pMsg->hwnd == GetDlgItem(IDC_EDIT1)->GetSafeHwnd())
            {
                CString str;
                GetDlgItemText(IDC_EDIT1, str);
                m_ListCtrl.SetItemText(iSavedItem, iSavedSubitem, str);

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
