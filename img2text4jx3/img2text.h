// img2text.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// Cimg2textApp:
// �йش����ʵ�֣������ img2text.cpp
//

class Cimg2textApp : public CWinApp
{
public:
	Cimg2textApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cimg2textApp theApp;
