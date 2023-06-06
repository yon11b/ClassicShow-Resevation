// CustomAll.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "CustomAll.h"


// CCustomAll 대화 상자

IMPLEMENT_DYNAMIC(CCustomAll, CDialogEx)

CCustomAll::CCustomAll(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOM_DLG2, pParent)
{

}

CCustomAll::~CCustomAll()
{
}

void CCustomAll::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_Show);
}


BEGIN_MESSAGE_MAP(CCustomAll, CDialogEx)
END_MESSAGE_MAP()


// CCustomAll 메시지 처리기
