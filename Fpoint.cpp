// fpoint.cpp : implementation file
//
#include "stdafx.h"
#include "fpoint.h"
#include "math.h"

CDPoint::CDPoint( )
{
	x=0.0f;
	y=0.0f;
}

CDPoint::CDPoint( double initX, double initY )
{
	x=initX;
	y=initY;
}

CDPoint& CDPoint::operator=(const CDPoint& other)
{
	x=other.x;			   
	y=other.y;
	return *this;
}


CDPoint::operator CPoint()
{
	return CPoint(long(x),long(y));
}

CDPoint::operator POINT()
{
	POINT point;
	point.x=(long)x;
	point.y=(long)y;
	return point;
}

//////////////////////////		 CFSIZE
CDSize::CDSize( )
{
	cx=cy=0.0f;
}

CDSize::CDSize( double initX, double initY )
{
	cx=initX;
	cy=initY;
}

CDSize& CDSize::operator=(CDSize& other)
{
	cx=other.cx;
	cy=other.cy;
	return *this;
}

CDSize::operator CSize()
{
	return CSize(long(cx),long(cy));
}

CDSize::operator SIZE()
{
	SIZE size;
	size.cx=(long)cx;
	size.cy=(long)cy;
	return size;
}

/////////////////////////			 CDRect
CDRect::CDRect( )
{
	left=top=right=bottom=0.0f;
}

CDRect::CDRect( double l, double t, double r, double b )
{
	left=l;
	top=t;
	right=r;
	bottom=b;
}

CDRect::CDRect( DPOINT topLeft, DPOINT bottomRight )
{
	left=topLeft.x;
	top=topLeft.y;
	right=bottomRight.x;
	bottom=bottomRight.y;
}

CDRect::CDRect( DPOINT point, DSIZE size )
{
	left=point.x;
	top=point.y;
	right=point.x+size.cx;
	bottom=point.y+size.cy;
}

void CDRect::SetRect( double l, double t, double r, double b )
{
	left=l;
	top=t;
	right=r;
	bottom=b;
}

BOOL CDRect::IsIntersectRect(const CDRect& limitrect)
{
	if((right-limitrect.left)*(limitrect.left-left)<=0 &&
	   (right-limitrect.right)*(limitrect.right-left)<=0)
	{
		if((limitrect.right-left)*(left-limitrect.left)<=0) return FALSE;
		else
		{
			if((top-limitrect.top)*(limitrect.top-bottom)<=0&&
			   (top-limitrect.bottom)*(limitrect.bottom-bottom)<=0&&
			   (limitrect.top-top)*(top-limitrect.bottom)<=0)
			   return FALSE;
			else return TRUE;
		}
	}
	else return TRUE;
}



BOOL CDRect::PtInRect( const DPOINT& point ) const
{
	if((right-point.x)*(point.x-left)>0 && (top-point.y)*(point.y-bottom)>0) return TRUE;
	else return FALSE;
	
}

BOOL CDRect::IsRectEmpty( ) const
{
	if(left==right && top==bottom) return TRUE;
	else return FALSE;
}

void CDRect::NormalizeRect( )
{
    double a;
    if(left>right)
    {
        a=left;
        left=right;
        right=a;
    }
    if(top<bottom)
    {
        a=top;
        top=bottom;
        bottom=a;
    }
}

CDRect& CDRect::operator=(const CDRect& other)
{
	top=other.top;
	bottom=other.bottom;
	left=other.left;
	right=other.right;
	return *this;
}

BOOL CDRect::operator==(const CDRect& other) const
{
	if(top==other.top && bottom==other.bottom && left==other.left && right==other.right)
		return TRUE;
	else return FALSE;
}

BOOL CDRect::operator!=(const CDRect& other) const
{
	if(top==other.top && bottom==other.bottom && left==other.left && right==other.right)
		return FALSE;
	else return TRUE;
}

void CDRect::operator+=(DPOINT other)
{
	top+=other.y;
	bottom+=other.y;
	left+=other.x;
	right+=other.x;
}
	 
CDRect::operator const CRect&()	const
{
	return CRect(long(left),long(top),long(right),long(bottom));
}	   

CDRect::operator CRect() const
{
	return CRect(long(left),long(top),long(right),long(bottom));
}

CDRect::operator RECT() const
{
	RECT rect;
	rect.left=(long)left;
	rect.top=(long)top;
	rect.right=(long)right;
	rect.bottom=(long)bottom;
	return rect;
}

////////////////////////////////////////////////////////////////////////

CArchive& AFXAPI operator<<(CArchive& ar, const CDPoint& fpoint)
{
	ar<<fpoint.x<<fpoint.y;
	return ar;
}

CArchive& AFXAPI operator>>(CArchive& ar, CDPoint& fpoint)
{
	ar>>fpoint.x>>fpoint.y;
	return ar;
}

CArchive& AFXAPI operator<<(CArchive& ar, const CDSize& fsize)
{
	ar<<fsize.cx<<fsize.cy;
	return ar;
}

CArchive& AFXAPI operator>>(CArchive& ar, CDSize& fsize)
{
	ar>>fsize.cx>>fsize.cy;
	return ar;
}

CArchive& AFXAPI operator<<(CArchive& ar, const CDRect& frect)
{
	ar<<frect.left<<frect.top<<frect.right<<frect.bottom;
	return ar;
}

CArchive& AFXAPI operator>>(CArchive& ar, CDRect& frect)
{
	ar>>frect.left>>frect.top>>frect.right>>frect.bottom;
	return ar;
}

double CDRect::GetArea()	const
{
	return fabs((right-left)*(top-bottom));
}
