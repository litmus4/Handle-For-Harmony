#pragma once


#include <Windows.h>
#include   <Stdio.h>   
#include   <Objbase.h>   
#include   <Windows.h>   
#include   <Gdiplus.h>   
#include   <GdiPlusEnums.h>   

using   namespace   Gdiplus;   
#pragma   comment(lib,"gdiplus") 

#include <iostream>
#include <tchar.h>
//HBITMAP的位图格式内存转换为jpg,调节质量，缩放.保存为内存jpg

class MyImage
{
public:
	MyImage(void);
	~MyImage(void);

	//加载
	bool LoadImage(HBITMAP hbit,HPALETTE hpal);


	//将图片缩放的数据保存到内存流.hMemBmp指针
	HGLOBAL SaveAsJPG(long quality, //0-100 图片质量
			UINT w=-1,  //图片宽
			UINT h=-1   //图片高
			);


	 

	 
private:
	Bitmap* image;

	ULONG   gdiplusToken; 

	ImageType imgtype;

	int   GetCodecClsid(const   WCHAR*   format,   CLSID*   pClsid)  ;

	bool MyImage::Startup();

	void MyImage::Shutdown();

	UINT width;
	UINT height;
};
