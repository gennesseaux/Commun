// DialogTest.cpp�: fichier d'impl�mentation
//

#include "stdafx.h"
#include "DialogTest.h"
#include "afxdialogex.h"


// Bo�te de dialogue CDialogTest

IMPLEMENT_DYNAMIC(CDialogTest, CDialogEx)

CDialogTest::CDialogTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogTest::IDD, pParent)
{

}

CDialogTest::~CDialogTest()
{
}

void CDialogTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogTest, CDialogEx)
END_MESSAGE_MAP()


// Gestionnaires de messages de CDialogTest
