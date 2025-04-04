
// JReverseDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "JReverse.h"
#include "JReverseDlg.h"
#include "afxdialogex.h"
#include "DD.h"
#include "ScreenShot.h"
#include "mmsystem.h"
#include <string>
#include <set>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CHANGE_VK VK_F6
#define MACRO 0
#define MACRO_VK 0x46
#define MACRO2_VK VK_OEM_3
#define SUN 0
#define SUNSET_VK 0x43
#define MOON 1
#define MOONFIVE1_VK 0x48
#define MOONFIVE2_VK 0x54
#define FLY 1
#define FLYF2L_VK 0x39


CJReverseDlg::ETimerType g_eHuitouTypeSeqs[] = {
	CJReverseDlg::ETimerType::HuitouFirst,
	CJReverseDlg::ETimerType::HuitouIn,
	CJReverseDlg::ETimerType::HuitouOut3Of4,
	CJReverseDlg::ETimerType::HuitouIn,
	CJReverseDlg::ETimerType::HuitouOut2Of3,
	CJReverseDlg::ETimerType::HuitouIn
};

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
	m_bSecondMode = false;

	m_bInputTrigger = false;

	m_iSunCooldownTickNum = 30;
	m_iCurSunCooldownTickNum = -1;
	m_bSunsetDown = false;
	m_iSunsetNum = 10;
	m_iCurSunsetNum = -1;

	m_iMoonCooldownTickNum = 25;
	m_iCurMoonCooldownTickNum = -1;
	m_bMoonFiveDown = false;
	m_iMoonFiveNum = 10;
	m_iCurMoonFiveNum = -1;

	m_iFlyDelayTickNum = 2;
	m_bLeftAlt = false;
	m_bLeftAltEx = false;
	m_bLeftCtrl = false;
	m_bVehicleFly = false;
	m_iVehicleMove = 0;

	m_uHuitouReadyTimer = 0;
	m_uHuitouFirstTimer = 0;
	m_uHuitouInTimer = 0;
	m_uHuitouOut3Of4Timer = 0;
	m_uHuitouOut2Of3Timer = 0;
	m_iHuitouStep = 0;

	m_bNormalChangeClickSwitch = true;
	m_iCurNormalTickNum = -1;
	m_iNormalClickSwQue = 0;
	m_bMacroDown = false;
	m_bMacro2 = false;
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
	ON_BN_CLICKED(IDC_CHECK, &CJReverseDlg::OnBnClickedSecondMode)
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

	RECT rcOK;
	m_btnOK.GetWindowRect(&rcOK);
	rcOK.left -=7;
	rcOK.right -= 7;
	rcOK.top -= 30;
	rcOK.bottom = rcOK.top + 25;
	m_btnOK.MoveWindow(&rcOK);
	RECT rcCancel;
	GetDlgItem(IDCANCEL)->GetWindowRect(&rcCancel);
	rcCancel.left -= 7;
	rcCancel.right -= 7;
	rcCancel.top -= 30;
	rcCancel.bottom = rcCancel.top + 25;
	GetDlgItem(IDCANCEL)->MoveWindow(&rcCancel);

	::SetWindowPos(GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);
	s_hKbHook = SetWindowsHookEx(WH_KEYBOARD_LL, &CJReverseDlg::KeyboardProc, NULL, NULL);
	s_hMHook = SetWindowsHookEx(WH_MOUSE_LL, &CJReverseDlg::MouseProc, NULL, NULL);
	s_pDlg = this;

	m_pdd = new CDD();
	std::string strFolder = "D:\\likehole\\jk\\Handle-For-Harmony\\JReverse\\";
#ifdef _DEBUG
	strFolder += "Debug\\";
#else
	strFolder += "Release\\";
#endif
	std::string strPath = strFolder + "dd32695.x32.dll";
	m_pdd->GetFunAddr(CString(strPath.c_str()));
	//strPath = strFolder + "hid.32.dll";
	//LoadLibrary(CString(strPath.c_str()));
	int ist = m_pdd->DD_btn(0);

	InitBuffTriggers();
#if MACRO
	SetTimer(0, 50, 0);
#else
	SetTimer(0, 100, 0);
