// img2textDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include "PictureEx.h"


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
	int m_x;
	int m_y;
	afx_msg void OnTimer(UINT nIDEvent);

	HDC hDC ;
	HDC hScrDC;

	BOOL Cimg2textDlg::OCRImageFile( CString Name);//OCR
 
	CPictureEx m_pic2;


	CString m_text2;
};
