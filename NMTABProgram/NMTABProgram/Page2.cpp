// Page2.cpp : 实现文件
//

#include "stdafx.h"
#include "NMTABProgram.h"
#include "Page2.h"
#include "afxdialogex.h"
#include "MyFont.h"

// CPage2 对话框

IMPLEMENT_DYNAMIC(CPage2, CDialogEx)

CPage2::CPage2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPage2::IDD, pParent)
{

}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CPage2::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_OPEN, &CPage2::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_SAVE, &CPage2::OnBnClickedSave)
	ON_BN_CLICKED(IDC_COLOR, &CPage2::OnBnClickedColor)
	ON_BN_CLICKED(IDC_FONT, &CPage2::OnBnClickedFont)
END_MESSAGE_MAP()


// CPage2 消息处理程序


void CPage2::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CMyFont dlg;
	dlg.DoModal();
}


void CPage2::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码
		CString m_strFileName;
	CFileDialog fileDlg(TRUE, _T("txt"),_T("*.txt"),OFN_EXPLORER,(_T("文本文件（*.txt）|*.txt|所有文件（*.*）|*.*|")));
	if(fileDlg.DoModal() == IDOK)
	{
		m_strFileName = fileDlg.GetPathName();
		MessageBox(m_strFileName + _T("文件已打开"),_T("打开文件"));
	}
	CString strFile = m_strFileName;
	CFile f;
	f.Open(strFile, CFile::modeRead);
	char* str = new char[f.GetLength()];
	f.Read(str, f.GetLength());
	f.Close();
	CString str1 = CString(str);
	GetDlgItem(IDC_CONTENT)->SetWindowTextW(str1);
}


void CPage2::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
			TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|Word文件(*.doc)|*.doc|所有文件(*.*)|*.*||"); 
		// 构造保存文件对话框 
		CFileDialog fileDlg(FALSE, _T("doc"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this); 
		CString strFilePath; 
		CStdioFile file;
		 CString a;

		 GetDlgItemText(IDC_CONTENT,a);
		 // 显示保存文件对话框 
		if (IDOK == fileDlg.DoModal()) 
		{ 
		// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里 
		strFilePath = fileDlg.GetPathName();
		file.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText); 

		file.WriteString(a); //写入edit box中的数据
		file.Close();
		 //SetDlgItemText(IDC_SAVE_EDIT, strFilePath); 
		} 

}


void CPage2::OnBnClickedColor()
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


void CPage2::OnBnClickedFont()
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