#endif

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
			//s_pDlg->InputNormalChangeEx(s_pDlg->m_bRevert);
			//s_pDlg->SetInputTrigger(s_pDlg->m_bRevert);
			if (!s_pDlg->m_bRevert)
			{
				s_pDlg->ResetSunTrigger();
				s_pDlg->ResetMoonTrigger();
				s_pDlg->m_bVehicleFly = false;
				s_pDlg->m_iVehicleMove = 0;
				s_pDlg->ResetTimers();
				((CStatic*)s_pDlg->GetDlgItem(IDC_STATIC))->SetWindowText(_T(""));
			}
			if (!s_pDlg->m_bRevert && s_pDlg->m_bMacroDown)
			{
				s_pDlg->Input((s_pDlg->m_bMacro2 ? MACRO2_VK : MACRO_VK), false);
				s_pDlg->m_bMacroDown = false;
				s_pDlg->m_bMacro2 = false;
			}
			break;
#if FLY
		case 0x35://5
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode && !s_pDlg->m_bLeftCtrl)
				s_pDlg->m_lisFlyForeQueue.push_back(0);
			break;
		case VK_LMENU://左Alt
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode)
			{
				s_pDlg->m_bLeftAlt = true;
				s_pDlg->m_bLeftAltEx = true;
			}
			break;
		case 0x51://Q
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode)
			{
				if (s_pDlg->m_bLeftAlt)
					s_pDlg->Input(0x41/*A*/, true);
				if (s_pDlg->m_bVehicleFly)
					s_pDlg->Input(0x31/*1*/, true);
			}
			break;
		case 0x57://W
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode && s_pDlg->m_bVehicleFly)
				s_pDlg->Input(0x33/*3*/, true);
			break;
		case 0x53://S
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode && s_pDlg->m_bVehicleFly)
				s_pDlg->Input(0x33/*3*/, true);
			break;
		case 0x45://E
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode)
			{
				if (s_pDlg->m_bLeftAlt)
					s_pDlg->Input(0x44/*D*/, true);
				if (s_pDlg->m_bVehicleFly)
					s_pDlg->Input(0x32/*2*/, true);
			}
			break;
		case VK_LCONTROL://左Ctrl
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode)
				s_pDlg->m_bLeftCtrl = true;
			break;
		case VK_F1://F1
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode && s_pDlg->m_bVehicleFly)
				s_pDlg->Input(0x31/*1*/, true);
			break;
		case VK_F2://F2
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode && s_pDlg->m_bVehicleFly)
				s_pDlg->Input(0x33/*3*/, true);
			break;
		case VK_F3://F3
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode && s_pDlg->m_bVehicleFly)
				s_pDlg->Input(0x32/*2*/, true);
			break;
#endif
		case 0x48://H
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode)
			{
				//s_pDlg->Input(0x54/*T*/, true);
				if (s_pDlg->m_bMacroDown)
				{
					s_pDlg->Input((s_pDlg->m_bMacro2 ? MACRO2_VK : MACRO_VK), false);
					s_pDlg->m_bMacroDown = false;
				}
				s_pDlg->m_bMacro2 = !s_pDlg->m_bMacro2;
			}
			break;
		case 0x5A://Z
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode)
			{
				s_pDlg->m_bVehicleFly = !s_pDlg->m_bVehicleFly;
				if (!s_pDlg->m_bVehicleFly)
					s_pDlg->m_iVehicleMove = 0;
				else
					s_pDlg->ResetTimers();
				((CStatic*)s_pDlg->GetDlgItem(IDC_STATIC))->SetWindowText(s_pDlg->m_bVehicleFly ? _T("V") : _T(""));
			}
			break;
		case 0x58://X
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode && !s_pDlg->m_bVehicleFly)
			{
				s_pDlg->m_uHuitouReadyTimer = timeSetEvent(9000, 1, callBackTimer, ETimerType::HuitouReady, TIME_ONESHOT);
				PlaySound(L"JRSTBuDong.wav", NULL, SND_ASYNC | SND_NODEFAULT);
			}
			break;
		case 0x43://C
			//if (s_pDlg->m_bRevert)
			//	s_pDlg->Input(s_pDlg->HookToInputVk(hookStruct->vkCode), true);
			break;
		case VK_OEM_3://`
			//s_pDlg->Input(VK_OEM_2, true);
			break;
		}
	}
	else if (iMsg == WM_KEYUP || iMsg == WM_SYSKEYUP)
	{
		switch (hookStruct->vkCode)
		{
#if FLY
		case VK_LMENU://左Alt
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode)
				s_pDlg->m_bLeftAlt = false;
			break;
		case 0x51://Q
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode)
			{
				if (s_pDlg->m_bLeftAltEx)
				{
					s_pDlg->Input(0x41/*A*/, false);
					s_pDlg->m_bLeftAltEx = false;
				}
				if (s_pDlg->m_bVehicleFly)
					s_pDlg->Input(0x31/*1*/, false);
			}
			break;
		case 0x57://W
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode && s_pDlg->m_bVehicleFly)
				s_pDlg->Input(0x33/*3*/, false);
			break;
		case 0x53://S
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode && s_pDlg->m_bVehicleFly)
				s_pDlg->Input(0x33/*3*/, false);
			break;
		case 0x45://E
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode)
			{
				if (s_pDlg->m_bLeftAltEx)
				{
					s_pDlg->Input(0x44/*D*/, false);
					s_pDlg->m_bLeftAltEx = false;
				}
				if (s_pDlg->m_bVehicleFly)
					s_pDlg->Input(0x32/*2*/, false);
			}
			break;
		case VK_LCONTROL://左Ctrl
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode)
				s_pDlg->m_bLeftCtrl = false;
			break;
		case VK_F1://F1
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode && s_pDlg->m_bVehicleFly)
				s_pDlg->Input(0x31/*1*/, false);
			break;
		case VK_F2://F2
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode && s_pDlg->m_bVehicleFly)
				s_pDlg->Input(0x33/*3*/, false);
			break;
		case VK_F3://F3
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode && s_pDlg->m_bVehicleFly)
				s_pDlg->Input(0x32/*2*/, false);
			break;
