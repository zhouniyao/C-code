
// TestJumpDlg.h : ͷ�ļ�
//

#pragma once


// CTestJumpDlg �Ի���
class CTestJumpDlg : public CDialogEx
{
// ����
public:
	CTestJumpDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTJUMP_DIALOG };

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
