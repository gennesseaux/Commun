#pragma once

#include "resource.h"

// Bo�te de dialogue CDialogTest

class CDialogTest : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTest)

public:
	CDialogTest(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CDialogTest();

// Donn�es de bo�te de dialogue
	enum { IDD = IDD_DIALOG_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
};
