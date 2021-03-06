﻿
// JReverseDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "JReverse.h"
#include "JReverseDlg.h"
#include "afxdialogex.h"
#include "DD.h"
#include "ScreenShot.h"
#include <string>
#include <set>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CHANGE_VK VK_DIVIDE


// CJReverseDlg 对话框

void CJReverseDlg::SBuffTrigger::CheckBuff(bool bCorrect)
{
	if (!pDlg) return;

	if (bCorrect)
	{
		if (!bBuff)
		{
			bBuff = true;
			bSpecial = true;
			if (pDlg->IsInputTriggered())
			{
				bRunning = true;
				pDlg->Start(*this);
			}
		}
	}
	else
	{
		if (bBuff)
		{
			bBuff = false;
			bRunning = false;
			pDlg->End(*this);
		}
	}
}

void CJReverseDlg::SBuffTrigger::CheckInput(bool bInput)
{
	if (!pDlg) return;

	if (bInput)
	{
		if (bBuff && bSpecial)
		{
			bRunning = true;
			pDlg->Start(*this);
		}
	}
	else
	{
		bSpecial = false;
		bRunning = false;
		pDlg->End(*this);
	}
}

bool CJReverseDlg::SBuffTrigger::CheckStart()
{
	switch (eType)
	{
	case EBuffTriggerType::FrequentClick:
		iCurTickNum = 0;
		bFreqDown = true;
		return true;
	case EBuffTriggerType::ClickSwitch:
		if (iCurTickNum < 0)
		{
			iCurTickNum = 0;
			return true;
		}
		iClickSwQue++;
		return false;
	case EBuffTriggerType::DownUpSwitch:
		return true;
	}
	return false;
}

int CJReverseDlg::SBuffTrigger::CheckTick()
{
	switch (eType)
	{
	case EBuffTriggerType::FrequentClick:
		if (iCurTickNum < 0) return 0;
		iCurTickNum++;
		if (bFreqDown)
		{
			if (iCurTickNum >= iClickTickNum)
			{
				iCurTickNum = 0;
				bFreqDown = false;
				return -1;
			}
		}
		else
		{
			if (iCurTickNum >= iFreqSpaceTickNum)
			{
				iCurTickNum = 0;
				bFreqDown = true;
				return 1;
			}
		}
		break;
	case EBuffTriggerType::ClickSwitch:
		if (iCurTickNum >= 0)
		{
			iCurTickNum++;
			if (iCurTickNum >= iClickTickNum)
			{
				iCurTickNum = -1;
				return -1;
			}
		}
		else
		{
			if (iClickSwQue > 0)
			{
				iClickSwQue--;
				iCurTickNum = 0;
				return 1;
			}
		}
		break;
	}
	return 0;
}

int CJReverseDlg::SBuffTrigger::CheckEnd()
{
	switch (eType)
	{
	case EBuffTriggerType::FrequentClick:
	{
		iCurTickNum = -1;
		int iRet = (bFreqDown ? -1 : 0);
		bFreqDown = false;
		return iRet;
	}
	case EBuffTriggerType::ClickSwitch:
		if (iCurTickNum < 0)
		{
			iCurTickNum = 0;
			return 1;
		}
		iClickSwQue++;
		return 0;
	case EBuffTriggerType::DownUpSwitch:
		return -1;
	}
	return 0;
}

HHOOK CJReverseDlg::s_hKbHook = NULL;
HHOOK CJReverseDlg::s_hMHook = NULL;
CJReverseDlg* CJReverseDlg::s_pDlg = NULL;

CJReverseDlg::CJReverseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_JREVERSE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bRevert = false;
	m_bInputTrigger = false;
	m_bNormalChangeClickSwitch = true;
	m_iCurNormalTickNum = -1;
	m_iNormalClickSwQue = 0;
}

void CJReverseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
}

