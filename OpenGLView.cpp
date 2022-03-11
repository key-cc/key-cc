// OpenGLView.cpp : implementation of the COpenGLView class
//
/////
#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "BIYESHEJI.h"
#endif

#include "BIYESHEJIDoc.h"
#include "OpenGLView.h"
#include "3dAxis.h"
#include <math.h>
#include "Workshop.h"
#include "MyDefine.h"
#include "StationOp.h"
#include "TAskSetDlg.h"


//////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CWorkshop theWorkShop;

/////////////////////////////////////////////////////////////////////////////
// COpenGLView


IMPLEMENT_DYNCREATE(COpenGLView, CView)

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	//{{AFX_MSG_MAP(COpenGLView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	//自己加的；
ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTTON_STATION1, &COpenGLView::OnBnClickedButtonStation1)
ON_BN_CLICKED(IDC_BUTTON_STATION2, &COpenGLView::OnBnClickedButtonStation2)
ON_BN_CLICKED(IDC_BUTTON_STATION3, &COpenGLView::OnBnClickedButtonStation3)
ON_BN_CLICKED(IDC_BUTTON_STATION4, &COpenGLView::OnBnClickedButtonStation4)
ON_BN_CLICKED(IDC_BUTTON_STATION5, &COpenGLView::OnBnClickedButtonStation5)
ON_BN_CLICKED(IDC_BUTTON_STATION6, &COpenGLView::OnBnClickedButtonStation6)
ON_BN_CLICKED(IDC_BUTTON_STATION7, &COpenGLView::OnBnClickedButtonStation7)
ON_BN_CLICKED(IDC_BUTTON_STATION8, &COpenGLView::OnBnClickedButtonStation8)
ON_BN_CLICKED(IDC_BUTTON_STATION9, &COpenGLView::OnBnClickedButtonStation9)
ON_BN_CLICKED(IDC_BUTTON_STATION10, &COpenGLView::OnBnClickedButtonStation10)
ON_BN_CLICKED(IDC_BUTTON_TASK_SET, &COpenGLView::OnBnClickedButtonTaskSet)
ON_COMMAND(ID_OP_STATION, &COpenGLView::OnOpStation)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLView construction/destruction

COpenGLView::COpenGLView()
{
	// TODO: add construction code here
	m_BackgroundColor=RGB(255,255,255);
	m_TextColor=RGB(0,255,255);
	m_LineColor=RGB(255,255,0);

    m_TrackBall.Init(m_oldRect.right,m_oldRect.bottom);
//	Initquat(60,45,30);
	m_TrackBall.Initquat(60,30,16);
	
	///////////////////////////
	//OpenGL 初始化；
	m_hGLContext=NULL;
	m_bLeftButtonDown = FALSE;
	m_Range=50000.0;	//控制工件显示大小；

	m_OffsetPunchZ=0.0;
	// Create a Axis class
	m_pAxis = C3dAxis::Create();
	ASSERT(m_pAxis);

	RestoreAllDefaultColors();	 //颜色初始化；

	InitGeometry();

	DecideOpenGLScale();
	Angle=0;
	m_nClock = 0;
}

COpenGLView::~COpenGLView()
{
	// Delete the C3dAxis attached to the world
	
	if(m_pAxis) {
		delete m_pAxis;
		m_pAxis = NULL;
	}
}

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView drawing

