#include "stdafx.h"
#include "HdEventMgr.h"
#include "InputModel.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

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
	while (itMap != m_mapClickFlow.end())
	{
		bRet = true;
		if (itMap->first <= fTime)
		{
			vecOut.push_back(itMap->second);
			itMap = m_mapClickFlow.erase(itMap);
		}
		else
			break;
	}
	return bRet;
}

void HdEvent::RestoreKeyClickFlow()
{
	m_mapClickFlow.clear();
	std::vector<KeyClick>::iterator iter = m_vecClicks.begin();
	for (; iter != m_vecClicks.end(); iter++)
		m_mapClickFlow.insert(std::make_pair((*iter).fDownTime, &(*iter)));
}

HdEventMgr* HdEventMgr::s_pInst = NULL;

HdEventMgr* HdEventMgr::GetInstance()
{
	if (!s_pInst)
		s_pInst = new HdEventMgr();
	return s_pInst;
}

void HdEventMgr::DeleteInstance()
{
	if (s_pInst)
	{
		delete s_pInst;
		s_pInst = NULL;
	}
}

HdEventMgr::HdEventMgr()
: m_pWnd(NULL)
, m_uTimerID(-1)
, m_pRunningEvent(NULL)
, m_fStartTime(0.0f)
{
}

HdEventMgr::~HdEventMgr()
{
	Release();
}

bool HdEventMgr::Init(CWnd* pWnd, UINT uTimerID)
{
	if (!pWnd) return false;

	m_pWnd = pWnd;
	m_uTimerID = uTimerID;

	m_pInputModel = new SendInputModel();
}

void HdEventMgr::Release()
{
	m_pWnd = NULL;
	m_uTimerID = -1;

	ForEachEvent([](HdEvent* pEvent, int i) -> bool
	{
		delete pEvent;
		return false;
	});
	m_pRunningEvent = NULL;
	m_mapUsingClicks.clear();
	delete m_pInputModel;
}

bool HdEventMgr::OnTimer(UINT uTimerID, float fForceTime)
{
	if (!m_pWnd || !m_pRunningEvent || uTimerID != m_uTimerID)
		return false;

	float fCurTime = (fForceTime >= 0.0f ? fForceTime : timeGetTime() / 1000.0f);
	float fTime = fCurTime - m_fStartTime;

	std::vector<HdEvent::KeyClick*> vecPopClicks;
	bool bHasClick = m_pRunningEvent->CheckAndPopClickTimeUp(fTime, vecPopClicks);
	if (bHasClick && !vecPopClicks.empty())
	{
		std::vector<HdEvent::KeyClick*>::iterator itPop = vecPopClicks.begin();
		for (; itPop != vecPopClicks.end(); itPop++)
		{
			m_pInputModel->Exec((*itPop)->wVk, true);
			m_mapUsingClicks.insert(std::make_pair((*itPop)->fUpTime, *itPop));
		}
	}
	
	std::multimap<float, HdEvent::KeyClick*>::iterator itUsing = m_mapUsingClicks.begin();
	while (itUsing != m_mapUsingClicks.end())
	{
		bHasClick = true;
		if (itUsing->first <= fTime)
		{
			m_pInputModel->Exec(itUsing->second->wVk, false);
			itUsing = m_mapUsingClicks.erase(itUsing);
		}
		else
			break;
	}

	if (!bHasClick)
	{
		m_pRunningEvent->RestoreKeyClickFlow();
		m_pRunningEvent = NULL;
		m_mapUsingClicks.clear();
		m_pWnd->KillTimer(m_uTimerID);
	}
	return true;
}

bool HdEventMgr::AddEvent(HdEvent* pEvent)
{
	if (!pEvent || m_pRunningEvent)
		return false;

	std::map<std::string, HdEvent*>::iterator iter = m_mapEvents.find(pEvent->GetKeyword());
	if (iter == m_mapEvents.end())
	{
		m_mapEvents.insert(std::make_pair(pEvent->GetKeyword(), pEvent));
		return true;
	}
	return false;
}

void HdEventMgr::RemoveEventByKeyword(const TCHAR* szKeyword)
{
	if (!szKeyword || m_pRunningEvent)
		return;

	std::map<std::string, HdEvent*>::iterator iter = m_mapEvents.find(szKeyword);
	if (iter != m_mapEvents.end())
		m_mapEvents.erase(iter);
}

HdEvent* HdEventMgr::GetEventByKeyword(const TCHAR* szKeyword)
{
	if (!szKeyword) return NULL;

	std::map<std::string, HdEvent*>::iterator iter = m_mapEvents.find(szKeyword);
	if (iter != m_mapEvents.end())
		return iter->second;
	return NULL;
}

int HdEventMgr::GetEventNum()
{
	return m_mapEvents.size();
}

HdEvent* HdEventMgr::ForEachEvent(std::function<bool(HdEvent*, int)> fnCallback)
{
	std::map<std::string, HdEvent*>::iterator iter = m_mapEvents.begin();
	for (int i = 0; iter != m_mapEvents.end(); iter++, ++i)
	{
		if (fnCallback(iter->second, i))
			return iter->second;
	}
	return NULL;
}

bool HdEventMgr::CheckAndRunFromText(const std::string& strText)
{
	if (!m_pWnd || m_pRunningEvent)
		return false;

	HdEvent* pHitEvent = ForEachEvent([strText](HdEvent* pEvent, int i) -> bool
	{
		std::size_t ipos = strText.find(pEvent->GetKeyword());
		if (ipos != std::string::npos)
			return true;
		return false;
	});

	if (pHitEvent)
	{
		m_pRunningEvent = pHitEvent;
		m_fStartTime = timeGetTime() / 1000.0f;
		m_pWnd->SetTimer(m_uTimerID, 50, 0);
		OnTimer(m_uTimerID, m_fStartTime);
		return true;
	}
	return false;
}

bool HdEventMgr::IsRunning()
{
	return (m_pRunningEvent != NULL);
}