// MyFont.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NMTABProgram.h"
#include "MyFont.h"
#include "afxdialogex.h"


// CMyFont �Ի���

IMPLEMENT_DYNAMIC(CMyFont, CDialogEx)

CMyFont::CMyFont(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyFont::IDD, pParent)
{

}

CMyFont::~CMyFont()
{
}

void CMyFont::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyFont, CDialogEx)
END_MESSAGE_MAP()


// CMyFont ��Ϣ�������
