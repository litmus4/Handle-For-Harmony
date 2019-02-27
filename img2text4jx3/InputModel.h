#pragma once
#include "afxwin.h"
#include <map>

class IInputModel
{
public:
	IInputModel();
	virtual ~IInputModel();

	virtual void Exec(WORD wVk, bool bDown) = 0;

protected:
	UINT GetScanCode(WORD wVk);

	std::map<WORD, UINT> m_mapScanCodes;
};

class SendInputModel : public IInputModel
{
public:
	SendInputModel();
	~SendInputModel();

	virtual void Exec(WORD wVk, bool bDown);
};