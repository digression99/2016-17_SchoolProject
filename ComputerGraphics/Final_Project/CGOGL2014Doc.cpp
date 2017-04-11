
// CGOGL2014Doc.cpp : CCGOGL2014Doc 클래스의 구현
//

#include "stdafx.h"
#include "CGOGL2014.h"

#include "CGOGL2014Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCGOGL2014Doc

IMPLEMENT_DYNCREATE(CCGOGL2014Doc, CDocument)

BEGIN_MESSAGE_MAP(CCGOGL2014Doc, CDocument)
END_MESSAGE_MAP()


// CCGOGL2014Doc 생성/소멸

CCGOGL2014Doc::CCGOGL2014Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CCGOGL2014Doc::~CCGOGL2014Doc()
{
}

BOOL CCGOGL2014Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CCGOGL2014Doc serialization

void CCGOGL2014Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CCGOGL2014Doc 진단

#ifdef _DEBUG
void CCGOGL2014Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCGOGL2014Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCGOGL2014Doc 명령
