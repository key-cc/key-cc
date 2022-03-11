// StationOp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BIYESHEJI.h"
#include "StationOp.h"
#include "afxdialogex.h"
#include "Workshop.h"


extern CWorkshop theWorkShop;

// CStationOp �Ի���

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


// CStationOp ��Ϣ�������



void CStationOp::OnBnClickedButtonBucket()
{
	for (int i = 0; i<10; i++)
	{
		theWorkShop.m_Station[i].BucketReady();
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CStationOp::OnBnClickedButtonMove()
{
	
	for (int i = 0; i<10; i++)
	{
		theWorkShop.m_Station[i].BucketMove();
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
