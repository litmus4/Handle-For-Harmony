// CHdEventDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "img2text.h"
#include "CHdEventDlg.h"
#include "afxdialogex.h"
#include "HdEventMgr.h"


// CHdEventDlg 对话框

IMPLEMENT_DYNAMIC(CHdEventDlg, CDialog)

CHdEventDlg::CHdEventDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EVENT_DIALOG, pParent)
	, m_pEvent(NULL)
	, m_bNew(false)
{

}

CHdEventDlg::~CHdEventDlg()
{
}

BOOL CHdEventDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_pEvent)
	{
		SetDlgItemText(IDC_EDIT_KEY, m_pEvent->GetKeyword().c_str());
		CListBox* plisClicks = static_cast<CListBox*>(GetDlgItem(IDC_LIST_CLICKS));
		for (int i = 0, iNum = m_pEvent->GetKeyClickNum(); i < iNum; ++i)
		{
			HdEvent::KeyClick* pClick = m_pEvent->GetKeyClick(i);
			TCHAR szBuf[100];
			sprintf(szBuf, "%d    %.2f    %.2f", pClick->wVk, pClick->fDownTime, pClick->fUpTime);
			plisClicks->AddString(szBuf);
		}
	}
	else
	{
		m_pEvent = new HdEvent();
		m_bNew = true;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CHdEventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KEY, m_ediKey);
	DDX_Control(pDX, IDC_LIST_CLICKS, m_lisClicks);
	DDX_Control(pDX, IDC_EDIT_VK, m_ediVk);
	DDX_Control(pDX, IDC_EDIT_DOWN, m_ediDown);
	DDX_Control(pDX, IDC_EDIT_UP, m_ediUp);
}


BEGIN_MESSAGE_MAP(CHdEventDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CHdEventDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MODI, &CHdEventDlg::OnBnClickedButtonModi)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CHdEventDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDOK, &CHdEventDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CHdEventDlg::OnBnClickedCancel)
	ON_LBN_SELCHANGE(IDC_LIST_CLICKS, &CHdEventDlg::OnLbnSelchangeListClicks)
END_MESSAGE_MAP()


// CHdEventDlg 消息处理程序


void CHdEventDlg::OnLbnSelchangeListClicks()
{
	int iSel = m_lisClicks.GetCurSel();
	HdEvent::KeyClick* pClick = m_pEvent->GetKeyClick(iSel);
	if (pClick)
	{
		TCHAR szBuf[100];
		m_ediVk.SetWindowText(itoa(pClick->wVk, szBuf, 10));
		sprintf(szBuf, "%.2f", pClick->fDownTime);
		m_ediDown.SetWindowText(szBuf);
		sprintf(szBuf, "%.2f", pClick->fUpTime);
		m_ediUp.SetWindowText(szBuf);
	}
}


void CHdEventDlg::OnBnClickedButtonAdd()
{
	CString sVk, sDown, sUp;
	m_ediVk.GetWindowText(sVk);
	m_ediDown.GetWindowText(sDown);
	m_ediUp.GetWindowText(sUp);
	if (sVk.GetLength() > 0 && sDown.GetLength() > 0 && sUp.GetLength() > 0)
	{
		m_pEvent->AddKeyClick(atoi(sVk), atof(sDown), atof(sUp));
		TCHAR szBuf[100];
		sprintf(szBuf, "%s    %.2f    %.2f", sVk, atof(sDown), atof(sUp));
		m_lisClicks.AddString(szBuf);
	}
}


void CHdEventDlg::OnBnClickedButtonModi()
{
	int iSel = m_lisClicks.GetCurSel();
	HdEvent::KeyClick* pClick = m_pEvent->GetKeyClick(iSel);
	CString sVk, sDown, sUp;
	m_ediVk.GetWindowText(sVk);
	m_ediDown.GetWindowText(sDown);
	m_ediUp.GetWindowText(sUp);
	if (pClick && sVk.GetLength() > 0 && sDown.GetLength() > 0 && sUp.GetLength() > 0)
	{
		pClick->wVk = atoi(sVk);
		pClick->fDownTime = atof(sDown);
		pClick->fUpTime = atof(sUp);
		m_lisClicks.DeleteString(iSel);
		TCHAR szBuf[100];
		sprintf(szBuf, "%s    %.2f    %.2f", sVk, atof(sDown), atof(sUp));
		m_lisClicks.InsertString(iSel, szBuf);
	}
}


void CHdEventDlg::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CHdEventDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


void CHdEventDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

void CHdEventDlg::SetHdEvent(HdEvent* pEvent)
{
	if (m_bNew)
	{
		delete m_pEvent;
		m_bNew = false;
	}
	m_pEvent = pEvent;
}
