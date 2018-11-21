// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IMiFont wrapper class

#pragma once



enum MiLANGUAGES 
{ miLANG_CHINESE_SIMPLIFIED = 2052,
miLANG_CHINESE_TRADITIONAL = 1028,
miLANG_CZECH = 5,
miLANG_DANISH = 6, 
miLANG_DUTCH = 19,
miLANG_ENGLISH = 9,
miLANG_FINNISH = 11,
miLANG_FRENCH = 12,
miLANG_GERMAN = 7,
miLANG_GREEK = 8, 
miLANG_HUNGARIAN = 14,
miLANG_ITALIAN = 16,
miLANG_JAPANESE = 17,
miLANG_KOREAN = 18,
miLANG_NORWEGIAN = 20,
miLANG_POLISH = 21,
miLANG_PORTUGUESE = 22,
miLANG_RUSSIAN = 25,
miLANG_SPANISH = 10,
miLANG_SWEDISH = 29,
miLANG_SYSDEFAULT = 2048,
miLANG_TURKISH = 31
};
enum MiFILE_FORMAT
{ miFILE_FORMAT_DEFAULTVALUE = -1,
miFILE_FORMAT_TIFF = 1,
miFILE_FORMAT_TIFF_LOSSLESS = 2, 
miFILE_FORMAT_MDI = 4
};
enum MiCOMP_LEVEL 
{ miCOMP_LEVEL_LOW = 0,
miCOMP_LEVEL_MEDIUM = 1, 
miCOMP_LEVEL_HIGH = 2
};

