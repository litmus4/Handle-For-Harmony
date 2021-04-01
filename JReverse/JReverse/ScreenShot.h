#pragma once
#include "MyImage.h"


//截屏类

class CScreenShot
{
public:
	CScreenShot(void);
	~CScreenShot(void);

	bool CScreenShot::capture_and_savetobmp(POINT pt,UINT w,UINT h,const wchar_t* savepath,int bit=24);

	bool capture(long quality,POINT pt,UINT w,UINT h);
	
	//得到文件大小
	UINT  GetFileSize();

	//读取文件某块数据
	void   GetFileStr(char* Dest_str,long filebegin,long filenend);

	void savetofile(const char* savepath);

	char* getJPGbuffer();
private:

	//将屏幕截取copy到位图
	HBITMAP  ScreenToBitmap(POINT lefttop ,POINT rightbottom );

	HGLOBAL hMemBmp; 

};

//位图保存到文件.指定位数
//lpfilename 为位图文件名，hbitmap 为刚才的屏幕位图句柄
int Tofile(HBITMAP hbitmap , LPWSTR lpfilename,int ibits);
 