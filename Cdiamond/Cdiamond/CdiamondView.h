
// CdiamondView.h : CCdiamondView ��Ľӿ�
//

#pragma once


class CCdiamondView : public CView
{
protected: // �������л�����
	CCdiamondView();
	DECLARE_DYNCREATE(CCdiamondView)

// ����
public:
	CCdiamondDoc* GetDocument() const;

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
	
	virtual void Cdiamond(CDC* pDC,CPoint p[]);//���ƽ��ʯ����
	virtual void CCenter(CRect rect,CDC* pDC, float radious,float angle,CPoint p[]);
	virtual int in(CPoint p1[],CPoint p2[]);
// ʵ��
public:
	virtual ~CCdiamondView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CdiamondView.cpp �еĵ��԰汾
inline CCdiamondDoc* CCdiamondView::GetDocument() const
   { return reinterpret_cast<CCdiamondDoc*>(m_pDocument); }
#endif

