
// CGOGL2014Doc.cpp : CCGOGL2014Doc Ŭ������ ����
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


// CCGOGL2014Doc ����/�Ҹ�

CCGOGL2014Doc::CCGOGL2014Doc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CCGOGL2014Doc::~CCGOGL2014Doc()
{
}

BOOL CCGOGL2014Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CCGOGL2014Doc serialization

void CCGOGL2014Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CCGOGL2014Doc ����

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


// CCGOGL2014Doc ���
