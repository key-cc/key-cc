
// BIYESHEJIView.cpp : CBIYESHEJIView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "BIYESHEJI.h"
#endif

#include "BIYESHEJIDoc.h"
#include "BIYESHEJIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBIYESHEJIView

IMPLEMENT_DYNCREATE(CBIYESHEJIView, CView)

BEGIN_MESSAGE_MAP(CBIYESHEJIView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CBIYESHEJIView ����/����

CBIYESHEJIView::CBIYESHEJIView()
{
	// TODO:  �ڴ˴���ӹ������

}

CBIYESHEJIView::~CBIYESHEJIView()
{
}

BOOL CBIYESHEJIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CBIYESHEJIView ����

void CBIYESHEJIView::OnDraw(CDC* /*pDC*/)
{
	CBIYESHEJIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CBIYESHEJIView ��ӡ

BOOL CBIYESHEJIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CBIYESHEJIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CBIYESHEJIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CBIYESHEJIView ���

#ifdef _DEBUG
void CBIYESHEJIView::AssertValid() const
{
	CView::AssertValid();
}

void CBIYESHEJIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBIYESHEJIDoc* CBIYESHEJIView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBIYESHEJIDoc)));
	return (CBIYESHEJIDoc*)m_pDocument;
}
#endif //_DEBUG


// CBIYESHEJIView ��Ϣ�������
