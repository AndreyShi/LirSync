#include "CLirSync.h"

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL CMainWnd::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(240, 240, 240));
	return TRUE;
}

CMainWnd::CMainWnd(){
	Create(NULL,L"CMainWnd def ctor", WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL);	// Создать окно программы
}

CMainWnd::CMainWnd(LPCTSTR WndName,int x, int y) {

	Create(NULL, WndName, WS_OVERLAPPEDWINDOW,CRect(x,y,x + 320,y + 300), NULL, NULL);	// Создать окно программы
	txt = new CStatic();
	txt->Create(L"Текст", WS_CHILD | WS_VISIBLE, CRect(20, 20, 100, 40), this);
}

CMainWnd::~CMainWnd(){
	delete txt;
}

CLirSync::CLirSync() // конструктор главного класса приложения
{
	
}

BOOL CLirSync::InitInstance() // стандартная инициализация
{
	m_pMainWnd = new CMainWnd(this->m_pszAppName,600,400);	// создать класс окна
	ASSERT(m_pMainWnd);	// проверить его правильность
	m_pMainWnd->ShowWindow(SW_SHOW);// Показать окно
	m_pMainWnd->UpdateWindow();	// Обновить окно
	return TRUE;		// Вернуть что все нормально
};