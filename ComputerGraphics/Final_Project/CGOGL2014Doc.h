
// CGOGL2014Doc.h : CCGOGL2014Doc Ŭ������ �������̽�
//


#pragma once


class CCGOGL2014Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CCGOGL2014Doc();
	DECLARE_DYNCREATE(CCGOGL2014Doc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CCGOGL2014Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


