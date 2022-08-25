// drawview.cpp : CDrawView クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "draw.h"

#include "drawdoc.h"
#include "drawview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawView

IMPLEMENT_DYNCREATE(CDrawView, CView)

BEGIN_MESSAGE_MAP(CDrawView, CView)
	//{{AFX_MSG_MAP(CDrawView)
		// NOTE - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawView クラスの構築/消滅

CDrawView::CDrawView()
{
	// TODO: この場所に構築用のコードを追加してください。
}

CDrawView::~CDrawView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView クラスの描画

void CDrawView::OnDraw(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView printing

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// デフォルトの印刷準備。
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView クラスの診断

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() // デバッグ バージョンでないものはインライン
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawView クラスのメッセージ ハンドラ


void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出

	CWnd::SetCapture();

	_ptStart = point;

	CView::OnLButtonDown(nFlags, point);
}


void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	if (CWnd::GetCapture() == this->m_hWnd)
	{

	}

	CView::OnLButtonUp(nFlags, point);

	::ReleaseCapture();
}
