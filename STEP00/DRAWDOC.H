// drawdoc.h : CDrawDoc クラスの宣言およびインターフェースの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

class CDrawDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CDrawDoc();
	DECLARE_DYNCREATE(CDrawDoc)

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard によって生成された仮想間数がオーバーライドします。
	//{{AFX_VIRTUAL(CDrawDoc)
	public:
	virtual BOOL OnNewDocument();
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
