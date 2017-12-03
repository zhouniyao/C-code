
// PublicDlgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PublicDlg.h"
#include "PublicDlgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CPublicDlgDlg 对话框



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


// CPublicDlgDlg 消息处理程序

BOOL CPublicDlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPublicDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPublicDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPublicDlgDlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_strFileName;
	CFileDialog fileDlg(TRUE, _T("txt"),_T("*.txt"),OFN_EXPLORER,(_T("文本文件（*.txt）|*.txt|所有文件（*.*）|*.*|")));
	if(fileDlg.DoModal() == IDOK)
	{
		m_strFileName = fileDlg.GetPathName();
		MessageBox(m_strFileName + _T("文件已打开"),_T("打开文件"));
	}
}


void CPublicDlgDlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_strFileName;
	CFileDialog fileDlg(TRUE, _T("txt"),_T("刘重阳的文件.txt"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,(_T("文本文件（*.txt）|*.txt|所有文件（*.*）|*.*|")));
	//CFileDialog fileDlg(TRUE, _T("xv"),_T("*.xv"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,(_T("影像文件（*.xv）|*.xv|所有文件（*.*）|*.*|")));
		if(fileDlg.DoModal() == IDOK)
	{
		m_strFileName = fileDlg.GetPathName();
		MessageBox(m_strFileName + _T("文件已保存"),_T("保存文件"));
	}
}


void CPublicDlgDlg::OnBnClickedColor()
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


void CPublicDlgDlg::OnBnClickedFont()
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
