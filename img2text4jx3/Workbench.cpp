#include "stdafx.h"
#include "Workbench.h"

IBench::~IBench()
{
	std::vector<std::string*>::iterator iter = m_vecCacheTexts.begin();
	for (; iter != m_vecCacheTexts.end(); iter++)
		delete *iter;
}

bool IBench::LoadImage(const TCHAR* szImagePath)
{
	if (szImagePath)
	{
		m_strImagePath = szImagePath;
		return true;
	}
	return false;
}

DocBench::DocBench()
: m_pDoc(NULL)
{
	//
}

DocBench::~DocBench()
{
	if (m_pDoc)
	{
		delete m_pDoc;
		m_pDoc = NULL;
	}
}

bool DocBench::LoadImage(const TCHAR* szImagePath)
{
	bool bRet = IBench::LoadImage(szImagePath);
	//FLAGJK
	return bRet;
}

int DocBench::RunOCR()
{
	//FLAGJK
	return 0;
}

const TCHAR* DocBench::GetTextByIndex(int iIndex)
{
	//FLAGJK
	return NULL;
}

void DocBench::End()
{
	//FLAGJK
}