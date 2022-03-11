// BCAAView.h : interface of the COpenGLView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLVIEW_H__EF3ED2B3_26FD_4C00_A901_60848E110E18__INCLUDED_)
#define AFX_OPENGLVIEW_H__EF3ED2B3_26FD_4C00_A901_60848E110E18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "BIYESHEJI.h"
#endif

#include "BIYESHEJIDoc.h"
#include "Fpoint.h"
#include "trackball.h"

#define THE_DOC CBIYESHEJIDoc

#define FONTLISTBASE 1000		  //字体列表基数；

class C3dAxis;

class COpenGLView : public CView
{
protected: // create from serialization only
public:
	COpenGLView();
	DECLARE_DYNCREATE(COpenGLView)

	// Attributes
public:
	CBIYESHEJIDoc* GetDocument();

	// Operations
public:
	int m_nClock;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGLView)
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:
	bool m_bViewTargetPunch;

	void DisplayHintInfo();
	void SetPunchQiuTouColor(int status);
	void SetPunchZhuTiColor(int status);
	void OnUpdateRestorePunchButton(CCmdUI *pCmdUI);
	BOOL m_bDispalyDownMoudle;
	BOOL m_bDispalyUpMoudle;
	void SetOpenGLColor(GLfloat color[4], float r, float g, float b, float a = 1.0f);
	void DrawObject(int flag = 0);
	void RestoreAllDefaultColors();
	//	void DrawPunch(double x, double y, double z,double h,int status,bool flag);
	//	void DrawWell(double x, double y, double z,double h,double R0,double R1,bool status);
	//	void DrawSwing(double h,double Angle,bool status);
	void DecideOpenGLScale();
	void DisplayScaleRuler();
	void InitGeometry();
	void DrawAxis();
	double m_OffsetPunchZ;	//显示冲头时的偏移量；
	double m_OffsetPunchZ_Step;	 //显示冲头时的偏移量每次增加的步长(OnInitialUpdate()中初始化；

	CString m_HintInfo;

	// Mouse 
	BOOL m_bLeftButtonDown;
	BOOL m_bRightButtonDown;
	CPoint m_LeftDownPos;
	CPoint m_RightDownPos;
	float m_xRotation;
	float m_yRotation;
	float m_zRotation;	//我加的；
	float m_xTranslation;
	float m_yTranslation;
	float m_zTranslation;
	float m_glScale, m_glOrgScale;


	int Angle;

	//所用到的颜色值；
	GLfloat m_diffuse_CamSurface[4];
	GLfloat m_diffuse_CamRound[4];
	GLfloat m_diffuse_CamAxis[4];
	GLfloat m_diffuse_ToolSurface[4];
	GLfloat m_diffuse_ToolRound[4];
	GLfloat m_diffuse_ModifiedPunchZhuTi[4];
	GLfloat m_diffuse_BadPunchQiuTou[4];

	//状态变量；
	BOOL m_bDisplayAxis;	   //是否显示坐标系；
	BOOL m_bDisplayHintInfo;	//是否显示提示信息；
	BOOL m_bDisplayOriginPoint;	   //是否显示原点；
	BOOL m_bDisplayScaleRuler;	   //是否显示比例尺；
	BOOL m_bDisplayPointNumber;	   //是否显示点标号；

	BOOL m_bRender;	   //是否采用光照模型；
	BOOL m_bSelected;	//是否进入选择状态；
	BOOL m_bMouseMove;		 //用鼠标移动物体；
	//	BOOL m_bModifyPart;		 //是否在调整工件；
	//////////////////////
	float matRot[4][4];
	BOOL DrawScene();
	double m_lmax;
	double m_Range;
	CDRect m_GLWindowClientRect;   //记录当前窗口的实际坐标。
	C3dAxis* m_pAxis;		// Axis pointer
	CTrackBall m_TrackBall;
	COLORREF m_BackgroundColor;
	COLORREF m_TextColor;
	COLORREF m_LineColor;
	CRect  m_oldRect;
	HGLRC m_hGLContext;
	void InitOpenGL();
	virtual ~COpenGLView();
	double DegreeCos(double fDegree);
	double DegreeSin(double fDegree);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(COpenGLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRestorePunchButton();
	afx_msg void OnDeltaposPunchOffsetSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDisplayaxisButton();
	afx_msg void OnInitgeographicsButton();
	afx_msg void OnModifytoxyButton();
	afx_msg void OnModifytoyzButton();
	afx_msg void OnModifytozxButton();
	afx_msg void OnMoveanywhereButton();
	afx_msg void OnOverturnButton();
	afx_msg void OnUpdownoverturnButton();
	afx_msg void OnZoomoutButton();
	afx_msg void OnZoominButton();
	afx_msg void OnRotatedownButton();
	afx_msg void OnRotateleftButton();
	afx_msg void OnRotaterightButton();
	afx_msg void OnRotateupButton();
	afx_msg void OnUpdateDisplayaxisButton(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMoveanywhereButton(CCmdUI* pCmdUI);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnViewtargetpunchButton();
	afx_msg void OnUpdateViewtargetpunchButton(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUpmoudleCheck(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDownmoudleCheck(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

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
	afx_msg void OnBnClickedButtonSetPos();
	afx_msg void OnBnClickedButtonTaskSet();
	afx_msg void OnOpStation();
};

#ifndef _DEBUG  // debug version in BCAAView.cpp
inline CRgvManagerDoc* COpenGLView::GetDocument()
{
	return (CRgvManagerDoc*)m_pDocument;
}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCAAVIEW_H__EF3ED2B3_26FD_4C00_A901_60848E110E18__INCLUDED_)
