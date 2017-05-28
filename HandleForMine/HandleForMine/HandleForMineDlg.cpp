
// HandleForMineDlg.cpp : ʵ���ļ�
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


// CHandleForMineDlg �Ի���



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


// CHandleForMineDlg ��Ϣ�������

BOOL CHandleForMineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHandleForMineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		//*������ʱ
		this->SetWindowPos(NULL, m_rcJHTime.left, m_rcJHTime.top, 0, 0, SWP_NOSIZE);
		//*/
		m_bRunning = true;
		SetTimer(0, MINE_TIME_TICK, NULL);
		SetDlgItemText(IDOK, _T("ֹͣ"));
	}
	else
	{
		m_bRunning = false;
		KillTimer(0);
		SetDlgItemText(IDOK, _T("��ʼ"));
	}
}

void CHandleForMineDlg::OnTimer(UINT_PTR nIDEvent)
{
	//*������ʱ
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
