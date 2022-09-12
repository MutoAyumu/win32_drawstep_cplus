// drawview.h : CDrawView �N���X�̐錾����уC���^�[�t�F�[�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

class CShape;

class CDrawView : public CView
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CDrawView();
	DECLARE_DYNCREATE(CDrawView)

// �A�g���r���[�g
public:
	CDrawDoc* GetDocument();
protected:
	CPoint m_ptStart;	//�����̊J�n�n�_
	CPoint m_ptPrev;	//���O�̃}�E�X�̈ʒu
	CShape* m_pShapeCur;	//�S�[�X�g�C���[�W�\�����̐}�`�I�u�W�F�N�g

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �ɂ���Đ������ꂽ���z�֐��ɂ���ăI�[�o�[���C�h���܂��B
	//{{AFX_VIRTUAL(CDrawView)
	public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷��ۂɃI�[�o�[���C�h����܂��B
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CDrawView)
		// NOTE - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // drawview.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CDrawDoc* CDrawView::GetDocument()
   { return (CDrawDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////