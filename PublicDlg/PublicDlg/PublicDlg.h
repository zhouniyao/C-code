
// PublicDlg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPublicDlgApp:
// �йش����ʵ�֣������ PublicDlg.cpp
//

class CPublicDlgApp : public CWinApp
{
public:
	CPublicDlgApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPublicDlgApp theApp;