#endif
		case 0x48://H
			if (s_pDlg->m_bRevert && !s_pDlg->m_bSecondMode)
			{
				//s_pDlg->Input(0x54/*T*/, false);
			}
			break;
		case 0x5A://Z
		case 0x58://X
		case 0x43://C
			//if (s_pDlg->m_bRevert)
			//	s_pDlg->Input(s_pDlg->HookToInputVk(hookStruct->vkCode), false);
			break;
		case VK_OEM_3://`
			//s_pDlg->Input(VK_OEM_2, false);
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
		//s_pDlg->InputNormalChangeEx(true);
		//s_pDlg->SetInputTrigger(true);
	}
	else if (iMsg == WM_RBUTTONUP)
	{
		//s_pDlg->InputNormalChangeEx(false);
		//s_pDlg->SetInputTrigger(false);
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

void CJReverseDlg::Move(EMouseMove eMove, int iPixel)
{
	int iX = 0, iY = 0;
	switch (eMove)
	{
	case EMouseMove::Left: iX = -iPixel; break;
	case EMouseMove::Top: iY = -iPixel; break;
	case EMouseMove::Right: iX = iPixel; break;
	case EMouseMove::Bottom: iY = iPixel; break;
	}
	m_pdd->DD_movR(iX, iY);
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
	case 0x32: return 202;//2
	case 0x33: return 203;//3
	case 0x34: return 204;//4
	case VK_DIVIDE: return 811;///(s)
	case 0x35: return 205;//5
	case 0x45: return 303;//E
	case 0x57: return 302;//W
	case 0x51: return 301;//Q
	case VK_F6:	return 106;//F6
	case 0x46: return 404;//F
	case 0x43: return 503;//C
	case 0x41: return 401;//A
	case 0x44: return 403;//D
	case 0x39: return 209;//9
	case 0x54: return 305;//T
	case 0x48: return 406;//H
	case VK_OEM_2: return 510;///(b)
	case VK_OEM_3: return 200;//`
	}
	return -1;
}