void COpenGLView::OnDraw(CDC* pDC)
{
	THE_DOC* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	::wglMakeCurrent(pDC->GetSafeHdc(),m_hGLContext);

	DrawScene();
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView printing

BOOL COpenGLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView diagnostics

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

THE_DOC* COpenGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(THE_DOC)));
	return (THE_DOC*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenGLView message handlers

void COpenGLView::InitOpenGL()
{
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

    static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
        1,                              // version number
        PFD_DRAW_TO_WINDOW |            // support window
          PFD_SUPPORT_OPENGL |          // support OpenGL
          PFD_DOUBLEBUFFER,             // double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        32,                             // 32-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };
    int pixelformat;

    if ( (pixelformat = ChoosePixelFormat(hDC, &pfd)) == 0 )
    {
        MessageBox(_T("ChoosePixelFormat failed"));
        return;
    }

    if (SetPixelFormat(hDC, pixelformat, &pfd) == FALSE)
    {
        MessageBox(_T("SetPixelFormat failed"));
        return;
    }

	GLfloat		fMaxObjSize, fAspect;
	GLfloat		fNearPlane, fFarPlane;

	//note:对多文档的View，wglMakeCurrent()应在OnDraw中出现；
	m_hGLContext = ::wglCreateContext(hDC);
	if(m_hGLContext==NULL) return;
	if(::wglMakeCurrent(hDC,m_hGLContext)==FALSE) return;

    GetClientRect(&m_oldRect);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);

	if (m_oldRect.bottom)
		fAspect = (GLfloat)m_oldRect.right/m_oldRect.bottom;
	else	// don't divide by zero, not that we should ever run into that...
		fAspect = 1.0f;
	fNearPlane = 3.0f;
	fFarPlane = 7.0f;
	fMaxObjSize = 3.0f;
//	m_fRadius = fNearPlane + fMaxObjSize / 2.0f;
	//////////////////////////////////
	//构造光源；
//	GLfloat light_position[]={100.0,50.0,10.0,0.0};
	GLfloat light_position[]={150.0,0.0,150.0,0.0};	//原来的；
	GLfloat light_ambient[]={0.2f,0.2f,0.2f,1.0};
	GLfloat light_diffuse[]={0.8f,0.8f,0.8f,1.0};
	GLfloat light_specular[]={1.0,1.0,1.0,1.0};
	GLfloat light_direction[]={0.0,0.0,-1.0};

	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
 	
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,light_direction);
  	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,0.0);
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,180);

	glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,1.0);
	glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,0.0);
	glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,0.0);

	glEnable(GL_LIGHT0);


	static float lmodel_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
//	static float lmodel_twoside[] = {GL_TRUE};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
//	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);
	glEnable(GL_NORMALIZE);
//	glEnable(GL_AUTO_NORMAL);
	glShadeModel(GL_SMOOTH);

	//创建字体列表；
//	SelectObject(hDC,GetStockObject(SYSTEM_FONT));
	wglUseFontBitmaps(hDC,0,255,FONTLISTBASE);	
	/////////////////////////////////
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	fAspect = 5.0;
    gluPerspective(45.0f, fAspect, fNearPlane, fFarPlane);
    glMatrixMode(GL_MODELVIEW);
}

int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	DragAcceptFiles();
	
	InitOpenGL();

	return 0;
}

void COpenGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	//使用客户区的值，否则不准；
	CRect rect;
	GetClientRect(&rect);
	cx=rect.right;
	cy=rect.bottom;

    m_TrackBall.Resize( cx, cy );
//	TRACE("cx=%d;cy=%d\n",cx,cy);
    if(cy > 0)
    {    
		//必须成为当前值，GL各函数才能生效！！！！！！
		HWND hWnd = GetSafeHwnd();
		HDC hDC = ::GetDC(hWnd);
		::wglMakeCurrent(hDC,m_hGLContext);

        glViewport(0, 0, cx, cy);

        if((m_oldRect.right > cx) || (m_oldRect.bottom > cy))
            RedrawWindow();

        m_oldRect.right = cx;
        m_oldRect.bottom = cy;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
		double lmax=m_Range/2.0;
		#define XS 20.0
		if(cx<=cy)
		{
			glOrtho(-lmax,lmax,-lmax*(GLfloat)cy/(GLfloat)cx, 
					lmax*(GLfloat)cy/(GLfloat)cx,-lmax*XS,lmax*XS); 
			//记录当前窗口的实际坐标。
			m_GLWindowClientRect.left=-lmax;
			m_GLWindowClientRect.bottom=-lmax*(GLfloat)cy/(GLfloat)cx;
			m_GLWindowClientRect.right=lmax;
			m_GLWindowClientRect.top=lmax*(GLfloat)cy/(GLfloat)cx;
		}
		else
		{
			glOrtho(-lmax*(GLfloat)cx/(GLfloat)cy, 
					lmax*(GLfloat)cx/(GLfloat)cy,-lmax,lmax,-lmax*XS,lmax*XS); 
			//记录当前窗口的实际坐标。
			m_GLWindowClientRect.left=-lmax*(GLfloat)cx/(GLfloat)cy;
			m_GLWindowClientRect.bottom=-lmax;
			m_GLWindowClientRect.right=lmax*(GLfloat)cx/(GLfloat)cy;
			m_GLWindowClientRect.top=lmax;
		}

		glMatrixMode(GL_MODELVIEW);
		InvalidateRect(NULL,FALSE);
    }
}

