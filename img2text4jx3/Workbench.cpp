#include "stdafx.h"
#include "Workbench.h"

IBench::~IBench()
{
	Reset();
}

bool IBench::LoadImage(const TCHAR* szImagePath)
{
	if (szImagePath)
	{
		m_strImagePath = szImagePath;
		Reset();
		return true;
	}
	return false;
}

int IBench::RunOCR()
{
	m_mapCacheTexts.clear();
	return 0;
}

void IBench::End()
{
	Reset();
}

const TCHAR* IBench::GetCacheText(int iIndex)
{
	std::map<int, std::string>::iterator iter = m_mapCacheTexts.find(iIndex);
	if (iter != m_mapCacheTexts.end())
		return iter->second.c_str();
	return NULL;
}

void IBench::SetCacheText(int iIndex, const std::string& strText)
{
	m_mapCacheTexts.insert(std::make_pair(iIndex, strText));
}

void IBench::Reset()
{
	m_mapCacheTexts.clear();
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
	if (!bRet) return false;
	
	m_pDoc = new IDoc();
	m_pDoc->CreateDispatch("MODI.Document");
	m_pDoc->Create(szImagePath);

	return bRet;
}

int DocBench::RunOCR()
{
	if (!m_pDoc) return 0;

	m_pDoc->OCR(miLANG_CHINESE_SIMPLIFIED, 0, 0);
	if (m_pImages) delete m_pImages;
	IBench::RunOCR();
	m_pImages = new IImages(m_pDoc->GetImages());
	return m_pImages->GetCount();
}

const TCHAR* DocBench::GetTextByIndex(int iIndex)
{
	if (!m_pDoc || !m_pImages)
		return NULL;

	const TCHAR* szText = GetCacheText(iIndex);
	if (!szText)
	{
		IImage image = m_pImages->GetItem(iIndex);
		ILayout layout = image.GetLayout();
		std::string strText = layout.GetText();
		SetCacheText(iIndex, strText);
		return strText.c_str();
	}
	return szText;
}

void DocBench::End()
{
	if (m_pDoc)
	{
		m_pDoc->Close(0);
		m_pDoc->ReleaseDispatch();
	}
	IBench::End();
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
	IBench::Reset();
}