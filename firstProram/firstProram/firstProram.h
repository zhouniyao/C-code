
// firstProram.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CfirstProramApp:
// �йش����ʵ�֣������ firstProram.cpp
//

class CfirstProramApp : public CWinApp
{
public:
	CfirstProramApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CfirstProramApp theApp;