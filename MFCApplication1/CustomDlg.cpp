﻿// CustomDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CustomDlg.h"


// CCustomDlg 대화 상자

IMPLEMENT_DYNAMIC(CCustomDlg, CDialogEx)

CCustomDlg::CCustomDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOM, pParent)
{

}

CCustomDlg::~CCustomDlg()
{
}

void CCustomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCustomDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCustomDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CCustomDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON2, &CCustomDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CCustomDlg 메시지 처리기


void CCustomDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CustomDlg1.DoModal();
}

void CCustomDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CustomDlg2.DoModal();
}


void CCustomDlg::OnBnClickedButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}
