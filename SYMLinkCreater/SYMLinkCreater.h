
// SYMLinkCreater.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSYMLinkCreaterApp:
// �� Ŭ������ ������ ���ؼ��� SYMLinkCreater.cpp�� �����Ͻʽÿ�.
//

class CSYMLinkCreaterApp : public CWinApp
{
public:
	CSYMLinkCreaterApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSYMLinkCreaterApp theApp;