void CJReverseDlg::OnBnClickedOk()
{
	m_bRevert = !m_bRevert;
	m_btnOK.SetWindowText(m_bRevert ? _T("关闭") : _T("确定"));
	if (!m_bRevert)
	{
		ResetSunTrigger();
		ResetMoonTrigger();
		m_bVehicleFly = false;
		m_iVehicleMove = 0;
		ResetTimers();
		((CStatic*)GetDlgItem(IDC_STATIC))->SetWindowText(_T(""));
	}
	if (!m_bRevert && m_bMacroDown)
	{
		Input((m_bMacro2 ? MACRO2_VK : MACRO_VK), false);
		m_bMacroDown = false;
		m_bMacro2 = false;
	}
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

void CJReverseDlg::OnBnClickedSecondMode()
{
	int iChecked = ((CButton*)GetDlgItem(IDC_CHECK))->GetCheck();
	m_bSecondMode = (iChecked == 1);
	if (m_bSecondMode)
	{
		m_bVehicleFly = false;
		m_iVehicleMove = 0;
		ResetTimers();
		((CStatic*)GetDlgItem(IDC_STATIC))->SetWindowText(_T(""));
	}
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
	//m_vecBuffTriggers.push_back(DaHuaTrigger);

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
	//m_vecBuffTriggers.push_back(WuHuiTrigger);
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

	if (m_bRevert)
	{
#if SUN
		if (m_bSecondMode)
			TickSunTrigger();
#endif
#if MOON
		if (m_bSecondMode)
			TickMoonTrigger();
#endif
#if FLY
		else
			TickFlyHelper();
#endif
	}

	TickNormalChangeEx();

#if MACRO
	if (m_bRevert)
	{
		m_bMacroDown = !m_bMacroDown;
		Input((m_bMacro2 ? MACRO2_VK : MACRO_VK), m_bMacroDown);
	}
#endif

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

		TCHAR cDrive = 'L';
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

void CJReverseDlg::TickSunTrigger()
{
	//多次按扶摇
	if (m_iCurSunsetNum >= 0)
	{
		m_bSunsetDown = !m_bSunsetDown;
		Input(SUNSET_VK, m_bSunsetDown);
		if (!m_bSunsetDown)
		{
			m_iCurSunsetNum++;
			if (m_iCurSunsetNum >= m_iSunsetNum)
				m_iCurSunsetNum = -1;
		}
	}

	if (m_iCurSunCooldownTickNum >= 0)
	{
		m_iCurSunCooldownTickNum++;
		if (m_iCurSunCooldownTickNum >= m_iSunCooldownTickNum)
			m_iCurSunCooldownTickNum = -1;
		return;
	}
	wchar_t file[100];

	//读条
	bool bReadingLeft = false, bReadingRight = false;

	//读条左
	SSunBmpParam srlParam;
	srlParam.wstrFileName = L"sunrl";
	srlParam.ptLeftTop.x = 549;//550
	srlParam.ptLeftTop.y = 161;//162
	srlParam.lWidth = 3;
	srlParam.lHeight = 3;
	srlParam.iSampleX = 1;
	srlParam.iSampleY = 1;
	srlParam.cRedLow = 110;//128-138
	srlParam.cGreenLow = 170;//182-201
	srlParam.cBlueLow = 160;//178-188
	srlParam.cRedHigh = 146;
	srlParam.cGreenHigh = 210;
	srlParam.cBlueHigh = 196;

	CScreenShot srl;
	memcpy(file, GetCachePath(srlParam.wstrFileName.c_str()), 100);
	if (srl.capture_and_savetobmp(srlParam.ptLeftTop,	//left top
		srlParam.ptLeftTop.x + srlParam.lWidth, srlParam.ptLeftTop.y + srlParam.lHeight //right bottom
		, file))
	{
		if (IsSunBmpCorrect(file, srlParam))
			bReadingLeft = true;
	}

	//读条右
	SSunBmpParam srrParam;
	srrParam.wstrFileName = L"sunrr";
	srrParam.ptLeftTop.x = 770;//771
	srrParam.ptLeftTop.y = 168;//169
	srrParam.lWidth = 3;
	srrParam.lHeight = 3;
	srrParam.iSampleX = 1;
	srrParam.iSampleY = 1;
	srrParam.cRedLow = 0;//38-26
	srrParam.cGreenLow = 0;//48-39
	srrParam.cBlueLow = 0;//49-36
	srrParam.cRedHigh = 46;
	srrParam.cGreenHigh = 56;
	srrParam.cBlueHigh = 57;

	CScreenShot srr;
	memcpy(file, GetCachePath(srrParam.wstrFileName.c_str()), 100);
	if (srr.capture_and_savetobmp(srrParam.ptLeftTop,	//left top
		srrParam.ptLeftTop.x + srrParam.lWidth, srrParam.ptLeftTop.y + srrParam.lHeight //right bottom
		, file))
	{
		if (IsSunBmpCorrect(file, srrParam))
			bReadingRight = true;
	}

	//判断读条
	if (!bReadingLeft || !bReadingRight) return;

	//日
	SSunBmpParam ssParam;
	ssParam.wstrFileName = L"suns";
	ssParam.ptLeftTop.x = 709;//710
	ssParam.ptLeftTop.y = 173;//174
	ssParam.lWidth = 3;
	ssParam.lHeight = 3;
	ssParam.iSampleX = 1;
	ssParam.iSampleY = 1;
	ssParam.cRedLow = 190;//201
	ssParam.cGreenLow = 190;//201
	ssParam.cBlueLow = 190;//201
	ssParam.cRedHigh = 255;
	ssParam.cGreenHigh = 255;
	ssParam.cBlueHigh = 255;

	CScreenShot ss;
	memcpy(file, GetCachePath(ssParam.wstrFileName.c_str()), 100);
	if (ss.capture_and_savetobmp(ssParam.ptLeftTop,	//left top
		ssParam.ptLeftTop.x + ssParam.lWidth, ssParam.ptLeftTop.y + ssParam.lHeight //right bottom
		, file))
	{
		if (!IsSunBmpCorrect(file, ssParam))
			return;
	}

	//落日（偏右上角无字迹）
	SSunBmpParam sssParam;
	sssParam.wstrFileName = L"sunss";
	sssParam.ptLeftTop.x = 699;//700
	sssParam.ptLeftTop.y = 165;//166
	sssParam.lWidth = 3;
	sssParam.lHeight = 3;
	sssParam.iSampleX = 1;
	sssParam.iSampleY = 1;
	sssParam.cRedLow = 0;//55
	sssParam.cGreenLow = 0;//55
	sssParam.cBlueLow = 0;//55
	sssParam.cRedHigh = 70;
	sssParam.cGreenHigh = 70;
	sssParam.cBlueHigh = 70;

	CScreenShot sss;
	memcpy(file, GetCachePath(sssParam.wstrFileName.c_str()), 100);
	if (sss.capture_and_savetobmp(sssParam.ptLeftTop,	//left top
		sssParam.ptLeftTop.x + sssParam.lWidth, sssParam.ptLeftTop.y + sssParam.lHeight //right bottom
		, file))
	{
		if (IsSunBmpCorrect(file, sssParam))
		{
			//播放声音“扶摇”
			PlaySound(L"JRSTFuYao.wav", NULL, SND_ASYNC | SND_NODEFAULT);

			m_bSunsetDown = !m_bSunsetDown;
			Input(SUNSET_VK, m_bSunsetDown);
			m_iCurSunsetNum = 0;

			m_iCurSunCooldownTickNum = 0;
			return;
		}
	}

	//旭日/烈日（偏右下角有字迹）
	SSunBmpParam ssrParam;
	ssrParam.wstrFileName = L"sunsr";
	ssrParam.ptLeftTop.x = 697;//698
	ssrParam.ptLeftTop.y = 174;//175
	ssrParam.lWidth = 3;
	ssrParam.lHeight = 3;
	ssrParam.iSampleX = 1;
	ssrParam.iSampleY = 1;
	ssrParam.cRedLow = 210;//228
	ssrParam.cGreenLow = 210;//228
	ssrParam.cBlueLow = 210;//228
	ssrParam.cRedHigh = 255;
	ssrParam.cGreenHigh = 255;
	ssrParam.cBlueHigh = 255;

	CScreenShot ssr;
	memcpy(file, GetCachePath(ssrParam.wstrFileName.c_str()), 100);
	if (ssr.capture_and_savetobmp(ssrParam.ptLeftTop,	//left top
		ssrParam.ptLeftTop.x + ssrParam.lWidth, ssrParam.ptLeftTop.y + ssrParam.lHeight //right bottom
		, file))
	{
		if (IsSunBmpCorrect(file, ssrParam))
		{
			//播放声音“不动”
			PlaySound(L"JRSTBuDong.wav", NULL, SND_ASYNC | SND_NODEFAULT);

			m_iCurSunCooldownTickNum = 0;
			return;
		}
		else
		{
			//播放声音“二段跳”
			PlaySound(L"JRSTErDuanTiao.wav", NULL, SND_ASYNC | SND_NODEFAULT);

			m_iCurSunCooldownTickNum = 0;
		}
	}
}

bool CJReverseDlg::IsSunBmpCorrect(const TCHAR* wszFile, const SSunBmpParam& param)
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
		BYTE* pPixel = pBits + (param.lHeight - param.iSampleY - 1) * bmp.bmWidthBytes + param.iSampleX * iFormat;

		int iPlus = (iFormat == 4 ? 1 : 0);
		BYTE cRed = *(pPixel + (2 + iPlus));
		BYTE cGreen = *(pPixel + (1 + iPlus));
		BYTE cBlue = *(pPixel + iPlus);

#ifdef _DEBUG
		TCHAR wszBuf[256];
		wsprintf(wszBuf, L"$$$$$$$ %s %d %d %d\n", param.wstrFileName.c_str(), cRed, cGreen, cBlue);
		OutputDebugString(wszBuf);
#endif
		return ((param.cRedLow <= cRed && cRed <= param.cRedHigh) &&
			(param.cGreenLow <= cGreen && cGreen <= param.cGreenHigh) &&
			(param.cBlueLow <= cBlue && cBlue <= param.cBlueHigh));
	}
	return false;
}

