#pragma once
#include "afxcmn.h"


// CnimingDlg �Ի���

class CnimingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CnimingDlg)

public:
	CnimingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CnimingDlg();

// �Ի�������
	enum { IDD = IDD_NMDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl m_tab;
};
