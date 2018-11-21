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
	long GetLanguage();//���OCR����ʱ��ʹ�õ���������
	long GetNumChars();//����Ѿ������ı����ַ���Ŀ
	long GetNumWords();
	long GetNumFonts();//�������
	CString GetText();//�Ե�CString��ʽ��ñ����ı�
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
	LPDISPATCH GetLayout();	//���OCRҳ����
	long GetPixelWidth();	//��ȡ���صĿ�
	long GetPixelHeight();	//��ȡ���صĸ�
	long GetXdpi();			//��ȡÿӢ��X������
	long GetYdpi();			//��ȡÿӢ��Y������
	long GetBitsPerPixel();	//��ȡÿ���ص�λ��
	LPDISPATCH GetThumbnail(long ThumbSize);//����IPictureDisp����ȡͼ��ָͼ
	LPDISPATCH GetPicture();//��ȡͼ�󷵻�IPictureDisp
	long GetCompression();	//��ȡͼƬѹ���̶�
	void OCR(long LangId, BOOL OCROrientImage, BOOL OCRStraightenImage);//��ҳ��ִ��OCR
	void Rotate(long Angle);//ת��ҳ������90��
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
	void Save();					//�����ĵ�
	void Close(BOOL SaveChanges);	//�ر��ĵ�
	void SaveAs(LPCTSTR FileName, long FileFormat, long CompLevel);//��ָ���ļ�����ͼƬ��ʽ��ѹ���̶��������ĵ�
	LPDISPATCH GetImages();			//��ȡ�ĵ�ҳ���ռ�
	LPDISPATCH GetBuiltInDocumentProperties();//��ȡOffice �ĵ����� 
	LPDISPATCH GetCustomDocumentProperties();//��ȡOffice �ĵ�����
	void Create(LPCTSTR FileOpen);	//�����µ��ĵ�
	BOOL GetDirty();				//���һ��ֵ�����Ƿ񲻱������޸Ĺ����ĵ�
	void OCR(long LangId, BOOL OCROrientImage, BOOL OCRStraightenImage);//�������ĵ�ִ��OCR
	void PrintOut(long From, long To, long Copies, LPCTSTR PrinterName, LPCTSTR PrintToFileName, BOOL PrintAnnotation, long FitMode);//��ӡ�ĵ�����ӡ�������ļ�
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
	long GetPageNumber();//��ȡ��ǰ����ʾҳ��
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
	void CopyToClipboard();		//������ѡ���ı���������
	CString GetText();			//��ȡѡ�����������ϳ����ı�
	LPDISPATCH GetWords();		//��������ϳ����ı����ַ�����
	LPDISPATCH GetSelectRects();//����һ��ѡ������
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
	void CopyToClipboard(long CopyAnnotation, long AlwaysKeepAnnotationColor);//������ѡ���ı���������
	LPDISPATCH ExportToPicture(long CopyAnnotation, long AlwaysKeepAnnotationColor);//����һ��IPictureDispͼ��ѡ��
	void GetBoundingRect(long* plPageNum, long* Left, long* Top, long* Right, long* Bottom);//����һ����������
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
	LPUNKNOWN GetDocument();				//��ȡ�ĵ�
	void SetDocument(LPUNKNOWN newValue);	//�����ĵ�
	CString GetFileName();					//��ȡ�ļ���
	void SetFileName(LPCTSTR lpszNewValue); //�����ļ���
	long GetNumPages();						//��ȡ�ĵ���ҳ��
	void ClientToDocument(long* plX, long* plY);//ת����ͼ���굽�ĵ�����
	void DocumentToClient(long* plX, long* plY);//ת���ĵ����굽��ͼ����
	void ClientToImage(long lSX, long lSY, long* pnPage, long* plX, long* plY);//ת����ͼ���굽ҳ������
	void ImageToClient(long nPage, long lX, long lY, long* plSX, long* plSY); //ҳ������ת��Ϊ��ͼ����
	void GetVisibleRect(long* Left, long* Top, long* Right, long* Bottom);//���ؿ��Ӿ�������
	void MoveRectIntoView(long Left, long Top, long Right, long Bottom); //�ƶ�ָ���ľ���������ͼ
	long GetDocViewMode();					//��þ�����ʾҳ��ķ�ʽ
	void SetDocViewMode(long nNewValue);	//���þ�����ʲô�ķ�ʽȥ��ʾҳ��
	long GetPageNum();						//��ȡ��ǰ����ʾҳ��
	void SetPageNum(long nNewValue);		//���õ�ǰ����ʾҳ��
	void GetScale(double* pdScaleX, double* pdScaleY);//��ȡ��ʹ����������
	void SetScale(double dScaleX, double dScaleY);//���ñ�ʹ����������
	long GetFitMode();						//����ȷ����ô�ʺ�ҳ�浽��ͼ����ֵ
	void SetFitMode(long nNewValue);		//��ȡȷ����ô�ʺ�ҳ�浽��ͼ����ֵ
	long GetActionState();					//��ȡ���в���״̬
	void SetActionState(long nNewValue);	//�����������״̬
	LPDISPATCH GetTextSelection();			//��ȡ�û�ѡ������
	void SetTextSelection(LPDISPATCH newValue);//�����û�ѡ������
	LPDISPATCH GetImageSelection();			//��ȡ�û�ѡ�񣬲���Image����
	void SetImageSelection(LPDISPATCH newValue);//�����û�ѡ�񣬲���Image����
	void SelectAll(long nPage);				//��ҳ����ѡ�����ж���
	void MoveSelectionToView(LPDISPATCH pdispSelection); //�ƶ��û���ѡ������ͼ
	void SetLayerVisible(long Index, BOOL bNewValue);//�����ĵ�����ͼ��
	BOOL GetLayerVisible(long Index);		//��ȡ�ĵ�����ͼ��
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
