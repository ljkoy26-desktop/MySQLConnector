
// MySqlMFC1.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

// CMySqlMFC1App:
// �� Ŭ������ ������ ���ؼ��� MySqlMFC1.cpp�� �����Ͻʽÿ�.
//

class CMySqlMFC1App : public CWinApp
{
public:
	CMySqlMFC1App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMySqlMFC1App theApp;