void CJReverseDlg::ResetSunTrigger()
{
	m_iCurSunCooldownTickNum = -1;

	m_iCurSunsetNum = -1;
	if (m_bSunsetDown)
	{
		Input(SUNSET_VK, false);
		m_bSunsetDown = false;
	}
}

void CJReverseDlg::TickMoonTrigger()
{
	//多次按加速
	if (m_iCurMoonFiveNum >= 0)
	{
		m_bMoonFiveDown = !m_bMoonFiveDown;
		Input(MOONFIVE1_VK, m_bMoonFiveDown);
		Input(MOONFIVE2_VK, m_bMoonFiveDown);
		if (!m_bMoonFiveDown)
		{
			m_iCurMoonFiveNum++;
			if (m_iCurMoonFiveNum >= m_iMoonFiveNum)
				m_iCurMoonFiveNum = -1;
		}
	}

	if (m_iCurMoonCooldownTickNum >= 0)
	{
		m_iCurMoonCooldownTickNum++;
		if (m_iCurMoonCooldownTickNum >= m_iMoonCooldownTickNum)
			m_iCurMoonCooldownTickNum = -1;
		return;
	}
	wchar_t file[100];

	//读条
	bool bReadingShield = false, bReadingLeft = false;

	//读条盾牌
	SSunBmpParam mrsParam;
	mrsParam.wstrFileName = L"moonrs";
	mrsParam.ptLeftTop.x = 560;//550/561
	mrsParam.ptLeftTop.y = 161;//162
	mrsParam.lWidth = 3;
	mrsParam.lHeight = 3;
	mrsParam.iSampleX = 1;
	mrsParam.iSampleY = 1;
	mrsParam.cRedLow = 110;//128-138
	mrsParam.cGreenLow = 170;//182-201
	mrsParam.cBlueLow = 160;//178-188
	mrsParam.cRedHigh = 146;
	mrsParam.cGreenHigh = 210;
	mrsParam.cBlueHigh = 196;

	CScreenShot srl;
	memcpy(file, GetCachePath(mrsParam.wstrFileName.c_str()), 100);
	if (srl.capture_and_savetobmp(mrsParam.ptLeftTop,	//left top
		mrsParam.ptLeftTop.x + mrsParam.lWidth, mrsParam.ptLeftTop.y + mrsParam.lHeight //right bottom
		, file))
	{
		if (IsSunBmpCorrect(file, mrsParam))
			bReadingShield = true;
	}

	//读条左
	SSunBmpParam mrlParam;
	mrlParam.wstrFileName = L"moonrl";
	mrlParam.ptLeftTop.x = 577;//567/578
	mrlParam.ptLeftTop.y = 168;//169
	mrlParam.lWidth = 3;
	mrlParam.lHeight = 3;
	mrlParam.iSampleX = 1;
	mrlParam.iSampleY = 1;
	mrlParam.cRedLow = 240;//255
	mrlParam.cGreenLow = 93;//103-113
	mrlParam.cBlueLow = 36;//46-56
	mrlParam.cRedHigh = 255;
	mrlParam.cGreenHigh = 123;
	mrlParam.cBlueHigh = 66;

	CScreenShot srr;
	memcpy(file, GetCachePath(mrlParam.wstrFileName.c_str()), 100);
	if (srr.capture_and_savetobmp(mrlParam.ptLeftTop,	//left top
		mrlParam.ptLeftTop.x + mrlParam.lWidth, mrlParam.ptLeftTop.y + mrlParam.lHeight //right bottom
		, file))
	{
		if (IsSunBmpCorrect(file, mrlParam))
			bReadingLeft = true;
	}

	//判断读条
	if (!bReadingShield || !bReadingLeft) return;

	PlaySound(L"JRSTErDuanTiao.wav", NULL, SND_ASYNC | SND_NODEFAULT);//FLAGJK
	m_iCurMoonCooldownTickNum = 0;
}

