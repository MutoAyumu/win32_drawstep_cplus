// draw.h : DRAW �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CDrawApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� draw.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CDrawApp : public CWinApp
{
public:
	CDrawApp();

// �I�[�o�[���C�h
	// ClassWizard �ɂ���Đ������ꂽ���z�֐����I�[�o�[���C�h���܂�
	//{{AFX_VIRTUAL(CDrawApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CDrawApp)
	afx_msg void OnAppAbout();
		// NOTE - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////