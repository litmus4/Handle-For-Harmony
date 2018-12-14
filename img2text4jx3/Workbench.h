#pragma once
#include "afxwin.h"
#include <string>
#include <vector>

class IBench
{
public:
	IBench(){}
	virtual ~IBench();

	virtual bool LoadImage(const TCHAR* szImagePath);
	virtual int RunOCR() = 0;
	virtual const TCHAR* GetTextByIndex(int iIndex) = 0;
	virtual void End(){}

protected:
	virtual void Reset(){}

	std::string m_strImagePath;
	std::vector<std::string*> m_vecCacheTexts;
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