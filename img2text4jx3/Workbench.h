#pragma once
#include "afxwin.h"
#include <string>
#include <map>

class IBench
{
public:
	IBench(){}
	virtual ~IBench();

	virtual bool LoadImage(const TCHAR* szImagePath);
	virtual int RunOCR();
	virtual const TCHAR* GetTextByIndex(int iIndex) = 0;
	virtual void End();

	const TCHAR* GetCacheText(int iIndex);
	void SetCacheText(int iIndex, const std::string& strText);

protected:
	virtual void Reset();

	std::string m_strImagePath;
	std::map<int, std::string> m_mapCacheTexts;
};

class IDoc;
class IImages;

class DocBench : public IBench
{
public:
	DocBench();
	~DocBench();

	bool LoadImage(const TCHAR* szImagePath);
	int RunOCR();
	const TCHAR* GetTextByIndex(int iIndex);
	void End();

protected:
	void Reset();

	IDoc* m_pDoc;
	IImages* m_pImages;
};

struct Pix;
struct Boxa;
namespace tesseract
{
	class TessBaseAPI;
}

class TrlBench : public IBench
{
public:
	TrlBench();
	~TrlBench();

	bool LoadImage(const TCHAR* szImagePath);
	int RunOCR();
	const TCHAR* GetTextByIndex(int iIndex);

protected:
	void Reset();

	Pix* m_pPix;
	tesseract::TessBaseAPI* m_pApi;
	Boxa* m_pBoxes;
};