// img2textDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "img2text.h"
#include "img2textDlg.h"
#include ".\img2textdlg.h"

#include "Picture.h"

#include "ScreenShot.h"

#include <set>

 


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cimg2textDlg �Ի���



Cimg2textDlg::Cimg2textDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cimg2textDlg::IDD, pParent)
	, m_text(_T(""))
	, m_x(0)
	, m_y(0)
	, m_text2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cimg2textDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_text);
	DDX_Text(pDX, IDC_EDIT2, m_x);
	DDX_Text(pDX, IDC_EDIT3, m_y);

	DDX_Control(pDX, IDC_PIC2, m_pic2);
	DDX_Text(pDX, IDC_EDIT4, m_text2);
}

BEGIN_MESSAGE_MAP(Cimg2textDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk) 
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Cimg2textDlg ��Ϣ�������

BOOL Cimg2textDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	//�ؼ�
	::CoInitialize(0); 
	
 /*
	CFile file("d:\\jjsg��Ŀ��.txt",CFile::modeRead);

DWORD dwFileLen; 
dwFileLen = file.GetLength(); 
pBuf = new char[dwFileLen+1]; 
pBuf[dwFileLen] = 0;
file.Read(pBuf,dwFileLen); 
file.Close();
*/
	 SetTimer(0,300,0);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void Cimg2textDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cimg2textDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR Cimg2textDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL Cimg2textDlg::OCRImageFile( CString Name)//OCR
{ 
	IDoc *pDoc = new IDoc();

	try
	{
		pDoc->CreateDispatch( "MODI.Document" );
		pDoc->Create(Name);
		pDoc->OCR( miLANG_CHINESE_SIMPLIFIED, 0, 0 );
 
		IImages images = pDoc->GetImages();
		long	  num =images.GetCount();
		for( int i = 0; i < num; i++ )
		{ 
			IImage  image = images.GetItem(i);
			ILayout layout = image.GetLayout();
			SetDlgItemText(IDC_EDIT1, layout.GetText()+"\r\n");
		}
		pDoc->Close(0);
		pDoc->ReleaseDispatch();
	}
	catch (CMemoryException* e)
	{
		
	}
	catch (CFileException* e)
	{
	}
	catch ( ...)
	{
	}
	 
	 
	delete pDoc;
	return 1;//(num > 0) ? TRUE : FALSE;
}

void Cimg2textDlg::OnBnClickedOk()
{
	//UpdateData(TRUE);

	 //���pic ctrl��size
	CRect rect;
	m_pic2.GetClientRect(&rect);
	int width=rect.right-rect.left;
	int height=rect.bottom-rect.top;

	//
	CScreenShot s;
	POINT p;
	p.x= 595-width/2;
	p.y= 331-height/2;

	char file[100];
	memcpy(file, GetCachePath(), 100);
	if (s.capture_and_savetobmp(p,	//left top
		p.x+width,p.y+height //right bottom
		, file ) )
	{
		ShowPIC( file );

		Sleep(50);

		OCRImageFile( file );
	}

	//OCRImageFile("c:\\b.jpg");
	//ShowPIC("c:\\b.jpg");

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnOK();
}

void Cimg2textDlg::ShowPIC(char* m_strFilePath)
{
	m_pic2.Load(m_strFilePath);
	m_pic2.Draw();
}
//���ڴ��ж�ȡͼƬ����ʾ,
void Cimg2textDlg::ShowPIC(char* buf,int iSize)
{
	if(iSize==0||buf==NULL) return;
	//ASSERT(buf!=NULL);
	CDC *pDC=GetDC();
	//ASSERT(pDC!=NULL);
	CPicture pic;
	pic.Load(buf,iSize);
	CRect rect;
	m_pic2.GetClientRect(&rect);
	rect.top+=15;
	rect.left+=5;
	rect.right-=5;
	rect.bottom-=5;
	pic.Render(pDC,rect);
	m_pic2.ReleaseDC(pDC);
}
void Cimg2textDlg::OnTimer(UINT nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


	//�õ���������
	DWORD   dw   =   ::GetMessagePos(); //����һ��DWORD,��λ����x,��λ��y 
	POINT   pt;
	pt.x=LOWORD(dw);
	pt.y=HIWORD(dw);//ת����������Ļ����
	
	m_x=pt.x;
	m_y=pt.y;
	UpdateData(FALSE);

	//���pic ctrl��size
	CRect rect;
	m_pic2.GetClientRect(&rect);
	int width=rect.right-rect.left;
	int height=rect.bottom-rect.top;

	//
	CScreenShot s;
	POINT p;
	p.x=m_x-width/2;
	p.y=m_y-height/2;
	
	/*
	//
	if(s.capture(100,
		p,	//left top
		p.x+width,p.y+height //right bottom
		))
	{
		s.savetofile("c://b.jpg");

		ShowPIC("c://b.jpg");
		
		Sleep(50);

	 	OCRImageFile("c://b.jpg");
	}

	*/

	char file[100];
	memcpy(file, GetCachePath(), 100);
	if (s.capture_and_savetobmp(p,	//left top
		p.x+width,p.y+height //right bottom
		, file ) )
	{
		ShowPIC( file );

		Sleep(50);

		OCRImageFile( file );

	}
  

	//CxImage * image = new CxImage();//
 
	//int lan= s.GetFileSize();	
	//char* buff=s.getJPGbuffer();//��ͼ���ļ�
	//image->Decode(  (BYTE*)buff , lan, CXIMAGE_FORMAT_JPG);	//ת��λͼ
	//int hBitW=(float)image->GetWidth();		//ͼ�δ�С
	//int hBitH=(float)image->GetHeight();	//ͼ�δ�С
 //
 
/*
	HDC     hMDC = CreateCompatibleDC(hScrDC);
	HBITMAP hBit = CreateCompatibleBitmap(hScrDC,(int)hBitW,(int)hBitH);
	HBITMAP hold =(HBITMAP)SelectObject(hMDC,hBit);
	image->Draw2(hMDC,0,0,(int)hBitW,(int)hBitH);
	SetStretchBltMode(hDC,STRETCH_HALFTONE);
	StretchBlt(hDC,82+(rect.Width()-90)/2,20,(rect.Width()-90)/2,rect.Height()-25,hMDC,0,0,(int)hBitW,(int)hBitH,SRCCOPY);//g_hDCS
	SelectObject(hMDC,hold);
	DeleteObject(hBit);
	DeleteDC(hMDC);
	image->Clear(0);					//
	image->Destroy();	
*/
//	delete buff;

	CDialog::OnTimer(nIDEvent);
}

const TCHAR* Cimg2textDlg::GetCachePath()
{
	if (m_strCachePath.empty())
	{
		TCHAR szBuf[101];
		memset(szBuf, 0, 101);
		GetLogicalDriveStrings(101, szBuf);

		std::set<TCHAR> setDrives;
		int i = 0;
		do
		{
			setDrives.insert(*(szBuf + i));
			do
			{
				i++;
			} while (*(szBuf + i) != 0);
			i++;
		} while (i < 100 && *(szBuf + i) != 0);

		TCHAR cDrive = 'N';
		for (; cDrive >= 'D'; --cDrive)
		{
			if (setDrives.find(cDrive) != setDrives.end())
				break;
		}
		m_strCachePath = "://b.bmp";
		m_strCachePath = cDrive + m_strCachePath;
	}
	return m_strCachePath.c_str();
}
