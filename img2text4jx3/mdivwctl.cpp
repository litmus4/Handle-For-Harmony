// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "mdivwctl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IMiFont properties

/////////////////////////////////////////////////////////////////////////////
// IMiFont operations

long IMiFont::GetFamily()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IMiFont::GetFaceStyle()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IMiFont::GetSerifStyle()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

short IMiFont::GetFontSize()
{
	short result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IMiRect properties

/////////////////////////////////////////////////////////////////////////////
// IMiRect operations

long IMiRect::GetTop()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IMiRect::GetLeft()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IMiRect::GetRight()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IMiRect::GetBottom()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IMiRects properties

/////////////////////////////////////////////////////////////////////////////
// IMiRects operations

long IMiRects::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPUNKNOWN IMiRects::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

LPDISPATCH IMiRects::GetItem(long Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		Index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IWord properties

/////////////////////////////////////////////////////////////////////////////
// IWord operations

short IWord::GetRecognitionConfidence()
{
	short result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

long IWord::GetFontId()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IWord::GetLineId()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IWord::GetRegionId()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IWord::GetText()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IWord::GetFont()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IWord::GetId()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IWord::GetRects()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IWords properties

/////////////////////////////////////////////////////////////////////////////
// IWords operations

long IWords::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPUNKNOWN IWords::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

LPDISPATCH IWords::GetItem(long Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		Index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ILayout properties

/////////////////////////////////////////////////////////////////////////////
// ILayout operations

long ILayout::GetLanguage()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ILayout::GetNumChars()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ILayout::GetNumWords()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ILayout::GetNumFonts()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString ILayout::GetText()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH ILayout::GetWords()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IImage properties

/////////////////////////////////////////////////////////////////////////////
// IImage operations

LPDISPATCH IImage::GetLayout()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IImage::GetPixelWidth()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IImage::GetPixelHeight()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IImage::GetXdpi()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IImage::GetYdpi()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IImage::GetBitsPerPixel()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IImage::GetThumbnail(long ThumbSize)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		ThumbSize);
	return result;
}

LPDISPATCH IImage::GetPicture()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IImage::GetCompression()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IImage::OCR(long LangId, BOOL OCROrientImage, BOOL OCRStraightenImage)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL VTS_BOOL;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 LangId, OCROrientImage, OCRStraightenImage);
}

void IImage::Rotate(long Angle)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Angle);
}


/////////////////////////////////////////////////////////////////////////////
// IImages properties

/////////////////////////////////////////////////////////////////////////////
// IImages operations

long IImages::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IImages::Add(LPDISPATCH Page, LPDISPATCH BeforePage)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Page, BeforePage);
}

LPUNKNOWN IImages::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

LPDISPATCH IImages::GetItem(long Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		Index);
	return result;
}

void IImages::Remove(LPDISPATCH Page)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Page);
}


/////////////////////////////////////////////////////////////////////////////
// IDoc properties

/////////////////////////////////////////////////////////////////////////////
// IDoc operations

void IDoc::Save()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IDoc::Close(BOOL SaveChanges)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveChanges);
}

void IDoc::SaveAs(LPCTSTR FileName, long FileFormat, long CompLevel)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, FileFormat, CompLevel);
}

LPDISPATCH IDoc::GetImages()
{
	LPDISPATCH result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IDoc::GetBuiltInDocumentProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IDoc::GetCustomDocumentProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IDoc::Create(LPCTSTR FileOpen)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileOpen);
}

BOOL IDoc::GetDirty()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IDoc::OCR(long LangId, BOOL OCROrientImage, BOOL OCRStraightenImage)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL VTS_BOOL;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 LangId, OCROrientImage, OCRStraightenImage);
}

void IDoc::PrintOut(long From, long To, long Copies, LPCTSTR PrinterName, LPCTSTR PrintToFileName, BOOL PrintAnnotation, long FitMode)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BOOL VTS_I4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 From, To, Copies, PrinterName, PrintToFileName, PrintAnnotation, FitMode);
}


/////////////////////////////////////////////////////////////////////////////
// _IDocumentEvents properties

/////////////////////////////////////////////////////////////////////////////
// _IDocumentEvents operations


/////////////////////////////////////////////////////////////////////////////
// _IImageEvents properties

/////////////////////////////////////////////////////////////////////////////
// _IImageEvents operations


/////////////////////////////////////////////////////////////////////////////
// IMiSelectRect properties

/////////////////////////////////////////////////////////////////////////////
// IMiSelectRect operations

long IMiSelectRect::GetPageNumber()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IMiSelectRect::GetLeft()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IMiSelectRect::GetTop()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IMiSelectRect::GetRight()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IMiSelectRect::GetBottom()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IMiSelectRects properties

/////////////////////////////////////////////////////////////////////////////
// IMiSelectRects operations

long IMiSelectRects::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPUNKNOWN IMiSelectRects::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

