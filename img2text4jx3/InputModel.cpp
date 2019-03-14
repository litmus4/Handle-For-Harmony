#include "stdafx.h"
#include "InputModel.h"

IInputModel::IInputModel()
{
}

IInputModel::~IInputModel()
{
}

UINT IInputModel::GetScanCode(WORD wVk)
{
	std::map<WORD, UINT>::iterator iter = m_mapScanCodes.find(wVk);
	if (iter == m_mapScanCodes.end())
	{
		auto resPair = m_mapScanCodes.insert(std::pair<WORD, UINT>(wVk, MapVirtualKey(wVk, 0)));
		iter = resPair.first;
	}
	return iter->second;
}

SendInputModel::SendInputModel()
{
}

SendInputModel::~SendInputModel()
{
}

void SendInputModel::Exec(WORD wVk, bool bDown)
{
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = wVk;
	input.ki.wScan = GetScanCode(wVk);
	input.ki.dwFlags = (bDown ? 0 : KEYEVENTF_KEYUP);
	SendInput(1, &input, sizeof(input));
}