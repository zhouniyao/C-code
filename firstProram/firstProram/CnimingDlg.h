#pragma once
#include "afxcmn.h"


// CnimingDlg 对话框

class CnimingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CnimingDlg)

public:
	CnimingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CnimingDlg();

// 对话框数据
	enum { IDD = IDD_NMDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl m_tab;
};
