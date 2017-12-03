// MyFont.cpp : 实现文件
//

#include "stdafx.h"
#include "NMTABProgram.h"
#include "MyFont.h"
#include "afxdialogex.h"


// CMyFont 对话框

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


// CMyFont 消息处理程序