BOOL COpenGLView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	
	return CView::OnEraseBkgnd(pDC);
}

BOOL COpenGLView::DrawScene()
{
	THE_DOC* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(m_glScale==0.0) return TRUE;	//比例出错拉，看CMy1997Doc::DecideOpenGLScale()函数；

	glClearColor(GetRValue(m_BackgroundColor)/255.0f, 
		GetGValue(m_BackgroundColor)/255.0f,
		GetBValue(m_BackgroundColor)/255.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glLoadIdentity();

	//鼠标移动物体时，不计算matRot，否则m_LeftDownPos冲突；
	//计算、更新旋转距阵(此处应是唯一修改matRot的地方)；
	if(!m_bMouseMove) m_TrackBall.CalcRotMatrix(matRot,m_LeftDownPos);

	glTranslated(m_xTranslation,m_yTranslation,m_zTranslation);
    glMultMatrixf(&(matRot[0][0]));
	glScalef(m_glScale,m_glScale,m_glScale);
	glColor3f(GetRValue(m_LineColor)/255.0f, 
		GetGValue(m_LineColor)/255.0f,
		GetBValue(m_LineColor)/255.0f);

	/////////////////////////////
	//此部分为绘图核心部分
	
	 DrawObject();

	/////////////////////
	//画一些标记性物体；(原点、坐标系、比例尺)
	//最后画，以免被覆盖
	
//	if(m_bRender==TRUE)	glDisable(GL_LIGHTING);	 //不要光照；
//	glPushMatrix();
	glLoadIdentity();
    glDisable(GL_DEPTH_TEST);	//避免被覆盖；

	//写提示信息文字；
//	if(m_bDisplayHintInfo) DisplayHintInfo();
	//画比例尺；
	if(m_bDisplayScaleRuler) DisplayScaleRuler();
	//画原点；
//	if(m_bDisplayOriginPoint) DisplayOriginPoint();
	//绘制坐标系；
	if(m_bDisplayAxis) DrawAxis();	

	glEnable(GL_DEPTH_TEST);

	glFinish();
	SwapBuffers(wglGetCurrentDC());
	return TRUE;
}

void COpenGLView::DrawAxis()
{
#define AXISLENGTH 5000.0f	   //坐标轴长度；
#define AXISLOCATION 6000.0f		   //坐标轴定位；
#define AXISWORDLOCATION 6000.0f		   //文字定位；
	//	m_AxisScene=glGenLists(1);
	
	//	glNewList(m_AxisScene,GL_COMPILE);
	glPushMatrix();
	glLoadIdentity();
	
    glClearDepth(1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);	//保证不被覆盖；
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);	 //不要光照；
	glTranslated(m_GLWindowClientRect.left+AXISLOCATION,m_GLWindowClientRect.bottom+AXISLOCATION,0.0);

    glMultMatrixf(&(matRot[0][0]) );
	/////////////
	CString str;
//	glColor3f(1.0,1.0,0.0);
	glColor3f(GetRValue(m_TextColor)/255.0f, 
		GetGValue(m_TextColor)/255.0f,
		GetBValue(m_TextColor)/255.0f);

	glListBase(FONTLISTBASE);
	
	glRasterPos3d(AXISWORDLOCATION,0,0);
	str.Format(_T("X"));
	glCallLists(str.GetLength(), GL_UNSIGNED_BYTE, str); 

	glRasterPos3d(0,AXISWORDLOCATION,0);
	str.Format(_T("Y"));
	glCallLists(str.GetLength(), GL_UNSIGNED_BYTE, str); 

	glRasterPos3d(0,0,AXISWORDLOCATION);
	str.Format(_T("Z"));
	glCallLists(str.GetLength(), GL_UNSIGNED_BYTE, str); 
	//////////////
	glEnable(GL_LIGHTING);	 //光照；
	// Display the World X, Y, Z Origin Axis
	m_pAxis->Display( AXISLENGTH,	// Axis length
					  250.0f,			// Axis diameter
					  1250.0f,			// Arrow length
					  600.0f,		// Arrow diameter
					  20,			// Number of slices around dia.
					  100,			// Number of Stacks about length
					  NULL,			// X-Axis Color (Use Defaults..)
					  NULL,			// Y-Axis Color
					  NULL,			// Z-Axis Color
					  TRUE);		// Display as Solid

	glPopMatrix();
}

void COpenGLView::InitGeometry()
{
	m_xRotation = 0.0f;
	m_yRotation = 0.0f;
	m_zRotation = 0.0f;	//我加的；
	m_xTranslation = 0.0f;
	m_yTranslation = 0.0f;
	m_zTranslation = 0.0f;

	m_glScale  = m_glOrgScale;
//	m_pDoc->DecideOpenGLScale();

	//////////////
	// 状态变量
	m_bDisplayAxis=TRUE;
	m_bDisplayHintInfo=TRUE;	//是否显示提示信息；
	m_bDisplayOriginPoint=TRUE;	   //是否显示原点；
	m_bDisplayScaleRuler=TRUE;	   //是否显示比例尺；
	m_bDisplayPointNumber=FALSE;   //是否显示点标号；

	m_bMouseMove=FALSE;		 //用鼠标移动物体；
//	m_bDisplayContactPoints=FALSE;
	m_bRender=TRUE;	   //是否采用光照模型；
//	m_bModifyPart=FALSE;
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m_bSelected=FALSE;		//是否进入选择状态；
	//冲头检查控制；

    m_TrackBall.Init(m_oldRect.right,m_oldRect.bottom);

	m_TrackBall.Initquat(60,30,16);

	m_bViewTargetPunch=false;
}

void COpenGLView::DisplayScaleRuler()
{
	//画比例尺；
	CString str;
	glDisable(GL_LIGHTING);	 //不要光照；
//	glColor3f(1.0,1.0,0.0);
	glColor3f(GetRValue(m_TextColor)/255.0f, 
		GetGValue(m_TextColor)/255.0f,
		GetBValue(m_TextColor)/255.0f);
	glBegin(GL_LINE_STRIP);
		glVertex2d(m_GLWindowClientRect.right-3.0,m_GLWindowClientRect.bottom+0.75);
		glVertex2d(m_GLWindowClientRect.right-3.0,m_GLWindowClientRect.bottom+0.5);
		glVertex2d(m_GLWindowClientRect.right-1.0,m_GLWindowClientRect.bottom+0.5);
		glVertex2d(m_GLWindowClientRect.right-1.0,m_GLWindowClientRect.bottom+0.75);
	glEnd();
	glRasterPos2d(m_GLWindowClientRect.right-3.0,m_GLWindowClientRect.bottom+1.0);
	glListBase(FONTLISTBASE);
	str.Format(_T("%.1fmm"),2.0/m_glScale);
	glCallLists(str.GetLength(), GL_UNSIGNED_BYTE, str); 
}

void COpenGLView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bLeftButtonDown = TRUE;
	m_LeftDownPos = point;
	/////
	m_TrackBall.OnLButtonDown(nFlags, point);
	
	CView::OnLButtonDown(nFlags, point);
}

void COpenGLView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bLeftButtonDown = FALSE;
	/////
    m_TrackBall.OnLButtonUp(nFlags,point);
		//gbLeftMouse = FALSE;
	////
	
	CView::OnLButtonUp(nFlags, point);
}

