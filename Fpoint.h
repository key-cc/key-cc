// fpoint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDPoint document
#ifndef  _CFPoint
#define _CFPoint
struct DPOINT
{
	double x;
	double y;
};

struct DSIZE
{
	double cx;
	double cy;
};

struct DRECT
{
	double top;
	double bottom;
	double left;
	double right;
};

class CDPoint : public DPOINT
{
public:
	CDPoint( );
	CDPoint( double initX, double initY );

    CDPoint& operator=(const CDPoint& other);
    BOOL operator==(const CDPoint& other)
		{
			if(x==other.x && y==other.y) return TRUE;
			else return FALSE;
		}
    CDPoint operator-(const DPOINT other) const
		{ return CDPoint(x-other.x , y-other.y); }
	operator CPoint();
	operator POINT();
};

class CDSize : public DSIZE
{
public:
	CDSize( );
	CDSize( double initX, double initY );
    CDSize& operator=(CDSize& other);
	operator CSize();
	operator SIZE();
};

class CDRect : public DRECT
{
public:
	CDRect( );
	CDRect( double l, double t, double r, double b );

	CDRect( DPOINT point, DSIZE size );
	CDRect( DPOINT topLeft, DPOINT bottomRight );
	BOOL IsRectEmpty( ) const;
	double Width( ) const { return right-left; }
	double Height( ) const { return top-bottom; }
	void SetRect( double l, double t, double r, double b );
	double GetArea() const;
    BOOL PtInRect( const DPOINT& point ) const;
	void NormalizeRect( );
	BOOL IsIntersectRect(const CDRect& limitrect);

	CDPoint BottomRight( ) { return CDPoint(right,bottom); }
	CDPoint TopLeft( ) { return CDPoint(left,top); }
	CDRect& operator=(const CDRect& other);
	BOOL operator==(const CDRect& other) const;
	BOOL operator!=(const CDRect& other) const;
	void operator+=(DPOINT other);
	operator const CRect&() const;
	operator RECT() const;
	operator CRect() const;
};

CArchive& AFXAPI operator<<(CArchive& ar, const CDPoint& fpoint);
CArchive& AFXAPI operator>>(CArchive& ar, CDPoint& fpoint);
CArchive& AFXAPI operator<<(CArchive& ar, const CDSize& fsize);
CArchive& AFXAPI operator>>(CArchive& ar, CDSize& fsize);
CArchive& AFXAPI operator<<(CArchive& ar, const CDRect& frect);
CArchive& AFXAPI operator>>(CArchive& ar, CDRect& frect);
#endif
