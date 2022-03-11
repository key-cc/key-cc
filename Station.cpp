#include "StdAfx.h"
#include "Station.h"
#include "MyDefine.h"
#include "math.h"

CStation::CStation(void)
{
	m_fCurrentPos = 0;
	m_fHeight = 600;
	m_fLength = 1500;
	m_fWidth = 1500;
	m_fBarHeight = 200;
	m_fBarWidth = 50;
	m_fDirectionAngle = 0;
	AAA.SetOpenGLColor(m_ColorLR,0, 1, 1);
	AAA.SetOpenGLColor(m_ColorFB,1, 0, 0);

	m_bIsBucket = FALSE;
	m_bIsBucketMove = FALSE;
	m_fBucketStep = 10;
	m_fBucketPos = 0;
	m_fBucketDis = m_fLength+STATION_VEHICLE_GAP;
	m_nClock = 0;
	m_nStartTime = 0;
	m_fCircleL = ORBIT_DIS*PI+ORBIT_LENGTH*2.0;

	m_Bucket[0] .SetPosition(-300,-300) ;
	m_Bucket[1] .SetPosition(-300,300) ;
	m_Bucket[2] .SetPosition(300,-300) ;
	m_Bucket[3] .SetPosition(300,300) ;

	m_nPeriod = 1000;

	m_nVehicleNo = -1;
	m_nRunMode=NULL_COMMAND;
	m_nID = -1;
	m_bIsRequested = FALSE;

	m_strRecorder.Empty();

}
CStation::~CStation(void)
{
}

/*
void CStation::SetOpenGLColor(GLfloat color[], float r, float g, float b, float a)
{
	color[0]=r;
	color[1]=g;
	color[2]=b;
	color[3]=a;
}*/

double CStation::SetPosition(double fCurrentPos)
{
	double fLastPos = m_fCurrentPos;
	
	int n = (int)(fCurrentPos/m_fCircleL);
	double pos = fCurrentPos-n*m_fCircleL;
	m_fCurrentPos = pos;
	//double fR = (ORBIT_DIS-m_fWidth)/2.0;
	if(m_fCurrentPos<ORBIT_LENGTH)
	{

		m_fX = ORBIT_LENGTH/2.0 - m_fCurrentPos ;
		m_fY = (ORBIT_DIS + m_fWidth)/2.0 + STATION_VEHICLE_GAP;

		m_fDirectionAngle = 0;
	}
	else if(m_fCurrentPos < ORBIT_LENGTH+PI*ORBIT_DIS/2.0)
	{
		double fL = m_fCurrentPos - ORBIT_LENGTH;
		double fRad = 2.0*fL/ORBIT_DIS;
		//double fR = (ORBIT_DIS-m_fWidth)*0.5;
		double fR = (ORBIT_DIS+ m_fWidth)/2.0 + STATION_VEHICLE_GAP ;
		m_fX = -ORBIT_LENGTH*0.5 - fR * sin(fRad);
		m_fY = fR*cos(fRad);
		m_fDirectionAngle = fRad*180.0/PI;

	}
	else if(m_fCurrentPos < ORBIT_LENGTH*2.0 + PI*ORBIT_DIS/2.0)
	{
		m_fX = - ORBIT_LENGTH/2.0 +m_fCurrentPos - ORBIT_LENGTH-PI*ORBIT_DIS/2.0;
		m_fY = -(ORBIT_DIS+m_fWidth)/2.0 - STATION_VEHICLE_GAP;
		m_fDirectionAngle =180.0;
	}
	else
	{
		double fL = m_fCurrentPos - ORBIT_LENGTH*2.0 - PI*ORBIT_DIS/2.0;
		double fRad = 2.0*fL/ORBIT_DIS;
		double fR = (ORBIT_DIS+m_fWidth)*0.5 + STATION_VEHICLE_GAP;
		m_fX =  ORBIT_LENGTH/2.0 + fR * sin(fRad);
		m_fY = -fR*cos(fRad);
		m_fDirectionAngle = fRad*180.0/PI+180.0;

	}
	
	return fLastPos;
}


