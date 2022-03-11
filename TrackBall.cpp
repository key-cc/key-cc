// TrackBall.cpp: implementation of the CTrackBall class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Cam.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "TrackBall.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
 * This size should really be based on the distance from the center of
 * rotation to the point on the object underneath the mouse.  That
 * point would then track the mouse as closely as possible.  This is a
 * simple example, though, so that is left as an Exercise for the
 * Programmer.
 */
#define TRACKBALLSIZE  (1.0f)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrackBall::CTrackBall()
{
   gbLeftMouse = FALSE;
   gbSpinning = FALSE;
   gbPauseSpinning = FALSE;   //控制在gbSpinning==true时，启动和停止旋转；
}

CTrackBall::~CTrackBall()
{

}

void CTrackBall::Init( GLint width, GLint height )
{
//    ghwnd = auxGetHWND();
    giWidth = width;
    giHeight = height;

    calc_quat( curquat, 0.0f, 0.0f, 0.0f, 0.0f );
//    calc_quat( curquat, 0.0f, 1.57f, 0.0f, 0.0f );
}

void CTrackBall::Initquat( float AngX, float AngY ,float AngZ )
{
// 	我加的，对角度进行条件初始化；
	float a[]={1,0,0};
	axis_to_quat(a,AngX/180.0f*3.14159f,curquat);  //兼有初始化功能；

	a[0]=0; a[1]=1; a[2]=0;
	if(AngY)
	{
		axis_to_quat(a,AngY/180.0f*3.14159f,lastquat);
		add_quats(lastquat, curquat, curquat);
	}
	a[0]=0; a[1]=0; a[2]=1;
	if(AngZ)
	{
		axis_to_quat(a,AngZ/180.0f*3.14159f,lastquat);
		add_quats(lastquat, curquat, curquat);
	}
}

void CTrackBall::Rotate( float AngX, float AngY ,float AngZ )
{
// 	我加的，依据现实坐标系旋转工件；
	float a[]={1,0,0};
	if(AngX)
	{
		axis_to_quat(a,AngX/180.0f*3.14159f,lastquat);
		add_quats(lastquat, curquat, curquat);
	}
	a[0]=0; a[1]=1; a[2]=0;
	if(AngY)
	{
		axis_to_quat(a,AngY/180.0f*3.14159f,lastquat);
		add_quats(lastquat, curquat, curquat);
	}
	a[0]=0; a[1]=0; a[2]=1;
	if(AngZ)
	{
		axis_to_quat(a,AngZ/180.0f*3.14159f,lastquat);
		add_quats(lastquat, curquat, curquat);
	}
}

void CTrackBall::Resize( GLint width, GLint height )
{
    giWidth = width;
    giHeight = height;
}

GLenum
#ifdef _USE_TK
CTrackBall::MouseDown( int mouseX, int mouseY, GLenum button ) 
#else
CTrackBall::MouseDown( AUX_EVENTREC *event) 
#endif
{
 //   SetCapture(ghwnd);
    glMouseDownX = event->data[AUX_MOUSEX];
    glMouseDownY = event->data[AUX_MOUSEY];
    gbLeftMouse = TRUE;
    return GL_TRUE;
}


GLenum
#ifdef _USE_TK
CTrackBall::MouseUp( int mouseX, int mouseY, GLenum button ) 
#else
CTrackBall::MouseUp( AUX_EVENTREC *event ) 
#endif
{
	event; //无意义，防警告；
  //  ReleaseCapture();
    gbLeftMouse = FALSE;
    return GL_TRUE;
}

/* these 4 not used yet */
void CTrackBall::MouseDownEvent( int mouseX, int mouseY, GLenum button )
{
   mouseX;mouseY;button;   //防警告，无意义；
}

void CTrackBall::MouseUpEvent( int mouseX, int mouseY, GLenum button )
{
   mouseX;mouseY;button;   //防警告，无意义；
}


void CTrackBall::CalcRotMatrix( GLfloat matRot[4][4] )
{
    POINT pt;

    if (gbLeftMouse)
    {
		pt.x=pt.y=0;   //防警告，无意义！

        // If mouse has moved since button was pressed, change quaternion.

            if (pt.x != glMouseDownX || pt.y != glMouseDownY)
            {
#if 1
    /* negate all params for proper operation with glTranslate(-z)
     */
                calc_quat(lastquat,
                          -(2.0f * ( giWidth - glMouseDownX ) / giWidth - 1.0f),
                          -(2.0f * glMouseDownY / giHeight - 1.0f),
                          -(2.0f * ( giWidth - pt.x ) / giWidth - 1.0f),
                          -(2.0f * pt.y / giHeight - 1.0f)
                         );
#else
// now out-of-date
                calc_quat(lastquat,
                          2.0f * ( Width - glMouseDownX ) / Width - 1.0f,
                          2.0f * glMouseDownY / Height - 1.0f,
                          2.0f * ( Width - pt.x ) / Width - 1.0f,
                          2.0f * pt.y / Height - 1.0f );
#endif

                gbSpinning = TRUE;
            }
            else
                gbSpinning = FALSE;

            glMouseDownX = pt.x;
            glMouseDownY = pt.y;
    }

    if (gbSpinning)	add_quats(lastquat, curquat, curquat);

    build_rotmatrix(matRot, curquat);
}