BEGIN_MESSAGE_MAP(CJReverseDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CJReverseDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CJReverseDlg::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CJReverseDlg 消息处理程序

BOOL CJReverseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	::SetWindowPos(GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);
	s_hKbHook = SetWindowsHookEx(WH_KEYBOARD_LL, &CJReverseDlg::KeyboardProc, NULL, NULL);
	s_hMHook = SetWindowsHookEx(WH_MOUSE_LL, &CJReverseDlg::MouseProc, NULL, NULL);
	s_pDlg = this;

	m_pdd = new CDD();
	std::string strPath = "D:\\likehole\\jk\\Handle-For-Harmony\\JReverse\\";
#ifdef _DEBUG
	strPath += "Debug\\";
#else
	strPath += "Release\\";
#endif
	strPath += "DD94687.32.dll";
	m_pdd->GetFunAddr(CString(strPath.c_str()));

	InitBuffTriggers();
	SetTimer(0, 200, 0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CJReverseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CJReverseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CJReverseDlg::KeyboardProc(int iCode, WPARAM wParam, LPARAM lParam)
{
	int iMsg = wParam;
	PKBDLLHOOKSTRUCT hookStruct = (PKBDLLHOOKSTRUCT)lParam;
	if ((iMsg == WM_KEYDOWN || iMsg == WM_SYSKEYDOWN) && s_pDlg)
	{
		switch (hookStruct->vkCode)
		{
		case 0x56://V
			s_pDlg->m_bRevert = !s_pDlg->m_bRevert;
			s_pDlg->m_btnOK.SetWindowText(s_pDlg->m_bRevert ? _T("关闭") : _T("确定"));
			s_pDlg->InputNormalChangeEx(s_pDlg->m_bRevert);
			s_pDlg->SetInputTrigger(s_pDlg->m_bRevert);
			break;
		case 0x5A://Z
		case 0x58://X
		case 0x43://C
			if (s_pDlg->m_bRevert)
				s_pDlg->Input(s_pDlg->HookToInputVk(hookStruct->vkCode), true);
			break;
		}
	}
	else if (iMsg == WM_KEYUP || iMsg == WM_SYSKEYUP)
	{
		switch (hookStruct->vkCode)
		{
		case 0x5A://Z
		case 0x58://X
		case 0x43://C
			if (s_pDlg->m_bRevert)
				s_pDlg->Input(s_pDlg->HookToInputVk(hookStruct->vkCode), false);
			break;
		}
	}

	return CallNextHookEx(s_hKbHook, iCode, wParam, lParam);
}

LRESULT CJReverseDlg::MouseProc(int iCode, WPARAM wParam, LPARAM lParam)
{
	if (!s_pDlg->m_bRevert)
		return CallNextHookEx(s_hMHook, iCode, wParam, lParam);

	int iMsg = wParam;
	PMSLLHOOKSTRUCT hookStruct = (PMSLLHOOKSTRUCT)lParam;
	int x = hookStruct->pt.x;
	int y = hookStruct->pt.y;
	int iDelta = (int)((hookStruct->mouseData >> 16) & 0xffff);

	if (iMsg == WM_RBUTTONDOWN)
	{
		s_pDlg->InputNormalChangeEx(true);
		s_pDlg->SetInputTrigger(true);
	}
	else if (iMsg == WM_RBUTTONUP)
	{
		s_pDlg->InputNormalChangeEx(false);
		s_pDlg->SetInputTrigger(false);
	}

	return CallNextHookEx(s_hMHook, iCode, wParam, lParam);
}

void CJReverseDlg::Input(DWORD dwVk, bool bDown)
{
	/*
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = dwVk;
	input.ki.wScan = MapVirtualKey(dwVk, 0);
	input.ki.dwFlags = (bDown ? 0 : KEYEVENTF_KEYUP);
	SendInput(1, &input, sizeof(input));
	//*/
	//TODOJK winio
	m_pdd->DD_key(VkToDDCode(dwVk), bDown ? 1 : 2);
}

DWORD CJReverseDlg::HookToInputVk(DWORD dwVk)
{
	switch (dwVk)
	{
	case 0x5A: return 0x45;//Z-E
	case 0x58: return 0x57;//X-W
	case 0x43: return 0x51;//C-Q
	}
	return dwVk;
}

int CJReverseDlg::VkToDDCode(DWORD dwVk)
{
	switch (dwVk)
	{
	case 0x56: return 504;//V
	case VK_SHIFT: return 500;//Shift
	case 0x31: return 201;//1
	case VK_DIVIDE: return 811;///
	case 0x35: return 205;//5
	case 0x45: return 303;//E
	case 0x57: return 302;//W
	case 0x51: return 301;//Q
	}
	return -1;
}

void CJReverseDlg::OnBnClickedOk()
{
	m_bRevert = !m_bRevert;
	m_btnOK.SetWindowText(m_bRevert ? _T("关闭") : _T("确定"));
}

void CJReverseDlg::OnBnClickedCancel()
{
	if (s_hKbHook)
		UnhookWindowsHookEx(s_hKbHook);
	if (s_hMHook)
		UnhookWindowsHookEx(s_hMHook);
	delete m_pdd;
	CDialogEx::OnCancel();
}

void CJReverseDlg::InitBuffTriggers()
{
	SBuffTrigger DaHuaTrigger;
	DaHuaTrigger.ptLeftTop.x = 242;//FLAGJK
	DaHuaTrigger.ptLeftTop.y = 814;//
	DaHuaTrigger.lWidth = 3;
	DaHuaTrigger.lHeight = 3;
	DaHuaTrigger.wstrFileName = L"a";
	DaHuaTrigger.iSampleX = 1;
	DaHuaTrigger.iSampleY = 1;
	DaHuaTrigger.cRedLow = 0;//
	DaHuaTrigger.cGreenLow = 0;//
	DaHuaTrigger.cBlueLow = 0;//
	DaHuaTrigger.cRedHigh = 1;//
	DaHuaTrigger.cGreenHigh = 1;//
	DaHuaTrigger.cBlueHigh = 1;//
	DaHuaTrigger.eType = EBuffTriggerType::ClickSwitch;
	DaHuaTrigger.dwVk = VK_DIVIDE;///
	DaHuaTrigger.iClickTickNum = 1;
	DaHuaTrigger.iFreqSpaceTickNum = 0;
	DaHuaTrigger.pDlg = this;
	m_vecBuffTriggers.push_back(DaHuaTrigger);

	SBuffTrigger WuHuiTrigger;
	WuHuiTrigger.ptLeftTop.x = 282;//
	WuHuiTrigger.ptLeftTop.y = 814;//
	WuHuiTrigger.lWidth = 3;
	WuHuiTrigger.lHeight = 3;
	WuHuiTrigger.wstrFileName = L"b";
	WuHuiTrigger.iSampleX = 1;
	WuHuiTrigger.iSampleY = 1;
	WuHuiTrigger.cRedLow = 0;//
	WuHuiTrigger.cGreenLow = 0;//
	WuHuiTrigger.cBlueLow = 0;//
	WuHuiTrigger.cRedHigh = 1;//
	WuHuiTrigger.cGreenHigh = 1;//
	WuHuiTrigger.cBlueHigh = 1;//
	WuHuiTrigger.eType = EBuffTriggerType::FrequentClick;
	WuHuiTrigger.dwVk = 0x35;//5
	WuHuiTrigger.iClickTickNum = 1;
	WuHuiTrigger.iFreqSpaceTickNum = 1;
	WuHuiTrigger.pDlg = this;
	m_vecBuffTriggers.push_back(WuHuiTrigger);
}

void CJReverseDlg::OnTimer(UINT nIDEvent)
{
	std::vector<SBuffTrigger>::iterator iter = m_vecBuffTriggers.begin();
	for (; iter != m_vecBuffTriggers.end(); iter++)
	{
		if (m_bRevert)
		{
			CScreenShot s;
			wchar_t file[100];
			memcpy(file, GetCachePath(iter->wstrFileName.c_str()), 100);
			if (s.capture_and_savetobmp(iter->ptLeftTop,	//left top
				iter->ptLeftTop.x + iter->lWidth, iter->ptLeftTop.y + iter->lHeight //right bottom
				, file))
			{
				iter->CheckBuff(IsBuffBmpCorrect(file, *iter));
			}
		}
		Tick(*iter);
	}

	TickNormalChangeEx();

	CDialogEx::OnTimer(nIDEvent);
}

const TCHAR* CJReverseDlg::GetCachePath(const TCHAR* wszName)
{
	if (!wszName) return NULL;

	std::map<std::wstring, std::wstring>::iterator iter = m_mapCachePaths.find(wszName);
	if (iter == m_mapCachePaths.end())
	{
		iter = m_mapCachePaths.insert(std::pair<std::wstring, std::wstring>(wszName, std::wstring())).first;

		TCHAR wszBuf[101];
		memset(wszBuf, 0, 101);
		GetLogicalDriveStrings(101, wszBuf);

		std::set<TCHAR> setDrives;
		int i = 0;
		do
		{
			setDrives.insert(*(wszBuf + i));
			do
			{
				i++;
			} while (*(wszBuf + i) != 0);
			i++;
		} while (i < 100 && *(wszBuf + i) != 0);

		TCHAR cDrive = 'N';
		for (; cDrive >= 'D'; --cDrive)
		{
			if (setDrives.find(cDrive) != setDrives.end())
				break;
		}

		std::wstring strName = wszName;
		iter->second = L"://" + strName + L".bmp";
		iter->second = cDrive + iter->second;
	}
	return iter->second.c_str();
}

bool CJReverseDlg::IsBuffBmpCorrect(const TCHAR* wszFile, const SBuffTrigger& trigger)
{
	//if (!wszFile) return false;
	HBITMAP hBmp = (HBITMAP)LoadImage(NULL, wszFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (!hBmp) return false;

	BITMAP bmp;
	int iRet = GetObject(hBmp, sizeof(BITMAP), &bmp);
	if (iRet)
	{
		BYTE* pBits = (BYTE*)bmp.bmBits;
		int iFormat = bmp.bmBitsPixel / 8;
		BYTE* pPixel = pBits + (trigger.lHeight - trigger.iSampleY - 1) * bmp.bmWidthBytes + trigger.iSampleX * iFormat;

		int iPlus = (iFormat == 4 ? 1 : 0);
		BYTE cRed = *(pPixel + (2 + iPlus));
		BYTE cGreen = *(pPixel + (1 + iPlus));
		BYTE cBlue = *(pPixel + iPlus);

		return ((trigger.cRedLow <= cRed && cRed <= trigger.cRedHigh) &&
			(trigger.cGreenLow <= cGreen && cGreen <= trigger.cGreenHigh) &&
			(trigger.cBlueLow <= cBlue && cBlue <= trigger.cBlueHigh));
	}
	return false;
}

void CJReverseDlg::SetInputTrigger(bool bInput)
{
	if (bInput == m_bInputTrigger)
		return;
	m_bInputTrigger = bInput;

	std::vector<SBuffTrigger>::iterator iter = m_vecBuffTriggers.begin();
	for (; iter != m_vecBuffTriggers.end(); iter++)
		iter->CheckInput(bInput);
}

bool CJReverseDlg::IsInputTriggered()
{
	return m_bInputTrigger;
}

void CJReverseDlg::Start(SBuffTrigger& trigger)
{
	if (trigger.CheckStart())
		Input(trigger.dwVk, true);
}

void CJReverseDlg::Tick(SBuffTrigger& trigger)
{
	int iRet = trigger.CheckTick();
	if (iRet > 0)
		Input(trigger.dwVk, true);
	else if (iRet < 0)
		Input(trigger.dwVk, false);
}

void CJReverseDlg::End(SBuffTrigger& trigger)
{
	int iRet = trigger.CheckEnd();
	if (iRet > 0)
		Input(trigger.dwVk, true);
	else if (iRet < 0)
		Input(trigger.dwVk, false);
}

void CJReverseDlg::InputNormalChangeEx(bool bDown)
{
	if (m_bNormalChangeClickSwitch)
	{
		if (m_iCurNormalTickNum < 0)
		{
			m_iCurNormalTickNum = 0;
			Input(CHANGE_VK, true);
		}
		else
			m_iNormalClickSwQue++;
	}
	else
		Input(CHANGE_VK, bDown);
}

void CJReverseDlg::TickNormalChangeEx()
{
	if (!m_bNormalChangeClickSwitch)
		return;

	if (m_iCurNormalTickNum >= 0)
	{
		m_iCurNormalTickNum++;
		if (m_iCurNormalTickNum >= 1)
		{
			m_iCurNormalTickNum = -1;
			Input(CHANGE_VK, false);
		}
	}
	else
	{
		if (m_iNormalClickSwQue > 0)
		{
			m_iNormalClickSwQue--;
			m_iCurNormalTickNum = 0;
			Input(CHANGE_VK, true);
		}
	}
}