void CStation::Draw(GLUquadricObj *obj)
{
	glEnable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	double x = m_fLength/2.0;
	double y = m_fWidth/2.0;
	
	
	glTranslated(m_fX,m_fY,-Z_POS+ORBIT_HEIGHT);
	
	glRotated(m_fDirectionAngle,0,0,1);
  

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,m_ColorLR);
		glBegin(GL_QUADS);
			glNormal3f(0.0,0.0,-1.0);  //ÏÂ°å£»
			glVertex3d(-x,-y,0);
			glVertex3d( x,-y,0);
			glVertex3d( x, y,0);
			glVertex3d(-x, y,0);
			
			
			glNormal3f(0.0,0.0,1.0);   //ÉÏ°å
			glVertex3d(-x,-y,m_fHeight);
			glVertex3d( x,-y,m_fHeight);
			glVertex3d( x, y,m_fHeight);
			glVertex3d(-x, y,m_fHeight);

					
			glNormal3f(0.0,-1.0,0.0);  //×ó°å
			glVertex3d(-x,-y,0);
			glVertex3d(-x,-y,m_fHeight);
			glVertex3d(x,-y,m_fHeight);
			glVertex3d(x,-y,0);
			
			glNormal3f(0.0,1.0,0.0);   //ÓÒ°å
			glVertex3d(-x,y,0);
			glVertex3d(-x,y,m_fHeight);
			glVertex3d(x,y,m_fHeight);
			glVertex3d(x,y,0);


		glEnd();

		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,m_ColorFB);
		glBegin(GL_QUADS);
			glNormal3f(-1.0,0.0,0.0);  //Ç°°å
			glVertex3d(-x,-y,0);
			glVertex3d(-x,-y,m_fHeight);
			glVertex3d(-x, y,m_fHeight);
			glVertex3d(-x, y,0);
			
			
			glNormal3f(1.0,0.0,0.0);  //ºó°å
			glVertex3d(x,-y,0);
			glVertex3d(x,-y,m_fHeight);
			glVertex3d(x, y,m_fHeight);
			glVertex3d(x, y,0);

		glEnd();

		glTranslated(0,0,m_fHeight);//»­À¸¸Ë
		glBegin(GL_QUADS);
		if(m_nMode == STATION_OUT)
		{
			if(m_nRunMode != STATION_BUCKET_MOVE)
			{
			glNormal3f(0.0,-1.0,0.0);  //×ó°å
			glVertex3d(-x,-y,0);
			glVertex3d(-x,-y,m_fBarHeight);
			glVertex3d(x,-y,m_fBarHeight);
			glVertex3d(x,-y,0);
			

			glNormal3f(0.0,1.0,0.0);  //×ó°åÄÚ
			glVertex3d(-x,-y+m_fBarWidth,0);
			glVertex3d(-x,-y+m_fBarWidth,m_fBarHeight);
			glVertex3d(x,-y+m_fBarWidth,m_fBarHeight);
			glVertex3d(x,-y+m_fBarWidth,0);

			glNormal3f(0.0,0.0,1.0);  //×ó°åÉÏ
			glVertex3d(-x,-y,m_fBarHeight);
			glVertex3d(-x,-y+m_fBarWidth,m_fBarHeight);
			glVertex3d(x,-y+m_fBarWidth,m_fBarHeight);
			glVertex3d(x,-y,m_fBarHeight);
			}
		}
		else
		{
			glNormal3f(0.0,1.0,0.0);  //ÓÒ°å
			glVertex3d(-x,y,0);
			glVertex3d(-x,y,m_fBarHeight);
			glVertex3d(x,y,m_fBarHeight);
			glVertex3d(x,y,0);

			glNormal3f(0.0,1.0,0.0);  //ÓÒ°åÄÚ
			glVertex3d(-x,y-m_fBarWidth,0);
			glVertex3d(-x,y-m_fBarWidth,m_fBarHeight);
			glVertex3d(x,y-m_fBarWidth,m_fBarHeight);
			glVertex3d(x,y-m_fBarWidth,0);

			glNormal3f(0.0,0.0,1.0);  //ÓÒ°åÉÏ
			glVertex3d(-x,y,m_fBarHeight);
			glVertex3d(-x,y-m_fBarWidth,m_fBarHeight);
			glVertex3d(x,y-m_fBarWidth,m_fBarHeight);
			glVertex3d(x,y,m_fBarHeight);
		}

			glNormal3f(-1.0,0.0,0.0);  //Ç°°å
			glVertex3d(-x,-y,0);
			glVertex3d(-x,-y,m_fBarHeight);
			glVertex3d(-x, y,m_fBarHeight);
			glVertex3d(-x, y,0);

			glNormal3f(1.0,0.0,0.0);  //Ç°°åÄÚ
			glVertex3d(-x+m_fBarWidth,-y,0);
			glVertex3d(-x+m_fBarWidth,-y,m_fBarHeight);
			glVertex3d(-x+m_fBarWidth, y,m_fBarHeight);
			glVertex3d(-x+m_fBarWidth, y,0);

			glNormal3f(0.0,0.0,1.0);  //Ç°°åÉÏ
			glVertex3d(-x,-y,m_fBarHeight);
			glVertex3d(-x+m_fBarWidth,-y,m_fBarHeight);
			glVertex3d(-x+m_fBarWidth, y,m_fBarHeight);
			glVertex3d(-x, y,m_fBarHeight);
			

			
			glNormal3f(1.0,0.0,0.0);  //ºó°å
			glVertex3d(x,-y,0);
			glVertex3d(x,-y,m_fBarHeight);
			glVertex3d(x, y,m_fBarHeight);
			glVertex3d(x, y,0);

			glNormal3f(1.0,0.0,0.0);  //ºó°åÄÚ
			glVertex3d(x-m_fBarWidth,-y,0);
			glVertex3d(x-m_fBarWidth,-y,m_fBarHeight);
			glVertex3d(x-m_fBarWidth, y,m_fBarHeight);
			glVertex3d(x-m_fBarWidth, y,0);

			glNormal3f(0.0,0.0,1.0);  //ºó°åÉÏ
			glVertex3d(x,-y,m_fBarHeight);
			glVertex3d(x-m_fBarWidth,-y,m_fBarHeight);
			glVertex3d(x-m_fBarWidth, y,m_fBarHeight);
			glVertex3d(x, y,m_fBarHeight);



			
			
		glEnd();


		

		if(m_bIsBucket)
		{
			glTranslated(0,m_fBucketPos,0);
			
			m_Bucket[0].Draw(obj);
			m_Bucket[1].Draw(obj);
			m_Bucket[2].Draw(obj);
			m_Bucket[3].Draw(obj);
			glTranslated(0,-m_fBucketPos,0);
		}

		glTranslated(0,0,-m_fHeight);

		glRotated(-m_fDirectionAngle,0,0,1);

		glTranslated(-m_fX,-m_fY,Z_POS-ORBIT_HEIGHT);
		glDisable(GL_LIGHTING);	//¹Ø±Õ¹âÕÕ£»
		


}
void CStation:: Requst()
{
	if(m_nRunMode != NULL_COMMAND) return;
	if(m_nMode == STATION_OUT)
	{
		m_fBucketPos = 0;
		m_bIsBucket = TRUE;
		m_nRunMode = STATION_REQUEST;
		m_bIsRequested = FALSE;

	}
	else
	{
		m_fBucketPos = -m_fBucketDis;
		m_bIsBucket = FALSE;
		m_nRunMode = STATION_REQUEST;
		m_bIsRequested = FALSE;
	}

}
void CStation::BucketReady()
{
	m_bIsBucket = TRUE;
	if(m_nMode == STATION_OUT)
	{
	
		m_fBucketPos = 0;
	}
	else
	{
	
		m_fBucketPos = -m_fBucketDis;
	}
}
void CStation::BucketMove()
{
	m_bIsBucketMove = TRUE;
	m_nStartTime = m_nClock;
	
}
/*
//STATION_RUN_MODE
#define NULL_COMMAND 0
#define STATION_REQUEST 400
#define STATION_BUCKET_ON 401
#define STATION_BUCKET_MOVE 402
#define STATION_BUCKET_FINISH 403
*/
void CStation::CalcuState(int nClock)
{
	m_nClock = nClock;
	
	if(m_nRunMode == NULL_COMMAND) return;
	else if(m_nRunMode == STATION_REQUEST)
	{

			return;
	}
	else if(m_nRunMode == STATION_BUCKET_MOVE)
	{
		int nMoveTimes = (int)(m_fBucketDis/m_fBucketStep)+1;
		int nMoveCounter = m_nClock - m_nStartTime;
		if(nMoveCounter < 0) nMoveCounter += CLOCK_MAX;
		
		m_bIsBucketMove = TRUE;
		if(m_nMode == STATION_OUT)
		{
			m_fBucketPos = -nMoveCounter * m_fBucketStep;
			if(m_fBucketPos<= -m_fBucketDis)
			{
				m_fBucketPos = -m_fBucketDis;
				m_bIsBucketMove = FALSE;
				m_bIsBucket = FALSE;
				m_nRunMode = STATION_BUCKET_FINISH;
		
			}
		}
		else//m_nMode == STATION_IN
		{
			m_bIsBucket = TRUE;
			m_fBucketPos = -m_fBucketDis+nMoveCounter * m_fBucketStep;
			if(m_fBucketPos>=0)
			{
			
				m_fBucketPos = 0;
				m_bIsBucketMove = FALSE;
				m_bIsBucket = TRUE;
				m_nRunMode = STATION_BUCKET_FINISH;
		
		
			}
		}
	}
	else if(m_nRunMode ==STATION_BUCKET_FINISH)
	{
			m_nRunMode = NULL_COMMAND;
		return;
	}
	return;
	
	
}
	
