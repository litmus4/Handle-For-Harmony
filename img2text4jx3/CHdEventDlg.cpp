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

	if (!m_pEvent)
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
END_MESSAGE_MAP()


// CHdEventDlg 消息处理程序


void CHdEventDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CHdEventDlg::OnBnClickedButtonModi()
{
	// TODO: 在此添加控件通知处理程序代码
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
