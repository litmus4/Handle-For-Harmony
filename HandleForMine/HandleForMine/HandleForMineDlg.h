
// HandleForMineDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CHandleForMineDlg �Ի���
class CHandleForMineDlg : public CDialogEx
{
// ����
public:
	CHandleForMineDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HANDLEFORMINE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	bool GetKGClientRect(RECT& rcClient);

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

protected:
	RECT m_rcJHTime;
	bool m_bRunning;
};
