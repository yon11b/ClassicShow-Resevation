// CustomDlg3.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CustomDlg3.h"
#include "DBConnect.h"


// CCustomDlg3 대화 상자

IMPLEMENT_DYNAMIC(CCustomDlg3, CDialogEx)

CCustomDlg3::CCustomDlg3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOM_DLG3, pParent)
{

}

CCustomDlg3::~CCustomDlg3()
{
}

void CCustomDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_HallBox);
	DDX_Control(pDX, IDC_COMBO1, m_ConcertBox);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CCustomDlg3, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCustomDlg3::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCustomDlg3::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CCustomDlg3 메시지 처리기

BOOL CCustomDlg3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CDialogEx::OnInitDialog();
	m_ConcertBox.AddString(_T("예술의 전당"));
	m_ConcertBox.AddString(_T("잠실 롯데"));
	m_ConcertBox.AddString(_T("세종문화회관"));

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

	return TRUE;
}

void CCustomDlg3::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


}


void CCustomDlg3::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int sel = m_ConcertBox.GetCurSel();
	m_HallBox.ResetContent();
	switch (sel) {
	case 0:
		m_HallBox.AddString(_T("콘서트홀"));
		m_HallBox.AddString(_T("IBK챔버"));
		m_HallBox.AddString(_T("리사이틀홀"));
		m_HallBox.AddString(_T("인춘아트홀"));
		m_HallBox.AddString(_T("CJ토월극장"));
		break;
	case 1:
		m_HallBox.AddString(_T("콘서트홀"));
		break;
	case 2:
		m_HallBox.AddString(_T("세종대극장"));
		m_HallBox.AddString(_T("세종M씨어터"));
		m_HallBox.AddString(_T("세종체임버홀"));
		m_HallBox.AddString(_T("세종S씨어터"));
		break;
	}
}
