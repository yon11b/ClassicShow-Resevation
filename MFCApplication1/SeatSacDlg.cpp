// SeatSacDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SeatSacDlg.h"


// CSeatSacDlg 대화 상자

IMPLEMENT_DYNAMIC(CSeatSacDlg, CDialogEx)

CSeatSacDlg::CSeatSacDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEAT_SAC_CONCERT, pParent)
{

}

CSeatSacDlg::~CSeatSacDlg()
{
}

void CSeatSacDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_Seat1);
}


BEGIN_MESSAGE_MAP(CSeatSacDlg, CDialogEx)
	ON_WM_DRAWITEM()
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
	if (nIDCtl == IDC_BUTTON1)
	{
		CDC dc;
		RECT rect;

		dc.Attach(lpDrawItemStruct->hDC);
		rect = lpDrawItemStruct->rcItem;	
		dc.Draw3dRect(&rect, RGB(200, 200, 200), RGB(20, 20, 20));
		dc.FillSolidRect(&rect, RGB(100, 150, 100));
		UINT state = lpDrawItemStruct->itemState;
		if ((state & ODS_SELECTED))
		{
			dc.DrawEdge(&rect, EDGE_SUNKEN, BF_RECT);
		}
		else
		{
			dc.DrawEdge(&rect, EDGE_RAISED, BF_RECT);
		}
		dc.SetBkColor(RGB(100, 150, 100));
		dc.SetTextColor(RGB(255, 100, 0));
		TCHAR buffer[MAX_PATH];

		ZeroMemory(buffer, MAX_PATH);
		::GetWindowText(lpDrawItemStruct->hwndItem, buffer, MAX_PATH);
		dc.DrawText(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		dc.Detach();		
	}
}

void CSeatSacDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
