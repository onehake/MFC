
// CdiamondView.cpp : CCdiamondView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Cdiamond.h"
#endif

#include "CdiamondDoc.h"
#include "CdiamondView.h"

#include<math.h>
#include<time.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX 30
#define MIN 29
#define PI 3.1415926
// CCdiamondView

IMPLEMENT_DYNCREATE(CCdiamondView, CView)

BEGIN_MESSAGE_MAP(CCdiamondView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCdiamondView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCdiamondView ����/����

CCdiamondView::CCdiamondView()
{
	// TODO: �ڴ˴���ӹ������

}

CCdiamondView::~CCdiamondView()
{
}

BOOL CCdiamondView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCdiamondView ����
void CCdiamondView::CCenter(CRect rect,CDC* pDC, float radious,float angle,CPoint p[] )//���ɵ�
{
	srand(time(0));
	int x=rand()%rect.Width();
	int y=rand()%rect.Height();

	for (int i=0;i<MAX;i++)
	{
		float s=((360/MAX)*(i+1)+angle)*(PI/180);
		p[i].x=radious*cos(s)+x;
		p[i].y=radious*sin(s)+y;
	}
}

void CCdiamondView::Cdiamond(CDC* pDC,CPoint p[])//����
{
	for (int i=0;i<MAX-1;i++)
	{
		for (int j=i+1;j<MAX;j++)
		{
			pDC->MoveTo(p[i]);
			pDC->LineTo(p[j]);
		}
	}
	
}

int CCdiamondView::in(CPoint p1[],CPoint p2[])//��Բ�ཻ��
{
	
		for (int i=0;i<MAX;i++)
		{
			for (int j=0;j<MIN;j++)
			{
				if (p1[i].x<=p2[j].x&&p1[i].y<=p2[j].y)
					return 0;
			}
		}
		return 1;
}

void CCdiamondView::OnDraw(CDC* pDC)
{
	CCdiamondDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rect;//�������
	GetClientRect(&rect);//��ÿͻ�������
	pDC->SetMapMode(MM_ANISOTROPIC);//����ӳ��ģ
	pDC->SetWindowExt(rect.Width(),rect.Height());//���ô���
	pDC->SetViewportExt(rect.Width(),-rect.Height());//����������x��ˮƽ����Ϊ����y�ᴹֱ���Ϸ���Ϊ��
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//���ÿͻ�������Ϊ����ϵԭ��
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);//�ͻ������ν���

	CPoint p1[MAX],p2[MIN];
	
	do{
		CCenter(rect,pDC,200,0,p1);
		CCenter(rect,pDC,200,0,p2);
	}while (in(p1,p2)==0);

	static int j=10;
	//while (j)
	{	

		Cdiamond(pDC,p1);
		Cdiamond(pDC,p2);

	/*	Cdiamond(pDC,200,60*j);
		Sleep(300);
		pDC->Rectangle(-2000,2000,2000,-2000);
		j=j+10;
	//	RedrawWindow();
	*/
	}

	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CCdiamondView ��ӡ


void CCdiamondView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCdiamondView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCdiamondView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCdiamondView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CCdiamondView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCdiamondView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCdiamondView ���

#ifdef _DEBUG
void CCdiamondView::AssertValid() const
{
	CView::AssertValid();

}

void CCdiamondView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCdiamondDoc* CCdiamondView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCdiamondDoc)));
	return (CCdiamondDoc*)m_pDocument;
}
#endif //_DEBUG


// CCdiamondView ��Ϣ�������
