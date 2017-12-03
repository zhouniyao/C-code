
// NMTABProgramDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "Page1.h"
#include "Page2.h"

// CNMTABProgramDlg �Ի���
class CNMTABProgramDlg : public CDialogEx
{
// ����
public:
	CNMTABProgramDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NMTABPROGRAM_DIALOG };

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
	CTabCtrl m_tab;
	CDialog* pDialog[2];  //��������Ի������ָ��
	int m_CurSelTab;
    CPage1 m_page1;
    CPage2 m_page2;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
