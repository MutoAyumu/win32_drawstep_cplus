// draw.cpp : アプリケーション用クラスの機能定義を行います。
//

#include "stdafx.h"
#include "draw.h"

#include "mainfrm.h"
#include "drawdoc.h"
#include "drawview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawApp

BEGIN_MESSAGE_MAP(CDrawApp, CWinApp)
	//{{AFX_MSG_MAP(CDrawApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// 標準の印刷セットアップ コマンド
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawApp クラスの構築

CDrawApp::CDrawApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CDrawApp オブジェクト

CDrawApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDrawApp クラスの初期化

BOOL CDrawApp::InitInstance()
{
	// 標準的な初期化処理。
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたければ
	// 以下の特定の初期化ルーチンの中から不必要なものを削除してください。


	Enable3dControls();

	LoadStdProfileSettings();  // 標準 INI ファイルをロードします。(MRU を含む)

	// アプリケーション用のドキュメント テンプレートを登録します。
	// ドキュメント テンプレートはドキュメント、フレーム ウィンドウと
	// ビューを結合するために機能します。

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DRAWTYPE,
		RUNTIME_CLASS(CDrawDoc),
		RUNTIME_CLASS(CMDIChildWnd),          // 標準 MDI 子フレーム。
		RUNTIME_CLASS(CDrawView));
	AddDocTemplate(pDocTemplate);

	// メイン MDI フレーム ウィンドウを作成。
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes();

	// 簡単なコマンド ラインの分解。
	if (m_lpCmdLine[0] == '\0')
	{
		// 新規に空のドキュメントを作成。
		OnFileNew();
	}
	else
	{
		// 既存のドキュメントを開きます。
		OpenDocumentFile(m_lpCmdLine);
	}

	// ドラッグ/ドロップ オープンを使用可能にします。
	m_pMainWnd->DragAcceptFiles();

	// メイン ウィンドウが初期化されたので表示と更新を行います。
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// インプリメンテーション
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート。
	//{{AFX_MSG(CAboutDlg)
		// メッセージハンドラがありません。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// メッセージハンドラがありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ダイアログを実行するためのアプリケーション コマンド
void CDrawApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDrawApp コマンド
