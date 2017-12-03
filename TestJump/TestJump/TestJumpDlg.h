
// TestJumpDlg.h : 头文件
//

#pragma once


// CTestJumpDlg 对话框
class CTestJumpDlg : public CDialogEx
{
// 构造
public:
	CTestJumpDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTJUMP_DIALOG };

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
	int m_first;
	int m_second;
	int m_result;
	afx_msg void OnBnClickedRadioAdd();
	afx_msg void OnBnClickedRadioSub();
	afx_msg void OnBnClickedRadioMul();
	afx_msg void OnBnClickedRadioDev();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit4();
	CString m_string;
	CString m_list;
	CString m_combo;
};