void CJReverseDlg::ResetMoonTrigger()
{
	m_iCurMoonCooldownTickNum = -1;

	m_iCurMoonFiveNum = -1;
	if (m_bMoonFiveDown)
	{
		Input(MOONFIVE1_VK, false);
		Input(MOONFIVE2_VK, false);
		m_bMoonFiveDown = false;
	}
}

void CJReverseDlg::TickFlyHelper()
{
	std::list<int>::iterator iter = m_lisFlyForeQueue.begin();
	while (iter != m_lisFlyForeQueue.end())
	{
		(*iter)++;
		if ((*iter) >= m_iFlyDelayTickNum + 1)
		{
			Input(FLYF2L_VK, false);
			iter = m_lisFlyForeQueue.erase(iter);
			continue;
		}
		else if((*iter) >= m_iFlyDelayTickNum)
			Input(FLYF2L_VK, true);
		iter++;
	}

	//if (m_bVehicleFly)
	//{
	//	m_iVehicleMove++;
	//	if (m_iVehicleMove == 1)
	//		Move(EMouseMove::Left, 1);
	//	else if ((m_iVehicleMove - 1) % 2 == 0)
	//		Move(EMouseMove::Left, 1);
	//	else if ((m_iVehicleMove - 1) % 2 == 1)
	//		Move(EMouseMove::Right, 1);
	//}
}

