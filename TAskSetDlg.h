#pragma once


// CTAskSetDlg �Ի���

class CTAskSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTAskSetDlg)

public:
	CTAskSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTAskSetDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_TASK_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strPeriod1;
	CString m_strPeriod2;
	CString m_strPeriod3;
	CString m_strPeriod4;
	CString m_strPeriod5;
	CString m_strPeriod6;
	CString m_strPeriod7;
	CString m_strPeriod8;
	CString m_strPeriod9;
	CString m_strPeriod10;
	BOOL m_bIsAuto;
	int m_nScheduleGrade;
};
