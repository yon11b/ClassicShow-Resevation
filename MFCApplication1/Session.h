#pragma once
#include "afxdialogex.h"
#include "afxwin.h"

class CSESSION {

public:
	CString userId;
	CString userPw;

	int showNo;
	int price;
};

extern CSESSION SESSION;