class IMiFont : public COleDispatchDriver
{
public:
	IMiFont() {}		// Calls COleDispatchDriver default constructor
	IMiFont(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMiFont(const IMiFont& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetFamily();
	long GetFaceStyle();
	long GetSerifStyle();
	short GetFontSize();
};
/////////////////////////////////////////////////////////////////////////////
// IMiRect wrapper class

class IMiRect : public COleDispatchDriver
{
public:
	IMiRect() {}		// Calls COleDispatchDriver default constructor
	IMiRect(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMiRect(const IMiRect& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetTop();
	long GetLeft();
	long GetRight();
	long GetBottom();
};
/////////////////////////////////////////////////////////////////////////////
// IMiRects wrapper class

class IMiRects : public COleDispatchDriver
{
public:
	IMiRects() {}		// Calls COleDispatchDriver default constructor
	IMiRects(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMiRects(const IMiRects& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH GetItem(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// IWord wrapper class

class IWord : public COleDispatchDriver
{
public:
	IWord() {}		// Calls COleDispatchDriver default constructor
	IWord(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWord(const IWord& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	short GetRecognitionConfidence();
	long GetFontId();
	long GetLineId();
	long GetRegionId();
	CString GetText();
	LPDISPATCH GetFont();
	long GetId();
	LPDISPATCH GetRects();
};
/////////////////////////////////////////////////////////////////////////////
// IWords wrapper class

class IWords : public COleDispatchDriver
{
public:
	IWords() {}		// Calls COleDispatchDriver default constructor
	IWords(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWords(const IWords& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH GetItem(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// ILayout wrapper class

class ILayout : public COleDispatchDriver
{
public:
	ILayout() {}		// Calls COleDispatchDriver default constructor
	ILayout(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ILayout(const ILayout& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetLanguage();//获得OCR处理时的使用的语言设置
	long GetNumChars();//获得已经辨认文本的字符数目
	long GetNumWords();
	long GetNumFonts();//获得字体
	CString GetText();//以单CString方式获得辨认文本
	LPDISPATCH GetWords();
};
/////////////////////////////////////////////////////////////////////////////
// IImage wrapper class

class IImage : public COleDispatchDriver
{
public:
	IImage() {}		// Calls COleDispatchDriver default constructor
	IImage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IImage(const IImage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetLayout();	//获得OCR页面结果
	long GetPixelWidth();	//获取像素的宽
	long GetPixelHeight();	//获取像素的高
	long GetXdpi();			//获取每英寸X轴像素
	long GetYdpi();			//获取每英寸Y轴像素
	long GetBitsPerPixel();	//获取每像素的位数
	LPDISPATCH GetThumbnail(long ThumbSize);//返回IPictureDisp，获取图象指图
	LPDISPATCH GetPicture();//获取图象返回IPictureDisp
	long GetCompression();	//获取图片压缩程度
	void OCR(long LangId, BOOL OCROrientImage, BOOL OCRStraightenImage);//对页面执行OCR
	void Rotate(long Angle);//转动页面增加90度
};
/////////////////////////////////////////////////////////////////////////////
// IImages wrapper class

class IImages : public COleDispatchDriver
{
public:
	IImages() {}		// Calls COleDispatchDriver default constructor
	IImages(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IImages(const IImages& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	void Add(LPDISPATCH Page, LPDISPATCH BeforePage);
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH GetItem(long Index);
	void Remove(LPDISPATCH Page);
};
/////////////////////////////////////////////////////////////////////////////
// IDoc wrapper class

class IDoc : public COleDispatchDriver
{
public:
	IDoc() {}		// Calls COleDispatchDriver default constructor
	IDoc(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IDoc(const IDoc& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void Save();					//保存文挡
	void Close(BOOL SaveChanges);	//关闭文挡
	void SaveAs(LPCTSTR FileName, long FileFormat, long CompLevel);//以指定文件名，图片格式，压缩程度来保存文挡
	LPDISPATCH GetImages();			//获取文挡页面收集
	LPDISPATCH GetBuiltInDocumentProperties();//获取Office 文挡属性 
	LPDISPATCH GetCustomDocumentProperties();//获取Office 文挡属性
	void Create(LPCTSTR FileOpen);	//创建新的文挡
	BOOL GetDirty();				//获得一个值，看是否不保存所修改过的文挡
	void OCR(long LangId, BOOL OCROrientImage, BOOL OCRStraightenImage);//对整个文挡执行OCR
	void PrintOut(long From, long To, long Copies, LPCTSTR PrinterName, LPCTSTR PrintToFileName, BOOL PrintAnnotation, long FitMode);//打印文挡到打印机或者文件
};
/////////////////////////////////////////////////////////////////////////////
// _IDocumentEvents wrapper class

class _IDocumentEvents : public COleDispatchDriver
{
public:
	_IDocumentEvents() {}		// Calls COleDispatchDriver default constructor
	_IDocumentEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_IDocumentEvents(const _IDocumentEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	// method 'OnOCRProgress' not emitted because of invalid return type or parameter type
};
/////////////////////////////////////////////////////////////////////////////
// _IImageEvents wrapper class

class _IImageEvents : public COleDispatchDriver
{
public:
	_IImageEvents() {}		// Calls COleDispatchDriver default constructor
	_IImageEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_IImageEvents(const _IImageEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// IMiSelectRect wrapper class

class IMiSelectRect : public COleDispatchDriver
{
public:
	IMiSelectRect() {}		// Calls COleDispatchDriver default constructor
	IMiSelectRect(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMiSelectRect(const IMiSelectRect& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetPageNumber();//获取当前所显示页面
	long GetLeft(); 
	long GetTop();
	long GetRight();
	long GetBottom();
};
/////////////////////////////////////////////////////////////////////////////
// IMiSelectRects wrapper class

class IMiSelectRects : public COleDispatchDriver
{
public:
	IMiSelectRects() {}		// Calls COleDispatchDriver default constructor
	IMiSelectRects(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMiSelectRects(const IMiSelectRects& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH GetItem(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// IMiSelectableItem wrapper class

class IMiSelectableItem : public COleDispatchDriver
{
public:
	IMiSelectableItem() {}		// Calls COleDispatchDriver default constructor
	IMiSelectableItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMiSelectableItem(const IMiSelectableItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void CopyToClipboard();		//拷贝所选择文本到剪贴板
	CString GetText();			//获取选择区域所辨认出的文本
	LPDISPATCH GetWords();		//获得所辨认出的文本的字符集合
	LPDISPATCH GetSelectRects();//返回一个选择区域
};
/////////////////////////////////////////////////////////////////////////////
// IMiSelectableImage wrapper class

class IMiSelectableImage : public COleDispatchDriver
{
public:
	IMiSelectableImage() {}		// Calls COleDispatchDriver default constructor
	IMiSelectableImage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMiSelectableImage(const IMiSelectableImage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void CopyToClipboard(long CopyAnnotation, long AlwaysKeepAnnotationColor);//拷贝所选择文本到剪贴板
	LPDISPATCH ExportToPicture(long CopyAnnotation, long AlwaysKeepAnnotationColor);//返回一个IPictureDisp图形选择
	void GetBoundingRect(long* plPageNum, long* Left, long* Top, long* Right, long* Bottom);//返回一个矩形区域
};
/////////////////////////////////////////////////////////////////////////////
// IMiDocView wrapper class

class IMiDocView : public COleDispatchDriver
{
public:
	IMiDocView() {}		// Calls COleDispatchDriver default constructor
	IMiDocView(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMiDocView(const IMiDocView& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN GetDocument();				//获取文挡
	void SetDocument(LPUNKNOWN newValue);	//设置文挡
	CString GetFileName();					//获取文件名
	void SetFileName(LPCTSTR lpszNewValue); //设置文件名
	long GetNumPages();						//获取文挡的页数
	void ClientToDocument(long* plX, long* plY);//转换视图坐标到文挡坐标
	void DocumentToClient(long* plX, long* plY);//转换文挡坐标到视图坐标
	void ClientToImage(long lSX, long lSY, long* pnPage, long* plX, long* plY);//转换视图坐标到页面坐标
	void ImageToClient(long nPage, long lX, long lY, long* plSX, long* plSY); //页面坐标转换为视图坐标
	void GetVisibleRect(long* Left, long* Top, long* Right, long* Bottom);//返回可视矩形坐标
	void MoveRectIntoView(long Left, long Top, long Right, long Bottom); //移动指定的矩形区域到视图
	long GetDocViewMode();					//获得决定显示页面的方式
	void SetDocViewMode(long nNewValue);	//设置决定以什么的方式去显示页面
	long GetPageNum();						//获取当前所显示页面
	void SetPageNum(long nNewValue);		//设置当前所显示页面
	void GetScale(double* pdScaleX, double* pdScaleY);//获取被使用坐标因素
	void SetScale(double dScaleX, double dScaleY);//设置被使用坐标因素
	long GetFitMode();						//设置确定怎么适合页面到视图窗口值
	void SetFitMode(long nNewValue);		//获取确定怎么适合页面到视图窗口值
	long GetActionState();					//获取运行操作状态
	void SetActionState(long nNewValue);	//设置允许操作状态
	LPDISPATCH GetTextSelection();			//获取用户选择区域
	void SetTextSelection(LPDISPATCH newValue);//设置用户选择区域
	LPDISPATCH GetImageSelection();			//获取用户选择，并以Image返回
	void SetImageSelection(LPDISPATCH newValue);//设置用户选择，并以Image返回
	void SelectAll(long nPage);				//在页面上选择所有东西
	void MoveSelectionToView(LPDISPATCH pdispSelection); //移动用户所选对象到视图
	void SetLayerVisible(long Index, BOOL bNewValue);//设置文挡可视图层
	BOOL GetLayerVisible(long Index);		//获取文挡可视图层
};
/////////////////////////////////////////////////////////////////////////////
// _IMiDocViewEvents wrapper class

class _IMiDocViewEvents : public COleDispatchDriver
{
public:
	_IMiDocViewEvents() {}		// Calls COleDispatchDriver default constructor
	_IMiDocViewEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_IMiDocViewEvents(const _IMiDocViewEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	// method 'FitmodeChanged' not emitted because of invalid return type or parameter type
	// method 'ScaleChanged' not emitted because of invalid return type or parameter type
	// method 'SelectionChanged' not emitted because of invalid return type or parameter type
	// method 'PageChanged' not emitted because of invalid return type or parameter type
	// method 'PageCountChanged' not emitted because of invalid return type or parameter type
	// method 'CurPageNumChanged' not emitted because of invalid return type or parameter type
	// method 'VisibleRectChanged' not emitted because of invalid return type or parameter type
};
/////////////////////////////////////////////////////////////////////////////
// IMiDocSearch wrapper class

class IMiDocSearch : public COleDispatchDriver
{
public:
	IMiDocSearch() {}		// Calls COleDispatchDriver default constructor
	IMiDocSearch(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMiDocSearch(const IMiDocSearch& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void Initialize(LPUNKNOWN piDoc, LPCTSTR strPattern, VARIANT* PageNum, VARIANT* WordIndex, VARIANT* StartAfterIndex, VARIANT* Backward, BOOL MatchMinus, BOOL MatchFullHalfWidthForm, BOOL MatchHiraganaKatakana, BOOL IgnoreSpace);
	void Search(LPUNKNOWN pSearchCallback, LPDISPATCH* ppiSearchResult);
};
