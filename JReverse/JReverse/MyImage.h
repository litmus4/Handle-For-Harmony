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
//HBITMAP��λͼ��ʽ�ڴ�ת��Ϊjpg,��������������.����Ϊ�ڴ�jpg

class MyImage
{
public:
	MyImage(void);
	~MyImage(void);

	//����
	bool LoadImage(HBITMAP hbit,HPALETTE hpal);


	//��ͼƬ���ŵ����ݱ��浽�ڴ���.hMemBmpָ��
	HGLOBAL SaveAsJPG(long quality, //0-100 ͼƬ����
			UINT w=-1,  //ͼƬ��
			UINT h=-1   //ͼƬ��
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
