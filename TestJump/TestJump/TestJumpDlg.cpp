
// TestJumpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestJump.h"
#include "TestJumpDlg.h"
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


// CTestJumpDlg 对话框



CTestJumpDlg::CTestJumpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestJumpDlg::IDD, pParent)
	, m_first(0)
	, m_second(0)
	, m_result(0)
	, m_string(_T(""))
	, m_list(_T(""))
	, m_combo(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestJumpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_first);
	DDV_MinMaxInt(pDX, m_first, 0, 100);
	DDX_Text(pDX, IDC_EDIT2, m_second);
	DDV_MinMaxInt(pDX, m_second, 0, 100);
	DDX_Text(pDX, IDC_EDIT3, m_result);
	DDX_Text(pDX, IDC_EDIT4, m_string);
	DDV_MaxChars(pDX, m_string, 200);
	DDX_LBString(pDX, IDC_LIST1, m_list);
	DDX_CBString(pDX, IDC_COMBO1, m_combo);
}

BEGIN_MESSAGE_MAP(CTestJumpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_ADD, &CTestJumpDlg::OnBnClickedRadioAdd)
	ON_BN_CLICKED(IDC_RADIO_SUB, &CTestJumpDlg::OnBnClickedRadioSub)
	ON_BN_CLICKED(IDC_RADIO_MUL, &CTestJumpDlg::OnBnClickedRadioMul)
	ON_BN_CLICKED(IDC_RADIO_DEV, &CTestJumpDlg::OnBnClickedRadioDev)
	ON_EN_CHANGE(IDC_EDIT1, &CTestJumpDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CTestJumpDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT4, &CTestJumpDlg::OnEnChangeEdit4)
END_MESSAGE_MAP()


// CTestJumpDlg 消息处理程序

BOOL CTestJumpDlg::OnInitDialog()
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
	CString first = _T("103011");
	CString second = _T("103021");
	CString third = _T("103031");
	//m_combo.AddString(first);
	//m_combo.AddString(second);
	//m_combo.AddString(third);
	//m_combo.SetCurSel(0);
	//m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//CRect rt;
	//m_list.GetClientRect(&rt);
	//m_list.InsertColumn(0, _T("学号"), LVCFMT_LEFT, rt.right/2, 0);
	//m_list.InsertColumn(0, _T("姓名"), LVCFMT_LEFT, rt.right/4, 1);
	//m_list.InsertColumn(0, _T("专业"), LVCFMT_LEFT, rt.right/4, 2);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestJumpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestJumpDlg::OnPaint()
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
HCURSOR CTestJumpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestJumpDlg::OnBnClickedRadioAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_result = m_first + m_second;


	//char *tmp = NULL;
	//IntToChar(m_first, tmp) ;
	//m_string += tmp;
	//m_string += _T("+");
	//IntToChar(m_second, tmp) ;
	//m_string += tmp;
	//m_string += _T(" = ");
	//IntToChar(m_result, tmp) ;
	//m_string += tmp;

	UpdateData(false);
}


void CTestJumpDlg::OnBnClickedRadioSub()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_result = m_first - m_second;
	UpdateData(false);
}


void CTestJumpDlg::OnBnClickedRadioMul()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_result = m_first * m_second;
	UpdateData(false);
}


void CTestJumpDlg::OnBnClickedRadioDev()
{
	// TODO: 在此添加控件通知处理程序代码
		UpdateData(true);
	m_result = m_first / m_second;
	UpdateData(false);
}

//
//void CTestJumpDlg::OnEnChangeEdit1()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//
//	// TODO:  在此添加控件通知处理程序代码
//	MessageBox(_T("第一个数值改变"));
//}
//
//
//void CTestJumpDlg::OnEnChangeEdit2()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//
//
//	// TODO:  在此添加控件通知处理程序代码
//	MessageBox(_T("第二个数值改变"));
//}
//

void CTestJumpDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。


	// TODO:  在此添加控件通知处理程序代码
	//UpdateData(true);
	char *tmp = NULL;
	IntToChar(m_first, tmp) ;
	m_string += tmp;
	m_string += _T("+");
	IntToChar(m_second, tmp) ;
	m_string += tmp;
	m_string += _T(" = ");
	IntToChar(m_result, tmp) ;
	m_string += tmp;
	//UpdateData(false);
}