LPDISPATCH IMiSelectRects::GetItem(long Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		Index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IMiSelectableItem properties

/////////////////////////////////////////////////////////////////////////////
// IMiSelectableItem operations

void IMiSelectableItem::CopyToClipboard()
{
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString IMiSelectableItem::GetText()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IMiSelectableItem::GetWords()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IMiSelectableItem::GetSelectRects()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IMiSelectableImage properties

/////////////////////////////////////////////////////////////////////////////
// IMiSelectableImage operations

void IMiSelectableImage::CopyToClipboard(long CopyAnnotation, long AlwaysKeepAnnotationColor)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 CopyAnnotation, AlwaysKeepAnnotationColor);
}

LPDISPATCH IMiSelectableImage::ExportToPicture(long CopyAnnotation, long AlwaysKeepAnnotationColor)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		CopyAnnotation, AlwaysKeepAnnotationColor);
	return result;
}

void IMiSelectableImage::GetBoundingRect(long* plPageNum, long* Left, long* Top, long* Right, long* Bottom)
{
	static BYTE parms[] =
		VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 plPageNum, Left, Top, Right, Bottom);
}


/////////////////////////////////////////////////////////////////////////////
// IMiDocView properties

/////////////////////////////////////////////////////////////////////////////
// IMiDocView operations

LPUNKNOWN IMiDocView::GetDocument()
{
	LPUNKNOWN result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void IMiDocView::SetDocument(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IMiDocView::GetFileName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IMiDocView::SetFileName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IMiDocView::GetNumPages()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IMiDocView::ClientToDocument(long* plX, long* plY)
{
	static BYTE parms[] =
		VTS_PI4 VTS_PI4;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 plX, plY);
}

void IMiDocView::DocumentToClient(long* plX, long* plY)
{
	static BYTE parms[] =
		VTS_PI4 VTS_PI4;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 plX, plY);
}

void IMiDocView::ClientToImage(long lSX, long lSY, long* pnPage, long* plX, long* plY)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 VTS_PI4;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lSX, lSY, pnPage, plX, plY);
}

void IMiDocView::ImageToClient(long nPage, long lX, long lY, long* plSX, long* plSY)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_PI4 VTS_PI4;
	InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nPage, lX, lY, plSX, plSY);
}

void IMiDocView::GetVisibleRect(long* Left, long* Top, long* Right, long* Bottom)
{
	static BYTE parms[] =
		VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Left, Top, Right, Bottom);
}

void IMiDocView::MoveRectIntoView(long Left, long Top, long Right, long Bottom)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Left, Top, Right, Bottom);
}

long IMiDocView::GetDocViewMode()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IMiDocView::SetDocViewMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IMiDocView::GetPageNum()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IMiDocView::SetPageNum(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IMiDocView::GetScale(double* pdScaleX, double* pdScaleY)
{
	static BYTE parms[] =
		VTS_PR8 VTS_PR8;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pdScaleX, pdScaleY);
}

void IMiDocView::SetScale(double dScaleX, double dScaleY)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 dScaleX, dScaleY);
}

long IMiDocView::GetFitMode()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IMiDocView::SetFitMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IMiDocView::GetActionState()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IMiDocView::SetActionState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IMiDocView::GetTextSelection()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IMiDocView::SetTextSelection(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IMiDocView::GetImageSelection()
{
	LPDISPATCH result;
	InvokeHelper(0x2f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IMiDocView::SetImageSelection(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x2f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void IMiDocView::SelectAll(long nPage)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nPage);
}

void IMiDocView::MoveSelectionToView(LPDISPATCH pdispSelection)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pdispSelection);
}

void IMiDocView::SetLayerVisible(long Index, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x1d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, bNewValue);
}

BOOL IMiDocView::GetLayerVisible(long Index)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		Index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _IMiDocViewEvents properties

/////////////////////////////////////////////////////////////////////////////
// _IMiDocViewEvents operations


/////////////////////////////////////////////////////////////////////////////
// IMiDocSearch properties

/////////////////////////////////////////////////////////////////////////////
// IMiDocSearch operations

void IMiDocSearch::Initialize(LPUNKNOWN piDoc, LPCTSTR strPattern, VARIANT* PageNum, VARIANT* WordIndex, VARIANT* StartAfterIndex, VARIANT* Backward, BOOL MatchMinus, BOOL MatchFullHalfWidthForm, BOOL MatchHiraganaKatakana, BOOL IgnoreSpace)
{
	static BYTE parms[] =
		VTS_UNKNOWN VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 piDoc, strPattern, PageNum, WordIndex, StartAfterIndex, Backward, MatchMinus, MatchFullHalfWidthForm, MatchHiraganaKatakana, IgnoreSpace);
}

void IMiDocSearch::Search(LPUNKNOWN pSearchCallback, LPDISPATCH* ppiSearchResult)
{
	static BYTE parms[] =
		VTS_UNKNOWN VTS_PDISPATCH;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pSearchCallback, ppiSearchResult);
}
