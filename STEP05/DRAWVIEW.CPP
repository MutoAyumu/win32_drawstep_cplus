// drawview.cpp : CDrawView �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "draw.h"

#include "drawdoc.h"
#include "drawview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//CPoint m_ptStart;

/////////////////////////////////////////////////////////////////////////////
// CDrawView

IMPLEMENT_DYNCREATE(CDrawView, CView)

BEGIN_MESSAGE_MAP(CDrawView, CView)
	//{{AFX_MSG_MAP(CDrawView)
		// NOTE - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
	// �W������R�}���h
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawView �N���X�̍\�z/����

CDrawView::CDrawView()
{
	// TODO: ���̏ꏊ�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
}

CDrawView::~CDrawView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView �N���X�̕`��

void CDrawView::OnDraw(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B

	pDoc->DrawShapeList(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView printing

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �f�t�H���g�̈�������B
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView �N���X�̐f�f

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() // �f�o�b�O �o�[�W�����łȂ����̂̓C�����C��
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawView �N���X�̃��b�Z�[�W �n���h��


void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo

	SetCapture();

	CDrawDoc* d = GetDocument();
	m_pShapeCur = d->NewShape(point);

	CClientDC dc(this);
	m_pShapeCur->NotOutline(&dc);

	CView::OnLButtonDown(nFlags, point);
}

void CDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	if (GetCapture() == this)
	{
		CClientDC dc(this);
		m_pShapeCur->NotOutline(&dc);
		m_pShapeCur->SetEndPoint(point);
		m_pShapeCur->NotOutline(&dc);
	}

	CView::OnMouseMove(nFlags, point);
}

void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	
	if (GetCapture() == this)
	{
		CClientDC dc(this);
		m_pShapeCur->NotOutline(&dc);
		m_pShapeCur->SetEndPoint(point);
		m_pShapeCur->NotOutline(&dc);
	}

	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}