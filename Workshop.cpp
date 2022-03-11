#include "StdAfx.h"
#include "Workshop.h"
#include "MyDefine.h"



CWorkshop::CWorkshop(void)
{
	m_fAreaLenth =  AREA_LENGTH/2.0;
	m_fAreaWidth = AREA_WIDTH/2.0;
	m_fOrbitLenth = ORBIT_LENGTH/2.0;
	m_fOrbitHeight = ORBIT_HEIGHT;
	m_fOrbitWidth = ORBIT_WIDTH;
	m_fOrbitGap = ORBIT_GAP;
	m_fOrbitDis = ORBIT_DIS/2.0;
	m_fCircleL = ORBIT_DIS*PI+ORBIT_LENGTH*2.0;

	SetOpenGLColor(m_ColorArea,0.3,0.3,0.3);	  
	SetOpenGLColor(m_ColorOrbit,100/255.0f,100/225.0f,200/255.0f); 
	SetOpenGLColor(m_ColorOrbitTop,1,1,1); 
	m_nScheduleGrade = 0;
	m_nCurrentClock = 0;
	for(int i=0;i<3;i++)
	{
		int nF = i+1;
		if(nF>=STATION_NUM) nF =0;
	
		m_Station[i].SetPosition(i*3000+2000);
		m_Station[i].m_nMode = STATION_OUT;
		m_Station[i].m_nID = i;
		m_Station[i].m_nPeriod = 1500+300*i;

		m_BucketSorter[i].SetPosition(i*3000+2000);

	}
	for(int i=3;i<6;i++)
	{
		int nF = i+1;
		if(nF>=STATION_NUM) nF =0;
	
		m_Station[i].SetPosition((i-3)*2500+18000);
		m_Station[i].m_nMode = STATION_OUT;
		m_Station[i].m_nID = i;
		m_Station[i].m_nPeriod = 1500+300*(i%4);

		m_BucketSorter[i].SetPosition((i-3)*2500+18000);
	}
	for(int i=6;i<STATION_NUM;i++)
	{
		int nF = i+1;
		if(nF>=STATION_NUM) nF =0;
	
		m_Station[i].SetPosition((i-6)*2000+50000);
		m_Station[i].m_nMode = STATION_IN;
		m_Station[i].m_bIsBucket = FALSE;
		m_Station[i].m_nID = i;
		m_Station[i].m_nPeriod = 1000+300*(i%4);
	}
		

	

	for(int i=0;i<VEHICLE_NUM;i++)
	{
		int nF = i+1;
		if(nF>=VEHICLE_NUM) nF =0;
		m_Vehicle[i].SetPosition(i*6500+6000);
		m_Vehicle[i].SetFront(&m_Vehicle[nF]);
		m_Vehicle[i].m_bIsBucket = FALSE;
		m_Vehicle[i].m_nID = i;
	
	}
//	for(int i=0;i<10;i++)
//	{
//		m_Task[i] = CTask(&m_Station[i]);
//	}
	
}


