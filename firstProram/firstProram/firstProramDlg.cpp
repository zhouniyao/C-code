
// firstProramDlg.cpp : 实现文件
//
//#include <CString>
#include "stdafx.h"
#include "firstProram.h"
#include "firstProramDlg.h"
#include "afxdialogex.h"
#include "MyFont.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

double tmp_first_real;
double tmp_first_image;
double tmp_second_real;
double tmp_second_image;
double tmp_result_real;
double tmp_result_image;

int flag;

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
public:
	afx_msg void On32775();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_32775, &CAboutDlg::On32775)
END_MESSAGE_MAP()


// CfirstProramDlg 对话框



CfirstProramDlg::CfirstProramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CfirstProramDlg::IDD, pParent)
	, m_show(_T(""))
	, m_first_real(_T(""))
	, m_first_image(_T(""))
	, m_second_real(_T(""))
	, m_second_image(_T(""))
	, m_result_real(_T(""))
	, m_result_image(_T(""))
	, m_ox(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfirstProramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT7, m_show);
	DDX_Control(pDX, IDC_RADIO_OX, m_sexadecimal);
	DDX_Control(pDX, IDC_RADIO_DE, m_decimal);
	DDX_Control(pDX, IDC_RADIO_SE, m_binary);
	DDX_Control(pDX, IDC_RADIO_ADD, m_add);
	DDX_Control(pDX, IDC_RADIO_SUB, m_sub);
	DDX_Control(pDX, IDC_RADIO_MUL, m_mul);
	DDX_Control(pDX, IDC_RADIO_DIV, m_div);
	DDX_Text(pDX, IDC_EDIT1, m_first_real);
	DDX_Text(pDX, IDC_EDIT2, m_first_image);
	DDX_Text(pDX, IDC_EDIT3, m_second_real);
	DDX_Text(pDX, IDC_EDIT4, m_second_image);
	DDX_Text(pDX, IDC_EDIT5, m_result_real);
	DDX_Text(pDX, IDC_EDIT6, m_result_image);
	DDX_Radio(pDX, IDC_RADIO_OX, m_ox);
	DDX_Control(pDX, IDC_EDIT7, m_Edit);
}

BEGIN_MESSAGE_MAP(CfirstProramDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_DE, &CfirstProramDlg::OnBnClickedRadioDe)
	ON_BN_CLICKED(IDC_BUTTON1, &CfirstProramDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO_OX, &CfirstProramDlg::OnBnClickedRadioOx)
	ON_BN_CLICKED(IDC_RADIO_SE, &CfirstProramDlg::OnBnClickedRadioSe)
	ON_BN_CLICKED(IDC_RADIO_ADD, &CfirstProramDlg::OnBnClickedRadioAdd)
	ON_BN_CLICKED(IDC_RADIO_SUB, &CfirstProramDlg::OnBnClickedRadioSub)
	ON_BN_CLICKED(IDC_RADIO_MUL, &CfirstProramDlg::OnBnClickedRadioMul)
	ON_BN_CLICKED(IDC_RADIO_DIV, &CfirstProramDlg::OnBnClickedRadioDiv)
	ON_COMMAND(ID_32774, &CfirstProramDlg::On32774)
	ON_COMMAND(ID_32775, &CAboutDlg::On32775)
	ON_BN_CLICKED(IDC_BUTTON2, &CfirstProramDlg::OnBnClickedButton2)
	ON_COMMAND(ID_32773, &CfirstProramDlg::On32773)
	ON_COMMAND(ID_32771, &CfirstProramDlg::On32771)
	ON_COMMAND(ID_32772, &CfirstProramDlg::On32772)
END_MESSAGE_MAP()


// CfirstProramDlg 消息处理程序

