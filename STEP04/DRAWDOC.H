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
	CTypedPtrList<CObject, CShape*> m_shapeList;

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
public:
	// 図形描画関数のインタフェースを規定する
	virtual void DrawShape(CDC* pDC) = 0;
	// 作成中の図形の“終了点”を変更する
	virtual void SetEndPoint(CPoint ptEnd) = 0;
	// 図形を反転する
	void NotOutline(CDC* pDC)
	{
		int rop = pDC->GetROP2();

		pDC->SetROP2(R2_NOT);
		DrawShape(pDC);
		pDC->SetROP2(rop);
	}
};

class CLine : public CShape
{
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
};
