
// firstProramDlg.cpp : ʵ���ļ�
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


// CfirstProramDlg �Ի���



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


// CfirstProramDlg ��Ϣ�������

BOOL CfirstProramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	//���ñ༭����ʾ��Ϣ
	m_first_real = "������ʵ��";
	m_first_image = "�������鲿";
	m_second_real = "������ʵ��";
	m_second_image = "�������鲿";
	flag = 0;
	m_menu.LoadMenu(IDR_MENU1);
	this->SetMenu(&m_menu);
	//������ʾ���
	//m_record.SetWindowTextW(_T("�����롭����\n"));
	//GetDlgItem(IDC_CALC)->EnableWindow(false);

	//CTime tm=CTime::GetCurrentTime();
	//CString str1=tm.Format("%Y-%m-%d %H:%M:%S");
	//SetDlgItemText(IDC_EDIT_DATETIME, str1);//IDC_EDIT  �Ǳ༭���ID �ţ���ı༭���ID��ʲô��дʲô

	UpdateData(FALSE);
	tmpstr = _T("");
	((CButton *)GetDlgItem(IDC_RADIO_DE))->SetCheck(TRUE);//ѡ��
	((CButton *)GetDlgItem(IDC_RADIO_OX))->SetCheck(FALSE);//��ѡ��

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
	SetTimer(1, 1000, NULL);//��ʱΪ1s,�ͻ��� ��һ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//ʮ����������Ϸ��Լ��
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
		AfxMessageBox(_T("ʮ������������Ϊ����ֵ��"), MB_OKCANCEL | MB_ICONQUESTION);
		//MessageBox(_T("ʮ������������Ϊ����ֵ"),_T("����"),MB_ICONINFORMATION);
		//MessageBox(_T("����һ���������Ϣ��"),_T("����"), MB_ICONEXCLAMATION ); 
		//MessageBox(_T("ʮ������������Ϊ����ֵ��"),_T("����"), MB_ICONEXCLAMATION ); 
		//pDX->Fail();
		return 0;
	}
	return 1;
}
//ʮ��������Ϸ��Լ��
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
		AfxMessageBox(_T("ʮ������������ĸ��"), MB_OKCANCEL | MB_ICONQUESTION);
		//pDX->Fail();
		return 0;
	}
	return 1;
}

//ʮ�������ַ�ת����ʮ������
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

//ʮ���Ƹ�������ѡ��˵�
void CfirstProramDlg::On32774()
{
	// TODO: �ڴ���������������
	flag = 0;
}


void CAboutDlg::On32775()
{
	// TODO: �ڴ���������������
	flag = 1;
	AfxMessageBox(_T("��ѡ����ǡ�ʮ�����ơ��������㣡"), MB_OKCANCEL | MB_ICONQUESTION);
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CfirstProramDlg::OnPaint()
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
HCURSOR CfirstProramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//��ձ༭������
void CfirstProramDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CNMDlg dlg2;
	//dlg2.DoModal();
	tmpstr = _T("");
	m_show = _T("");
	UpdateData(FALSE);
}

//ʱ��
void CfirstProramDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CTime tm=CTime::GetCurrentTime();
	CString str1 = _T("�����ǣ� ");
		str1 += tm.Format("%Y-%m-%d %H:%M:%S");
	SetDlgItemText(IDC_EDIT_DATETIME, str1);//IDC_EDIT  �Ǳ༭���ID �ţ���ı༭���ID��ʲô��дʲô

	CDialogEx::OnTimer(nIDEvent);
}


void CfirstProramDlg::OnBnClickedRadioOx()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ox = 0;
}

void CfirstProramDlg::OnBnClickedRadioDe()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ox = 1;
}


void CfirstProramDlg::OnBnClickedRadioSe()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ox = 2;
}


