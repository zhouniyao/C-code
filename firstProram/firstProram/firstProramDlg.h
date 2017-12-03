
// firstProramDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CfirstProramDlg �Ի���
class CfirstProramDlg : public CDialogEx
{
// ����
public:
	CfirstProramDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FIRSTPRORAM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMenu m_menu;
	CString tmpstr;
	afx_msg void OnIdrBg1();
	CString m_show;
	CButton m_sexadecimal;
	CButton m_decimal;
	CButton m_binary;
	CButton m_add;
	CButton m_sub;
	CButton m_mul;
	CButton m_div;
	CString m_first_real;
	CString m_first_image;
	CString m_second_real;
	CString m_second_image;
	CString m_result_real;
	CString m_result_image;
	afx_msg void OnBnClickedRadioDe();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_ox;
	afx_msg void OnBnClickedRadioOx();
	afx_msg void OnBnClickedRadioSe();
	afx_msg void OnBnClickedRadioAdd();
	afx_msg void OnBnClickedRadioSub();
	afx_msg void OnBnClickedRadioMul();
	afx_msg void OnBnClickedRadioDiv();
	bool CheckIsComplex(CString& str);
	afx_msg void On32774();
	afx_msg void OnBnClickedButton2();
	afx_msg void On32773();
	afx_msg void On32771();
	afx_msg void On32772();
	CEdit m_Edit;
};
