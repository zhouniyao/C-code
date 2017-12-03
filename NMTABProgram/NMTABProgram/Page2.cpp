// Page2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NMTABProgram.h"
#include "Page2.h"
#include "afxdialogex.h"
#include "MyFont.h"

// CPage2 �Ի���

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


// CPage2 ��Ϣ�������


void CPage2::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMyFont dlg;
	dlg.DoModal();
}


void CPage2::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		CString m_strFileName;
	CFileDialog fileDlg(TRUE, _T("txt"),_T("*.txt"),OFN_EXPLORER,(_T("�ı��ļ���*.txt��|*.txt|�����ļ���*.*��|*.*|")));
	if(fileDlg.DoModal() == IDOK)
	{
		m_strFileName = fileDlg.GetPathName();
		MessageBox(m_strFileName + _T("�ļ��Ѵ�"),_T("���ļ�"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
			TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|Word�ļ�(*.doc)|*.doc|�����ļ�(*.*)|*.*||"); 
		// ���챣���ļ��Ի��� 
		CFileDialog fileDlg(FALSE, _T("doc"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this); 
		CString strFilePath; 
		CStdioFile file;
		 CString a;

		 GetDlgItemText(IDC_CONTENT,a);
		 // ��ʾ�����ļ��Ի��� 
		if (IDOK == fileDlg.DoModal()) 
		{ 
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭���� 
		strFilePath = fileDlg.GetPathName();
		file.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText); 

		file.WriteString(a); //д��edit box�е�����
		file.Close();
		 //SetDlgItemText(IDC_SAVE_EDIT, strFilePath); 
		} 

}


void CPage2::OnBnClickedColor()
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


void CPage2::OnBnClickedFont()
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
