#pragma once
#include "afxwin.h"


// CPage1 对话框

class CPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPage1();

// 对话框数据
	enum { IDD = IDD_PAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_ox;
	afx_msg void OnBnClickedRadioOx();
	afx_msg void OnBnClickedRadioDe();
	afx_msg void OnBnClickedRadioBi();
	CString m_first_real;	//第一个数实部
	CString m_first_image;	//第一个数虚部
	CString m_second_real;	//第二个数实部
	CString m_second_image;	//第二个数虚部
	CString m_result_real;	//结果的实部
	CString m_result_image;	//结果的虚部
	CEdit m_f_r;//第一个数实部
	CEdit m_f_i;//第一个数虚部
	CEdit m_s_r;//第二个数实部
	CEdit m_s_i;//第二个数虚部
	CEdit m_r_r;//结果的实部
	CEdit m_r_i;//结果的虚部

	afx_msg void OnBnClickedRadioAdd();
	CString m_show;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadioSub();
	afx_msg void OnBnClickedRadioMul();
	afx_msg void OnBnClickedRadioDiv();
};
