
// BIYESHEJI.h : BIYESHEJI Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CBIYESHEJIApp:
// �йش����ʵ�֣������ BIYESHEJI.cpp
//

class CBIYESHEJIApp : public CWinAppEx
{
public:
	CBIYESHEJIApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;




	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBIYESHEJIApp theApp;