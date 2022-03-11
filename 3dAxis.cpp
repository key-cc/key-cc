/////////////////////////////////////////////////////////////////////////////
// 3dAxis.cpp : Implementation file of the 3dAxis class
//
// glOOP (OpenGL Object Oriented Programming library)
// Copyright (c) Craig Fahrnbach 1997, 1998
//
// OpenGL is a registered trademark of Silicon Graphics
//
//
// This program is provided for educational and personal use only and
// is provided without guarantee or warrantee expressed or implied.
//
// Commercial use is strickly prohibited without written permission
// from ImageWare Development.
//
// This program is -not- in the public domain.
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3dAxis.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////
// C3dAxis

IMPLEMENT_DYNAMIC(C3dAxis, CObject)


/////////////////////////////////////////////////////////////////////////////
// C3dAxis construction

C3dAxis::C3dAxis()
{
	// Assign Default values to member attributes
	m_fXAxisColor[0] = 1.00f; // Red
	m_fXAxisColor[1] = 0.00f;
	m_fXAxisColor[2] = 0.00f;
	m_fXAxisColor[3] = 1.00f;

	m_fYAxisColor[0] = 0.00f; // Green
	m_fYAxisColor[1] = 1.00f;
	m_fYAxisColor[2] = 0.00f;
	m_fYAxisColor[3] = 1.00f;

	m_fZAxisColor[0] = 0.00f; // Blue
	m_fZAxisColor[1] = 0.00f;
	m_fZAxisColor[2] = 1.00f;
	m_fZAxisColor[3] = 1.00f;
}

/////////////////////////////////////////////////////////////////////////////
// C3dAxis Destructor

C3dAxis::~C3dAxis()
{
}


/////////////////////////////////////////////////////////////////////////////
// C3dAxis virtual overrides

void C3dAxis::Serialize(CArchive& ar)
{
	CString szBuffer;

	if (ar.IsStoring())
	{
		// Save the C3dAxis class header
		szBuffer.Format(_T("C3dAxis {\n"));
		ar.WriteString(szBuffer);

		// Save the axis default color information
		szBuffer.Format(_T("\tX-AxisColor   < %f %f %f %f >\n"), m_fXAxisColor[0], m_fXAxisColor[1], m_fXAxisColor[2], m_fXAxisColor[3]);
		ar.WriteString(szBuffer);
		szBuffer.Format(_T("\tY-AxisColor   < %f %f %f %f >\n"), m_fYAxisColor[0], m_fYAxisColor[1], m_fYAxisColor[2], m_fYAxisColor[3]);
		ar.WriteString(szBuffer);
		szBuffer.Format(_T("\tZ-AxisColor   < %f %f %f %f >\n"), m_fZAxisColor[0], m_fZAxisColor[1], m_fZAxisColor[2], m_fZAxisColor[3]);
		ar.WriteString(szBuffer);
		szBuffer.Format(_T("}\n\n")); // end of material def
		ar.WriteString(szBuffer);
	}
	else
	{
		// Read the axis color data...
		ar.ReadString(szBuffer);
		szBuffer.TrimLeft();	// Remove leading white spaces
		swscanf_s(szBuffer.GetBuffer(), _T("X-AxisColor   < %f %f %f %f >\n"), &m_fXAxisColor[0], &m_fXAxisColor[1], &m_fXAxisColor[2], &m_fXAxisColor[3]);
		ar.ReadString(szBuffer);
		szBuffer.TrimLeft();
		swscanf_s(szBuffer, _T("Y-AxisColor   < %f %f %f %f >\n"), &m_fYAxisColor[0], &m_fYAxisColor[1], &m_fYAxisColor[2], &m_fYAxisColor[3]);
		ar.ReadString(szBuffer);
		szBuffer.TrimLeft();
		swscanf_s(szBuffer, _T("Z-AxisColor   < %f %f %f %f >\n"), &m_fZAxisColor[0], &m_fZAxisColor[1], &m_fZAxisColor[2], &m_fZAxisColor[3]);
	}
}

/////////////////////////////////////////////////////////////////////////////
// C3dAxis Procedures

C3dAxis* C3dAxis::Create()
{
	C3dAxis* pAxis = new C3dAxis;
	if (pAxis) {
		return pAxis;
	}
	return NULL;
}

void C3dAxis::Display(GLdouble	dAxisLength,
					  GLdouble	dAxisRadius,
					  GLdouble	dArrowLength,
					  GLdouble	dArrowRadius,
					  GLint		iSlices,
					  GLint		iStacks,
					  GLfloat	fColorX[4],
					  GLfloat	fColorY[4],
					  GLfloat	fColorZ[4],
					  BOOL		bSolid)
{
	GLdouble dArrowPosn = dAxisLength - (dArrowLength/2);

	// Save the current transformation matrix..
	glPushMatrix();	


	// Disable textsure maping
	glDisable(GL_TEXTURE_2D);

	// Create a quadratic object used to draw our axis
	// cylinders and cones
	GLUquadricObj* m_pQuadric = gluNewQuadric();

	if(bSolid) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		gluQuadricDrawStyle(m_pQuadric, GLU_FILL);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		gluQuadricDrawStyle(m_pQuadric, GLU_LINE);
	}

	// Display the Z-Axis and arrow
	// Set the color
	if(fColorZ)
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,  fColorZ);
		glColor4fv(fColorZ);
	}
	else
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ,  m_fZAxisColor);
		glColor4fv(m_fZAxisColor);
	}

	gluCylinder(m_pQuadric, dAxisRadius, dAxisRadius, dAxisLength, iSlices, iStacks);
	glTranslated(0.0f, 0.0f, dArrowPosn);	// Move to arrow position
	gluCylinder(m_pQuadric, dArrowRadius, 0.0f, dArrowLength, iSlices, iStacks);
 

	// Display the X-Axis and arrow
	// Set the color
	if(fColorX)
	{
		glColor4fv(fColorX);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,  fColorX);
	}
	else
	{
		glColor4fv(m_fXAxisColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,  m_fXAxisColor);
	}

	glTranslated(0.0f, 0.0f, -dArrowPosn);// Move to 0, 0, 0
	glRotated(90, 0.0, 1.0, 0.0);	// Rotate for X
	gluCylinder(m_pQuadric, dAxisRadius, dAxisRadius, dAxisLength, iSlices, iStacks);
	glTranslated(0.0f, 0.0f, dArrowPosn);	// Move to arrow position
	gluCylinder(m_pQuadric, dArrowRadius, 0.0f, dArrowLength, iSlices, iStacks);

	
	// Display the Y-Axis and arrow
	// Set the color
	if(fColorY)
	{
		glColor4fv(fColorY);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,  fColorY);
	}
	else
	{
		glColor4fv(m_fYAxisColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,  m_fYAxisColor);
	}

	glTranslated(0.0f, 0.0f, -dArrowPosn);// Move to 0, 0, 0
	glRotated(-90, 1.0, 0.0, 0.0);	// Rotate for X
	gluCylinder(m_pQuadric, dAxisRadius, dAxisRadius, dAxisLength, iSlices, iStacks);
	glTranslated(0.0f, 0.0f, dArrowPosn);	// Move to arrow position
	gluCylinder(m_pQuadric, dArrowRadius, 0.0f, dArrowLength, iSlices, iStacks);

	// Delete the quadric
	gluDeleteQuadric(m_pQuadric);

	// Restore the current transformation matrix..
	glPopMatrix();

}
