// draw.h : DRAW アプリケーションのメイン ヘッダー ファイル
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CDrawApp:
// このクラスの動作の定義に関しては draw.cpp ファイルを参照してください。
//

class CDrawApp : public CWinApp
{
public:
	CDrawApp();

// オーバーライド
	// ClassWizard によって生成された仮想関数がオーバーライドします
	//{{AFX_VIRTUAL(CDrawApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CDrawApp)
	afx_msg void OnAppAbout();
		// NOTE - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
