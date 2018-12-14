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
, m_pImages(NULL)
{
	//
}

DocBench::~DocBench()
{
	Reset();
}

bool DocBench::LoadImage(const TCHAR* szImagePath)
{
	bool bRet = IBench::LoadImage(szImagePath);
	
	m_pDoc = new IDoc();
	m_pDoc->CreateDispatch("MODI.Document");
	m_pDoc->Create(szImagePath);

	return bRet;
}

int DocBench::RunOCR()
{
	if (!m_pDoc) return 0;

	m_pDoc->OCR(miLANG_CHINESE_SIMPLIFIED, 0, 0);
	m_pImages = new IImages(m_pDoc->GetImages());
	return m_pImages->GetCount();
}

const TCHAR* DocBench::GetTextByIndex(int iIndex)
{
	if (!m_pDoc || !m_pImages)
		return NULL;

	IImage image = m_pImages->GetItem(iIndex);
	ILayout layout = image.GetLayout();
	return layout.GetText();
}

void DocBench::End()
{
	if (m_pDoc)
	{
		m_pDoc->Close(0);
		m_pDoc->ReleaseDispatch();
	}
	Reset();
}

void DocBench::Reset()
{
	if (m_pDoc)
	{
		delete m_pDoc;
		m_pDoc = NULL;
	}
	if (m_pImages)
	{
		delete m_pImages;
		m_pImages = NULL;
	}
}