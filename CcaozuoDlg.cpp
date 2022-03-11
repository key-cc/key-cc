// CcaozuoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BIYESHEJI.h"
#include "CcaozuoDlg.h"
#include "afxdialogex.h"
#include"TAskSetDlg.h"
#include "MyDefine.h"
#include "Workshop.h"


extern CWorkshop theWorkShop;


// CcaozuoDlg 对话框

IMPLEMENT_DYNAMIC(CcaozuoDlg, CDialogEx)

CcaozuoDlg::CcaozuoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcaozuoDlg::IDD, pParent)
	, m_nClock(0)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CcaozuoDlg::~CcaozuoDlg()
{
}

void CcaozuoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CcaozuoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TASK_SET, &CcaozuoDlg::OnBnClickedButtonTaskSet)
	ON_BN_CLICKED(IDC_BUTTON_STATION1, &CcaozuoDlg::OnBnClickedButtonStation1)
	ON_BN_CLICKED(IDC_BUTTON_STATION2, &CcaozuoDlg::OnBnClickedButtonStation2)
	ON_BN_CLICKED(IDC_BUTTON_STATION3, &CcaozuoDlg::OnBnClickedButtonStation3)
	ON_BN_CLICKED(IDC_BUTTON_STATION4, &CcaozuoDlg::OnBnClickedButtonStation4)
	ON_BN_CLICKED(IDC_BUTTON_STATION5, &CcaozuoDlg::OnBnClickedButtonStation5)
	ON_BN_CLICKED(IDC_BUTTON_STATION6, &CcaozuoDlg::OnBnClickedButtonStation6)
	ON_BN_CLICKED(IDC_BUTTON_STATION7, &CcaozuoDlg::OnBnClickedButtonStation7)
	ON_BN_CLICKED(IDC_BUTTON_STATION8, &CcaozuoDlg::OnBnClickedButtonStation8)
	ON_BN_CLICKED(IDC_BUTTON_STATION9, &CcaozuoDlg::OnBnClickedButtonStation9)
	ON_BN_CLICKED(IDC_BUTTON_STATION10, &CcaozuoDlg::OnBnClickedButtonStation10)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CcaozuoDlg::OnBnClickedButtonReset)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CcaozuoDlg 消息处理程序


