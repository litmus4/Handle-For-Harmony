
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



void CHandleForMineDlg::OnBnClickedOk()
{
	//CDialogEx::OnOK();
	if (!m_bRunning)
	{
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
	//*testtemp
	DWORD dwTestTime = timeGetTime();
	WCHAR wszTestTime[100];
	swprintf(wszTestTime, sizeof(wszTestTime), _T("%d"), dwTestTime);
	SetDlgItemText(IDC_STATIC, wszTestTime);
	//*/
}
