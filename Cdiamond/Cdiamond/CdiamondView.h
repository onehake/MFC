
// CdiamondView.h : CCdiamondView 类的接口
//

#pragma once


class CCdiamondView : public CView
{
protected: // 仅从序列化创建
	CCdiamondView();
	DECLARE_DYNCREATE(CCdiamondView)

// 特性
public:
	CCdiamondDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	
	virtual void Cdiamond(CDC* pDC,CPoint p[]);//绘制金钢石函数
	virtual void CCenter(CRect rect,CDC* pDC, float radious,float angle,CPoint p[]);
	virtual int in(CPoint p1[],CPoint p2[]);
// 实现
public:
	virtual ~CCdiamondView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CdiamondView.cpp 中的调试版本
inline CCdiamondDoc* CCdiamondView::GetDocument() const
   { return reinterpret_cast<CCdiamondDoc*>(m_pDocument); }
#endif