void COpenGLView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bMouseMove && m_bLeftButtonDown)
	{
		CPoint pt=point;
		double dx,dy;
	//	CRect rect;
	//	GetClientRect(&rect);
	//	ScreenToClient(&pt);

		dx = (float)(pt.x-m_LeftDownPos.x)/m_oldRect.right*m_GLWindowClientRect.Width();
		dy = (float)(pt.y-m_LeftDownPos.y)/m_oldRect.bottom*m_GLWindowClientRect.Height();
		m_xTranslation +=(float)dx ;
		m_yTranslation -=(float)dy ;
	//	m_xTranslation +=(float)1.0 ;
	//	m_yTranslation +=(float)1.0 ;

		m_LeftDownPos = point;
	//	CClientDC dc(this);
	//	OnDraw(&dc);
		InvalidateRect(NULL,FALSE);
	}
	else if(m_bLeftButtonDown)
	{
	//sz	m_yRotation -= (float)(m_LeftDownPos.x - point.x)/3.0f;
		m_xRotation -= (float)(m_LeftDownPos.y - point.y)/3.0f;
		//我加的；
//		m_zRotation -= (float)length2(m_LeftDownPos.x - point.x,m_LeftDownPos.y-point.y)/3.0f;
		m_LeftDownPos = point;
	//	InvalidateRect(&m_oldRect,FALSE);
//		CalcRotMatrix(matRot,point);
		InvalidateRect(NULL,FALSE);
	}
	
	CView::OnMouseMove(nFlags, point);
}

void COpenGLView::DecideOpenGLScale()
{
	//用于确定openGL绘图比例；
	// m_glOrgScale--用于记录工件基本比例；m_glScale--是绘图实际使用的比例；

//	m_glOrgScale=m_glScale=float(m_Range/(16*26.0));
	m_glOrgScale=m_glScale=float(2.0/1.0);
}

void COpenGLView::RestoreAllDefaultColors()
{
	//程序颜色初始化；
	m_BackgroundColor=RGB(255,255,255);
	m_TextColor=RGB(0,255,255);
	m_LineColor=RGB(255,255,0);
	////////////////////////
	//颜色初始值；
	SetOpenGLColor(m_diffuse_CamSurface,142.0f/255.0f,200.0f/255.0f,217.0f/255.0f);  //凸轮面颜色
	SetOpenGLColor(m_diffuse_CamRound,0.7,0.7,0.7);  //凸轮边缘颜色
	SetOpenGLColor(m_diffuse_ToolSurface,0,1,1);	  //砂轮面颜色
	SetOpenGLColor(m_diffuse_ToolRound,1.0f,0.0f,0.0f);  //砂轮边缘颜色
//	SetOpenGLColor(m_diffuse_ToolSurface,1,0,0); //越界的冲头柱体或球头
	SetOpenGLColor(m_diffuse_ModifiedPunchZhuTi,0,0.5f,0.5f); //受过调整的冲头柱体
	SetOpenGLColor(m_diffuse_BadPunchQiuTou,1,0,1);	//接触不良的冲头球头；
}

void COpenGLView::DrawObject(int flag)
{
	THE_DOC* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	//启动光照；
	glEnable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	double OffsetPunchZ=m_OffsetPunchZ;

	OffsetPunchZ=0.0;	//工件定位的模板显示无需偏移；
	
//	#define FS 10			  //划分精度；

	GLUquadricObj *obj=gluNewQuadric();
	glPushMatrix();

//	实际画图函数
//	pDoc->DrawCube();
	
	theWorkShop.Draw(obj);


	

	glPopMatrix();



	glDisable(GL_LIGHTING);	//关闭光照；
	return;
}

void COpenGLView::SetOpenGLColor(GLfloat color[], float r, float g, float b, float a)
{
	color[0]=r;
	color[1]=g;
	color[2]=b;
	color[3]=a;
}





void COpenGLView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
//	m_OffsetPunchZ_Step=atof(AfxGetApp()->GetProfileString(_T("Option"),_T("OffsetPunch Step"),_T("5.0")));
////////////////////////////////////
	m_bDispalyDownMoudle=m_bDispalyUpMoudle=TRUE;
	
	SetTimer(15,10,NULL);
}

void COpenGLView::OnRestorePunchButton() 
{
	// TODO: Add your control notification handler code here
	m_OffsetPunchZ=0;
	Invalidate();
}

