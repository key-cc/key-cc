#pragma once


// CStationOp �Ի���

class CStationOp : public CDialogEx
{
	DECLARE_DYNAMIC(CStationOp)

public:
	CStationOp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStationOp();

// �Ի�������
	enum { IDD = IDD_DIALOG_STATION_OP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButtonBucket();
	afx_msg void OnBnClickedButtonMove();
};