void CTrackBall::vzero(float *v)
{
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
}

void CTrackBall::vset(float *v, float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

void CTrackBall::vsub(const float *src1, const float *src2, float *dst)
{
    dst[0] = src1[0] - src2[0];
    dst[1] = src1[1] - src2[1];
    dst[2] = src1[2] - src2[2];
}

void CTrackBall::vcopy(const float *v1, float *v2)
{
    register int i;
    for (i = 0 ; i < 3 ; i++)
        v2[i] = v1[i];
}

void CTrackBall::vcross(const float *v1, const float *v2, float *cross)
{
    float temp[3];

    temp[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    temp[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    temp[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
    vcopy(temp, cross);
}

float CTrackBall::vlength(const float *v)
{
    return (float) sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void CTrackBall::vscale(float *v, float div)
{
    v[0] *= div;
    v[1] *= div;
    v[2] *= div;
}

void CTrackBall::vnormal(float *v)
{
    vscale(v,1.0f/vlength(v));
}

float CTrackBall::vdot(const float *v1, const float *v2)
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

void CTrackBall::vadd(const float *src1, const float *src2, float *dst)
{
    dst[0] = src1[0] + src2[0];
    dst[1] = src1[1] + src2[1];
    dst[2] = src1[2] + src2[2];
}

/*
 * Ok, simulate a track-ball.  Project the points onto the virtual
 * trackball, then figure out the axis of rotation, which is the cross
 * product of P1 P2 and O P1 (O is the center of the ball, 0,0,0)
 * Note:  This is a deformed trackball-- is a trackball in the center,
 * but is deformed into a hyperbolic sheet of rotation away from the
 * center.  This particular function was chosen after trying out
 * several variations.
 * 
 * It is assumed that the arguments to this routine are in the range
 * (-1.0 ... 1.0)
 */
void CTrackBall::calc_quat(float q[4], float p1x, float p1y, float p2x, float p2y)
{
    float a[3]; /* Axis of rotation */
    float phi;  /* how much to rotate about axis */
    float p1[3], p2[3], d[3];
    float t;

    if (p1x == p2x && p1y == p2y) {
	/* Zero rotation */
        vzero(q); 
	q[3] = 1.0f; 
        return;
    }

    /*
     * First, figure out z-coordinates for projection of P1 and P2 to
     * deformed sphere
     */
    vset(p1,p1x,p1y,tb_project_to_sphere(TRACKBALLSIZE,p1x,p1y));
    vset(p2,p2x,p2y,tb_project_to_sphere(TRACKBALLSIZE,p2x,p2y));

    /*
     *  Now, we want the cross product of P1 and P2
     */
    vcross(p2,p1,a);

    /*
     *  Figure out how much to rotate around that axis.
     */
    vsub(p1,p2,d);
    t = vlength(d) / (2.0f*TRACKBALLSIZE);

    /*
     * Avoid problems with out-of-control values...
     */
    if (t > 1.0f) t = 1.0f;
    if (t < -1.0f) t = -1.0f;
    phi = 2.0f * (float) asin(t);

    axis_to_quat(a,phi,q);
}

/*
 *  Given an axis and angle, compute quaternion.
 */
void CTrackBall::axis_to_quat(float a[3], float phi, float q[4])
{
    vnormal(a);
    vcopy(a,q);
    vscale(q,(float) sin(phi/2.0f));
    q[3] = (float) cos(phi/2.0f);
}

/*
 * Project an x,y pair onto a sphere of radius r OR a hyperbolic sheet
 * if we are away from the center of the sphere.
 */
float CTrackBall::tb_project_to_sphere(float r, float x, float y)
{
    float d, t, z;

    d = (float) sqrt(x*x + y*y);
    if (d < r * 0.70710678118654752440f) {    /* Inside sphere */
	z = (float) sqrt(r*r - d*d);
    } else {           /* On hyperbola */
        t = r / 1.41421356237309504880f;
        z = t*t / d;
    }
    return z;
}

/*
 * Given two rotations, e1 and e2, expressed as quaternion rotations,
 * figure out the equivalent single rotation and stuff it into dest.
 * 
 * This routine also normalizes the result every RENORMCOUNT times it is
 * called, to keep error from creeping in.
 *
 * NOTE: This routine is written so that q1 or q2 may be the same
 * as dest (or each other).
 */

#define RENORMCOUNT 97

void CTrackBall::add_quats(float q1[4], float q2[4], float dest[4])
{
    static int count=0;
    float t1[4], t2[4], t3[4];
    float tf[4];

    vcopy(q1,t1); 
    vscale(t1,q2[3]);

    vcopy(q2,t2); 
    vscale(t2,q1[3]);

    vcross(q2,q1,t3);
    vadd(t1,t2,tf);
    vadd(t3,tf,tf);
    tf[3] = q1[3] * q2[3] - vdot(q1,q2);

    dest[0] = tf[0];
    dest[1] = tf[1];
    dest[2] = tf[2];
    dest[3] = tf[3];

    if (++count > RENORMCOUNT) {
        count = 0;
        normalize_quat(dest);
    }
}

/*
 * Quaternions always obey:  a^2 + b^2 + c^2 + d^2 = 1.0
 * If they don't add up to 1.0, dividing by their magnitued will
 * renormalize them.
 *
 * Note: See the following for more information on quaternions:
 * 
 * - Shoemake, K., Animating rotation with quaternion curves, Computer
 *   Graphics 19, No 3 (Proc. SIGGRAPH'85), 245-254, 1985.
 * - Pletinckx, D., Quaternion calculus as a basic tool in computer
 *   graphics, The Visual Computer 5, 2-13, 1989.
 */
void CTrackBall::normalize_quat(float q[4])
{
    int i;
    float mag;

    mag = (q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
    for (i = 0; i < 4; i++) q[i] /= mag;
}

/*
 * Build a rotation matrix, given a quaternion rotation.
 *
 */
void CTrackBall::build_rotmatrix(float m[4][4], float q[4])
{
    m[0][0] = 1.0f - 2.0f * (q[1] * q[1] + q[2] * q[2]);
    m[0][1] = 2.0f * (q[0] * q[1] - q[2] * q[3]);
    m[0][2] = 2.0f * (q[2] * q[0] + q[1] * q[3]);
    m[0][3] = 0.0f;

    m[1][0] = 2.0f * (q[0] * q[1] + q[2] * q[3]);
    m[1][1]= 1.0f - 2.0f * (q[2] * q[2] + q[0] * q[0]);
    m[1][2] = 2.0f * (q[1] * q[2] - q[0] * q[3]);
    m[1][3] = 0.0f;

    m[2][0] = 2.0f * (q[2] * q[0] - q[1] * q[3]);
    m[2][1] = 2.0f * (q[1] * q[2] + q[0] * q[3]);
    m[2][2] = 1.0f - 2.0f * (q[1] * q[1] + q[0] * q[0]);
    m[2][3] = 0.0f;

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

void CTrackBall::CalcRotMatrix( GLfloat matRot[4][4] ,const CPoint pt)
{
	//我改编的根据鼠标位置计算旋转矩阵的程序；
//    POINT pt;

    if (gbLeftMouse)
    {
//        auxGetMouseLoc( &pt.x, &pt.y );

        // If mouse has moved since button was pressed, change quaternion.

            if (pt.x != glMouseDownX || pt.y != glMouseDownY)
            {
#if 1
    /* negate all params for proper operation with glTranslate(-z)
     */
                calc_quat(lastquat,
                          -(2.0f * ( giWidth - glMouseDownX ) / giWidth - 1.0f),
                          -(2.0f * glMouseDownY / giHeight - 1.0f),
                          -(2.0f * ( giWidth - pt.x ) / giWidth - 1.0f),
                          -(2.0f * pt.y / giHeight - 1.0f)
                         );


#else
// now out-of-date
                calc_quat(lastquat,
                          2.0f * ( Width - glMouseDownX ) / Width - 1.0f,
                          2.0f * glMouseDownY / Height - 1.0f,
                          2.0f * ( Width - pt.x ) / Width - 1.0f,
                          2.0f * pt.y / Height - 1.0f );
#endif

                gbPauseSpinning = FALSE;	  //开始旋转；
				if(!gbSpinning) add_quats(lastquat, curquat, curquat);
            }
            else
			{
				gbPauseSpinning = TRUE;
			}

            glMouseDownX = pt.x;
            glMouseDownY = pt.y;
    }

   // if (gbSpinning || flag)  add_quats(lastquat, curquat, curquat);
   if (gbSpinning && !gbPauseSpinning)  add_quats(lastquat, curquat, curquat);

    build_rotmatrix(matRot, curquat);
}

void CTrackBall::OnLButtonUp(UINT nFlags, CPoint point)
{
	nFlags;	point; //未用的参数；
    gbLeftMouse = FALSE;
}

void CTrackBall::OnLButtonDown(UINT nFlags, CPoint point)
{
	nFlags;	//未用的参数；
	glMouseDownX=point.x;
	glMouseDownY=point.y;
    gbLeftMouse = TRUE;
}
