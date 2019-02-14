#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <map>

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

private:
	std::string m_strKeyword;
	std::vector<KeyClick> m_vecClicks;
	std::multimap<float, KeyClick*> m_mapClickFlow;
};

class HdEventMgr
{
	//
};