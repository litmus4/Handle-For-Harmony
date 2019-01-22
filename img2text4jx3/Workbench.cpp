#include "stdafx.h"
#include "Workbench.h"
#include "api\baseapi.h"
#include "allheaders.h"

std::string Utf8ToStr(const std::string& stru)
{
	std::string strRet;
	if (stru.empty())
		return strRet;
	int iSize = MultiByteToWideChar(CP_UTF8, 0, stru.c_str(), -1, NULL, 0);
	if (iSize != 0)
	{
		LPWSTR wszBuf = new WCHAR[iSize];
		MultiByteToWideChar(CP_UTF8, 0, stru.c_str(), -1, wszBuf, iSize);
		iSize = WideCharToMultiByte(CP_ACP, 0, wszBuf, -1, NULL, 0, NULL, NULL);
		if (iSize != 0)
		{
			LPSTR szBuf = new CHAR[iSize];
			WideCharToMultiByte(CP_ACP, 0, wszBuf, -1, szBuf, iSize, NULL, NULL);
			strRet = szBuf;
			delete[] szBuf;
		}
		delete[] wszBuf;
	}
	return strRet;
}

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

TrlBench::TrlBench()
: m_pPix(NULL)
, m_pBoxes(NULL)
{
	m_pApi = new tesseract::TessBaseAPI();
	m_pApi->Init(NULL, "chi_sim");
}

TrlBench::~TrlBench()
{
	Reset();
	//delete m_pApi;
}

bool TrlBench::LoadImage(const TCHAR* szImagePath)
{
	bool bRet = IBench::LoadImage(szImagePath);
	if (!bRet) return false;

	m_pPix = pixRead(szImagePath);
	if (m_pPix)
	{
		m_pApi->SetImage(m_pPix);
		return bRet;
	}
	return false;
}

int TrlBench::RunOCR()
{
	//if (m_pBoxes) delete m_pBoxes;
	IBench::RunOCR();
	m_pBoxes = m_pApi->GetComponentImages(tesseract::RIL_TEXTLINE, true, NULL, NULL);
	return (m_pBoxes ? m_pBoxes->n : 0);
}

const TCHAR* TrlBench::GetTextByIndex(int iIndex)
{
	if (!m_pApi || !m_pBoxes)
		return NULL;

	const TCHAR* szText = GetCacheText(iIndex);
	if (!szText)
	{
		Box* pBox = boxaGetBox(m_pBoxes, iIndex, L_CLONE);
		m_pApi->SetRectangle(pBox->x, pBox->y, pBox->w, pBox->h);
		std::string strText = Utf8ToStr(m_pApi->GetUTF8Text());
		SetCacheText(iIndex, strText);
		return strText.c_str();
	}
	return szText;
}

void TrlBench::Reset()
{
	//if (m_pPix)
	//{
	//	delete m_pPix;
	//	m_pPix = NULL;
	//}
	//if (m_pBoxes)
	//{
	//	delete m_pBoxes;
	//	m_pBoxes = NULL;
	//}
	IBench::Reset();
}