CWorkshop::~CWorkshop(void)
{
}
void CWorkshop::SetOpenGLColor(GLfloat color[], float r, float g, float b, float a)
{
	color[0]=r;
	color[1]=g;
	color[2]=b;
	color[3]=a;
}
void CWorkshop::DrawArea()
{
	/*
	m_fAreaLenth = 220000.0;
	m_fAreaWidth = 50000.0;
	m_fOrbitLenth = 200000;
	m_fOrbitHeight = 50000;
	m_fOrbitWidth = 50000;
	m_fOrbitGap = 100000;
	*/
#define HEIGHT 1000
//	if(!m_bDispaly) return;
	CString strArray[] = {"I","II","III","IV","V","VI","VII","VIII"};
	//启动光照；
	glEnable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,m_ColorArea);
	
	
	//画场地；

	
		glTranslated(0,0,-Z_POS);//OffsetPunchZ);

		glBegin(GL_QUADS);
			glNormal3f(0.0,0.0,1.0);   //上板
			glVertex3d(-m_fAreaLenth,-m_fAreaWidth,0);
			glVertex3d( m_fAreaLenth,-m_fAreaWidth,0);
			glVertex3d( m_fAreaLenth, m_fAreaWidth,0);
			glVertex3d(-m_fAreaLenth, m_fAreaWidth,0);
			
			glNormal3f(0.0,0.0,-1.0);  //下板；
			glVertex3d(-m_fAreaLenth,-m_fAreaWidth,-HEIGHT);
			glVertex3d( m_fAreaLenth,-m_fAreaWidth,-HEIGHT);
			glVertex3d( m_fAreaLenth, m_fAreaWidth,-HEIGHT);
			glVertex3d(-m_fAreaLenth, m_fAreaWidth,-HEIGHT);
			
			
			
			glNormal3f(-1.0,0.0,0.0);  //左板
			glVertex3d(-m_fAreaLenth,-m_fAreaWidth,-HEIGHT);
			glVertex3d(-m_fAreaLenth,-m_fAreaWidth,0);
			glVertex3d(-m_fAreaLenth, m_fAreaWidth,0);
			glVertex3d(-m_fAreaLenth, m_fAreaWidth,-HEIGHT);
			
			
			glNormal3f(1.0,0.0,0.0);  //右板
			glVertex3d(m_fAreaLenth,-m_fAreaWidth,-HEIGHT);
			glVertex3d(m_fAreaLenth,-m_fAreaWidth,0);
			glVertex3d(m_fAreaLenth, m_fAreaWidth,0);
			glVertex3d(m_fAreaLenth, m_fAreaWidth,-HEIGHT);
			
			glNormal3f(0.0,-1.0,0.0);  //近板
			glVertex3d(-m_fAreaLenth,-m_fAreaWidth,-HEIGHT);
			glVertex3d(-m_fAreaLenth,-m_fAreaWidth,0);
			glVertex3d(m_fAreaLenth,-m_fAreaWidth,0);
			glVertex3d(m_fAreaLenth,-m_fAreaWidth,-HEIGHT);
			
			glNormal3f(0.0,1.0,0.0);   //远板
			glVertex3d(-m_fAreaLenth,m_fAreaWidth,-HEIGHT);
			glVertex3d(-m_fAreaLenth,m_fAreaWidth,0);
			glVertex3d(m_fAreaLenth,m_fAreaWidth,0);
			glVertex3d(m_fAreaLenth,m_fAreaWidth,-HEIGHT);

			
		glEnd();

		

		glTranslated(0,0,Z_POS);
		glDisable(GL_LIGHTING);	//关闭光照；
		
}
void CWorkshop::DrawOrbit(GLUquadricObj *obj)
{
	glEnable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,m_ColorOrbit);
	glTranslated(0,0,-Z_POS);//OffsetPunchZ);
	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);   //上板
		glVertex3d(-m_fOrbitLenth,-m_fOrbitDis+m_fOrbitGap,m_fOrbitHeight);
		glVertex3d( m_fOrbitLenth,-m_fOrbitDis+m_fOrbitGap,m_fOrbitHeight);
		glVertex3d( m_fOrbitLenth,-m_fOrbitDis,m_fOrbitHeight);
		glVertex3d(-m_fOrbitLenth,-m_fOrbitDis,m_fOrbitHeight);

		glNormal3f(0.0,1.0,0.0);  //近板
		glVertex3d(-m_fOrbitLenth,-m_fOrbitDis+m_fOrbitGap,m_fOrbitHeight);
		glVertex3d(-m_fOrbitLenth,-m_fOrbitDis+m_fOrbitGap,0);
		glVertex3d( m_fOrbitLenth,-m_fOrbitDis+m_fOrbitGap,0);
		glVertex3d( m_fOrbitLenth,-m_fOrbitDis+m_fOrbitGap,m_fOrbitHeight);

		glNormal3f(0.0,-1.0,0.0);   //远板
		glVertex3d(-m_fOrbitLenth,-m_fOrbitDis,m_fOrbitHeight);
		glVertex3d(-m_fOrbitLenth,-m_fOrbitDis,0);
		glVertex3d( m_fOrbitLenth,-m_fOrbitDis,0);
		glVertex3d( m_fOrbitLenth,-m_fOrbitDis,m_fOrbitHeight);


		glNormal3f(0.0,0.0,1.0);   //上板
		glVertex3d(-m_fOrbitLenth,m_fOrbitDis-m_fOrbitGap,m_fOrbitHeight);
		glVertex3d( m_fOrbitLenth,m_fOrbitDis-m_fOrbitGap,m_fOrbitHeight);
		glVertex3d( m_fOrbitLenth,m_fOrbitDis,m_fOrbitHeight);
		glVertex3d(-m_fOrbitLenth,m_fOrbitDis,m_fOrbitHeight);

		glNormal3f(0.0,-1.0,0.0);  //外板
		glVertex3d(-m_fOrbitLenth,m_fOrbitDis-m_fOrbitGap,m_fOrbitHeight);
		glVertex3d(-m_fOrbitLenth,m_fOrbitDis-m_fOrbitGap,0);
		glVertex3d( m_fOrbitLenth,m_fOrbitDis-m_fOrbitGap,0);
		glVertex3d( m_fOrbitLenth,m_fOrbitDis-m_fOrbitGap,m_fOrbitHeight);

		glNormal3f(0.0,1.0,0.0);   //内板
		glVertex3d(-m_fOrbitLenth,m_fOrbitDis,m_fOrbitHeight);
		glVertex3d(-m_fOrbitLenth,m_fOrbitDis,0);
		glVertex3d( m_fOrbitLenth,m_fOrbitDis,0);
		glVertex3d( m_fOrbitLenth,m_fOrbitDis,m_fOrbitHeight);

	glEnd();


	glTranslated(-m_fOrbitLenth,0,m_fOrbitHeight);
	gluPartialDisk(obj,m_fOrbitDis-m_fOrbitGap,m_fOrbitDis,20,20,180,180);
	glTranslated(0,0,-m_fOrbitHeight);
	gluCylinder(obj,m_fOrbitDis,m_fOrbitDis,m_fOrbitHeight,20,20);
	gluCylinder(obj,m_fOrbitDis-m_fOrbitGap,m_fOrbitDis-m_fOrbitGap,m_fOrbitHeight,20,20);
 


	glTranslated(2.0*m_fOrbitLenth,0,m_fOrbitHeight);
	gluPartialDisk(obj,m_fOrbitDis-m_fOrbitGap,m_fOrbitDis,20,20,0,180);
	glTranslated(0,0,-m_fOrbitHeight);
	gluCylinder(obj,m_fOrbitDis,m_fOrbitDis,m_fOrbitHeight,20,20);
	gluCylinder(obj,m_fOrbitDis-m_fOrbitGap,m_fOrbitDis-m_fOrbitGap,m_fOrbitHeight,20,20);
	glTranslated(-m_fOrbitLenth,0,0);
  
 


	glTranslated(0,0,Z_POS);
	glDisable(GL_LIGHTING);	//关闭光照；
}

