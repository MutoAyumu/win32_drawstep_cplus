// drawdoc.h : CDrawDoc �N���X�̐錾����уC���^�[�t�F�[�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

class CDrawDoc : public CDocument
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CDrawDoc();
	DECLARE_DYNCREATE(CDrawDoc)

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �ɂ���Đ������ꂽ���z�Ԑ����I�[�o�[���C�h���܂��B
	//{{AFX_VIRTUAL(CDrawDoc)
	public:
	virtual BOOL OnNewDocument();
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