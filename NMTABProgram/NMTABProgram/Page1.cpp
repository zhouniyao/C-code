// Page1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NMTABProgram.h"
#include "Page1.h"
#include "afxdialogex.h"


// CPage1 �Ի���

double tmp_first_real;
double tmp_first_image;
double tmp_second_real;
double tmp_second_image;
double tmp_result_real;
double tmp_result_image;
CString tmpstr = _T("");
IMPLEMENT_DYNAMIC(CPage1, CDialogEx)

CPage1::CPage1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPage1::IDD, pParent)
	, m_ox(0)
	, m_first_real(_T(""))
	, m_first_image(_T(""))
	, m_second_real(_T(""))
	, m_second_image(_T(""))
	, m_result_real(_T(""))
	, m_result_image(_T(""))
	, m_show(_T(""))
{

}

CPage1::~CPage1()
{
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
void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RADIO_OX, m_ox);
	DDV_MinMaxInt(pDX, m_ox, 0, 5);
	DDX_Text(pDX, IDC_EDIT1, m_first_real);
	DDX_Text(pDX, IDC_EDIT2, m_first_image);
	DDX_Text(pDX, IDC_EDIT3, m_second_real);
	DDX_Text(pDX, IDC_EDIT4, m_second_image);
	DDX_Text(pDX, IDC_EDIT5, m_result_real);
	DDX_Text(pDX, IDC_EDIT6, m_result_image);
	DDX_Control(pDX, IDC_EDIT1, m_f_r);
	DDX_Control(pDX, IDC_EDIT2, m_f_i);
	DDX_Control(pDX, IDC_EDIT3, m_s_r);
	DDX_Control(pDX, IDC_EDIT4, m_s_i);
	DDX_Control(pDX, IDC_EDIT5, m_r_r);
	DDX_Control(pDX, IDC_EDIT6, m_r_i);
	DDX_Text(pDX, IDC_EDIT8, m_show);
}


BEGIN_MESSAGE_MAP(CPage1, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_OX, &CPage1::OnBnClickedRadioOx)
	ON_BN_CLICKED(IDC_RADIO_DE, &CPage1::OnBnClickedRadioDe)
	ON_BN_CLICKED(IDC_RADIO_BI, &CPage1::OnBnClickedRadioBi)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO_ADD, &CPage1::OnBnClickedRadioAdd)
	ON_BN_CLICKED(IDC_BUTTON1, &CPage1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO_SUB, &CPage1::OnBnClickedRadioSub)
	ON_BN_CLICKED(IDC_RADIO_MUL, &CPage1::OnBnClickedRadioMul)
	ON_BN_CLICKED(IDC_RADIO_DIV, &CPage1::OnBnClickedRadioDiv)
END_MESSAGE_MAP()


// CPage1 ��Ϣ�������

//������ʾ���
	//m_record.SetWindowTextW(_T("�����롭����\n"));
	//GetDlgItem(IDC_CALC)->EnableWindow(false);

	//CTime tm=CTime::GetCurrentTime();
	//CString str1=tm.Format("%Y-%m-%d %H:%M:%S");
	//SetDlgItemText(IDC_EDIT_DATETIME, str1);//IDC_EDIT  �Ǳ༭���ID �ţ���ı༭���ID��ʲô��дʲô
void CPage1::OnBnClickedRadioOx()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ox = 0;

}


void CPage1::OnBnClickedRadioDe()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ox = 1;
}


