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

#define CHANGE_VK 0x31//VK_SHIFT


// CJReverseDlg 对话框

HHOOK CJReverseDlg::s_hKbHook = NULL;
HHOOK CJReverseDlg::s_hMHook = NULL;
CJReverseDlg* CJReverseDlg::s_pDlg = NULL;

CJReverseDlg::CJReverseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_JREVERSE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bRevert = false;
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
			s_pDlg->Input(CHANGE_VK, s_pDlg->m_bRevert);
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
		s_pDlg->Input(CHANGE_VK, true);
	else if (iMsg == WM_RBUTTONUP)
		s_pDlg->Input(CHANGE_VK, false);

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

void CJReverseDlg::OnTimer(UINT nIDEvent)
{
	if (!m_bRevert) return;

	CScreenShot s;
	POINT p;
	p.x = 1;
	p.y = 1;

	wchar_t file[100];
	memcpy(file, GetCachePath(), 100);
	if (s.capture_and_savetobmp(p,	//left top
		p.x + 3, p.y + 3 //right bottom
		, file))
	{
		//FLAGJK
	}

	CDialogEx::OnTimer(nIDEvent);
}

const TCHAR* CJReverseDlg::GetCachePath()
{
	if (m_wstrCachePath.empty())
	{
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
		m_wstrCachePath = L"://b.bmp";
		m_wstrCachePath = cDrive + m_wstrCachePath;
	}
	return m_wstrCachePath.c_str();
}