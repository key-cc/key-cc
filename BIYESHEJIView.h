
// BIYESHEJIView.h : CBIYESHEJIView ��Ľӿ�
//

#pragma once


class CBIYESHEJIView : public CView
{
protected: // �������л�����
	CBIYESHEJIView();
	DECLARE_DYNCREATE(CBIYESHEJIView)

// ����
public:
	CBIYESHEJIDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CBIYESHEJIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // BIYESHEJIView.cpp �еĵ��԰汾
inline CBIYESHEJIDoc* CBIYESHEJIView::GetDocument() const
   { return reinterpret_cast<CBIYESHEJIDoc*>(m_pDocument); }
#endif

