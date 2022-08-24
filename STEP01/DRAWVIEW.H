// drawview.h : CDrawView クラスの宣言およびインターフェースの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

class CDrawView : public CView
{
protected: // シリアライズ機能のみから作成します。
	CDrawView();
	DECLARE_DYNCREATE(CDrawView)

// アトリビュート
public:
	CDrawDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard によって生成された仮想関数によってオーバーライドします。
	//{{AFX_VIRTUAL(CDrawView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CDrawView)
		// NOTE - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // drawview.cpp ファイルがデバッグ環境の時使用されます。
inline CDrawDoc* CDrawView::GetDocument()
   { return (CDrawDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
