// drawdoc.h : CDrawDoc クラスの宣言およびインターフェースの定義をします。
//
/////////////////////////////////////////////////////////////////////////////
class CShape;

class CDrawDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CDrawDoc();
	DECLARE_DYNCREATE(CDrawDoc)

// アトリビュート
public:

protected:
	// 現在選択中の図形の種類
	UINT	m_idShapeCur;

	enum ShapeType
	{
		ID_SHAPE_LINE = 0,
		ID_SHAPE_RECTANGLE = 1,
		ID_SHAPE_ELLIPSE = 2,
	};
	// 直線図形：	ID_SHAPE_LINE
	// 長方形図形：	ID_SHAPE_RECTANGLE
	// 楕円図形：	ID_SHAPE_ELLIPSE
// 描画図形のリスト
	CTypedPtrList<CObList, CShape*> m_shapeList;

// オペレーション
public:
	//新規図形オブジェクトを作成し、リストを追加する
	CShape* NewShape(CPoint point);

	//図形リストを描画する
	void DrawShapeList(CDC* pDC);

// オーバーライド
	// ClassWizard によって生成された仮想間数がオーバーライドします。
	//{{AFX_VIRTUAL(CDrawDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CDrawDoc();
	virtual void Serialize(CArchive& ar);   // ドキュメント I/O に対してオーバーライドされます。
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CDrawDoc)
		// NOTE - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//CShape

class CShape : public CObject
{
	DECLARE_SERIAL(CShape)
protected:
	CShape(){}
public:
	// 図形描画関数のインタフェースを規定する
	virtual void DrawShape(CDC* pDC) {}
	// 作成中の図形の“終了点”を変更する
	virtual void SetEndPoint(CPoint ptEnd) {}
	// 図形を反転する
	void NotOutline(CDC* pDC);
	// 図形を正規化するためのインターフェースを規定する
	virtual void Normalize() { }

public:
	virtual void Serialize(CArchive& ar);
};

class CLine : public CShape
{
	// シリアライズのための追加
	DECLARE_SERIAL(CLine)
protected:
	// デフォルトコンストラクタは、シリアライズのために使用される
	CLine() {}
	// コンストラクタ
public:
	CLine(CPoint ptStart, CPoint ptEnd);

	// オペレーション
public:
	// 直線図形（自分自身）を描画する
	virtual void DrawShape(CDC* pDC);

	// 作成中の直線図形の“終了点”を変更する
	virtual void SetEndPoint(CPoint ptEnd);

	// アトリビュート
	CPoint m_ptStart;	//直線の開始点
	CPoint m_ptEnd;		//直線の終了点
public:
	virtual void Serialize(CArchive& ar);
};

//CBox

class CBox : public CShape
{
	// シリアライズ
	DECLARE_SERIAL(CBox)
protected:
	// デフォルトコンストラクタは、シリアライズのために使用される
	CBox() {}
	// コンストラクタ
public:
	CBox(CRect rect);

	// ボックス図形の“終了点”を変更する
	virtual void SetEndPoint(CPoint ptEnd);

	// ボックス図形を正規化する
	virtual void Normalize();

	// アトリビュート
protected:
	// ボックス長方形
	CRect  m_rcBox;

	// オーバーライド
public:
	// シリアライズ
	virtual void Serialize(CArchive& ar);
};

// CRectangle

class CRectangle :public CBox
{
	// シリアライズ
	DECLARE_SERIAL(CRectangle)
protected:
	// デフォルトコンストラクタは、シリアライズのために使用される
	CRectangle() {}

	// コンストラクタ
public:
	CRectangle(CRect rect)
		: CBox(rect) {}

	// オペレーション
public:
	// 長方形を描画する
	virtual void DrawShape(CDC* pDC);

	// オーバーライド
public:
	// シリアライズ
	virtual void Serialize(CArchive& ar);
};

// CEllipse

class CEllipse : public CBox
{
	// シリアライズ
	DECLARE_SERIAL(CEllipse)
protected:
	// デフォルトコンストラクタは、シリアライズのために使用される
	CEllipse() { }

	// コンストラクタ
public:
	CEllipse(CRect rect)
		:CBox(rect) { }

	// オペレーション
public:
	// 楕円図形を描画する
	virtual void DrawShape(CDC* pDC);

	// オーバーライド
public:
	// シリアライズ
	virtual void Serialize(CArchive& ar);
};
