#pragma once
// CGOGL2014View.h : CCGOGL2014View 클래스의 인터페이스
//

#pragma once
#include "stdafx.h"
#include "CGOGL2014.h"
#include "CGOGL2014Doc.h"


class COpenGLContext;

class CCGOGL2014View : public CView
{
protected: // serialization에서만 만들어집니다.
	CCGOGL2014View();
	DECLARE_DYNCREATE(CCGOGL2014View)

// 특성입니다.
public:
	CCGOGL2014Doc* GetDocument() const;
	
// 작업입니다.
public:

	TDObj tdobj;
	//vector<TDObj *> tdobjVec;
	MatrixConversion mc;
	Light light;
	Floor f;

	bool isLanded;
	bool isCleared;

	int i;
	int j;
	int k;
	int l;

	void createObjVector();
	void setObjVector(); // 여러 가지의 물체를 생성.
	void drawObjVector();
	void setElements();


	//////
	void quad(int a, int b, int c, int d);
	void colorCube();
	void init();
	void display();

//	glm::mat4 
protected:
	bool GetRenderingContext(void);
	bool GetOldStyleRenderingContext(void);
	bool SetupModernPixelFormat(void);

	CDC* m_pDC;
	HGLRC m_hRC;
	

	COpenGLContext *m_OGLContext;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CCGOGL2014View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:



	

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};

#ifndef _DEBUG  // CGOGL2014View.cpp의 디버그 버전
inline CCGOGL2014Doc* CCGOGL2014View::GetDocument() const
   { return reinterpret_cast<CCGOGL2014Doc*>(m_pDocument); }
#endif

