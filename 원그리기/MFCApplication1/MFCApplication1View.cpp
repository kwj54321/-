﻿
// MFCApplication1View.cpp: CMFCApplication1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMFCApplication1View 생성/소멸

CMFCApplication1View::CMFCApplication1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_bClick = FALSE;
	m_tcRGB = 'r';
}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View 그리기

void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CBrush br, * pOldBr = NULL;
	int nRadius = (int)m_dRadius;
	if (m_tcRGB == 'r')
	{
		br.CreateSolidBrush(RGB(nRadius % 256, 0, 0));
		pOldBr = (CBrush *)pDC->SelectObject(&br);
	}
	else if (m_tcRGB == 'g')
	{
		br.CreateSolidBrush(RGB(0, nRadius % 256, 0));
		pOldBr = (CBrush*)pDC->SelectObject(&br);
	}
	else if (m_tcRGB == 'b')
	{
		br.CreateSolidBrush(RGB(0, 0, nRadius % 256));
		pOldBr = (CBrush*)pDC->SelectObject(&br);
	}

	pDC->Ellipse(m_ptMiddle.x - (int)(m_dRadius), m_ptMiddle.y - (int)(m_dRadius),
		m_ptMiddle.x + (int)(m_dRadius), m_ptMiddle.y + (int)(m_dRadius));

	if (m_tcRGB == 'r' || m_tcRGB == 'g' || m_tcRGB == 'b')
	{
		pDC->SelectObject(pOldBr);
		br.DeleteObject();
	}

}


// CMFCApplication1View 인쇄

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCApplication1View 진단

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 메시지 처리기


void CMFCApplication1View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == 'r' || nChar == 'R') m_tcRGB = 'r';
	else if (nChar == 'g' || nChar == 'G') m_tcRGB = 'g';
	else if (nChar == 'b' || nChar == 'B') m_tcRGB = 'b';
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptMiddle = point;
	m_dRadius = 0;
	m_bClick = TRUE;
	CView::OnLButtonDown(nFlags, point);
}


void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bClick)
	{
		int x = point.x - m_ptMiddle.x;
		int y = point.y - m_ptMiddle.y;
		m_dRadius = sqrt(((double)x * x) + ((double)y * y));
		Invalidate(TRUE);
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	int x = point.x - m_ptMiddle.x;
	int y = point.y - m_ptMiddle.y;
	m_dRadius = sqrt(((double)x * x) + ((double)y * y));
	Invalidate(TRUE);

	m_bClick = FALSE;
	CView::OnLButtonUp(nFlags, point);
}