BOOL CfirstProramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	//设置编辑框提示信息
	m_first_real = "请输入实部";
	m_first_image = "请输入虚部";
	m_second_real = "请输入实部";
	m_second_image = "请输入虚部";
	flag = 0;
	m_menu.LoadMenu(IDR_MENU1);
	this->SetMenu(&m_menu);
	//设置提示语句
	//m_record.SetWindowTextW(_T("请输入……！\n"));
	//GetDlgItem(IDC_CALC)->EnableWindow(false);

	//CTime tm=CTime::GetCurrentTime();
	//CString str1=tm.Format("%Y-%m-%d %H:%M:%S");
	//SetDlgItemText(IDC_EDIT_DATETIME, str1);//IDC_EDIT  是编辑框的ID 号，你的编辑框的ID是什么就写什么

	UpdateData(FALSE);
	tmpstr = _T("");
	((CButton *)GetDlgItem(IDC_RADIO_DE))->SetCheck(TRUE);//选上
	((CButton *)GetDlgItem(IDC_RADIO_OX))->SetCheck(FALSE);//不选上

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
	SetTimer(1, 1000, NULL);//定时为1s,就会如 表一样跳动

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//十六进制输入合法性检查
bool CheckOX(const CString& str)
{
	int sl = str.GetLength();
	if (sl > 8) {
		AfxMessageBox(AFX_IDP_PARSE_INT);
		//pDX->Fail();
		return 0;
	}
	int i;
	for(i = 0; i < sl; ++i) {
		if (str[i] >= '0' && str[i] <= '9')
			continue;
		if (str[i] >= 'a' && str[i] <= 'f')
			continue;
		if (str[i] >= 'A' && str[i] <= 'F')
			continue;
		if (str[i] == '-')
			continue;
		AfxMessageBox(AFX_IDP_PARSE_INT);
		AfxMessageBox(_T("十六进制数必须为整型值！"), MB_OKCANCEL | MB_ICONQUESTION);
		//MessageBox(_T("十六进制数必须为整形值"),_T("错误"),MB_ICONINFORMATION);
		//MessageBox(_T("这是一个警告的消息框！"),_T("标题"), MB_ICONEXCLAMATION ); 
		//MessageBox(_T("十六进制数必须为整形值！"),_T("错误"), MB_ICONEXCLAMATION ); 
		//pDX->Fail();
		return 0;
	}
	return 1;
}
//十进制输入合法性检查
bool CheckDE(const CString& str)
{
	int sl = str.GetLength();
	if (sl > 8) {
		AfxMessageBox(AFX_IDP_PARSE_INT);
		//pDX->Fail();
		return 0;
	}
	int i;
	for(i = 0; i < sl; ++i) {
		if (str[i] >= '0' && str[i] <= '9')
			continue;
		if (str[i] == '.')
			continue;
		if (str[i] == '-')
			continue;
		//if (str[i] >= 'a' && str[i] <= 'f')
		//	continue;
		//if (str[i] >= 'A' && str[i] <= 'F')
		//	continue;
		AfxMessageBox(AFX_IDP_PARSE_INT);
		AfxMessageBox(_T("十进制数不含字母！"), MB_OKCANCEL | MB_ICONQUESTION);
		//pDX->Fail();
		return 0;
	}
	return 1;
}

//十六进制字符转换成十进制数
double EnchageToDE(const CString& str)
{
	double number=0;
	int k;
	int i = str.GetLength();
	for(k=0;k<i;k++)
	{ if(str[k]>='a'&&str[k]<='f') number=(str[k]-'a'+10)+16*number;
	else if(str[k]>='A'&&str[k]<='F') number=(str[k]-'A'+10)+16*number;
	else if(str[k]>='0'&&str[k]<='9') number=(str[k]-'0')+16*number;}
	return number;
}

//十进制复数运算选择菜单
void CfirstProramDlg::On32774()
{
	// TODO: 在此添加命令处理程序代码
	flag = 0;
}


void CAboutDlg::On32775()
{
	// TODO: 在此添加命令处理程序代码
	flag = 1;
	AfxMessageBox(_T("您选择的是【十六进制】复数运算！"), MB_OKCANCEL | MB_ICONQUESTION);
}

void CfirstProramDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CfirstProramDlg::OnPaint()
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
HCURSOR CfirstProramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//清空编辑框内容
void CfirstProramDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//CNMDlg dlg2;
	//dlg2.DoModal();
	tmpstr = _T("");
	m_show = _T("");
	UpdateData(FALSE);
}

//时钟
void CfirstProramDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTime tm=CTime::GetCurrentTime();
	CString str1 = _T("现在是： ");
		str1 += tm.Format("%Y-%m-%d %H:%M:%S");
	SetDlgItemText(IDC_EDIT_DATETIME, str1);//IDC_EDIT  是编辑框的ID 号，你的编辑框的ID是什么就写什么

	CDialogEx::OnTimer(nIDEvent);
}


void CfirstProramDlg::OnBnClickedRadioOx()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ox = 0;
}

void CfirstProramDlg::OnBnClickedRadioDe()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ox = 1;
}


void CfirstProramDlg::OnBnClickedRadioSe()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ox = 2;
}


void CfirstProramDlg::OnBnClickedRadioAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//CString str1_r = _T("");
	//CString str1_i = _T("");
	//CString str2_r = _T("");
	//CString str2_i = _T("");
	//str1_r +=  m_first_real;
	//str1_i += m_first_image;
	//str2_r += m_second_real;
	//str2_i += m_second_image;
	//float f1_r = _ttof(str1_r);
	//float f1_i = _ttof(str1_i);
	//float f2_r = _ttof(str2_r);
	//float f2_i = _ttof(str2_i);
	CString str1_r, str1_i, str2_r, str2_i;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str1_r);
		GetDlgItem(IDC_EDIT2)->GetWindowText(str1_i);
			GetDlgItem(IDC_EDIT3)->GetWindowText(str2_r);
				GetDlgItem(IDC_EDIT4)->GetWindowText(str2_i);
	if(flag == 0 && CheckDE(str1_r) && CheckDE(str1_i) && CheckDE(str2_r) && CheckDE(str2_i))
	{
		float f1_r = _ttof(m_first_real);
		float f1_i = _ttof(m_first_image);
		float f2_r = _ttof(m_second_real);
		float f2_i = _ttof(m_second_image);
		float f3_r = f1_r + f2_r;
		float f3_i = f1_i + f2_i;
		m_result_real.Format(_T("%f"), f3_r);
		m_result_image.Format(_T("%f"), f3_i);
		//格式输出
			tmpstr += _T(" \r\n\t\t ");
		tmpstr += m_first_real;
		if(f1_i > 0)
			tmpstr += _T("+");
		tmpstr += m_first_image;
		tmpstr += _T(" i ");
			tmpstr += _T(" \n ");
			tmpstr += _T("\r\n +     \t");
		tmpstr += m_second_real;
		if(f2_i > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \n ");
		tmpstr += _T("---------------------------------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(f3_i > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show += tmpstr;
	}
	else if(flag == 1 && CheckOX(str1_r) && CheckOX(str1_i) && CheckOX(str2_r) && CheckOX(str2_i))
	{
		//处理十六进制
		//判断输入合法
		//double tmp_first_real;
		//double tmp_first_image;
		//double tmp_second_real;
		//double tmp_second_image;
		//double tmp_result_real;
		//double tmp_result_image;
		
		//字符转十进制
		tmp_first_real = EnchageToDE(str1_r);
		tmp_first_image = EnchageToDE(str1_i);
		tmp_second_real = EnchageToDE(str2_r);
		tmp_second_image = EnchageToDE(str2_i);

		//运算
		tmp_result_real = tmp_first_real + tmp_second_real;
		tmp_result_image = tmp_first_image + tmp_second_image;
		//十进制转十六进制
		m_result_real.Format(_T("%f"), tmp_result_real);
		m_result_image.Format(_T("%f"), tmp_result_image);

		//十六进制转字符串输出
		tmpstr += _T(" \r\n\t\t ");
		tmpstr += m_first_real;
		if(tmp_first_image > 0)
			tmpstr += _T("+");
		tmpstr += m_first_image;
		tmpstr += _T(" i ");
			tmpstr += _T(" \n ");
			tmpstr += _T("\r\n +    \t");
		tmpstr += m_second_real;
		if(tmp_second_image > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \r\n ");
		tmpstr += _T("------------------------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(tmp_result_image > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show += tmpstr;
	}
	UpdateData(FALSE);
}


void CfirstProramDlg::OnBnClickedRadioSub()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str1_r, str1_i, str2_r, str2_i;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str1_r);
		GetDlgItem(IDC_EDIT2)->GetWindowText(str1_i);
			GetDlgItem(IDC_EDIT3)->GetWindowText(str2_r);
				GetDlgItem(IDC_EDIT4)->GetWindowText(str2_i);
	if(flag == 0 && CheckDE(str1_r) && CheckDE(str1_i) && CheckDE(str2_r) && CheckDE(str2_i))
	{
		float f1_r = _ttof(m_first_real);
		float f1_i = _ttof(m_first_image);
		float f2_r = _ttof(m_second_real);
		float f2_i = _ttof(m_second_image);
		float f3_r = f1_r - f2_r;
		float f3_i = f1_i - f2_i;
		m_result_real.Format(_T("%f"), f3_r);
		m_result_image.Format(_T("%f"), f3_i);

			tmpstr += _T(" \r\n\t\t ");
		tmpstr += m_first_real;
		if(f1_i > 0)
			tmpstr += _T("+");
		tmpstr += m_first_image;
		tmpstr += _T(" i ");
			tmpstr += _T(" \n ");
			tmpstr += _T("\r\n -     \t");
		tmpstr += m_second_real;
		if(f2_i > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \n ");
		tmpstr += _T("---------------------------------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(f3_i > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show += tmpstr;
	}
	else if(flag == 1 && CheckOX(str1_r) && CheckOX(str1_i) && CheckOX(str2_r) && CheckOX(str2_i))
	{
		//处理十六进制
		//判断输入合法
		//double tmp_first_real;
		//double tmp_first_image;
		//double tmp_second_real;
		//double tmp_second_image;
		//double tmp_result_real;
		//double tmp_result_image;
		
		//字符转十进制
		tmp_first_real = EnchageToDE(str1_r);
		tmp_first_image = EnchageToDE(str1_i);
		tmp_second_real = EnchageToDE(str2_r);
		tmp_second_image = EnchageToDE(str2_i);

		//运算
		tmp_result_real = tmp_first_real - tmp_second_real;
		tmp_result_image = tmp_first_image - tmp_second_image;
		//十进制转十六进制
		m_result_real.Format(_T("%f"), tmp_result_real);
		m_result_image.Format(_T("%f"), tmp_result_image);
		//十六进制转字符串输出
		tmpstr += _T(" \r\n\t\t ");
		tmpstr += m_first_real;
		if(tmp_first_image > 0)
			tmpstr += _T("+");
		tmpstr += m_first_image;
		tmpstr += _T(" i ");
			tmpstr += _T(" \n ");
			tmpstr += _T("\r\n -     \t");
		tmpstr += m_second_real;
		if(tmp_second_image > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \r\n ");
		tmpstr += _T("------------------------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(tmp_result_image > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show += tmpstr;
	}
	UpdateData(FALSE);
}


void CfirstProramDlg::OnBnClickedRadioMul()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str1_r, str1_i, str2_r, str2_i;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str1_r);
		GetDlgItem(IDC_EDIT2)->GetWindowText(str1_i);
			GetDlgItem(IDC_EDIT3)->GetWindowText(str2_r);
				GetDlgItem(IDC_EDIT4)->GetWindowText(str2_i);
	if(flag == 0 && CheckDE(str1_r) && CheckDE(str1_i) && CheckDE(str2_r) && CheckDE(str2_i))
	{
		//real * b.real - imag * b.imag , imag * b.real + real * b.imag
		float f1_r = _ttof(m_first_real);
		float f1_i = _ttof(m_first_image);
		float f2_r = _ttof(m_second_real);
		float f2_i = _ttof(m_second_image);
		float f3_r = f1_r * f2_r - f1_i * f2_i;
		float f3_i = f1_i * f2_r + f1_r * f2_i;
		m_result_real.Format(_T("%f"), f3_r);
		m_result_image.Format(_T("%f"), f3_i);

			tmpstr += _T(" \r\n\t\t ");
		tmpstr += m_first_real;
		if(f1_i > 0)
			tmpstr += _T("+");
		tmpstr += m_first_image;
		tmpstr += _T(" i ");
			tmpstr += _T(" \n ");
			tmpstr += _T("\r\n *     \t");
		tmpstr += m_second_real;
		if(f2_i > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \n ");
		tmpstr += _T("---------------------------------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(f3_i > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show += tmpstr;
	}
	else if(flag == 1 && CheckOX(str1_r) && CheckOX(str1_i) && CheckOX(str2_r) && CheckOX(str2_i))
	{
		//处理十六进制
		//判断输入合法
		//double tmp_first_real;
		//double tmp_first_image;
		//double tmp_second_real;
		//double tmp_second_image;
		//double tmp_result_real;
		//double tmp_result_image;
		
		//字符转十进制
		tmp_first_real = EnchageToDE(str1_r);
		tmp_first_image = EnchageToDE(str1_i);
		tmp_second_real = EnchageToDE(str2_r);
		tmp_second_image = EnchageToDE(str2_i);

		//运算
		tmp_result_real = tmp_first_real * tmp_second_real - tmp_first_image * tmp_second_image;
		tmp_result_image = tmp_first_image * tmp_second_real + tmp_first_real * tmp_second_image;
		//十进制转十六进制
		m_result_real.Format(_T("%f"), tmp_result_real);
		m_result_image.Format(_T("%f"), tmp_result_image);
		//十六进制转字符串输出
		tmpstr += _T(" \r\n\t\t ");
		tmpstr += m_first_real;
		if(tmp_first_image > 0)
			tmpstr += _T("+");
		tmpstr += m_first_image;
		tmpstr += _T(" i ");
			tmpstr += _T(" \n ");
			tmpstr += _T("\r\n *     \t");
		tmpstr += m_second_real;
		if(tmp_second_image > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \r\n ");
		tmpstr += _T("------------------------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(tmp_result_image > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show += tmpstr;
	}
	UpdateData(FALSE);
}


void CfirstProramDlg::OnBnClickedRadioDiv()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str1_r, str1_i, str2_r, str2_i;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str1_r);
		GetDlgItem(IDC_EDIT2)->GetWindowText(str1_i);
			GetDlgItem(IDC_EDIT3)->GetWindowText(str2_r);
				GetDlgItem(IDC_EDIT4)->GetWindowText(str2_i);
	if(flag == 0 && CheckDE(str1_r) && CheckDE(str1_i) && CheckDE(str2_r) && CheckDE(str2_i))
	{
		//tmreal = (a.real * b.real + a.imag * b.imag)/(b.real * b.real + b.imag * b.imag);
		//tmimage = (a.imag * b.real - a.real * b.imag)/(b.real * b.real + b.imag * b.imag);
		float f1_r = _ttof(m_first_real);
		float f1_i = _ttof(m_first_image);
		float f2_r = _ttof(m_second_real);
		float f2_i = _ttof(m_second_image);
		float tmp = f2_r * f2_r + f2_i * f2_i;
		float f3_r = (f1_r * f2_r + f1_i * f2_i) / tmp;
		float f3_i = (f1_i * f2_r - f1_r * f2_i) / tmp;
		m_result_real.Format(_T("%f"), f3_r);
		m_result_image.Format(_T("%f"), f3_i);

			tmpstr += _T(" \r\n\t\t ");
		tmpstr += m_first_real;
		if(f1_i > 0)
			tmpstr += _T("+");
		tmpstr += m_first_image;
		tmpstr += _T(" i ");
			tmpstr += _T(" \n ");
			tmpstr += _T("\r\n /     \t");
		tmpstr += m_second_real;
		if(f2_i > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \n ");
		tmpstr += _T("---------------------------------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(f3_i > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show += tmpstr;
	}
	else if(flag == 1 && CheckOX(str1_r) && CheckOX(str1_i) && CheckOX(str2_r) && CheckOX(str2_i))
	{
			//处理十六进制
		//判断输入合法
		//double tmp_first_real;
		//double tmp_first_image;
		//double tmp_second_real;
		//double tmp_second_image;
		//double tmp_result_real;
		//double tmp_result_image;
		
		//字符转十进制
		tmp_first_real = EnchageToDE(str1_r);
		tmp_first_image = EnchageToDE(str1_i);
		tmp_second_real = EnchageToDE(str2_r);
		tmp_second_image = EnchageToDE(str2_i);

		//运算
		double tmp = tmp_second_real * tmp_second_real + tmp_second_image * tmp_second_image;
		tmp_result_real = ( tmp_first_real * tmp_second_real + tmp_first_image * tmp_second_image ) / tmp;
		tmp_result_image = ( tmp_first_image * tmp_second_real - tmp_first_real * tmp_second_image ) / tmp;
		//十进制转十六进制
		m_result_real.Format(_T("%f"), tmp_result_real);
		m_result_image.Format(_T("%f"), tmp_result_image);
		//十六进制转字符串输出
		tmpstr += _T(" \r\n\t\t ");
		tmpstr += m_first_real;
		if(tmp_first_image > 0)
			tmpstr += _T("+");
		tmpstr += m_first_image;
		tmpstr += _T(" i ");
			tmpstr += _T(" \n ");
			tmpstr += _T("\r\n /     \t");
		tmpstr += m_second_real;
		if(tmp_second_image > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \r\n ");
		tmpstr += _T("------------------------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(tmp_result_image > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show += tmpstr;
	}
	UpdateData(FALSE);
}




void CfirstProramDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CMyFont dlg;
	dlg.DoModal();
}


void CfirstProramDlg::On32773()
{
	// TODO: 在此添加命令处理程序代码
	CMyFont dlg;
	dlg.DoModal();
}


void CfirstProramDlg::On32771()
{
	// TODO: 在此添加命令处理程序代码
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
	GetDlgItem(IDC_EDIT7)->SetWindowTextW(str1);
	//m_show = str1;
	//UpdateData(FALSE);
}


void CfirstProramDlg::On32772()
{
	m_Edit.ModifyStyle(ES_LEFT,ES_RIGHT);//CEdit m_Edit
	// TODO: 在此添加命令处理程序代码
	//CString m_strFileName = _T("F:\\刘重阳的文件.txt");
	//CFileDialog fileDlg(FALSE, _T("txt"),_T("*.txt"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,(_T("文本文件（*.txt）|*.txt|所有文件（*.*）|*.*|")));
	////CFileDialog fileDlg(TRUE, _T("xv"),_T("*.xv"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,(_T("影像文件（*.xv）|*.xv|所有文件（*.*）|*.*|")));
	//if(fileDlg.DoModal() == IDOK)
	//{
	//	m_strFileName = fileDlg.GetPathName();
	// //file.Open(m_txtName, CFile::modeCreate | CFile::modeWrite | CFile::typeText);

	//	CString str = _T("");
	//		//str = m_show;
	//	CStdioFile file;
	//	file.Open(m_strFileName ,CFile::modeWrite); 
	//	m_Edit.GetWindowTextW(str);
	//	//m_Edit.GetWindowText(str);//编辑框控件的control的绑定变量 
	//	file.Write(str,str.GetLength()); 
	//	//file.Close();

	//	MessageBox(m_strFileName + _T("文件已保存"),_T("保存文件"));
	//}
	//保存文件

		//BOOL isOpen = FALSE;		//是否打开(否则为保存)
		//CString defaultDir = L"E:\\FileTest";	//默认打开的文件路径
		//CString fileName = L"test.txt";			//默认打开的文件名
		//CString filter = L"文件 (*.txt; *.doc; *.ppt; *.xls)|*.doc;*.ppt;*.xls||";	//文件过虑的类型
		//CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, NULL); openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\test.doc";
		//INT_PTR result = openFileDlg.DoModal();
		//CString filePath = defaultDir + "\\" + fileName;
		//if(result == IDOK) {
		//	filePath = openFileDlg.GetPathName();
		//}
		////CWnd::SetDlgItemTextW(IDC_EDIT7, filePath);
		//MessageBox(fileName + _T("文件已保存"),_T("保存文件"));
	// TODO: Add your command handler code here
		TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|Word文件(*.doc)|*.doc|所有文件(*.*)|*.*||"); 
		// 构造保存文件对话框 
		CFileDialog fileDlg(FALSE, _T("doc"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this); 
		CString strFilePath; 
		CStdioFile file;
		 CString a;

		 GetDlgItemText(IDC_EDIT7,a);
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