void CWorkshop::Draw(GLUquadricObj *obj)
{
	DrawArea();
	DrawOrbit(obj);
	for(int i=0;i<VEHICLE_NUM;i++)
	{
		m_Vehicle[i].Draw(obj);
	}
	for(int i=0;i<STATION_NUM;i++)
	{
		m_Station[i].Draw(obj);
	}
	for(int i=0;i<6;i++)
	{
		m_BucketSorter[i].Draw(obj);
	}
}
int CWorkshop::GetNearestVehicle(CStation Station)//返回离m_Station最近的车在数组中的序号
{
	double fDis[VEHICLE_NUM];
	for(int i=VEHICLE_NUM-1;i>=0;i--)
	{
		fDis[i] = Station.m_fCurrentPos - m_Vehicle[i].m_fCurrentPos;
		if(fDis[i]<0) fDis[i]+= m_fCircleL;
	}
	double fD = fDis[0];
	int n = 0;
	for(int i=0;i<VEHICLE_NUM;i++)
	{

		if(fD > fDis[i])
		{
			n = i;
			fD = fDis[i];
		}
	}
	return n;
}
void CWorkshop::WaitCommand()
{
	int nVehicleNo[STATION_NUM];
	int nStationNo[STATION_NUM];
	for(int i=STATION_NUM-1;i>=0;i--)
	{
		
		if(m_Station[i].m_nMode == STATION_OUT)
		{
			nVehicleNo[i] = GetNearestVehicle(m_Station[i]);
			

		}
		else
		{
			nVehicleNo[i] = -1;
		}
	}
	
/*	for(int i=9;i>0;i--)
	{
		if(nVehicleNo[i]>=0)
		{
			nVehicleNo[i].SetObjectPos(m_Station[nStationNo[i]])
		}
	}

		if(nStartStation>=0)
		{

	*/	


	
}
//利用数据编程程序
/*
车和站的工作状态分别定义如下，当车的状态发生变化时，
一直记录车的目标站号、状态变化等，当原本某台车的目标站号变化时，
或某站的车发生变化时，都用变量表示，可以在下个计算周期中重新申请
例如：某站（A）已经上下申请了某台车（X），若另一站剥夺了车X，
则站A的状态重新变成了申请新车状态，在下一个计算周期时，会重新申请新车

#define NULL_COMMAND 0
#define STATION_REQUEST 400
#define STATION_BUCKET_ON 401
#define STATION_BUCKET_MOVE 402
#define STATION_BUCKET_FINISH 403

//VEHICLE_RUN_MODE
#define VEHICLE_MOVE_ONLY 500
#define VEHICLE_MOVE_TO_STATION 501
#define VEHICLE_IN_STATION 502
#define VEHICLE_BUCKET_ON 503
#define VEHICLE_BUCKET_OFF 504
*/
BOOL CWorkshop::RequestVehicle(int nStationNo)
{
	BOOL bIsSuccess = FALSE;
	if(m_nScheduleGrade == 0)
	{

		bIsSuccess = RequestVehicleSimple(nStationNo);
	}
	if(m_nScheduleGrade == 1)
	{

		bIsSuccess = RequestVehicleAdvanced(nStationNo);
	}
	return bIsSuccess;
}
BOOL CWorkshop::RequestVehicleSimple(int nStationNo)
{
	///if(m_Station[nStationNo].m_nRunMode != NULL_COMMAND)
	//	return FALSE;
	if(m_Station[nStationNo].m_bIsRequested) return FALSE;
//	m_Station[nStationNo].Requst();
	int nVehicleNo = GetNearestVehicle(m_Station[nStationNo]);
	int nVNo = nVehicleNo;
		
	for(int i=0;i<VEHICLE_NUM;i++)
	{
		if(m_Station[nStationNo].m_nMode == STATION_OUT)
		{
			if(!m_Vehicle[nVNo].m_bIsBucket)//出货站，表示将桶送出到车上，因而与空车配对
			{

				if(m_Vehicle[nVNo].m_nStationNo == -1)//未配对车
				{
					m_Station[nStationNo].m_nVehicleNo = nVNo;						//指定站申请到的车号
				//	m_Station[nStationNo].m_nRunMode = STATION_REQUEST;
					m_Station[nStationNo].m_bIsRequested = TRUE;					//站已申请到车
					m_Vehicle[nVNo].SetObject(m_Station[nStationNo].m_fCurrentPos);	//设定申请到的车的目标位置，向该站
					m_Vehicle[nVNo].m_nStationNo = nStationNo;						//指定车要配对的站号
					m_Vehicle[nVNo].m_nRunMode = VEHICLE_MOVE_TO_STATION;
					return TRUE;
				}
				
			}
		//	else
			{
				nVNo--;
				if(nVNo<0) nVNo = VEHICLE_NUM-1;
			}
		}
		else//(m_Station[nStationNo].m_nMode == STATION_IN)//入货站，从小车接收货物，因而与有桶车配对
		{
			if(m_Vehicle[nVNo].m_bIsBucket)
			{
				if((m_Vehicle[nVNo].m_nStationNo >=0)&&(m_Vehicle[nVNo].m_nStationNo <6))
				{
					m_Station[nStationNo].m_nVehicleNo = nVNo;
				//	m_Station[nStationNo].m_nRunMode = STATION_REQUEST;
					m_Station[nStationNo].m_bIsRequested = TRUE;
					m_Vehicle[nVNo].SetObject(m_Station[nStationNo].m_fCurrentPos);
					m_Vehicle[nVNo].m_nStationNo = nStationNo;
					m_Vehicle[nVNo].m_nRunMode = VEHICLE_MOVE_TO_STATION;

					return TRUE;
				}
				
				else
				{
					;
				}
			}

		//	else
			{
				nVNo--;
				if(nVNo<0) nVNo = VEHICLE_NUM-1;
			}
		}
			
	}
	return FALSE;
}

