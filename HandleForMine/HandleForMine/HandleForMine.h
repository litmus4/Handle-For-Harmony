
// HandleForMine.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHandleForMineApp: 
// �йش����ʵ�֣������ HandleForMine.cpp
//

class CHandleForMineApp : public CWinApp
{
public:
	CHandleForMineApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHandleForMineApp theApp;
