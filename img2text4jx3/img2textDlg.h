// img2textDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include "PictureEx.h"


class IBench;
// Cimg2textDlg �Ի���
class Cimg2textDlg : public CDialog
{
// ����
public:
	Cimg2textDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IMG2TEXT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	void Cimg2textDlg::ShowPIC(char* buf,int iSize);
	void Cimg2textDlg::ShowPIC(char* m_strFilePath);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_text;
	afx_msg void OnBnClickedOk(); 
	afx_msg void OnChkClicked();
	int m_x;
	int m_y;
	afx_msg void OnTimer(UINT nIDEvent);

	HDC hDC ;
	HDC hScrDC;

	BOOL Cimg2textDlg::OCRImageFile( CString Name);//OCR
	const TCHAR* Cimg2textDlg::GetCachePath();
 
	CPictureEx m_pic2;
	CListBox m_listBox;

	IBench* m_pBench;

	std::string m_strCachePath;
	BOOL m_bFixed;
};
