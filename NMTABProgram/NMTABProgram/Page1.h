#pragma once
#include "afxwin.h"


// CPage1 �Ի���

class CPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPage1();

// �Ի�������
	enum { IDD = IDD_PAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_ox;
	afx_msg void OnBnClickedRadioOx();
	afx_msg void OnBnClickedRadioDe();
	afx_msg void OnBnClickedRadioBi();
	CString m_first_real;	//��һ����ʵ��
	CString m_first_image;	//��һ�����鲿
	CString m_second_real;	//�ڶ�����ʵ��
	CString m_second_image;	//�ڶ������鲿
	CString m_result_real;	//�����ʵ��
	CString m_result_image;	//������鲿
	CEdit m_f_r;//��һ����ʵ��
	CEdit m_f_i;//��һ�����鲿
	CEdit m_s_r;//�ڶ�����ʵ��
	CEdit m_s_i;//�ڶ������鲿
	CEdit m_r_r;//�����ʵ��
	CEdit m_r_i;//������鲿

	afx_msg void OnBnClickedRadioAdd();
	CString m_show;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadioSub();
	afx_msg void OnBnClickedRadioMul();
	afx_msg void OnBnClickedRadioDiv();
};
