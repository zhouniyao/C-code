
// NMTABProgram.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNMTABProgramApp:
// �йش����ʵ�֣������ NMTABProgram.cpp
//

class CNMTABProgramApp : public CWinApp
{
public:
	CNMTABProgramApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNMTABProgramApp theApp;