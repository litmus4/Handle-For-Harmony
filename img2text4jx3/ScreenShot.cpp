#include "StdAfx.h"
#include ".\screenshot.h"

CScreenShot::CScreenShot(void)
{
}

CScreenShot::~CScreenShot(void)
{
}


//����Ļ��ȡcopy��λͼ
HBITMAP CScreenShot::ScreenToBitmap(POINT lefttop ,POINT rightbottom )
{
	HDC hscrdc, hmemdc; // ��Ļ���ڴ��豸������
	HBITMAP hbitmap, holdbitmap; // λͼ���
	int nx, ny, nx2, ny2; // ����Ļ������rect����
	int nwidth, nheight; // λͼ��Ⱥ͸߶�
	int xscrn, yscrn; // ��Ļ�ֱ���

	hscrdc = CreateDC("display", NULL, NULL, NULL);	//Ϊ��Ļ�����豸������
	hmemdc = CreateCompatibleDC(hscrdc);//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������


	// �����Ļ�ֱ���
	xscrn = GetDeviceCaps(hscrdc, HORZRES);//������Ļ�Ŀ�� ��λ����
	yscrn = GetDeviceCaps(hscrdc, VERTRES);//������Ļ�ĸ߶� ��λ����

	//���Ͻ�
	nx = lefttop.x;
	ny = lefttop.y;

	//Ϊ��Ļ�������½�
	nx2 = rightbottom.x;//xscrn;
	ny2 = rightbottom.y;//yscrn;

	nwidth = nx2 - nx;
	nheight = ny2 - ny;

	// ����һ������Ļ�豸��������ݵ�λͼ
	hbitmap = CreateCompatibleBitmap(hscrdc, nwidth, nheight);
	if(hbitmap==NULL)//����õ�ʧ��
	{
		//��� 
		DeleteDC(hscrdc);
		DeleteDC(hmemdc);
		return NULL;
	}
	// ����λͼѡ���ڴ��豸��������
	holdbitmap = (HBITMAP)SelectObject(hmemdc, hbitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	BitBlt(hmemdc, 0, 0, nwidth, nheight,hscrdc, nx, ny, SRCCOPY);
	//�õ���Ļλͼ�ľ��
	hbitmap = (HBITMAP)SelectObject(hmemdc, holdbitmap);

	//��� 
	DeleteDC(hscrdc);
	DeleteDC(hmemdc);

	// ����λͼ���
	return hbitmap;
}	

bool CScreenShot::capture_and_savetobmp(POINT pt,UINT w,UINT h,const char* savepath,int bit)
{
	 


	POINT pt2;
	pt2.x=w;
	pt2.y=h;
	HBITMAP tempmap = ScreenToBitmap(pt,pt2);
	if(tempmap)
	{
		
		::Tofile(tempmap,(LPSTR)savepath,bit);

		DeleteObject(tempmap); 

		return true;
	}

	return false;
}


bool CScreenShot::capture(long quality,POINT pt,UINT w,UINT h)
{
	//�����ϴε��ڴ�
	if (hMemBmp)
	{
		GlobalFree(hMemBmp);
		hMemBmp=0;
	}

	HBITMAP tempmap;
	//����Ļ��ԭʼλͼ	
	POINT pt2;
	pt2.x=w;
	pt2.y=h;

	tempmap = ScreenToBitmap(pt,pt2);
	if(tempmap)
	{
		//����λͼ����jpgͼƬ.��ת������,����jpg.
		MyImage img;
		img.LoadImage(tempmap,(HPALETTE)GetStockObject(DEFAULT_PALETTE));

		//jpg�ļ��ڴ�ָ�뱻���浽hMemBmp
		hMemBmp=img.SaveAsJPG(quality,-1,-1);//w,h);
			
		//λͼʹ�����,��DeleteObject����.���������Դй¶
		//ɾ��λͼ
		DeleteObject(tempmap); 

		UINT jpgsize= GetFileSize();//�õ�ת�����ڴ�jpg��ͼƬ��С
		if (jpgsize>0)
		{
			return true;
		}

	}
	return false;

}

void CScreenShot::savetofile(const char* savepath)
{
	int size=GetFileSize();
	char* b=getJPGbuffer();
	FILE* f=fopen(savepath,"wb+");
	if(f) 
	{
		fwrite(b,size,1,f);
		fclose(f);	
	}

}
 

/*
�õ��ļ���С
*/
UINT  CScreenShot::GetFileSize()
{
	if (hMemBmp)
	{
		//���ļ���С
		UINT s=GlobalSize(this->hMemBmp);
		return s;
	}
	 return 0;
}

char* CScreenShot::getJPGbuffer()
{
	int size=GetFileSize();

	char* buff=new char[size+1];
	
	GetFileStr(buff,0,size);

	return buff;
}


/*
��ȡ�ļ�ĳ������
*/
void   CScreenShot::GetFileStr(char* Dest_str,long filebegin,long filenend)
{
	if (hMemBmp)
	{
		//
		BYTE* pbyBmp = (BYTE *)GlobalLock(hMemBmp);//�õ�����������ʼ��ַ,˳�����
		//��ȡ��
		memcpy(Dest_str,pbyBmp+filebegin,filenend-filebegin);

		GlobalUnlock(hMemBmp);//����
	}

}


//λͼ���浽�ļ�.ָ��λ��
//lpfilename Ϊλͼ�ļ�����hbitmap Ϊ�ղŵ���Ļλͼ���
int Tofile(HBITMAP hbitmap , LPSTR lpfilename,int ibits)
{ 
	HDC hdc; //�豸������
	//	int ibits; 
	WORD wbitcount; 	//��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ���

	//λͼ��ÿ��������ռ�ֽ����������ɫ���С��λͼ�������ֽڴ�С��λͼ�ļ���С ��д���ļ��ֽ���
	DWORD dwpalettesize=0, dwbmbitssize, dwdibsize, dwwritten;

	BITMAP bitmap; //λͼ���Խṹ
	BITMAPFILEHEADER bmfhdr; //λͼ�ļ�ͷ�ṹ
	BITMAPINFOHEADER bi; //λͼ��Ϣͷ�ṹ
	LPBITMAPINFOHEADER lpbi; //ָ��λͼ��Ϣͷ�ṹ

	//�����ļ��������ڴ�������ɫ����
	HANDLE fh, hdib, hpal,holdpal=NULL;

	//����λͼ�ļ�ÿ��������ռ�ֽ���
	//	hdc = CreateDC("display",NULL,NULL,NULL);
	//	ibits = GetDeviceCaps(hdc, BITSPIXEL) * GetDeviceCaps(hdc, PLANES);
	//	DeleteDC(hdc);

	//	ibits=1;

	if (ibits <= 1)
		wbitcount = 1;
	else if (ibits <= 4)
		wbitcount = 4;
	else if (ibits <= 8)
		wbitcount = 8;
	else if (ibits <= 16)
		wbitcount = 16;
	else if (ibits <= 24)
		wbitcount = 24;
	else 
		wbitcount = 32;

	//�����ɫ���С
	if (wbitcount <= 8)
		dwpalettesize = (1 << wbitcount) * sizeof(RGBQUAD);

	//����λͼ��Ϣͷ�ṹ
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bitmap.bmWidth;
	bi.biHeight = bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wbitcount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	dwbmbitssize = ((bitmap.bmWidth * wbitcount+31)/32)* 4 * bitmap.bmHeight ;
	//Ϊλͼ���ݷ����ڴ�
	hdib = GlobalAlloc(GHND,dwbmbitssize + dwpalettesize + 
		sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hdib);
	*lpbi = bi;

	// �����ɫ�� 
	hpal = GetStockObject(DEFAULT_PALETTE);
	if (hpal)
	{
		hdc = ::GetDC(NULL);
		holdpal = SelectPalette(hdc, (HPALETTE)hpal, false);
		RealizePalette(hdc);
	}

	// ��ȡ�õ�ɫ�����µ�����ֵ
	GetDIBits(hdc, hbitmap, 0, (UINT) bitmap.bmHeight,(LPSTR)lpbi + 
		sizeof(BITMAPINFOHEADER)+dwpalettesize,(BITMAPINFO*)lpbi, DIB_RGB_COLORS);

	//�ָ���ɫ�� 
	if (holdpal)
	{
		SelectPalette(hdc, (HPALETTE)holdpal, true);
		RealizePalette(hdc);
		::ReleaseDC(NULL, hdc);
	}

	//����λͼ�ļ� 
	fh = CreateFile(lpfilename, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL|
		FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE)
		return false;

	// ����λͼ�ļ�ͷ
	bmfhdr.bfType = 0x4d42; // "bm"
	dwdibsize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+ 
		dwpalettesize + dwbmbitssize; 
	bmfhdr.bfSize = dwdibsize;
	bmfhdr.bfReserved1 = 0;
	bmfhdr.bfReserved2 = 0;
	bmfhdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + 
		(DWORD)sizeof(BITMAPINFOHEADER)+ dwpalettesize;

	// д��λͼ�ļ�ͷ
	WriteFile(fh, (LPSTR)&bmfhdr, sizeof(BITMAPFILEHEADER), &dwwritten, NULL);

	// д��λͼ�ļ���������
	WriteFile(fh, (LPSTR)lpbi, dwdibsize, &dwwritten, NULL);
	//��� 
	GlobalUnlock(hdib);
	GlobalFree(hdib);
	CloseHandle(fh);
	return true;
}