void CPage1::OnBnClickedRadioBi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ox = 2;
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
void CPage1::OnBnClickedRadioAdd()
{
	UpdateData(TRUE);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str1_r, str1_i, str2_r, str2_i;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str1_r);
		GetDlgItem(IDC_EDIT2)->GetWindowText(str1_i);
			GetDlgItem(IDC_EDIT3)->GetWindowText(str2_r);
				GetDlgItem(IDC_EDIT4)->GetWindowText(str2_i);
	if(m_ox == 1 && CheckDE(str1_r) && CheckDE(str1_i) && CheckDE(str2_r) && CheckDE(str2_i))
	{
		//����ʮ���Ƹ����ӷ�����
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
			tmpstr += _T("\t\n +     \t");
		tmpstr += m_second_real;
		if(f2_i > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \n ");
		tmpstr += _T("------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(f3_i > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show = tmpstr;
	}
	else if(m_ox == 0 && CheckOX(str1_r) && CheckOX(str1_i) && CheckOX(str2_r) && CheckOX(str2_i))
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
			tmpstr += _T("\t\n +     \t");
		tmpstr += m_second_real;
		if(tmp_second_image > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \n ");
		tmpstr += _T("------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(tmp_result_image > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show = tmpstr;
	}
	else
	{
		;
		AfxMessageBox(AFX_IDP_PARSE_INT);
	}
	UpdateData(FALSE);
}


void CPage1::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	tmpstr = _T("");;
	m_show = _T("");//������
	UpdateData(FALSE);
}


void CPage1::OnBnClickedRadioSub()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		UpdateData(TRUE);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str1_r, str1_i, str2_r, str2_i;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str1_r);
		GetDlgItem(IDC_EDIT2)->GetWindowText(str1_i);
			GetDlgItem(IDC_EDIT3)->GetWindowText(str2_r);
				GetDlgItem(IDC_EDIT4)->GetWindowText(str2_i);
	if(m_ox == 1 && CheckDE(str1_r) && CheckDE(str1_i) && CheckDE(str2_r) && CheckDE(str2_i))
	{
		//����ʮ���Ƹ�����������
		float f1_r = _ttof(m_first_real);
		float f1_i = _ttof(m_first_image);
		float f2_r = _ttof(m_second_real);
		float f2_i = _ttof(m_second_image);
		float f3_r = f1_r - f2_r;
		float f3_i = f1_i - f2_i;
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
			tmpstr += _T("\t\n -     \t");
		tmpstr += m_second_real;
		if(f2_i > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \n ");
		tmpstr += _T("------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(f3_i > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show = tmpstr;
	}
	else if(m_ox == 0 && CheckOX(str1_r) && CheckOX(str1_i) && CheckOX(str2_r) && CheckOX(str2_i))
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
			tmpstr += _T("\t\n -     \t");
		tmpstr += m_second_real;
		if(tmp_second_image > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \n ");
		tmpstr += _T("------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(tmp_result_image > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show = tmpstr;
	}
	else
	{
		;
		AfxMessageBox(AFX_IDP_PARSE_INT);
	}
	UpdateData(FALSE);
}


void CPage1::OnBnClickedRadioMul()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		UpdateData(TRUE);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str1_r, str1_i, str2_r, str2_i;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str1_r);
		GetDlgItem(IDC_EDIT2)->GetWindowText(str1_i);
			GetDlgItem(IDC_EDIT3)->GetWindowText(str2_r);
				GetDlgItem(IDC_EDIT4)->GetWindowText(str2_i);
	if(m_ox == 1 && CheckDE(str1_r) && CheckDE(str1_i) && CheckDE(str2_r) && CheckDE(str2_i))
	{
		//����ʮ���Ƹ����˷�����
		//real * b.real - imag * b.imag , imag * b.real + real * b.imag
		float f1_r = _ttof(m_first_real);
		float f1_i = _ttof(m_first_image);
		float f2_r = _ttof(m_second_real);
		float f2_i = _ttof(m_second_image);
		float f3_r = f1_r * f2_r - f1_i * f2_i;
		float f3_i = f1_i * f2_r + f1_r * f2_i;
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
			tmpstr += _T("\t\n *     \t");
		tmpstr += m_second_real;
		if(f2_i > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \n ");
		tmpstr += _T("------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(f3_i > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show = tmpstr;
	}
	else if(m_ox == 0 && CheckOX(str1_r) && CheckOX(str1_i) && CheckOX(str2_r) && CheckOX(str2_i))
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
			tmpstr += _T("\t\n *     \t");
		tmpstr += m_second_real;
		if(tmp_second_image > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \n ");
		tmpstr += _T("------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(tmp_result_image > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show = tmpstr;
	}
	else
	{
		;
		AfxMessageBox(AFX_IDP_PARSE_INT);
	}
	UpdateData(FALSE);

}


void CPage1::OnBnClickedRadioDiv()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		// TODO: �ڴ���ӿؼ�֪ͨ����������
		UpdateData(TRUE);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str1_r, str1_i, str2_r, str2_i;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str1_r);
		GetDlgItem(IDC_EDIT2)->GetWindowText(str1_i);
			GetDlgItem(IDC_EDIT3)->GetWindowText(str2_r);
				GetDlgItem(IDC_EDIT4)->GetWindowText(str2_i);
	if(m_ox == 1 && CheckDE(str1_r) && CheckDE(str1_i) && CheckDE(str2_r) && CheckDE(str2_i))
	{
		//����ʮ���Ƹ�����������
		float f1_r = _ttof(m_first_real);
		float f1_i = _ttof(m_first_image);
		float f2_r = _ttof(m_second_real);
		float f2_i = _ttof(m_second_image);
		float tmp = f2_r * f2_r + f2_i * f2_i;
		float f3_r = (f1_r * f2_r + f1_i * f2_i) / tmp;
		float f3_i = (f1_i * f2_r - f1_r * f2_i) / tmp;
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
			tmpstr += _T("\t\n /    \t");
		tmpstr += m_second_real;
		if(f2_i > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \n ");
		tmpstr += _T("------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(f3_i > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show = tmpstr;
	}
	else if(m_ox == 0 && CheckOX(str1_r) && CheckOX(str1_i) && CheckOX(str2_r) && CheckOX(str2_i))
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
			tmpstr += _T("\t\n /     \t");
		tmpstr += m_second_real;
		if(tmp_second_image > 0)
			tmpstr += _T("+");
		tmpstr += m_second_image;
		tmpstr += _T(" i ");
		tmpstr += _T(" \n ");
		tmpstr += _T("------------------------------");
		tmpstr += _T("\r\n ");
		tmpstr += m_result_real;
		if(tmp_result_image > 0)
			tmpstr += _T("+");
		tmpstr += m_result_image;
		tmpstr += _T(" i ");
		tmpstr += _T("\r\n");
		m_show = tmpstr;
	}
	else
	{
		;
		AfxMessageBox(AFX_IDP_PARSE_INT);
	}
	UpdateData(FALSE);
}
