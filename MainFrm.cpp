
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "BIYESHEJI.h"

#include "MainFrm.h"
#include"CcaozuoDlg.h"
#include "Workshop.h"
#include <stdlib.h>
#include "MyDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
extern CWorkshop theWorkShop;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_PANE, &CMainFrame::OnViewPane)
	ON_BN_CLICKED(IDC_BUTTON_GET_POS, &CMainFrame::OnBnClickedButtonGetPos)
	ON_BN_CLICKED(IDC_BUTTON_SET_POS, &CMainFrame::OnBnClickedButtonSetPos)
	ON_BN_CLICKED(IDC_BUTTON_WAIT_COMMAND, &CMainFrame::OnBnClickedButtonWaitCommand)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// TODO:  �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������






void CMainFrame::OnViewPane()
{
	CcaozuoDlg dlg;
	dlg.DoModal();
	// TODO:  �ڴ���������������
}


void CMainFrame::OnBnClickedButtonGetPos()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMainFrame::OnBnClickedButtonSetPos()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMainFrame::OnBnClickedButtonWaitCommand()
{
	theWorkShop.WaitCommand();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
