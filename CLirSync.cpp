#include "CLirSync.h"

CLirSync theApp;	// запуск приложения

//=================================================CLirSync==================================================================
CLirSync::CLirSync() // конструктор главного класса приложения
{

}

BOOL CLirSync::InitInstance() // стандартная инициализация
{
	SetRegistryKey(_T("SKBIS"));
	m_pMainWnd = new CMainWnd(IDD_MainDlg, this->m_pszAppName);	// создать класс окна
	ASSERT(m_pMainWnd);	// проверить его правильность
	//m_pMainWnd->ShowWindow(SW_SHOW);// Показать окно
	//m_pMainWnd->UpdateWindow();	// Обновить окно
	//((CDialog*)m_pMainWnd)->Create(IDD_MainDlg, NULL);
	//((CDialog*)m_pMainWnd)->ShowWindow(SW_SHOW);
	return TRUE;		// Вернуть что все нормально
};
//===========================================================================================================================


//=================================================CMainWnd==================================================================
BEGIN_MESSAGE_MAP(CMainWnd, CDialog)
	//ON_WM_ERASEBKGND()
	ON_WM_DEVICECHANGE()
	ON_BN_CLICKED(IDM_Editor, &CMainWnd::OnMenuClickedEditor)
END_MESSAGE_MAP()

CMainWnd::CMainWnd() {
	//Create(NULL,L"CMainWnd def ctor", WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL);	// Создать окно программы
}

CMainWnd::CMainWnd(LPCTSTR WndName, int x, int y) {

	//Create(NULL, WndName, WS_OVERLAPPEDWINDOW,CRect(x,y,x + 320,y + 300), NULL, NULL);	// Создать окно программы
	this->txt = new CStatic();
	this->txt->Create(L"Текст", WS_CHILD | WS_VISIBLE, CRect(20, 20, 100, 40), this);
}

CMainWnd::CMainWnd(int res_id, LPCTSTR WndName)
{
	this->Create(res_id, NULL);
	this->ShowWindow(SW_SHOW);
	this->SetWindowTextW(WndName);

	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);  установка иконки
}

CMainWnd::~CMainWnd() {
	delete ewnd;
}

BOOL CMainWnd::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(240, 240, 240));
	return FALSE; 
}

void CMainWnd::OnCancel()
{
	//CWinApp* app = AfxGetApp();
	//app->WriteProfileInt(L"Controls", L"COMName", 777);
	this->DestroyWindow();
	delete this;
}

void CMainWnd::OnMenuClickedEditor()
{
	ewnd = new CEditorWnd(this);
}

//===========================================================================================================================



//========================================================CEditorWnd=========================================================
BEGIN_MESSAGE_MAP(CEditorWnd, CDialog)
END_MESSAGE_MAP()
CEditorWnd::CEditorWnd(CWnd* parent)
{
	this->Create(IDD_EditorDlg,parent);
	this->ShowWindow(SW_SHOW);
}

CEditorWnd::~CEditorWnd()
{
	delete ep;
}

void CEditorWnd::OnCancel()
{	
	this->DestroyWindow();
}
//===========================================================================================================================