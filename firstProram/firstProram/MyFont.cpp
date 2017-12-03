// MyFont.cpp : 实现文件
//

#include "stdafx.h"
#include "firstProram.h"
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
	ON_BN_CLICKED(IDC_FONT, &CMyFont::OnBnClickedFont)
	ON_BN_CLICKED(IDC_COLOR, &CMyFont::OnBnClickedColor)
END_MESSAGE_MAP()


// CMyFont 消息处理程序


void CMyFont::OnBnClickedFont()
{
	// TODO: 在此添加控件通知处理程序代码
	LOGFONT lf;
	CFontDialog dlg(&lf);
	if(dlg.DoModal())
	{
		CString str = _T("设置字体为");
		MessageBox(str + lf.lfFaceName);
	}

}


void CMyFont::OnBnClickedColor()
{
	// TODO: 在此添加控件通知处理程序代码
	COLORREF color;
	CString strcolor;
	CColorDialog dlg(0,CC_FULLOPEN);
	if(dlg.DoModal())
	{
		color = dlg.GetColor();
		strcolor.Format(_T("%x"),color);
		MessageBox(_T("已取得颜色，值为")+ strcolor, _T("选择颜色"));
	}
}
