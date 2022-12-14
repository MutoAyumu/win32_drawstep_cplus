// drawdoc.cpp : CDrawDoc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "draw.h"

#include "drawdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc

IMPLEMENT_DYNCREATE(CDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawDoc, CDocument)
	//{{AFX_MSG_MAP(CDrawDoc)
		// NOTE - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_32772, &CDrawDoc::OnShapeLine)
	ON_COMMAND(ID_32773, &CDrawDoc::OnShapeRectangle)
	ON_COMMAND(ID_32774, &CDrawDoc::OnShapeEllipse)
	ON_UPDATE_COMMAND_UI(ID_32772, &CDrawDoc::OnUpdateShapeLine)
	ON_UPDATE_COMMAND_UI(ID_32773, &CDrawDoc::OnUpdateShapeRectangle)
	ON_UPDATE_COMMAND_UI(ID_32774, &CDrawDoc::OnUpdateShapeEllipse)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc クラスの構築/消滅

CDrawDoc::CDrawDoc()
{
	// TODO: ここにクラスの構築コードを追加します。
	m_idShapeCur = ID_SHAPE_LINE;
}

CDrawDoc::~CDrawDoc()
{
}

BOOL CDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc クラスのシリアライゼーション

void CDrawDoc::Serialize(CArchive& ar)
{
	m_shapeList.Serialize(ar);

	if (ar.IsStoring())
	{
		// TODO:この位置に保存用のコードを追加してください。
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
	}
}


/////////////////////////////////////////////////////////////////////////////
// CDrawDoc クラスの診断

#ifdef _DEBUG
void CDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc コマンド


/////////////////////////////////////////////////////////////////////////////
// CLine

CLine::CLine(CPoint ptStart, CPoint ptEnd)
{
	m_ptStart = ptStart;
	m_ptEnd = ptEnd;
}

void CLine::SetEndPoint(CPoint ptEnd)
{
	m_ptEnd = ptEnd;
}

void CLine::DrawShape(CDC* pDC)
{
	pDC->MoveTo(m_ptStart);
	pDC->LineTo(m_ptEnd);
}

CShape* CDrawDoc::NewShape(CPoint point)
{
	SetModifiedFlag();

	if (m_idShapeCur == ID_SHAPE_LINE)
	{
		CLine* line = new CLine(point, point);
		m_shapeList.AddTail(line);
		return line;
	}
	else if (m_idShapeCur == ID_SHAPE_RECTANGLE)
	{
		CRect rect = new CRect();
		rect.SetRect(point,point);
		CRectangle* rectAngle = new CRectangle(rect);
		m_shapeList.AddTail(rectAngle);
		return rectAngle;
	}
	else if (m_idShapeCur == ID_SHAPE_ELLIPSE)
	{
		CRect rect = new CRect();
		rect.SetRect(point, point);
		CEllipse* ellipse = new CEllipse(rect);
		m_shapeList.AddTail(ellipse);
		return ellipse;
	}
}

void CDrawDoc::DeleteContents()
{
	while (!m_shapeList.IsEmpty())
	{
		CShape* shape = m_shapeList.RemoveHead();
		delete shape;
	}

	SetModifiedFlag();

	CDocument::DeleteContents();
}

void CDrawDoc::DrawShapeList(CDC* pDC)
{
	POSITION p;
	p = m_shapeList.GetHeadPosition();

	while(p != NULL)
	{
		CShape* shape = m_shapeList.GetNext(p);
		shape->DrawShape(pDC);
	}
}

void CShape::NotOutline(CDC* pDC)
{
	//以前のラスタオペレーションモードを保存しておく。
	int rop = pDC->GetROP2();
	//以前選択されていたブラシは保存しておく。
	CBrush* stock = pDC->GetCurrentBrush();
	//デバイスコンテキストにNULL_BRUSHを選択する。
	pDC->SelectStockObject(NULL_BRUSH);
	//ラスタオペレーションモードをR2_NOT(反転)とする。
	pDC->SetROP2(R2_NOT);
	//当関数を起動した派生クラスオブジェクトのDrawShape仮想関数を呼び出す。
	DrawShape(pDC);
	//デバイスコンテキストのブラシを以前の状態に戻す。
	pDC->SelectObject(stock);
	//デバイスコンテキストのラスタオペレーションモードを以前の状態に戻す.
	pDC->SetROP2(rop);
}

IMPLEMENT_SERIAL(CShape, CObject, 1)
void CShape::Serialize(CArchive& ar)
{

}
IMPLEMENT_SERIAL(CLine, CShape, 1)
void CLine::Serialize(CArchive& ar)
{
	CShape::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_ptStart;
		ar << m_ptEnd;
	}
	else
	{
		ar >> m_ptStart;
		ar >> m_ptEnd;
	}
}

//CBox
IMPLEMENT_SERIAL(CBox, CShape, 1)

CBox::CBox(CRect rect)
{
	m_rcBox = rect;
}

void CBox::SetEndPoint(CPoint ptEnd)
{
	CRect rect = m_rcBox;
	rect.SetRect(rect.TopLeft(), ptEnd);
	m_rcBox = rect;
}

void CBox::Normalize()
{
	m_rcBox.NormalizeRect();
}

void CBox::Serialize(CArchive& ar)
{
	CShape::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_rcBox;
	}
	else
	{
		ar >> m_rcBox;
	}
}

//CRectangle

IMPLEMENT_SERIAL(CRectangle, CBox, 1)

void CRectangle::DrawShape(CDC* pDC)
{
	pDC->Rectangle(m_rcBox);
}

void CRectangle::Serialize(CArchive& ar)
{
	CBox::Serialize(ar);
}

// CEllipse
IMPLEMENT_SERIAL(CEllipse, CBox, 1)

void CEllipse::DrawShape(CDC* pDC)
{
	pDC->Ellipse(m_rcBox);
}

void CEllipse::Serialize(CArchive& ar)
{
	CBox::Serialize(ar);
}

void CDrawDoc::OnShapeLine()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	m_idShapeCur = ID_SHAPE_LINE;
}


void CDrawDoc::OnShapeRectangle()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	m_idShapeCur = ID_SHAPE_RECTANGLE;
}


void CDrawDoc::OnShapeEllipse()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	m_idShapeCur = ID_SHAPE_ELLIPSE;
}


void CDrawDoc::OnUpdateShapeLine(CCmdUI* pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	if (m_idShapeCur == ID_SHAPE_LINE)
	{
		pCmdUI->SetCheck(true);
	}
	else
	{
		pCmdUI->SetCheck(false);
	}
}


void CDrawDoc::OnUpdateShapeRectangle(CCmdUI* pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	if (m_idShapeCur == ID_SHAPE_RECTANGLE)
	{
		pCmdUI->SetCheck(true);
	}
	else
	{
		pCmdUI->SetCheck(false);
	}
}


void CDrawDoc::OnUpdateShapeEllipse(CCmdUI* pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	if (m_idShapeCur == ID_SHAPE_ELLIPSE)
	{
		pCmdUI->SetCheck(true);
	}
	else
	{
		pCmdUI->SetCheck(false);
	}
}
