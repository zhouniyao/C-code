#pragma once


// CMyFont �Ի���

class CMyFont : public CDialogEx
{
	DECLARE_DYNAMIC(CMyFont)

public:
	CMyFont(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyFont();

// �Ի�������
	enum { IDD = IDD_DIALOG_FONT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFont();
	afx_msg void OnBnClickedColor();
};