void COpenGLView::OnDeltaposPunchOffsetSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMUpDown->iDelta<0) m_OffsetPunchZ+=m_OffsetPunchZ_Step;
	else m_OffsetPunchZ-=m_OffsetPunchZ_Step;

//	if(m_OffsetPunchZ<0) m_OffsetPunchZ=0;
	
	*pResult = 0;
    
	Invalidate();
}

void COpenGLView::OnUpdateRestorePunchButton(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(fabs(m_OffsetPunchZ)>0.0000001);
}

void COpenGLView::OnDisplayaxisButton() 
{
	// TODO: Add your command handler code here
	m_bDisplayAxis=!m_bDisplayAxis;
	Invalidate();
}

void COpenGLView::OnInitgeographicsButton() 
{
	// TODO: Add your command handler code here
	InitGeometry();
	Invalidate();
}

void COpenGLView::OnModifytoxyButton() 
{
	// TODO: Add your command handler code here
	m_TrackBall.Initquat(0,0,0);
	Invalidate();
}

void COpenGLView::OnModifytoyzButton() 
{
	// TODO: Add your command handler code here
	m_TrackBall.Initquat(90,90,0);
	Invalidate();
}

void COpenGLView::OnModifytozxButton() 
{
	// TODO: Add your command handler code here
	m_TrackBall.Initquat(90,0,0);
	Invalidate();
}

void COpenGLView::OnMoveanywhereButton() 
{
	// TODO: Add your command handler code here
	m_bMouseMove=!m_bMouseMove;
}

void COpenGLView::OnOverturnButton() 
{
	// TODO: Add your command handler code here
	m_TrackBall.Rotate(0,180,0);
	Invalidate();
}

void COpenGLView::OnUpdownoverturnButton() 
{
	// TODO: Add your command handler code here
	m_TrackBall.Rotate(180,0,0);
	Invalidate();
}

void COpenGLView::OnZoomoutButton() 
{
	// TODO: Add your command handler code here
	m_glScale*=1.1f;
	Invalidate();
}

void COpenGLView::OnZoominButton() 
{
	// TODO: Add your command handler code here
	m_glScale/=1.1f;
	Invalidate();
}

void COpenGLView::OnRotatedownButton() 
{
	// TODO: Add your command handler code here
	m_TrackBall.Rotate(-5,0,0);
	Invalidate();
}

void COpenGLView::OnRotateleftButton() 
{
	// TODO: Add your command handler code here
	m_TrackBall.Rotate(0,5,0);
	Invalidate();
}

void COpenGLView::OnRotaterightButton() 
{
	// TODO: Add your command handler code here
	m_TrackBall.Rotate(0,-5,0);
	Invalidate();
}

void COpenGLView::OnRotateupButton() 
{
	// TODO: Add your command handler code here
	m_TrackBall.Rotate(5,0,0);
	Invalidate();
}

void COpenGLView::OnUpdateDisplayaxisButton(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bDisplayAxis);
}

void COpenGLView::OnUpdateMoveanywhereButton(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bMouseMove);
}



void COpenGLView::DisplayHintInfo()
{
//	COpenGLDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);

	//用opengl写提示信息文字；
	if(m_bViewTargetPunch) m_HintInfo="TargetPunch";
//	else m_HintInfo=BCAA_YAM3C.GetHintInfo();
//	m_HintInfo=pDoc->GetPathName();
	glDisable(GL_LIGHTING);	 //不要光照；
	glColor3f(GetRValue(m_TextColor)/255.0f, 
		GetGValue(m_TextColor)/255.0f,
		GetBValue(m_TextColor)/255.0f);
	glRasterPos2d(m_GLWindowClientRect.left+1.0,m_GLWindowClientRect.top-1.0);
//	glListBase(FONTLISTBASE);
//	glCallLists(m_HintInfo.GetLength(), GL_UNSIGNED_BYTE, m_HintInfo); 
}

BOOL COpenGLView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bMouseMove)
	{
	
		return TRUE;
	}
	else return CView::OnSetCursor(pWnd, nHitTest, message);
//	return CView::OnSetCursor(pWnd, nHitTest, message);
}

