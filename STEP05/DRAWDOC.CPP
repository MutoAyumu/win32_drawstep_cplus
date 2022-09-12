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
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc クラスの構築/消滅

CDrawDoc::CDrawDoc()
{
	// TODO: ここにクラスの構築コードを追加します。

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
	CLine* line = new CLine(point, point);
	m_shapeList.AddTail(line);

	SetModifiedFlag();

	return line;
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
	int rop = pDC->GetROP2();

	pDC->SetROP2(R2_NOT);
	DrawShape(pDC);
	pDC->SetROP2(rop);
}