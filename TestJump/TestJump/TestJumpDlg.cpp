
// TestJumpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestJump.h"
#include "TestJumpDlg.h"
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


// CTestJumpDlg �Ի���



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


// CTestJumpDlg ��Ϣ�������

BOOL CTestJumpDlg::OnInitDialog()
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
	//m_list.InsertColumn(0, _T("ѧ��"), LVCFMT_LEFT, rt.right/2, 0);
	//m_list.InsertColumn(0, _T("����"), LVCFMT_LEFT, rt.right/4, 1);
	//m_list.InsertColumn(0, _T("רҵ"), LVCFMT_LEFT, rt.right/4, 2);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestJumpDlg::OnPaint()
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
HCURSOR CTestJumpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestJumpDlg::OnBnClickedRadioAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	m_result = m_first - m_second;
	UpdateData(false);
}


void CTestJumpDlg::OnBnClickedRadioMul()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	m_result = m_first * m_second;
	UpdateData(false);
}


void CTestJumpDlg::OnBnClickedRadioDev()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		UpdateData(true);
	m_result = m_first / m_second;
	UpdateData(false);
}

//
//void CTestJumpDlg::OnEnChangeEdit1()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	MessageBox(_T("��һ����ֵ�ı�"));
//}
//
//
//void CTestJumpDlg::OnEnChangeEdit2()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	MessageBox(_T("�ڶ�����ֵ�ı�"));
//}
//

void CTestJumpDlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�


	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
