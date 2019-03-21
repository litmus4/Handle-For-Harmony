#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <functional>

class HdEvent
{
public:
	struct KeyClick
	{
		WORD wVk;
		float fDownTime;
		float fUpTime;
	};

public:
	HdEvent();
	HdEvent(const TCHAR* szKeyword);
	~HdEvent();

	void SetKeyword(const TCHAR* szKeyword);
	std::string GetKeyword();
	void AddKeyClick(WORD wVk, float fDownTime, float fUpTime);
	void RemoveKeyClick(int iIndex);
	KeyClick* GetKeyClick(int iIndex);
	int GetKeyClickNum();
	void ClearAllKeyClicks();
	bool CheckAndPopClickTimeUp(float fTime, std::vector<KeyClick*>& vecOut);
	void RestoreKeyClickFlow();

private:
	std::string m_strKeyword;
	std::vector<KeyClick> m_vecClicks;
	std::multimap<float, KeyClick*> m_mapClickFlow;
};

class CWnd;
class IInputModel;

class HdEventMgr
{
public:
	static HdEventMgr* GetInstance();
	static void DeleteInstance();
	~HdEventMgr();

	bool Init(CWnd* pWnd, UINT uTimerID);
	void Release();
	bool OnTimer(UINT uTimerID, float fForceTime = -1.0f);

	bool AddEvent(HdEvent* pEvent);
	void RemoveEventByKeyword(const TCHAR* szKeyword);
	HdEvent* GetEventByKeyword(const TCHAR* szKeyword);
	int GetEventNum();
	HdEvent* ForEachEvent(std::function<bool(HdEvent*, int)> fnCallback);
	void SetAutoCycle(bool b);

	bool CheckAndRunFromText(const std::string& strText);
	bool IsRunning();

private:
	HdEventMgr();
	static HdEventMgr* s_pInst;

	CWnd* m_pWnd;
	UINT m_uTimerID;
	std::map<std::string, HdEvent*> m_mapEvents;
	bool m_bAutoCycle;
	HdEvent* m_pRunningEvent;
	float m_fStartTime;
	std::multimap<float, HdEvent::KeyClick*> m_mapUsingClicks;
	IInputModel* m_pInputModel;
};