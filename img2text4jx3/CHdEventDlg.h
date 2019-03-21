#pragma once


// CHdEventDlg 对话框

class CHdEventDlg : public CDialog
{
	DECLARE_DYNAMIC(CHdEventDlg)

public:
	CHdEventDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHdEventDlg();

	virtual BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EVENT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonModi();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	CEdit m_ediKey;
	CListBox m_lisClicks;
	CEdit m_ediVk;
	CEdit m_ediDown;
	CEdit m_ediUp;
};
