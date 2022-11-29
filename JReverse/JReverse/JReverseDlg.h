
// JReverseDlg.h: 头文件
//

#pragma once
#include <string>
#include <map>
#include <vector>
#include <list>


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

	struct SBuffTrigger
	{
	public:
		SBuffTrigger() : bBuff(false), bSpecial(false), bRunning(false),
			iCurTickNum(-1), bFreqDown(false), iClickSwQue(0), pDlg(NULL) {}

		void CheckBuff(bool bCorrect);
		void CheckInput(bool bInput);
		bool CheckStart();
		int CheckTick();
		int CheckEnd();

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

		CJReverseDlg* pDlg;

	private:
		bool bBuff;
		bool bSpecial;
		bool bRunning;

		int iCurTickNum;
		bool bFreqDown;
		int iClickSwQue;
	};

	struct SSunBmpParam
	{
	public:
		std::wstring wstrFileName;
		POINT ptLeftTop;
		LONG lWidth, lHeight;
		int iSampleX, iSampleY;
		BYTE cRedLow, cGreenLow, cBlueLow;
		BYTE cRedHigh, cGreenHigh, cBlueHigh;
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
	afx_msg void OnBnClickedSecondMode();

	void InitBuffTriggers();
	afx_msg void OnTimer(UINT nIDEvent);
	const TCHAR* GetCachePath(const TCHAR* wszName);
	bool IsBuffBmpCorrect(const TCHAR* wszFile, const SBuffTrigger& trigger);
	void SetInputTrigger(bool bInput);
	bool IsInputTriggered();
	void Start(SBuffTrigger& trigger);
	void Tick(SBuffTrigger& trigger);
	void End(SBuffTrigger& trigger);

	void TickSunTrigger();
	bool IsSunBmpCorrect(const TCHAR* wszFile, const SSunBmpParam& param);
	void ResetSunTrigger();

	void TickFlyHelper();

	void InputNormalChangeEx(bool bDown);
	void TickNormalChangeEx();

protected:
	static HHOOK s_hKbHook;
	static HHOOK s_hMHook;
	static CJReverseDlg* s_pDlg;
	CButton m_btnOK;

	bool m_bRevert;
	CDD* m_pdd;
	bool m_bSecondMode;

	std::map<std::wstring, std::wstring> m_mapCachePaths;
	std::vector<SBuffTrigger> m_vecBuffTriggers;
	bool m_bInputTrigger;

	int m_iSunCooldownTickNum;
	int m_iCurSunCooldownTickNum;
	bool m_bSunsetDown;
	int m_iSunsetNum;
	int m_iCurSunsetNum;

	std::list<int> m_lisFlyForeQueue;
	int m_iFlyDelayTickNum;
	bool m_bLeftAlt;
	bool m_bLeftAltEx;
	bool m_bLeftCtrl;
	bool m_bVehicleFly;

	bool m_bNormalChangeClickSwitch;
	int m_iCurNormalTickNum;
	int m_iNormalClickSwQue;
	bool m_bMacroDown;
};
