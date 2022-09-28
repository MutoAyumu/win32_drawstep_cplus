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
	// ���ݑI�𒆂̐}�`�̎��
	UINT	m_idShapeCur;

	enum ShapeType
	{
		ID_SHAPE_LINE = 0,
		ID_SHAPE_RECTANGLE = 1,
		ID_SHAPE_ELLIPSE = 2,
	};
	// �����}�`�F	ID_SHAPE_LINE
	// �����`�}�`�F	ID_SHAPE_RECTANGLE
	// �ȉ~�}�`�F	ID_SHAPE_ELLIPSE
// �`��}�`�̃��X�g
	CTypedPtrList<CObList, CShape*> m_shapeList;

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
	DECLARE_SERIAL(CShape)
protected:
	CShape(){}
public:
	// �}�`�`��֐��̃C���^�t�F�[�X���K�肷��
	virtual void DrawShape(CDC* pDC) {}
	// �쐬���̐}�`�́g�I���_�h��ύX����
	virtual void SetEndPoint(CPoint ptEnd) {}
	// �}�`�𔽓]����
	void NotOutline(CDC* pDC);
	// �}�`�𐳋K�����邽�߂̃C���^�[�t�F�[�X���K�肷��
	virtual void Normalize() { }

public:
	virtual void Serialize(CArchive& ar);
};

class CLine : public CShape
{
	// �V���A���C�Y�̂��߂̒ǉ�
	DECLARE_SERIAL(CLine)
protected:
	// �f�t�H���g�R���X�g���N�^�́A�V���A���C�Y�̂��߂Ɏg�p�����
	CLine() {}
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
public:
	virtual void Serialize(CArchive& ar);
};

//CBox

class CBox : public CShape
{
	// �V���A���C�Y
	DECLARE_SERIAL(CBox)
protected:
	// �f�t�H���g�R���X�g���N�^�́A�V���A���C�Y�̂��߂Ɏg�p�����
	CBox() {}
	// �R���X�g���N�^
public:
	CBox(CRect rect);

	// �{�b�N�X�}�`�́g�I���_�h��ύX����
	virtual void SetEndPoint(CPoint ptEnd);

	// �{�b�N�X�}�`�𐳋K������
	virtual void Normalize();

	// �A�g���r���[�g
protected:
	// �{�b�N�X�����`
	CRect  m_rcBox;

	// �I�[�o�[���C�h
public:
	// �V���A���C�Y
	virtual void Serialize(CArchive& ar);
};

// CRectangle

class CRectangle :public CBox
{
	// �V���A���C�Y
	DECLARE_SERIAL(CRectangle)
protected:
	// �f�t�H���g�R���X�g���N�^�́A�V���A���C�Y�̂��߂Ɏg�p�����
	CRectangle() {}

	// �R���X�g���N�^
public:
	CRectangle(CRect rect)
		: CBox(rect) {}

	// �I�y���[�V����
public:
	// �����`��`�悷��
	virtual void DrawShape(CDC* pDC);

	// �I�[�o�[���C�h
public:
	// �V���A���C�Y
	virtual void Serialize(CArchive& ar);
};

// CEllipse

class CEllipse : public CBox
{
	// �V���A���C�Y
	DECLARE_SERIAL(CEllipse)
protected:
	// �f�t�H���g�R���X�g���N�^�́A�V���A���C�Y�̂��߂Ɏg�p�����
	CEllipse() { }

	// �R���X�g���N�^
public:
	CEllipse(CRect rect)
		:CBox(rect) { }

	// �I�y���[�V����
public:
	// �ȉ~�}�`��`�悷��
	virtual void DrawShape(CDC* pDC);

	// �I�[�o�[���C�h
public:
	// �V���A���C�Y
	virtual void Serialize(CArchive& ar);
};