void CJReverseDlg::StartHuitouTimer(ETimerType eTimerType)
{
	switch (eTimerType)
	{
	case ETimerType::HuitouFirst:
		m_uHuitouFirstTimer = timeSetEvent(8000, 1, callBackTimer, eTimerType, TIME_ONESHOT);
		break;
	case ETimerType::HuitouIn:
		m_uHuitouInTimer = timeSetEvent(4000, 1, callBackTimer, eTimerType, TIME_ONESHOT);
		PlaySound(L"JRSTFuYao.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	case ETimerType::HuitouOut3Of4:
		m_uHuitouOut3Of4Timer = timeSetEvent(3000, 1, callBackTimer, eTimerType, TIME_ONESHOT);
		PlaySound(L"JRHTDuan.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	case ETimerType::HuitouOut2Of3:
		m_uHuitouOut2Of3Timer = timeSetEvent(2000, 1, callBackTimer, eTimerType, TIME_ONESHOT);
		PlaySound(L"JRHTDuan.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		break;
	}
}

void CJReverseDlg::ResetTimers()
{
	timeKillEvent(m_uHuitouReadyTimer);
	m_uHuitouReadyTimer = 0;
	timeKillEvent(m_uHuitouFirstTimer);
	m_uHuitouFirstTimer = 0;
	timeKillEvent(m_uHuitouInTimer);
	m_uHuitouInTimer = 0;
	timeKillEvent(m_uHuitouOut3Of4Timer);
	m_uHuitouOut3Of4Timer = 0;
	timeKillEvent(m_uHuitouOut2Of3Timer);
	m_uHuitouOut2Of3Timer = 0;

	m_iHuitouStep = 0;
}

void CJReverseDlg::RunHuitouTimer()
{
	int iNum = sizeof(g_eHuitouTypeSeqs) / sizeof(ETimerType);
	if (s_pDlg->m_iHuitouStep < iNum)
	{
		s_pDlg->StartHuitouTimer(g_eHuitouTypeSeqs[s_pDlg->m_iHuitouStep]);
		s_pDlg->m_iHuitouStep++;
	}
	else
	{
		PlaySound(L"JRHTDuan.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		s_pDlg->ResetTimers();
	}
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

void CALLBACK callBackTimer(UINT wTimerID, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	switch ((CJReverseDlg::ETimerType)dwUser)
	{
	case CJReverseDlg::ETimerType::HuitouReady:
	case CJReverseDlg::ETimerType::HuitouFirst:
	case CJReverseDlg::ETimerType::HuitouIn:
	case CJReverseDlg::ETimerType::HuitouOut3Of4:
	case CJReverseDlg::ETimerType::HuitouOut2Of3:
	{
		CJReverseDlg::RunHuitouTimer();
		break;
	}
	}
}