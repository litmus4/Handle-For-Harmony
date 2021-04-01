#pragma once
#include "MyImage.h"


//������

class CScreenShot
{
public:
	CScreenShot(void);
	~CScreenShot(void);

	bool CScreenShot::capture_and_savetobmp(POINT pt,UINT w,UINT h,const wchar_t* savepath,int bit=24);

	bool capture(long quality,POINT pt,UINT w,UINT h);
	
	//�õ��ļ���С
	UINT  GetFileSize();

	//��ȡ�ļ�ĳ������
	void   GetFileStr(char* Dest_str,long filebegin,long filenend);

	void savetofile(const char* savepath);

	char* getJPGbuffer();
private:

	//����Ļ��ȡcopy��λͼ
	HBITMAP  ScreenToBitmap(POINT lefttop ,POINT rightbottom );

	HGLOBAL hMemBmp; 

};

//λͼ���浽�ļ�.ָ��λ��
//lpfilename Ϊλͼ�ļ�����hbitmap Ϊ�ղŵ���Ļλͼ���
int Tofile(HBITMAP hbitmap , LPWSTR lpfilename,int ibits);
 