BOOL COpenGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	if(zDelta>0) m_glScale=float(m_glScale*1.05);
	else m_glScale=float(m_glScale/1.05);

	Invalidate();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void COpenGLView::OnViewtargetpunchButton() 
{
	// TODO: Add your command handler code here
	m_bViewTargetPunch=!m_bViewTargetPunch;
	Invalidate();
}

void COpenGLView::OnUpdateViewtargetpunchButton(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	THE_DOC* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

//	pCmdUI->Enable(pDoc->m_bIsPunchsValid);
	pCmdUI->SetCheck(m_bViewTargetPunch);
}

void COpenGLView::OnUpdateUpmoudleCheck(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bDispalyUpMoudle);
}

void COpenGLView::OnUpdateDownmoudleCheck(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bDispalyDownMoudle);
}

void COpenGLView::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(nFlags&MK_LBUTTON)
	{
//		BCAA_YAM3C.m_bDisplayUnusedUnit=!(BCAA_YAM3C.m_bDisplayUnusedUnit);
		Invalidate();
	}

	CView::OnRButtonDblClk(nFlags, point);
}

void COpenGLView::OnDestroy() 
{
	CView::OnDestroy();
	KillTimer(1);
	// TODO: Add your message handler code here
	
}


double COpenGLView::DegreeCos(double fDegree)
{
	return cos(fDegree*3.141592654/180.0);
}
double COpenGLView::DegreeSin(double fDegree)
{
	return sin(fDegree*3.141592654/180.0);
}


void COpenGLView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 15)
	{
		m_nClock++;
		if (m_nClock >= CLOCK_MAX)
		{
			m_nClock = 0;
		}
		theWorkShop.CalcuState(m_nClock);

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
	CView::OnTimer(nIDEvent);
}




void COpenGLView::OnBnClickedButtonStation1()
{
	// TODO: Add your control notification handler code here
	//	theWorkShop.RequestVehicle(0);
	//	theWorkShop.m_Station[0].Requst();
	theWorkShop.m_BucketSorter[0].AddBucket();
}


void COpenGLView::OnBnClickedButtonStation2()
{
	// TODO: Add your control notification handler code here
	//	theWorkShop.m_Station[1].Requst();
	//	theWorkShop.m_BucketSorter[0].m_nBucketCounter = 0;

	theWorkShop.m_BucketSorter[1].AddBucket();
}
void COpenGLView::OnBnClickedButtonStation3()
{
	// TODO: Add your control notification handler code here
	//theWorkShop.m_Station[2].Requst();
	theWorkShop.m_BucketSorter[2].AddBucket();

}


void COpenGLView::OnBnClickedButtonStation4()
{
	// TODO: Add your control notification handler code here
	//	theWorkShop.m_Station[3].Requst();
	theWorkShop.m_BucketSorter[3].AddBucket();

}
void COpenGLView::OnBnClickedButtonStation5()
{
	// TODO: Add your control notification handler code here
	//theWorkShop.m_Station[4].Requst();
	theWorkShop.m_BucketSorter[4].AddBucket();

}


void COpenGLView::OnBnClickedButtonStation6()
{
	// TODO: Add your control notification handler code here
	//	theWorkShop.m_Station[5].Requst();
	theWorkShop.m_BucketSorter[5].AddBucket();
}
void COpenGLView::OnBnClickedButtonStation7()
{
	// TODO: Add your control notification handler code here
	theWorkShop.m_Station[6].Requst();
}


void COpenGLView::OnBnClickedButtonStation8()
{
	// TODO: Add your control notification handler code here
	theWorkShop.m_Station[7].Requst();
}
void COpenGLView::OnBnClickedButtonStation9()
{
	// TODO: Add your control notification handler code here
	theWorkShop.m_Station[8].Requst();
}


void COpenGLView::OnBnClickedButtonStation10()
{
	// TODO: Add your control notification handler code here
	theWorkShop.m_Station[9].Requst();
}



void COpenGLView::OnBnClickedButtonTaskSet()
{
	
}


void COpenGLView::OnOpStation()
{
	CStationOp dlg;
	dlg.DoModal();
	// TODO:  在此添加命令处理程序代码
}
