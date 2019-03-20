// CHdEventDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "img2text.h"
#include "CHdEventDlg.h"
#include "afxdialogex.h"


// CHdEventDlg 对话框

IMPLEMENT_DYNAMIC(CHdEventDlg, CDialog)

CHdEventDlg::CHdEventDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EVENT_DIALOG, pParent)
{

}

CHdEventDlg::~CHdEventDlg()
{
}

void CHdEventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHdEventDlg, CDialog)
END_MESSAGE_MAP()


// CHdEventDlg 消息处理程序