BOOL CWorkshop::RequestVehicleAdvanced(int nStationNo)
{
	///if(m_Station[nStationNo].m_nRunMode != NULL_COMMAND)
	//	return FALSE;
	if(m_Station[nStationNo].m_bIsRequested) return FALSE;
//	m_Station[nStationNo].Requst();
	int nVehicleNo = GetNearestVehicle(m_Station[nStationNo]);
	int nVNo = nVehicleNo;

	for(int i=0;i<VEHICLE_NUM;i++)
	{
		if(m_Station[nStationNo].m_nMode == STATION_OUT)
		{
			if(!m_Vehicle[nVNo].m_bIsBucket)//出货站，表示将桶送出到车上，因而与空车配对
			{

				if(m_Vehicle[nVNo].m_nStationNo == -1)
				{
					m_Station[nStationNo].m_nVehicleNo = nVNo;						//指定站申请到的车号
				//	m_Station[nStationNo].m_nRunMode = STATION_REQUEST;
					m_Station[nStationNo].m_bIsRequested = TRUE;					//站已申请到车
					m_Vehicle[nVNo].SetObject(m_Station[nStationNo].m_fCurrentPos);	//设定申请到的车的目标位置，向该站
					m_Vehicle[nVNo].m_nStationNo = nStationNo;						//指定车要配对的站号
					m_Vehicle[nVNo].m_nRunMode = VEHICLE_MOVE_TO_STATION;
					return TRUE;
				}
				else if((m_Vehicle[nVNo].m_nStationNo<m_Station[nStationNo].m_nID) && m_Vehicle[nVNo].m_bIsMoving)
				{
					int nStationDeprived = m_Vehicle[nVNo].m_nStationNo;
					m_Station[nStationDeprived].m_nRunMode = NULL_COMMAND;

					m_Station[nStationNo].m_nVehicleNo = nVNo;
				//	m_Station[nStationNo].m_nRunMode = STATION_REQUEST;
					m_Station[nStationNo].m_bIsRequested = TRUE;
					m_Vehicle[nVNo].SetObject(m_Station[nStationNo].m_fCurrentPos);
					m_Vehicle[nVNo].m_nStationNo = nStationNo;
					m_Vehicle[nVNo].m_nRunMode = VEHICLE_MOVE_TO_STATION;

				//	RequestVehicle(nStationDeprived);
					m_Station[nStationDeprived].Requst();
					return TRUE;
				}
				else
				{
					;
				}

			}
		//	else
			{
				nVNo--;
				if(nVNo<0) nVNo = VEHICLE_NUM-1;
			}
		}
		else//(m_Station[nStationNo].m_nMode == STATION_IN)//入货站，从小车接收货物，因而与有桶车配对
		{
			if(m_Vehicle[nVNo].m_bIsBucket)
			{
				if((m_Vehicle[nVNo].m_nStationNo >=0)&&(m_Vehicle[nVNo].m_nStationNo <6))
				{
					m_Station[nStationNo].m_nVehicleNo = nVNo;
				//	m_Station[nStationNo].m_nRunMode = STATION_REQUEST;
					m_Station[nStationNo].m_bIsRequested = TRUE;
					m_Vehicle[nVNo].SetObject(m_Station[nStationNo].m_fCurrentPos);
					m_Vehicle[nVNo].m_nStationNo = nStationNo;
					m_Vehicle[nVNo].m_nRunMode = VEHICLE_MOVE_TO_STATION;

					return TRUE;
				}
				else if((m_Vehicle[nVNo].m_nStationNo<m_Station[nStationNo].m_nID) && m_Vehicle[nVNo].m_bIsMoving)
				{
					int nStationDeprived = m_Vehicle[nVNo].m_nStationNo;
					m_Station[nStationDeprived].m_nRunMode = NULL_COMMAND;

					m_Station[nStationNo].m_nVehicleNo = nVNo;
				//	m_Station[nStationNo].m_nRunMode = STATION_REQUEST;
					m_Station[nStationNo].m_bIsRequested = TRUE;
					m_Vehicle[nVNo].SetObject(m_Station[nStationNo].m_fCurrentPos);
					m_Vehicle[nVNo].m_nStationNo = nStationNo;
					m_Vehicle[nVNo].m_nRunMode = VEHICLE_MOVE_TO_STATION;

				//	RequestVehicle(nStationDeprived);
					m_Station[nStationDeprived].Requst();
					return TRUE;
				}
				else
				{
					;
				}
			}

		//	else
			{
				nVNo--;
				if(nVNo<0) nVNo = VEHICLE_NUM-1;
			}
		}
			
	}
	return FALSE;

}
/*
//利用递归调用编程的程序
BOOL CWorkshop::RequestVehicle(int nStationNo)
{
	if(m_Station[nStationNo].m_nRunMode != NULL_COMMAND)
		return FALSE;
	m_Station[nStationNo].Requst();
	int nVehicleNo = GetNearestVehicle(m_Station[nStationNo]);
	int nVNo = nVehicleNo;

	for(int i=0;i<10;i++)
	{
		if(m_Station[nStationNo].m_nMode == STATION_OUT)
		{
			if(!m_Vehicle[nVNo].m_bIsBucket)
			{

				if(m_Vehicle[nVNo].m_nStationNo == -1)
				{
					m_Station[nStationNo].m_nVehicleNo = nVNo;
					m_Station[nStationNo].m_nRunMode = STATION_REQUEST;
					m_Vehicle[nVNo].SetObject(m_Station[nStationNo].m_fCurrentPos);
					m_Vehicle[nVNo].m_nStationNo = nStationNo;
					m_Vehicle[nVNo].m_nRunMode = VEHICLE_MOVE_TO_STATION;
					return TRUE;
				}
				else if((m_Vehicle[nVNo].m_nStationNo<m_Station[nStationNo].m_nID) && m_Vehicle[nVNo].m_bIsMoving)
				{
					int nStationDeprived = m_Vehicle[nVNo].m_nStationNo;
					m_Station[nStationDeprived].m_nRunMode = NULL_COMMAND;

					m_Station[nStationNo].m_nVehicleNo = nVNo;
					m_Station[nStationNo].m_nRunMode = STATION_REQUEST;
					m_Vehicle[nVNo].SetObject(m_Station[nStationNo].m_fCurrentPos);
					m_Vehicle[nVNo].m_nStationNo = nStationNo;
					m_Vehicle[nVNo].m_nRunMode = VEHICLE_MOVE_TO_STATION;

					RequestVehicle(nStationDeprived);
					return TRUE;
				}
				else
				{
					;
				}

			}
		//	else
			{
				nVNo--;
				if(nVNo<0) nVNo = 9;
			}
		}
		else//(m_Station[nStationNo].m_nMode == STATION_IN)
		{
			if(m_Vehicle[nVNo].m_bIsBucket)
			{
				if((m_Vehicle[nVNo].m_nStationNo >=0)&&(m_Vehicle[nVNo].m_nStationNo <6))
				{
					m_Station[nStationNo].m_nVehicleNo = nVNo;
					m_Station[nStationNo].m_nRunMode = STATION_REQUEST;
					m_Vehicle[nVNo].SetObject(m_Station[nStationNo].m_fCurrentPos);
					m_Vehicle[nVNo].m_nStationNo = nStationNo;
					m_Vehicle[nVNo].m_nRunMode = VEHICLE_MOVE_TO_STATION;
					return TRUE;
				}
				else if((m_Vehicle[nVNo].m_nStationNo<m_Station[nStationNo].m_nID) && m_Vehicle[nVNo].m_bIsMoving)
				{
					int nStationDeprived = m_Vehicle[nVNo].m_nStationNo;
					m_Station[nStationDeprived].m_nRunMode = NULL_COMMAND;

					m_Station[nStationNo].m_nVehicleNo = nVNo;
					m_Station[nStationNo].m_nRunMode = STATION_REQUEST;
					m_Vehicle[nVNo].SetObject(m_Station[nStationNo].m_fCurrentPos);
					m_Vehicle[nVNo].m_nStationNo = nStationNo;
					m_Vehicle[nVNo].m_nRunMode = VEHICLE_MOVE_TO_STATION;

					RequestVehicle(nStationDeprived);
					return TRUE;
				}
				else
				{
					;
				}
			}

		//	else
			{
				nVNo--;
				if(nVNo<0) nVNo = 9;
			}
		}
			
	}
	return FALSE;

}

*/

