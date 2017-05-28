
// HandleForMineDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HandleForMine.h"
#include "HandleForMineDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "winmm.lib")

#define MINE_TIME_TICK 250


// CHandleForMineDlg 对话框



CHandleForMineDlg::CHandleForMineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HANDLEFORMINE_DIALOG, pParent)
	, m_bRunning(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHandleForMineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtScale);
}

BEGIN_MESSAGE_MAP(CHandleForMineDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CHandleForMineDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHandleForMineDlg 消息处理程序

BOOL CHandleForMineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHandleForMineDlg::OnPaint()
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
HCURSOR CHandleForMineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CHandleForMineDlg::GetKGClientRect(RECT& rcClient)
{
	HWND hKG = ::FindWindow(_T("KGWin32App"), NULL);
	if (hKG)
	{
		if (::GetClientRect(hKG, &rcClient))
		{
			POINT ptClientLT, ptClientRB;
			ptClientLT.x = rcClient.left;
			ptClientLT.y = rcClient.top;
			ptClientRB.x = rcClient.right;
			ptClientRB.y = rcClient.bottom;
			if (::ClientToScreen(hKG, &ptClientLT) && ::ClientToScreen(hKG, &ptClientRB))
			{
				rcClient.left = ptClientLT.x;
				rcClient.top = ptClientLT.y;
				rcClient.right = ptClientRB.x;
				rcClient.bottom = ptClientRB.y;
				return true;
			}
		}
	}
	return false;
}

bool CHandleForMineDlg::GetDBMSTRect(RECT& rcST)
{
	float fWidth = (float)(rcST.right - rcST.left);
	float fHeight = (float)(rcST.bottom - rcST.top);

	CString scaleStr;
	int iScaleLength = GetDlgItemText(IDC_EDIT1, scaleStr);
	if (iScaleLength <= 0 || iScaleLength > 10)
		return false;
	float fScale = (float)_wtof(scaleStr.GetString());

	RECT rcResult;
	float fHalfSTWidth = fWidth * (156.0f / 1440.0f) * fScale;
	rcResult.left = (LONG)(fWidth / 2.0f - fHalfSTWidth) + rcST.left;
	rcResult.top = (LONG)(fHeight / 2.0f - fHeight * (266.0f / 900.0f) * fScale) + rcST.top;
	rcResult.right = rcResult.left + (LONG)fHalfSTWidth * 2;
	rcResult.bottom = 32;//TODOJK

	rcST = rcResult;
	return true;
}



void CHandleForMineDlg::OnBnClickedOk()
{
	//CDialogEx::OnOK();
	if (!m_bRunning)
	{
		RECT rc;
		if (!GetKGClientRect(rc))
			return;

		if (!GetDBMSTRect(rc))
			return;

		m_rcJHTime = rc;
		//*测试临时
		this->SetWindowPos(NULL, m_rcJHTime.left, m_rcJHTime.top, 0, 0, SWP_NOSIZE);
		//*/
		m_bRunning = true;
		SetTimer(0, MINE_TIME_TICK, NULL);
		SetDlgItemText(IDOK, _T("停止"));
	}
	else
	{
		m_bRunning = false;
		KillTimer(0);
		SetDlgItemText(IDOK, _T("开始"));
	}
}

void CHandleForMineDlg::OnTimer(UINT_PTR nIDEvent)
{
	//*测试临时
	DWORD dwTestTime = timeGetTime();

	unsigned char uRed = 0, uGreen = 0, uBlue = 0;
	HDC hdcScreen = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
	if (hdcScreen)
	{
		COLORREF dwTestColor = GetPixel(hdcScreen, m_rcJHTime.left + 60, m_rcJHTime.top + 10);
		uRed = GetRValue(dwTestColor);
		uGreen = GetGValue(dwTestColor);
		uBlue = GetBValue(dwTestColor);
	}
	DeleteDC(hdcScreen);

	WCHAR wszTest[100];
	swprintf(wszTest, sizeof(wszTest), _T("%d %d %d %d"), dwTestTime, uRed, uGreen, uBlue);
	SetDlgItemText(IDC_STATIC, wszTest);
	//*/
}
