#include "StdAfx.h"
#include ".\myimage.h"

////�������ͼƬ��ָ���������.�����µ�ͼƬ.���ú�Ҫdelete
//Bitmap * ScaleBitmap(Bitmap * pBitmap,UINT nWidth,UINT nHeight)
//{
//	Bitmap * pTemp = new Bitmap(nWidth,nHeight,pBitmap->GetPixelFormat());
//	if( pTemp )
//	{
//		Graphics * g = Graphics::FromImage(pTemp);
//		if( g )
//		{
//			// use the best interpolation mode 
//			g->SetInterpolationMode(InterpolationModeHighQualityBicubic);
//			g->DrawImage(pBitmap,0,0,nWidth,nHeight);
//			delete g;
//		}
//	}
//	return pTemp;
//}
MyImage::MyImage(void)
{
	width=0;
	height=0;
	image=0;
}

MyImage::~MyImage(void)
{
   if (image)
   {
	   delete image;
	   Shutdown();
   }
}

int   MyImage::GetCodecClsid(const   WCHAR*   format,   CLSID*   pClsid)   
{   
	UINT     num   =   0;                     //   number   of   image   encoders   
	UINT     size   =   0;                   //   size   of   the   image   encoder   array   in   bytes   

	ImageCodecInfo*   pImageCodecInfo   =   NULL;   

	GetImageEncodersSize(&num,   &size);   
	if(size   ==   0)   
		return   -1;     //   Failure   

	pImageCodecInfo   =   (ImageCodecInfo*)(malloc(size));   
	if(pImageCodecInfo   ==   NULL)   
		return   -1;     //   Failure   

	GetImageEncoders(num,   size,   pImageCodecInfo);   

	for(int   j   =   0;   j   <   num;   ++j)   
	{   
		if(   wcscmp(pImageCodecInfo[j].MimeType,   format)   ==   0   )   
		{   
			*pClsid   =   pImageCodecInfo[j].Clsid;   
			free(pImageCodecInfo);//�ڴ����
			return   j;     //   Success   
		}           
	}   //   for   

	free(pImageCodecInfo);//�ڴ����
	return   -1;     //   Failure   

}  

bool MyImage::Startup()
{
	Status	stat ;
	GdiplusStartupInput   gdiplusStartupInput;     
	 
	stat=GdiplusStartup(&gdiplusToken,   &gdiplusStartupInput,   NULL);     
	if (stat != Ok)
	{
		return false;
	}
	return true;
}

void MyImage::Shutdown()
{
	GdiplusShutdown(gdiplusToken); 
}

//����
bool MyImage::LoadImage(HBITMAP hbit,HPALETTE hpal)
{
	Startup();

	image = new Bitmap(hbit,hpal);
	if (image==NULL)
	{
		Shutdown();
		return false;
	}
	width=image->GetWidth();
	height=image->GetHeight();

	imgtype=image->GetType();
	if (imgtype==ImageTypeBitmap)
	{

		//CLSID codecClsid; 
		//GetCodecClsid(L"image/bmp",   &codecClsid);   
	}
}



HGLOBAL MyImage::SaveAsJPG( long quality,UINT w,UINT h)
{
	if (!image)
	{
		return 0;
	}
	if (w==-1 || h==-1)
	{
		w=width;
		h=height;
	}

	//����ͼƬ
	Image* pScaledImage = NULL;   
	pScaledImage = image->GetThumbnailImage(w, h, NULL, NULL);   

	CLSID codecClsid; 
	//   Get   the   CLSID   of   the   JPEG   codec.    
	GetCodecClsid(L"image/jpeg",   &codecClsid);   

	EncoderParameters encoderParameters;   
	encoderParameters.Count   =   1;   
	encoderParameters.Parameter[0].Guid   =   EncoderQuality;   
	encoderParameters.Parameter[0].Type   =   EncoderParameterValueTypeLong;   
	encoderParameters.Parameter[0].NumberOfValues   =   1;   
	//   Save   the   image   as   a   JPEG   with   quality   level   0.   
	encoderParameters.Parameter[0].Value   =   &quality;   



	//��ָ��
	IStream* pStmImage = NULL;
	HGLOBAL hMemBmp = GlobalAlloc(GMEM_MOVEABLE,0);//���ƶ��Ļ�����
	if (hMemBmp == NULL)
	{
		goto tag_exit;
	}
	HRESULT h_ret=CreateStreamOnHGlobal(hMemBmp, FALSE, &pStmImage);//���ڴ���B��Ϊ������ʼ
	//creates a stream object stored in global memory
	//
	if (h_ret!=S_OK )
	{
		//	if (pStmImage == NULL)
		{
			GlobalFree(hMemBmp);
			hMemBmp=0;
			goto tag_exit;
		}
	}

	Status	stat ;
	//�������ŵ�ͼ��pStmImage��.
	stat   = pScaledImage->Save(pStmImage,   &codecClsid,   &encoderParameters);   
	//if(stat   ==   Ok)   
		//printf("saved successfully\n");   
//	else   
		//printf("save failed\n" );   


tag_exit:

	delete pScaledImage;  

	return hMemBmp;

}