/*
//STATION_RUN_MODE
#define NULL_COMMAND 0
#define STATION_REQUEST 400
#define STATION_BUCKET_ON 401
#define STATION_BUCKET_MOVE 402
#define STATION_BUCKET_FINISH 403

//VEHICLE_RUN_MODE
#define VEHICLE_MOVE_ONLY 500
#define VEHICLE_MOVE_TO_STATION 501
#define VEHICLE_IN_STATION 502
#define VEHICLE_BUCKET_ON 503
#define VEHICLE_BUCKET_OFF 504
*/


void CWorkshop::CalcuState(int nClock)
{
	CFile theFile,theFile2;
	CString strFileName,strFileName2;
	strFileName.Format(_T("D:\\RgvRecorder%d.txt"),((int)(nClock/1000))%10+1);    //在D盘进行数据记录
	strFileName2.Format(_T("D:\\RgvRecorder2%d.txt"),((int)(nClock/1000))%10+1);
	int nIndex1 = (int)(nClock/1000)%10+1;
	static int nIndex0 =0;
	static int nCounter = 0;
	static int nCounter2 = 0;
	if(nIndex0 != nIndex1)
	{
		nCounter = 0;
		nIndex0 = nIndex1;
		theFile.Open(strFileName,CFile::modeCreate|CFile::modeWrite );
		theFile.Write(_T("NewFile\r\n"),18);
		theFile.Close();
		nCounter2 =0;
		theFile2.Open(strFileName2,CFile::modeCreate|CFile::modeWrite );
		theFile2.Write(_T("NewFile\r\n"),18);
		theFile2.Close();
	}
	

	m_nCurrentClock = nClock;
	for(int i=0;i<STATION_NUM;i++)
	{
		if(m_Station[i].m_nRunMode == STATION_REQUEST)
		{
			if(RequestVehicle(i))
			{
				nCounter ++;
				if(theFile.Open(strFileName,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite ))
				{
					

				//	CArchive ar(&theFile,CArchive::store);
					{
						(m_Station[i].m_strRecorder).Format(_T("Index = %d,clock= %d,Station[%d],Request VehicleNo %d\r\n"),nCounter,nClock,i,m_Station[i].m_nVehicleNo);
				//		ar << m_Station[i].m_strRecorder;
						theFile.SeekToEnd( );
						theFile.Write(m_Station[i].m_strRecorder.GetBuffer(),m_Station[i].m_strRecorder.GetLength()*2);
					}
				//	ar.Close();
					theFile.Close();
				}
				
			}
				

		}
		else if(m_Station[i].m_nRunMode == STATION_BUCKET_FINISH)
		{
			int nVehcileNo = m_Station[i].m_nVehicleNo;
			if(m_Station[i].m_nMode == STATION_OUT)
			{
				m_Vehicle[nVehcileNo].m_nRunMode = VEHICLE_BUCKET_ON;
				m_Vehicle[nVehcileNo].m_bIsBucket = TRUE;
				m_Vehicle[nVehcileNo].SetObject(m_fCircleL/2.0);
			}
			else
			{
				m_Vehicle[nVehcileNo].m_nRunMode = VEHICLE_BUCKET_OFF;
				m_Vehicle[nVehcileNo].m_bIsBucket = FALSE;
				m_Vehicle[nVehcileNo].SetObject(0);
				m_Vehicle[nVehcileNo].m_nRunMode = VEHICLE_MOVE_ONLY;
				m_Vehicle[nVehcileNo].m_nStationNo = -1;
			}
			nCounter2++;

			if(theFile2.Open(strFileName2,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite ))
				{
					
					(m_Station[i].m_strRecorder).Format(_T("Index = %d,clock= %d,Station[%d],Send/Get Bucket to/from VehicleNo %d\r\n"),nCounter2,nClock,i,m_Station[i].m_nVehicleNo);
				
					theFile2.SeekToEnd( );
					theFile2.Write(m_Station[i].m_strRecorder.GetBuffer(),m_Station[i].m_strRecorder.GetLength()*2);
					
			
					theFile2.Close();
				}

		}
		else
		{
			//return;
		}
	}
	for(int i=0;i<VEHICLE_NUM;i++)
	{
		if(m_Vehicle[i].m_nRunMode == VEHICLE_IN_STATION)
		{
			int nStationNo = m_Vehicle[i].m_nStationNo;
			if(m_Station[nStationNo].m_nRunMode != STATION_BUCKET_MOVE)
			{
			//	if(m_Station[nStationNo].m_nMode == STATION_IN)
				{
					m_Vehicle[i].m_bIsBucket = FALSE;
				}
				m_Station[nStationNo].m_nRunMode = STATION_BUCKET_MOVE;
				m_Station[nStationNo].m_nStartTime = nClock;
			}
		}
	}
	for(int i=0;i<BUCKET_SORTER_NUM;i++)
	{
		if(m_BucketSorter[i].m_nRunMode == SORTER_REQUEST)
		{
			RequestStation(i);
		}
		if(m_BucketSorter[i].m_nRunMode == SORTER_MOVE_FINISH)
		{
		//	m_BucketSorter[0].m_nRunMode = SORTER_BUCKET_IN;
			m_Station[i].Requst();
		
		}
		m_BucketSorter[i].CalcuState( nClock);
	}

	for(int i=0;i<STATION_NUM;i++)
	{
		m_Station[i].CalcuState(nClock);
	}
	for(int i=0;i<VEHICLE_NUM;i++)
	{
	
		m_Vehicle[i].CalcuState(nClock);
	}

	m_BucketSorter[0].CalcuState(nClock);

	//m_BucketSorter[0].CalcuState( nClock);
}

BOOL CWorkshop::RequestStation(int BucketSorterIndex)
{
	if(!m_Station[BucketSorterIndex].m_bIsBucket)
	{
		m_BucketSorter[BucketSorterIndex].BucketMove();
		return TRUE;
	}

	return FALSE;
}