void CcaozuoDlg::OnBnClickedButtonTaskSet()
{
	CTAskSetDlg dlg;
	dlg.m_strPeriod1.Format(_T("%4.1lf"), theWorkShop.m_Station[0].m_nPeriod*0.001);
	dlg.m_strPeriod2.Format(_T("%4.1lf"), theWorkShop.m_Station[1].m_nPeriod*0.001);
	dlg.m_strPeriod3.Format(_T("%4.1lf"), theWorkShop.m_Station[2].m_nPeriod*0.001);
	dlg.m_strPeriod4.Format(_T("%4.1lf"), theWorkShop.m_Station[3].m_nPeriod*0.001);
	dlg.m_strPeriod5.Format(_T("%4.1lf"), theWorkShop.m_Station[4].m_nPeriod*0.001);
	dlg.m_strPeriod6.Format(_T("%4.1lf"), theWorkShop.m_Station[5].m_nPeriod*0.001);
	dlg.m_strPeriod7.Format(_T("%4.1lf"), theWorkShop.m_Station[6].m_nPeriod*0.001);
	dlg.m_strPeriod8.Format(_T("%4.1lf"), theWorkShop.m_Station[7].m_nPeriod*0.001);
	dlg.m_strPeriod9.Format(_T("%4.1lf"), theWorkShop.m_Station[8].m_nPeriod*0.001);
	dlg.m_strPeriod10.Format(_T("%4.1lf"), theWorkShop.m_Station[9].m_nPeriod*0.001);

	dlg.m_nScheduleGrade = theWorkShop.m_nScheduleGrade;
	if (dlg.DoModal() == IDOK)
	{
		theWorkShop.m_Station[0].m_nPeriod = _wtof(dlg.m_strPeriod1.GetBuffer()) * 1000;
		theWorkShop.m_Station[1].m_nPeriod = _wtof(dlg.m_strPeriod2.GetBuffer()) * 1000;
		theWorkShop.m_Station[2].m_nPeriod = _wtof(dlg.m_strPeriod3.GetBuffer()) * 1000;
		theWorkShop.m_Station[3].m_nPeriod = _wtof(dlg.m_strPeriod4.GetBuffer()) * 1000;
		theWorkShop.m_Station[4].m_nPeriod = _wtof(dlg.m_strPeriod5.GetBuffer()) * 1000;
		theWorkShop.m_Station[5].m_nPeriod = _wtof(dlg.m_strPeriod6.GetBuffer()) * 1000;
		theWorkShop.m_Station[6].m_nPeriod = _wtof(dlg.m_strPeriod7.GetBuffer()) * 1000;
		theWorkShop.m_Station[7].m_nPeriod = _wtof(dlg.m_strPeriod8.GetBuffer()) * 1000;
		theWorkShop.m_Station[8].m_nPeriod = _wtof(dlg.m_strPeriod9.GetBuffer()) * 1000;
		theWorkShop.m_Station[9].m_nPeriod = _wtof(dlg.m_strPeriod10.GetBuffer()) * 1000;

		theWorkShop.m_nScheduleGrade = dlg.m_nScheduleGrade;
		if (!dlg.m_bIsAuto)
		{
			for (int i = 1; i<11; i++)
				KillTimer(i);
			return;
		}


		if (theWorkShop.m_Station[0].m_nPeriod >= 1000)
		{
			SetTimer(1, theWorkShop.m_Station[0].m_nPeriod, NULL);
		}
		else
		{
			KillTimer(1);
		}
		if (theWorkShop.m_Station[1].m_nPeriod >= 1000)
		{
			SetTimer(2, theWorkShop.m_Station[1].m_nPeriod, NULL);
		}
		else
		{
			KillTimer(2);
		}
		if (theWorkShop.m_Station[2].m_nPeriod >= 1000)
		{
			SetTimer(3, theWorkShop.m_Station[2].m_nPeriod, NULL);
		}
		else
		{
			KillTimer(3);
		}
		if (theWorkShop.m_Station[3].m_nPeriod >= 1000)
		{
			SetTimer(4, theWorkShop.m_Station[3].m_nPeriod, NULL);
		}
		else
		{
			KillTimer(4);
		}
		if (theWorkShop.m_Station[4].m_nPeriod >= 1000)
		{
			SetTimer(5, theWorkShop.m_Station[4].m_nPeriod, NULL);
		}
		else
		{
			KillTimer(5);
		}
		if (theWorkShop.m_Station[5].m_nPeriod >= 1000)
		{
			SetTimer(6, theWorkShop.m_Station[5].m_nPeriod, NULL);
		}
		else
		{
			KillTimer(6);
		}
		if (theWorkShop.m_Station[6].m_nPeriod >= 1000)
		{
			SetTimer(7, theWorkShop.m_Station[6].m_nPeriod, NULL);
		}
		else
		{
			KillTimer(7);
		}
		if (theWorkShop.m_Station[7].m_nPeriod >= 1000)
		{
			SetTimer(8, theWorkShop.m_Station[7].m_nPeriod, NULL);
		}
		else
		{
			KillTimer(8);
		}

		if (theWorkShop.m_Station[8].m_nPeriod >= 1000)
		{
			SetTimer(9, theWorkShop.m_Station[8].m_nPeriod, NULL);
		}
		else
		{
			KillTimer(9);
		}
		if (theWorkShop.m_Station[9].m_nPeriod >= 1000)
		{
			SetTimer(10, theWorkShop.m_Station[9].m_nPeriod, NULL);
		}
		else
		{
			KillTimer(10);
		}
	}
}





void CcaozuoDlg::OnBnClickedButtonStation1()
{
	// TODO:  在此添加控件通知处理程序代码
	theWorkShop.m_BucketSorter[0].AddBucket();
}


