#pragma once


// CcaozuoDlg �Ի���

class CcaozuoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CcaozuoDlg)

public:
	CcaozuoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CcaozuoDlg();

// �Ի�������
	enum { IDD = IDD_PANE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTaskSet();
	afx_msg void OnBnClickedButtonStation1();
	afx_msg void OnBnClickedButtonStation2();
	afx_msg void OnBnClickedButtonStation3();
	afx_msg void OnBnClickedButtonStation4();
	afx_msg void OnBnClickedButtonStation5();
	afx_msg void OnBnClickedButtonStation6();
	afx_msg void OnBnClickedButtonStation7();
	afx_msg void OnBnClickedButtonStation8();
	afx_msg void OnBnClickedButtonStation9();
	afx_msg void OnBnClickedButtonStation10();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_nClock;
};
