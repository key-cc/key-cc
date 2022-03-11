#pragma once


// CStationOp 对话框

class CStationOp : public CDialogEx
{
	DECLARE_DYNAMIC(CStationOp)

public:
	CStationOp(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStationOp();

// 对话框数据
	enum { IDD = IDD_DIALOG_STATION_OP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButtonBucket();
	afx_msg void OnBnClickedButtonMove();
};