void CcaozuoDlg::OnBnClickedButtonStation2()
{
	// TODO:  在此添加控件通知处理程序代码
	theWorkShop.m_BucketSorter[1].AddBucket();
}


void CcaozuoDlg::OnBnClickedButtonStation3()
{
	// TODO:  在此添加控件通知处理程序代码
	theWorkShop.m_BucketSorter[2].AddBucket();
}


void CcaozuoDlg::OnBnClickedButtonStation4()
{
	// TODO:  在此添加控件通知处理程序代码
	theWorkShop.m_BucketSorter[3].AddBucket();
}


void CcaozuoDlg::OnBnClickedButtonStation5()
{
	// TODO:  在此添加控件通知处理程序代码
	theWorkShop.m_BucketSorter[4].AddBucket();
}


void CcaozuoDlg::OnBnClickedButtonStation6()
{
	// TODO:  在此添加控件通知处理程序代码
	theWorkShop.m_BucketSorter[5].AddBucket();
}


void CcaozuoDlg::OnBnClickedButtonStation7()
{
	// TODO:  在此添加控件通知处理程序代码
	theWorkShop.m_Station[6].Requst();
}


void CcaozuoDlg::OnBnClickedButtonStation8()
{
	// TODO:  在此添加控件通知处理程序代码
	theWorkShop.m_Station[7].Requst();
}


void CcaozuoDlg::OnBnClickedButtonStation9()
{
	// TODO:  在此添加控件通知处理程序代码
	theWorkShop.m_Station[8].Requst();
}


void CcaozuoDlg::OnBnClickedButtonStation10()
{
	// TODO:  在此添加控件通知处理程序代码
	theWorkShop.m_Station[9].Requst();
}


void CcaozuoDlg::OnBnClickedButtonReset()
{
	// TODO:  在此添加控件通知处理程序代码
	for (int i = 0; i<VEHICLE_NUM; i++)
	{
		theWorkShop.m_Vehicle[i].SetObject(0);
		theWorkShop.m_Vehicle[i].m_nRunMode = VEHICLE_MOVE_ONLY;
		theWorkShop.m_Vehicle[i].m_nStationNo = -1;
		theWorkShop.m_Vehicle[i].m_bIsBucket = FALSE;
	}
	for (int i = 0; i<STATION_NUM; i++)
	{
		theWorkShop.m_Station[i].m_nVehicleNo = -1;
		theWorkShop.m_Station[i].m_bIsBucket = FALSE;

	}
}


void CcaozuoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 15)
	{
		m_nClock++;
		if (m_nClock >= CLOCK_MAX)
		{
			m_nClock = 0;
		}
		theWorkShop.CalcuState(m_nClock);

		/*
		for(int i=0;i<10;i++)
		{
		theWorkShop.m_Station[i].CalcuState(m_nClock);
		}
		for(int i=0;i<10;i++)
		{

		theWorkShop.m_Vehicle[i].CalcuState(m_nClock);
		}*/

	}
	else if (nIDEvent == 1)
	{
		OnBnClickedButtonStation1();
	}
	else if (nIDEvent == 2)
	{
		OnBnClickedButtonStation2();
	}
	else if (nIDEvent == 3)
	{
		OnBnClickedButtonStation3();
	}
	else if (nIDEvent == 4)
	{
		OnBnClickedButtonStation4();
	}
	else if (nIDEvent == 5)
	{
		OnBnClickedButtonStation5();
	}
	else if (nIDEvent == 6)
	{
		OnBnClickedButtonStation6();
	}
	else if (nIDEvent == 7)
	{
		OnBnClickedButtonStation7();
	}
	else if (nIDEvent == 8)
	{
		OnBnClickedButtonStation8();
	}
	else if (nIDEvent == 9)
	{
		OnBnClickedButtonStation9();
	}
	else if (nIDEvent == 10)
	{
		OnBnClickedButtonStation10();
	}
	else
	{
		;
	}
	Invalidate();


	CDialogEx::OnTimer(nIDEvent);
}
