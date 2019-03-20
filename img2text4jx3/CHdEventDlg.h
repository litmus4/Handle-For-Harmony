#pragma once


// CHdEventDlg 对话框

class CHdEventDlg : public CDialog
{
	DECLARE_DYNAMIC(CHdEventDlg)

public:
	CHdEventDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHdEventDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EVENT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
