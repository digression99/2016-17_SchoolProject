
// CGOGL2014.h : CGOGL2014 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CCGOGL2014App:
// �� Ŭ������ ������ ���ؼ��� CGOGL2014.cpp�� �����Ͻʽÿ�.
//

class CCGOGL2014App : public CWinAppEx
{
public:
	CCGOGL2014App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCGOGL2014App theApp;
