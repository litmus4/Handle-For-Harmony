
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
	enum EMouseMove
	{
		Left,
		Top,
		Right,
		Bottom
	};

	enum EBuffTriggerType
	{
		FrequentClick,
		ClickSwitch,
		DownUpSwitch,
	};

	enum ETimerType
	{
		HuitouReady,
		HuitouFirst,
		HuitouIn,
		HuitouOut3Of4,
		HuitouOut2Of3,
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
	void Move(EMouseMove eMove, int iPixel);
	DWORD HookToInputVk(DWORD dwVk);
	int VkToDDCode(DWORD dwVk);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSecondMode();
	afx_msg void OnBnClickedSecondOffset();

	void InitBuffTriggers();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
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

	void TickMoonTrigger();
	void ResetMoonTrigger();

	void TickFlyHelper();
	void StartHuitouTimer(ETimerType eTimerType);
	void ResetTimers();
	static void RunHuitouTimer();

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
	bool m_bSecondOffset;

	std::map<std::wstring, std::wstring> m_mapCachePaths;
	std::vector<SBuffTrigger> m_vecBuffTriggers;
	bool m_bInputTrigger;

	bool m_bFyToRageAlways;
	bool m_bFyToRageDown;//VK_F7 107 VK_SPACE 603

	int m_iSunCooldownTickNum;
	int m_iCurSunCooldownTickNum;
	bool m_bSunsetDown;
	int m_iSunsetNum;
	int m_iCurSunsetNum;

	int m_iMoonCooldownTickNum;
	int m_iCurMoonCooldownTickNum;
	bool m_bMoonFiveDown;
	int m_iMoonFiveNum;
	int m_iCurMoonFiveNum;
	int m_iMoonFiveOrder;
	int m_iMoonFive2Step;
	int m_iMoonFive2Num;
	int m_iCurMoonFive2Num;
	int m_iMoonFive2ReadyNum;

	std::list<int> m_lisFlyForeQueue;
	int m_iFlyDelayTickNum;
	bool m_bLeftAlt;
	bool m_bLeftAltEx;
	bool m_bLeftCtrl;
	bool m_bVehicleFly;
	int m_iVehicleMove;

	UINT m_uHuitouReadyTimer;
	UINT m_uHuitouFirstTimer;
	UINT m_uHuitouInTimer;
	UINT m_uHuitouOut3Of4Timer;
	UINT m_uHuitouOut2Of3Timer;
	int m_iHuitouStep;

	bool m_bNormalChangeClickSwitch;
	int m_iCurNormalTickNum;
	int m_iNormalClickSwQue;
	bool m_bMacroDown;
	bool m_bMacro2;
};

void CALLBACK callBackTimer(UINT wTimerID, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);