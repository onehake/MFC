
// CdiamondView.cpp : CCdiamondView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCdiamondView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCdiamondView 构造/析构

CCdiamondView::CCdiamondView()
{
	// TODO: 在此处添加构造代码

}

CCdiamondView::~CCdiamondView()
{
}

BOOL CCdiamondView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCdiamondView 绘制
void CCdiamondView::CCenter(CRect rect,CDC* pDC, float radious,float angle,CPoint p[] )//生成点
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

void CCdiamondView::Cdiamond(CDC* pDC,CPoint p[])//绘制
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

int CCdiamondView::in(CPoint p1[],CPoint p2[])//两圆相交？
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

	CRect rect;//定义矩形
	GetClientRect(&rect);//获得客户区矩形
	pDC->SetMapMode(MM_ANISOTROPIC);//设置映射模
	pDC->SetWindowExt(rect.Width(),rect.Height());//设置窗口
	pDC->SetViewportExt(rect.Width(),-rect.Height());//设置视区：x轴水平方向为正，y轴垂直向上方向为正
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//设置客户区中心为坐标系原点
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);//客户区矩形较正

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

	// TODO: 在此处为本机数据添加绘制代码
}


// CCdiamondView 打印


void CCdiamondView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCdiamondView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCdiamondView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCdiamondView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CCdiamondView 诊断

#ifdef _DEBUG
void CCdiamondView::AssertValid() const
{
	CView::AssertValid();

}

void CCdiamondView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCdiamondDoc* CCdiamondView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCdiamondDoc)));
	return (CCdiamondDoc*)m_pDocument;
}
#endif //_DEBUG


// CCdiamondView 消息处理程序
