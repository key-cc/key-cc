// TAskSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BIYESHEJI.h"
#include "TAskSetDlg.h"
#include "afxdialogex.h"


// CTAskSetDlg 对话框

IMPLEMENT_DYNAMIC(CTAskSetDlg, CDialogEx)

CTAskSetDlg::CTAskSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTAskSetDlg::IDD, pParent)
	, m_strPeriod1(_T(""))
	, m_strPeriod2(_T(""))
	, m_strPeriod3(_T(""))
	, m_strPeriod4(_T(""))
	, m_strPeriod5(_T(""))
	, m_strPeriod6(_T(""))
	, m_strPeriod7(_T(""))
	, m_strPeriod8(_T(""))
	, m_strPeriod9(_T(""))
	, m_strPeriod10(_T(""))
	, m_bIsAuto(TRUE)
	, m_nScheduleGrade(0)
{

}

CTAskSetDlg::~CTAskSetDlg()
{
}

void CTAskSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PERIOD1, m_strPeriod1);
	DDX_Text(pDX, IDC_EDIT_PERIOD2, m_strPeriod2);
	DDX_Text(pDX, IDC_EDIT_PERIOD3, m_strPeriod3);
	DDX_Text(pDX, IDC_EDIT_PERIOD4, m_strPeriod4);
	DDX_Text(pDX, IDC_EDIT_PERIOD5, m_strPeriod5);
	DDX_Text(pDX, IDC_EDIT_PERIOD6, m_strPeriod6);
	DDX_Text(pDX, IDC_EDIT_PERIOD7, m_strPeriod7);
	DDX_Text(pDX, IDC_EDIT_PERIOD8, m_strPeriod8);
	DDX_Text(pDX, IDC_EDIT_PERIOD9, m_strPeriod9);
	DDX_Text(pDX, IDC_EDIT_PERIOD10, m_strPeriod10);
	DDX_Check(pDX, IDC_CHECK_AUTO, m_bIsAuto);
	DDV_MaxChars(pDX, m_strPeriod1, 5);
	DDX_Radio(pDX, IDC_RADIO_SCHEDULE_GRADE1, m_nScheduleGrade);
}


BEGIN_MESSAGE_MAP(CTAskSetDlg, CDialogEx)
END_MESSAGE_MAP()


// CTAskSetDlg 消息处理程序
