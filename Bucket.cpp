#include "StdAfx.h"
#include "Bucket.h"
#include "MyDefine.h"

#include "math.h"


CBucket::CBucket(void)
{
	m_fX = 0;
	m_fY = 0;
	m_fHeight = 1200;
	m_fRad = 300;
	SetOpenGLColor(m_ColorBody,1,1,0);
	SetOpenGLColor(m_ColorCover,1, 1, 1);
}
CBucket::CBucket(double x, double  y)
{
	m_fX = x;
	m_fY = y;
	m_fHeight = 1200;
	m_fRad = 300;
	SetOpenGLColor(m_ColorBody,1, 1, 0);
	SetOpenGLColor(m_ColorCover,1, 1, 1);
}
CBucket::~CBucket(void)
{
}
void CBucket::SetOpenGLColor(GLfloat color[], float r, float g, float b, float a)
{
	color[0]=r;
	color[1]=g;
	color[2]=b;
	color[3]=a;
}

void CBucket::SetPosition(double x, double  y)
{
	m_fX = x;
	m_fY = y;

}
void CBucket::Draw(GLUquadricObj *obj)
{
//	glEnable(GL_LIGHTING);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPushMatrix();
	glTranslated(m_fX,m_fY,0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,m_ColorBody);
	//gluDisk(obj,0,m_fRad,10,10);
	gluCylinder(obj,m_fRad,m_fRad,m_fHeight,10,10);
	
	glTranslated(0,0,m_fHeight);
	gluDisk(obj,0,m_fRad,10,10);

	//glPopMatrix();	
	glTranslated(-m_fX,-m_fY,-m_fHeight);
//	glDisable(GL_LIGHTING);	//πÿ±’π‚’’£ª
		

}
void CBucket::Draw(GLUquadricObj *obj,double x, double  y)
{
	SetPosition( x,   y);
	Draw(obj);
}
