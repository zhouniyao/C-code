// MyFont.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "firstProram.h"
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
	ON_BN_CLICKED(IDC_FONT, &CMyFont::OnBnClickedFont)
	ON_BN_CLICKED(IDC_COLOR, &CMyFont::OnBnClickedColor)
END_MESSAGE_MAP()


// CMyFont ��Ϣ�������


void CMyFont::OnBnClickedFont()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LOGFONT lf;
	CFontDialog dlg(&lf);
	if(dlg.DoModal())
	{
		CString str = _T("��������Ϊ");
		MessageBox(str + lf.lfFaceName);
	}

}


void CMyFont::OnBnClickedColor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	COLORREF color;
	CString strcolor;
	CColorDialog dlg(0,CC_FULLOPEN);
	if(dlg.DoModal())
	{
		color = dlg.GetColor();
		strcolor.Format(_T("%x"),color);
		MessageBox(_T("��ȡ����ɫ��ֵΪ")+ strcolor, _T("ѡ����ɫ"));
	}
}
