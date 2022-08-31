// drawdoc.h : CDrawDoc �N���X�̐錾����уC���^�[�t�F�[�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////
class CShape;

class CDrawDoc : public CDocument
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CDrawDoc();
	DECLARE_DYNCREATE(CDrawDoc)

// �A�g���r���[�g
public:

protected:
	CTypedPtrList<CObject, CShape*> m_shapeList;

// �I�y���[�V����
public:
	//�V�K�}�`�I�u�W�F�N�g���쐬���A���X�g��ǉ�����
	CShape* NewShape(CPoint point);

	//�}�`���X�g��`�悷��
	void DrawShapeList(CDC* pDC);

// �I�[�o�[���C�h
	// ClassWizard �ɂ���Đ������ꂽ���z�Ԑ����I�[�o�[���C�h���܂��B
	//{{AFX_VIRTUAL(CDrawDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CDrawDoc();
	virtual void Serialize(CArchive& ar);   // �h�L�������g I/O �ɑ΂��ăI�[�o�[���C�h����܂��B
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CDrawDoc)
		// NOTE - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//CShape

class CShape : public CObject
{
public:
	// �}�`�`��֐��̃C���^�t�F�[�X���K�肷��
	virtual void DrawShape(CDC* pDC) = 0;
	// �쐬���̐}�`�́g�I���_�h��ύX����
	virtual void SetEndPoint(CPoint ptEnd) = 0;
	// �}�`�𔽓]����
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
	// �R���X�g���N�^
public:
	CLine(CPoint ptStart, CPoint ptEnd);

	// �I�y���[�V����
public:
	// �����}�`�i�������g�j��`�悷��
	virtual void DrawShape(CDC* pDC);

	// �쐬���̒����}�`�́g�I���_�h��ύX����
	virtual void SetEndPoint(CPoint ptEnd);

	// �A�g���r���[�g
	CPoint m_ptStart;	//�����̊J�n�_
	CPoint m_ptEnd;		//�����̏I���_
};