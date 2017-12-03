
// NMTABProgramDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "Page1.h"
#include "Page2.h"

// CNMTABProgramDlg 对话框
class CNMTABProgramDlg : public CDialogEx
{
// 构造
public:
	CNMTABProgramDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NMTABPROGRAM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	CDialog* pDialog[2];  //用来保存对话框对象指针
	int m_CurSelTab;
    CPage1 m_page1;
    CPage2 m_page2;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
