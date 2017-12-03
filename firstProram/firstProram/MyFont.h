#pragma once


// CMyFont 对话框

class CMyFont : public CDialogEx
{
	DECLARE_DYNAMIC(CMyFont)

public:
	CMyFont(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyFont();

// 对话框数据
	enum { IDD = IDD_DIALOG_FONT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFont();
	afx_msg void OnBnClickedColor();
};
