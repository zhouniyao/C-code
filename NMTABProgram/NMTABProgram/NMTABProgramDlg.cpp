
// NMTABProgramDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NMTABProgram.h"
#include "NMTABProgramDlg.h"
#include "afxdialogex.h"

#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB") 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL PlaySound(LPCSTR pszSound, HMODULE hmod,DWORD fdwSound); 

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


// CNMTABProgramDlg 对话框



CNMTABProgramDlg::CNMTABProgramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNMTABProgramDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_page1.m_ox = 1;//默认十进制
}

void CNMTABProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CNMTABProgramDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CNMTABProgramDlg::OnTcnSelchangeTab1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CNMTABProgramDlg 消息处理程序

BOOL CNMTABProgramDlg::OnInitDialog()
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

	//为Tab Control增加两个页面
	m_tab.InsertItem(0, _T("复数运算"));
	m_tab.InsertItem(1, _T("文字处理"));
	//创建两个对话框
	m_page1.Create(IDD_PAGE1, &m_tab);
	m_page2.Create(IDD_PAGE2, &m_tab);
	//设定在Tab内显示的范围
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_page1.MoveWindow(&rc);
	m_page2.MoveWindow(&rc);
	//把对话框对象指针保存起来
	pDialog[0] = &m_page1;
	pDialog[1] = &m_page2;
	//这里我们用了一个CDialog指针数组来进行保存Tab Control的每个页，数组的大小是Tab Control页面的个数，数组下标对应着每个页面的索引（这样方便快速存取）。
	//显示初始页面
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	//保存当前选择
	m_CurSelTab = 0;

	
	//...
	//m_pMyDlg = new CMyDlg;
	//m_pMyDlg->Create(CMyDlg::IDD, &m_tabctrl /*CXTabCtrl variable*/);
	//m_tabctrl.AddTab(m_pMyDlg, "Tab caption", 0 /* image number*/);
	//...

	    //TCITEM tc1,tc2;
     //    tc1.mask = TCIF_TEXT;
     //    tc1.pszText = _T("第一页");
     //    tc2.mask = TCIF_TEXT;
     //    tc2.pszText = _T("第二页");

     //    m_tab.InsertItem(0, &tc1);
     //    m_tab.InsertItem(1, &tc2); //到这里只是添加了两个tab页

     //    CRect rec;
     //    m_tab.GetClientRect(&rec);//获得TAB控件的坐标

     //    //定位选项卡页的位置，这里可以根据情况自己调节偏移量
     //    rec.bottom -= 2;
     //    rec.left += 1;
     //    rec.top += 27;
     //    rec.right -= 3;

     //    //创建子页面
     //    m_page1.Create(IDD_PAGE1,GetDlgItem(IDC_TAB1));
     //    m_page2.Create(IDD_PAGE2,GetDlgItem(IDC_TAB1));
     //    //将子页面移动到指定的位置
     //    m_page1.MoveWindow(&rec);
     //    m_page2.MoveWindow(&rec);
     //    //显示子页面
     //    m_page1.ShowWindow(SW_SHOW);
     //    m_page2.ShowWindow(SW_HIDE);

		m_page1.m_f_r.SetWindowTextW(_T("请输入实部\n"));
	//GetDlgItem(IDC_EDIT1)->EnableWindow(false);//禁止编辑
		m_page1.m_f_i.SetWindowTextW(_T("请输入虚部\n"));
		m_page1.m_s_r.SetWindowTextW(_T("请输入实部\n"));
		m_page1.m_s_i.SetWindowTextW(_T("请输入虚部\n"));

		//PlaySound((LPCTSTR)IDR_STARTWIN, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC); 
		//PlaySound("E:\\VisualStudio\\MFC\\NMTABProgram\\NMTABProgram\\res\\fwo.wav", NULL, SND_RESOURCE | SND_ASYNC);
		//mciSendString(_T("E:\\VisualStudio\\MFC\\NMTABProgram\\NMTABProgram\\res\\fwo.wav"),_T(""),0,NULL);
		//sndPlaySound(TEXT("E:\\VisualStudio\\MFC\\NMTABProgram\\NMTABProgram\\res\\fwo.wav"), SND_ASYNC | SND_LOOP);
		//PlaySound(TEXT("C:\\windows\\Media\\Windows 打印完成.wav"),NULL,SND_FILENAME|SND_ASYNC);
		//mciSendString(L"E:\\VisualStudio\\MFC\\NMTABProgram\\NMTABProgram\\res\\fwo.wav", NULL, 0, NULL);
		SetTimer(1, 1000, NULL);//定时为1s,就会如 表一样跳动
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNMTABProgramDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNMTABProgramDlg::OnPaint()
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
HCURSOR CNMTABProgramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNMTABProgramDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	//switch(m_tab.GetCurSel())
 //   {
 //     case0:
 //           m_page1.ShowWindow(SW_SHOW);
 //           m_page2.ShowWindow(SW_HIDE);
 //           break;
 //      case1:
 //           m_page1.ShowWindow(SW_HIDE);
 //           m_page2.ShowWindow(SW_SHOW);
 //           break;
 //     default:
 //           break;
 //   }

	  //把当前的页面隐藏起来
    pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
    //得到新的页面索引
    m_CurSelTab = m_tab.GetCurSel();
    //把新的页面显示出来
    pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
}


void CNMTABProgramDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTime tm=CTime::GetCurrentTime();
	CString str1 = _T("现在是： ");
		str1 += tm.Format("%Y-%m-%d %H:%M:%S");
	SetDlgItemText(IDC_EDIT_DATETIME, str1);//IDC_EDIT  是编辑框的ID 号，你的编辑框的ID是什么就写什么

	CDialogEx::OnTimer(nIDEvent);
}
