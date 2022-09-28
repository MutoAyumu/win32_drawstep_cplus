// drawdoc.cpp : CDrawDoc �N���X�̓���̒�`���s���܂��B
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
		// NOTE - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc �N���X�̍\�z/����

CDrawDoc::CDrawDoc()
{
	// TODO: �����ɃN���X�̍\�z�R�[�h��ǉ����܂��B
	m_idShapeCur = ID_SHAPE_LINE;
}

CDrawDoc::~CDrawDoc()
{
}

BOOL CDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc �N���X�̃V���A���C�[�[�V����

void CDrawDoc::Serialize(CArchive& ar)
{
	m_shapeList.Serialize(ar);

	if (ar.IsStoring())
	{
		// TODO:���̈ʒu�ɕۑ��p�̃R�[�h��ǉ����Ă��������B
	}
	else
	{
		// TODO: ���̈ʒu�ɓǂݍ��ݗp�̃R�[�h��ǉ����Ă��������B
	}
}


/////////////////////////////////////////////////////////////////////////////
// CDrawDoc �N���X�̐f�f

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
// CDrawDoc �R�}���h


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
	//�ȑO�̃��X�^�I�y���[�V�������[�h��ۑ����Ă����B
	int rop = pDC->GetROP2();
	//�ȑO�I������Ă����u���V�͕ۑ����Ă����B
	CBrush* stock = pDC->GetCurrentBrush();
	//�f�o�C�X�R���e�L�X�g��NULL_BRUSH��I������B
	pDC->SelectStockObject(NULL_BRUSH);
	//���X�^�I�y���[�V�������[�h��R2_NOT(���])�Ƃ���B
	pDC->SetROP2(R2_NOT);
	//���֐����N�������h���N���X�I�u�W�F�N�g��DrawShape���z�֐����Ăяo���B
	DrawShape(pDC);
	//�f�o�C�X�R���e�L�X�g�̃u���V���ȑO�̏�Ԃɖ߂��B
	pDC->SelectObject(stock);
	//�f�o�C�X�R���e�L�X�g�̃��X�^�I�y���[�V�������[�h���ȑO�̏�Ԃɖ߂�.
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

//Rectangle

IMPLEMENT_SERIAL(CRectangle, CBox, 1)

CRectangle::CRectangle(CRect rect)
{
	m_rcBox = rect;
}

void CRectangle::Serialize(CArchive& ar)
{
	CBox::Serialize(ar);
}

// CRectangle
IMPLEMENT_SERIAL(CEllipse, CBox, 1)

CEllipse::CEllipse(CRect rect)
{
	m_rcBox = rect;
}

void CEllipse::DrawShape(CDC* pDC)
{
	pDC->Ellipse(m_rcBox);
}

void CEllipse::Serialize(CArchive& ar)
{
	CBox::Serialize(ar);
}