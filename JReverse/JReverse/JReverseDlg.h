﻿
// JReverseDlg.h: 头文件
//

#pragma once
#include <string>


class CDD;
// CJReverseDlg 对话框
class CJReverseDlg : public CDialogEx
{
public:
	enum EBuffTriggerType
	{
		FrequentClick,
		ClickSwitch,
		DownUpSwitch,
	};

	struct SBuffTigger
	{
	public:
		POINT ptLeftTop;
		LONG lWidth, lHeight;
		std::wstring wstrFileName;
		int iSampleX, iSampleY;
		BYTE cRedLow, cGreenLow, cBlueLow;
		BYTE cRedHigh, cGreenHigh, cBlueHigh;

		EBuffTriggerType eType;
		DWORD dwVk;
		int iClickTickNum;
		int iFreqSpaceTickNum;

	private:
		bool bBuff;
		bool bSpecial;
		bool bRunning;

		int iCurTickNum;
		bool bFreqDown;
	};

// 构造
public:
	CJReverseDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JREVERSE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	static LRESULT CALLBACK KeyboardProc(int iCode, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK MouseProc(int iCode, WPARAM wParam, LPARAM lParam);

public:
	void Input(DWORD dwVk, bool bDown);
	DWORD HookToInputVk(DWORD dwVk);
	int VkToDDCode(DWORD dwVk);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	afx_msg void OnTimer(UINT nIDEvent);
	const TCHAR* GetCachePath();

protected:
	static HHOOK s_hKbHook;
	static HHOOK s_hMHook;
	static CJReverseDlg* s_pDlg;
	CButton m_btnOK;

	bool m_bRevert;
	CDD* m_pdd;

	std::wstring m_wstrCachePath;
};