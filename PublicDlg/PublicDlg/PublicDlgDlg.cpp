
// PublicDlgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PublicDlg.h"
#include "PublicDlgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPublicDlgDlg �Ի���



CPublicDlgDlg::CPublicDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPublicDlgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPublicDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPublicDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &CPublicDlgDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_SAVE, &CPublicDlgDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_COLOR, &CPublicDlgDlg::OnBnClickedColor)
	ON_BN_CLICKED(IDC_FONT, &CPublicDlgDlg::OnBnClickedFont)
END_MESSAGE_MAP()


// CPublicDlgDlg ��Ϣ�������

BOOL CPublicDlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPublicDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPublicDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPublicDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPublicDlgDlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString m_strFileName;
	CFileDialog fileDlg(TRUE, _T("txt"),_T("*.txt"),OFN_EXPLORER,(_T("�ı��ļ���*.txt��|*.txt|�����ļ���*.*��|*.*|")));
	if(fileDlg.DoModal() == IDOK)
	{
		m_strFileName = fileDlg.GetPathName();
		MessageBox(m_strFileName + _T("�ļ��Ѵ�"),_T("���ļ�"));
	}
}


void CPublicDlgDlg::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString m_strFileName;
	CFileDialog fileDlg(TRUE, _T("txt"),_T("���������ļ�.txt"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,(_T("�ı��ļ���*.txt��|*.txt|�����ļ���*.*��|*.*|")));
	//CFileDialog fileDlg(TRUE, _T("xv"),_T("*.xv"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,(_T("Ӱ���ļ���*.xv��|*.xv|�����ļ���*.*��|*.*|")));
		if(fileDlg.DoModal() == IDOK)
	{
		m_strFileName = fileDlg.GetPathName();
		MessageBox(m_strFileName + _T("�ļ��ѱ���"),_T("�����ļ�"));
	}
}


void CPublicDlgDlg::OnBnClickedColor()
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


void CPublicDlgDlg::OnBnClickedFont()
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
