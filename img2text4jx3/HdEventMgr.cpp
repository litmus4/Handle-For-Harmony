#include "HdEventMgr.h"

HdEvent::HdEvent()
{
}

HdEvent::HdEvent(const TCHAR* szKeyword)
: m_strKeyword(szKeyword)
{
}

HdEvent::~HdEvent()
{
}

void HdEvent::SetKeyword(const TCHAR* szKeyword)
{
	if (!szKeyword) return;
	m_strKeyword = szKeyword;
}

std::string HdEvent::GetKeyword()
{
	return m_strKeyword;
}

void HdEvent::AddKeyClick(WORD wVk, float fDownTime, float fUpTime)
{
	KeyClick click;
	click.wVk = wVk;
	click.fDownTime = fDownTime;
	click.fUpTime = fUpTime;

	m_vecClicks.push_back(click);
	m_mapClickFlow.insert(std::make_pair(fDownTime, &m_vecClicks.back()));
}

void HdEvent::RemoveKeyClick(int iIndex)
{
	if (iIndex < 0 || iIndex >= m_vecClicks.size())
		return;

	KeyClick& click = m_vecClicks[iIndex];
	std::multimap<float, KeyClick*>::iterator itMap = m_mapClickFlow.begin();
	for (; itMap != m_mapClickFlow.end(); itMap++)
	{
		if (itMap->second == &click)
		{
			m_mapClickFlow.erase(itMap);
			break;
		}
	}
	m_vecClicks.erase(m_vecClicks.begin() + iIndex);
}

HdEvent::KeyClick* HdEvent::GetKeyClick(int iIndex)
{
	if (iIndex < 0 || iIndex >= m_vecClicks.size())
		return NULL;
	return &m_vecClicks[iIndex];
}

int HdEvent::GetKeyClickNum()
{
	return m_vecClicks.size();
}

void HdEvent::ClearAllKeyClicks()
{
	m_vecClicks.clear();
	m_mapClickFlow.clear();
}

bool HdEvent::CheckAndPopClickTimeUp(float fTime, std::vector<KeyClick*>& vecOut)
{
	bool bRet = false;
	std::multimap<float, KeyClick*>::iterator itMap = m_mapClickFlow.begin();
	for (; itMap != m_mapClickFlow.end(); itMap++)
	{
		if (itMap->first <= fTime)
		{
			vecOut.push_back(itMap->second);
			bRet = true;
		}
		else
			break;
	}
	return bRet;
}