
// NMTABProgramDlg.cpp : ʵ���ļ�
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


// CNMTABProgramDlg �Ի���



CNMTABProgramDlg::CNMTABProgramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNMTABProgramDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_page1.m_ox = 1;//Ĭ��ʮ����
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


// CNMTABProgramDlg ��Ϣ�������

BOOL CNMTABProgramDlg::OnInitDialog()
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

	//ΪTab Control��������ҳ��
	m_tab.InsertItem(0, _T("��������"));
	m_tab.InsertItem(1, _T("���ִ���"));
	//���������Ի���
	m_page1.Create(IDD_PAGE1, &m_tab);
	m_page2.Create(IDD_PAGE2, &m_tab);
	//�趨��Tab����ʾ�ķ�Χ
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_page1.MoveWindow(&rc);
	m_page2.MoveWindow(&rc);
	//�ѶԻ������ָ�뱣������
	pDialog[0] = &m_page1;
	pDialog[1] = &m_page2;
	//������������һ��CDialogָ�����������б���Tab Control��ÿ��ҳ������Ĵ�С��Tab Controlҳ��ĸ����������±��Ӧ��ÿ��ҳ�������������������ٴ�ȡ����
	//��ʾ��ʼҳ��
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	//���浱ǰѡ��
	m_CurSelTab = 0;

	
	//...
	//m_pMyDlg = new CMyDlg;
	//m_pMyDlg->Create(CMyDlg::IDD, &m_tabctrl /*CXTabCtrl variable*/);
	//m_tabctrl.AddTab(m_pMyDlg, "Tab caption", 0 /* image number*/);
	//...

	    //TCITEM tc1,tc2;
     //    tc1.mask = TCIF_TEXT;
     //    tc1.pszText = _T("��һҳ");
     //    tc2.mask = TCIF_TEXT;
     //    tc2.pszText = _T("�ڶ�ҳ");

     //    m_tab.InsertItem(0, &tc1);
     //    m_tab.InsertItem(1, &tc2); //������ֻ�����������tabҳ

     //    CRect rec;
     //    m_tab.GetClientRect(&rec);//���TAB�ؼ�������

     //    //��λѡ�ҳ��λ�ã�������Ը�������Լ�����ƫ����
     //    rec.bottom -= 2;
     //    rec.left += 1;
     //    rec.top += 27;
     //    rec.right -= 3;

     //    //������ҳ��
     //    m_page1.Create(IDD_PAGE1,GetDlgItem(IDC_TAB1));
     //    m_page2.Create(IDD_PAGE2,GetDlgItem(IDC_TAB1));
     //    //����ҳ���ƶ���ָ����λ��
     //    m_page1.MoveWindow(&rec);
     //    m_page2.MoveWindow(&rec);
     //    //��ʾ��ҳ��
     //    m_page1.ShowWindow(SW_SHOW);
     //    m_page2.ShowWindow(SW_HIDE);

		m_page1.m_f_r.SetWindowTextW(_T("������ʵ��\n"));
	//GetDlgItem(IDC_EDIT1)->EnableWindow(false);//��ֹ�༭
		m_page1.m_f_i.SetWindowTextW(_T("�������鲿\n"));
		m_page1.m_s_r.SetWindowTextW(_T("������ʵ��\n"));
		m_page1.m_s_i.SetWindowTextW(_T("�������鲿\n"));

		//PlaySound((LPCTSTR)IDR_STARTWIN, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC); 
		//PlaySound("E:\\VisualStudio\\MFC\\NMTABProgram\\NMTABProgram\\res\\fwo.wav", NULL, SND_RESOURCE | SND_ASYNC);
		//mciSendString(_T("E:\\VisualStudio\\MFC\\NMTABProgram\\NMTABProgram\\res\\fwo.wav"),_T(""),0,NULL);
		//sndPlaySound(TEXT("E:\\VisualStudio\\MFC\\NMTABProgram\\NMTABProgram\\res\\fwo.wav"), SND_ASYNC | SND_LOOP);
		//PlaySound(TEXT("C:\\windows\\Media\\Windows ��ӡ���.wav"),NULL,SND_FILENAME|SND_ASYNC);
		//mciSendString(L"E:\\VisualStudio\\MFC\\NMTABProgram\\NMTABProgram\\res\\fwo.wav", NULL, 0, NULL);
		SetTimer(1, 1000, NULL);//��ʱΪ1s,�ͻ��� ��һ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNMTABProgramDlg::OnPaint()
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
HCURSOR CNMTABProgramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNMTABProgramDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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

	  //�ѵ�ǰ��ҳ����������
    pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
    //�õ��µ�ҳ������
    m_CurSelTab = m_tab.GetCurSel();
    //���µ�ҳ����ʾ����
    pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
}


void CNMTABProgramDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CTime tm=CTime::GetCurrentTime();
	CString str1 = _T("�����ǣ� ");
		str1 += tm.Format("%Y-%m-%d %H:%M:%S");
	SetDlgItemText(IDC_EDIT_DATETIME, str1);//IDC_EDIT  �Ǳ༭���ID �ţ���ı༭���ID��ʲô��дʲô

	CDialogEx::OnTimer(nIDEvent);
}
