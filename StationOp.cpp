// StationOp.cpp : 实现文件
//

#include "stdafx.h"
#include "BIYESHEJI.h"
#include "StationOp.h"
#include "afxdialogex.h"
#include "Workshop.h"


extern CWorkshop theWorkShop;

// CStationOp 对话框

IMPLEMENT_DYNAMIC(CStationOp, CDialogEx)

CStationOp::CStationOp(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStationOp::IDD, pParent)
{

}

CStationOp::~CStationOp()
{
}

void CStationOp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStationOp, CDialogEx)
	ON_BN_CLICKED(IDC_Button_Bucket, &CStationOp::OnBnClickedButtonBucket)
	ON_BN_CLICKED(IDC_Button_Move, &CStationOp::OnBnClickedButtonMove)
END_MESSAGE_MAP()


// CStationOp 消息处理程序



void CStationOp::OnBnClickedButtonBucket()
{
	for (int i = 0; i<10; i++)
	{
		theWorkShop.m_Station[i].BucketReady();
	}
	// TODO:  在此添加控件通知处理程序代码
}


void CStationOp::OnBnClickedButtonMove()
{
	
	for (int i = 0; i<10; i++)
	{
		theWorkShop.m_Station[i].BucketMove();
	}
	// TODO:  在此添加控件通知处理程序代码
}
