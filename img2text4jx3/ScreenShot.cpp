#include "StdAfx.h"
#include ".\screenshot.h"

CScreenShot::CScreenShot(void)
{
}

CScreenShot::~CScreenShot(void)
{
}


//将屏幕截取copy到位图
HBITMAP CScreenShot::ScreenToBitmap(POINT lefttop ,POINT rightbottom )
{
	HDC hscrdc, hmemdc; // 屏幕和内存设备描述表
	HBITMAP hbitmap, holdbitmap; // 位图句柄
	int nx, ny, nx2, ny2; // 截屏幕的区域rect坐标
	int nwidth, nheight; // 位图宽度和高度
	int xscrn, yscrn; // 屏幕分辨率

	hscrdc = CreateDC("display", NULL, NULL, NULL);	//为屏幕创建设备描述表
	hmemdc = CreateCompatibleDC(hscrdc);//为屏幕设备描述表创建兼容的内存设备描述表


	// 获得屏幕分辨率
	xscrn = GetDeviceCaps(hscrdc, HORZRES);//物理屏幕的宽度 单位像素
	yscrn = GetDeviceCaps(hscrdc, VERTRES);//物理屏幕的高度 单位像素

	//左上角
	nx = lefttop.x;
	ny = lefttop.y;

	//为屏幕的最右下角
	nx2 = rightbottom.x;//xscrn;
	ny2 = rightbottom.y;//yscrn;

	nwidth = nx2 - nx;
	nheight = ny2 - ny;

	// 创建一个与屏幕设备描述表兼容的位图
	hbitmap = CreateCompatibleBitmap(hscrdc, nwidth, nheight);
	if(hbitmap==NULL)//如果得到失败
	{
		//清除 
		DeleteDC(hscrdc);
		DeleteDC(hmemdc);
		return NULL;
	}
	// 把新位图选到内存设备描述表中
	holdbitmap = (HBITMAP)SelectObject(hmemdc, hbitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hmemdc, 0, 0, nwidth, nheight,hscrdc, nx, ny, SRCCOPY);
	//得到屏幕位图的句柄
	hbitmap = (HBITMAP)SelectObject(hmemdc, holdbitmap);

	//清除 
	DeleteDC(hscrdc);
	DeleteDC(hmemdc);

	// 返回位图句柄
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
	//回收上次的内存
	if (hMemBmp)
	{
		GlobalFree(hMemBmp);
		hMemBmp=0;
	}

	HBITMAP tempmap;
	//截屏幕到原始位图	
	POINT pt2;
	pt2.x=w;
	pt2.y=h;

	tempmap = ScreenToBitmap(pt,pt2);
	if(tempmap)
	{
		//根据位图创建jpg图片.并转换质量,缩放jpg.
		MyImage img;
		img.LoadImage(tempmap,(HPALETTE)GetStockObject(DEFAULT_PALETTE));

		//jpg文件内存指针被保存到hMemBmp
		hMemBmp=img.SaveAsJPG(quality,-1,-1);//w,h);
			
		//位图使用完后,用DeleteObject销毁.否则就是资源泄露
		//删除位图
		DeleteObject(tempmap); 

		UINT jpgsize= GetFileSize();//得到转换成内存jpg的图片大小
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
得到文件大小
*/
UINT  CScreenShot::GetFileSize()
{
	if (hMemBmp)
	{
		//读文件大小
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
读取文件某块数据
*/
void   CScreenShot::GetFileStr(char* Dest_str,long filebegin,long filenend)
{
	if (hMemBmp)
	{
		//
		BYTE* pbyBmp = (BYTE *)GlobalLock(hMemBmp);//得到缓冲区的起始地址,顺便加锁
		//读取块
		memcpy(Dest_str,pbyBmp+filebegin,filenend-filebegin);

		GlobalUnlock(hMemBmp);//解锁
	}

}


//位图保存到文件.指定位数
//lpfilename 为位图文件名，hbitmap 为刚才的屏幕位图句柄
int Tofile(HBITMAP hbitmap , LPSTR lpfilename,int ibits)
{ 
	HDC hdc; //设备描述表
	//	int ibits; 
	WORD wbitcount; 	//当前显示分辨率下每个像素所占字节数

	//位图中每个像素所占字节数，定义调色板大小，位图中像素字节大小，位图文件大小 ，写入文件字节数
	DWORD dwpalettesize=0, dwbmbitssize, dwdibsize, dwwritten;

	BITMAP bitmap; //位图属性结构
	BITMAPFILEHEADER bmfhdr; //位图文件头结构
	BITMAPINFOHEADER bi; //位图信息头结构
	LPBITMAPINFOHEADER lpbi; //指向位图信息头结构

	//定义文件，分配内存句柄，调色板句柄
	HANDLE fh, hdib, hpal,holdpal=NULL;

	//计算位图文件每个像素所占字节数
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

	//计算调色板大小
	if (wbitcount <= 8)
		dwpalettesize = (1 << wbitcount) * sizeof(RGBQUAD);

	//设置位图信息头结构
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
	//为位图内容分配内存
	hdib = GlobalAlloc(GHND,dwbmbitssize + dwpalettesize + 
		sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hdib);
	*lpbi = bi;

	// 处理调色板 
	hpal = GetStockObject(DEFAULT_PALETTE);
	if (hpal)
	{
		hdc = ::GetDC(NULL);
		holdpal = SelectPalette(hdc, (HPALETTE)hpal, false);
		RealizePalette(hdc);
	}

	// 获取该调色板下新的像素值
	GetDIBits(hdc, hbitmap, 0, (UINT) bitmap.bmHeight,(LPSTR)lpbi + 
		sizeof(BITMAPINFOHEADER)+dwpalettesize,(BITMAPINFO*)lpbi, DIB_RGB_COLORS);

	//恢复调色板 
	if (holdpal)
	{
		SelectPalette(hdc, (HPALETTE)holdpal, true);
		RealizePalette(hdc);
		::ReleaseDC(NULL, hdc);
	}

	//创建位图文件 
	fh = CreateFile(lpfilename, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL|
		FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE)
		return false;

	// 设置位图文件头
	bmfhdr.bfType = 0x4d42; // "bm"
	dwdibsize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+ 
		dwpalettesize + dwbmbitssize; 
	bmfhdr.bfSize = dwdibsize;
	bmfhdr.bfReserved1 = 0;
	bmfhdr.bfReserved2 = 0;
	bmfhdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + 
		(DWORD)sizeof(BITMAPINFOHEADER)+ dwpalettesize;

	// 写入位图文件头
	WriteFile(fh, (LPSTR)&bmfhdr, sizeof(BITMAPFILEHEADER), &dwwritten, NULL);

	// 写入位图文件其余内容
	WriteFile(fh, (LPSTR)lpbi, dwdibsize, &dwwritten, NULL);
	//清除 
	GlobalUnlock(hdib);
	GlobalFree(hdib);
	CloseHandle(fh);
	return true;
}