void CfirstProramDlg::OnBnClickedRadioAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		//��ʽ���
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
		//����ʮ������
		//�ж�����Ϸ�
		//double tmp_first_real;
		//double tmp_first_image;
		//double tmp_second_real;
		//double tmp_second_image;
		//double tmp_result_real;
		//double tmp_result_image;
		
		//�ַ�תʮ����
		tmp_first_real = EnchageToDE(str1_r);
		tmp_first_image = EnchageToDE(str1_i);
		tmp_second_real = EnchageToDE(str2_r);
		tmp_second_image = EnchageToDE(str2_i);

		//����
		tmp_result_real = tmp_first_real + tmp_second_real;
		tmp_result_image = tmp_first_image + tmp_second_image;
		//ʮ����תʮ������
		m_result_real.Format(_T("%f"), tmp_result_real);
		m_result_image.Format(_T("%f"), tmp_result_image);

		//ʮ������ת�ַ������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		//����ʮ������
		//�ж�����Ϸ�
		//double tmp_first_real;
		//double tmp_first_image;
		//double tmp_second_real;
		//double tmp_second_image;
		//double tmp_result_real;
		//double tmp_result_image;
		
		//�ַ�תʮ����
		tmp_first_real = EnchageToDE(str1_r);
		tmp_first_image = EnchageToDE(str1_i);
		tmp_second_real = EnchageToDE(str2_r);
		tmp_second_image = EnchageToDE(str2_i);

		//����
		tmp_result_real = tmp_first_real - tmp_second_real;
		tmp_result_image = tmp_first_image - tmp_second_image;
		//ʮ����תʮ������
		m_result_real.Format(_T("%f"), tmp_result_real);
		m_result_image.Format(_T("%f"), tmp_result_image);
		//ʮ������ת�ַ������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		//����ʮ������
		//�ж�����Ϸ�
		//double tmp_first_real;
		//double tmp_first_image;
		//double tmp_second_real;
		//double tmp_second_image;
		//double tmp_result_real;
		//double tmp_result_image;
		
		//�ַ�תʮ����
		tmp_first_real = EnchageToDE(str1_r);
		tmp_first_image = EnchageToDE(str1_i);
		tmp_second_real = EnchageToDE(str2_r);
		tmp_second_image = EnchageToDE(str2_i);

		//����
		tmp_result_real = tmp_first_real * tmp_second_real - tmp_first_image * tmp_second_image;
		tmp_result_image = tmp_first_image * tmp_second_real + tmp_first_real * tmp_second_image;
		//ʮ����תʮ������
		m_result_real.Format(_T("%f"), tmp_result_real);
		m_result_image.Format(_T("%f"), tmp_result_image);
		//ʮ������ת�ַ������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			//����ʮ������
		//�ж�����Ϸ�
		//double tmp_first_real;
		//double tmp_first_image;
		//double tmp_second_real;
		//double tmp_second_image;
		//double tmp_result_real;
		//double tmp_result_image;
		
		//�ַ�תʮ����
		tmp_first_real = EnchageToDE(str1_r);
		tmp_first_image = EnchageToDE(str1_i);
		tmp_second_real = EnchageToDE(str2_r);
		tmp_second_image = EnchageToDE(str2_i);

		//����
		double tmp = tmp_second_real * tmp_second_real + tmp_second_image * tmp_second_image;
		tmp_result_real = ( tmp_first_real * tmp_second_real + tmp_first_image * tmp_second_image ) / tmp;
		tmp_result_image = ( tmp_first_image * tmp_second_real - tmp_first_real * tmp_second_image ) / tmp;
		//ʮ����תʮ������
		m_result_real.Format(_T("%f"), tmp_result_real);
		m_result_image.Format(_T("%f"), tmp_result_image);
		//ʮ������ת�ַ������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMyFont dlg;
	dlg.DoModal();
}


void CfirstProramDlg::On32773()
{
	// TODO: �ڴ���������������
	CMyFont dlg;
	dlg.DoModal();
}


void CfirstProramDlg::On32771()
{
	// TODO: �ڴ���������������
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
	GetDlgItem(IDC_EDIT7)->SetWindowTextW(str1);
	//m_show = str1;
	//UpdateData(FALSE);
}


void CfirstProramDlg::On32772()
{
	m_Edit.ModifyStyle(ES_LEFT,ES_RIGHT);//CEdit m_Edit
	// TODO: �ڴ���������������
	//CString m_strFileName = _T("F:\\���������ļ�.txt");
	//CFileDialog fileDlg(FALSE, _T("txt"),_T("*.txt"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,(_T("�ı��ļ���*.txt��|*.txt|�����ļ���*.*��|*.*|")));
	////CFileDialog fileDlg(TRUE, _T("xv"),_T("*.xv"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,(_T("Ӱ���ļ���*.xv��|*.xv|�����ļ���*.*��|*.*|")));
	//if(fileDlg.DoModal() == IDOK)
	//{
	//	m_strFileName = fileDlg.GetPathName();
	// //file.Open(m_txtName, CFile::modeCreate | CFile::modeWrite | CFile::typeText);

	//	CString str = _T("");
	//		//str = m_show;
	//	CStdioFile file;
	//	file.Open(m_strFileName ,CFile::modeWrite); 
	//	m_Edit.GetWindowTextW(str);
	//	//m_Edit.GetWindowText(str);//�༭��ؼ���control�İ󶨱��� 
	//	file.Write(str,str.GetLength()); 
	//	//file.Close();

	//	MessageBox(m_strFileName + _T("�ļ��ѱ���"),_T("�����ļ�"));
	//}
	//�����ļ�

		//BOOL isOpen = FALSE;		//�Ƿ��(����Ϊ����)
		//CString defaultDir = L"E:\\FileTest";	//Ĭ�ϴ򿪵��ļ�·��
		//CString fileName = L"test.txt";			//Ĭ�ϴ򿪵��ļ���
		//CString filter = L"�ļ� (*.txt; *.doc; *.ppt; *.xls)|*.doc;*.ppt;*.xls||";	//�ļ����ǵ�����
		//CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, NULL); openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\test.doc";
		//INT_PTR result = openFileDlg.DoModal();
		//CString filePath = defaultDir + "\\" + fileName;
		//if(result == IDOK) {
		//	filePath = openFileDlg.GetPathName();
		//}
		////CWnd::SetDlgItemTextW(IDC_EDIT7, filePath);
		//MessageBox(fileName + _T("�ļ��ѱ���"),_T("�����ļ�"));
	// TODO: Add your command handler code here
		TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|Word�ļ�(*.doc)|*.doc|�����ļ�(*.*)|*.*||"); 
		// ���챣���ļ��Ի��� 
		CFileDialog fileDlg(FALSE, _T("doc"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this); 
		CString strFilePath; 
		CStdioFile file;
		 CString a;

		 GetDlgItemText(IDC_EDIT7,a);
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
