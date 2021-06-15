#include "CLirSync.h"

CLirSync theApp;	// запуск приложения

//=================================================CLirSync==================================================================
CLirSync::CLirSync() // конструктор главного класса приложения
{

}

BOOL CLirSync::InitInstance() // стандартная инициализация
{
	SetRegistryKey(_T("SKBIS"));
	//m_pMainWnd = new CMainWnd(IDD_MainDlg,NULL, this->m_pszAppName);
	m_pMainWnd = new CEditorWnd(IDD_EditorDlg, NULL,NULL);
	ASSERT(m_pMainWnd);	// проверить его правильность
	return TRUE;		// Вернуть что все нормально
};
//===========================================================================================================================


//=================================================CMainWnd==================================================================
BEGIN_MESSAGE_MAP(CMainWnd, CDialog)
	//ON_WM_ERASEBKGND()
	ON_WM_DEVICECHANGE()
	ON_BN_CLICKED(IDM_Editor, &CMainWnd::OnMenuClickedEditor)
END_MESSAGE_MAP()

CMainWnd::CMainWnd(int res_id, CWnd* parent, LPCTSTR WndName)
{
	this->Create(res_id, parent);
	this->ShowWindow(SW_SHOW);
	if(WndName != NULL)
		this->SetWindowTextW(WndName);

	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);  установка иконки
}

CMainWnd::~CMainWnd() {
	delete EWindow;
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
	EWindow = new CEditorWnd(IDD_EditorDlg,this,NULL);
}

//===========================================================================================================================



//========================================================CEditorWnd=========================================================
BEGIN_MESSAGE_MAP(CEditorWnd, CDialog)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_Btn_Editor_Open, &CEditorWnd::OnClickedOpen)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_param, &CEditorWnd::OnClickedTree)
	ON_NOTIFY(TVN_SELCHANGING,IDC_TREE_param, &CEditorWnd::OnClickingTree)
	ON_NOTIFY(NM_CLICK, IDC_LIST_param, &CEditorWnd::OnClickedList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_param, &CEditorWnd::OnClickedList)
END_MESSAGE_MAP()

CEditorWnd::CEditorWnd(int res_id,CWnd* parent, LPCTSTR WndName)
{
	this->Create(res_id,parent);
	this->ShowWindow(SW_SHOW);
	if(WndName != NULL)
		this->SetWindowTextW(WndName);
	tree.Attach(this->GetDlgItem(IDC_TREE_param)->GetSafeHwnd());
	list.Attach(this->GetDlgItem(IDC_LIST_param)->GetSafeHwnd());
	InitTree();	
	list.Disable();
}

CEditorWnd::~CEditorWnd()
{
	
}

void CEditorWnd::OnClickedOpen()
{
	CFileDialog fileDialog(TRUE, NULL, L"*.lireep");	//объект класса выбора файла
	int result = fileDialog.DoModal();	//запустить диалоговое окно
	if (result == IDOK)	//если файл выбран
	{
		list.data.load(fileDialog.GetPathName());
	}
}
/*
* Инициализация таблицы
*/
void CEditorWnd::OnClickedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEWW pNMA = (LPNMTREEVIEWW)pNMHDR;
	CString str = tree.GetItemText(pNMA->itemNew.hItem);

	if (str == L"Оси - Измерительные каналы")
		list.init_PA();					
	else if(str == L"Оси - экран")
		list.init_DA();

	*pResult = 0;
}
/*
* Переключения между таблицами ,очищаем поле
*/
void CEditorWnd::OnClickingTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	if(list.GetItemCount())
		list.Clear(3);
	ASSERT(list.GetItemCount() == 0);
	*pResult = 0;
}

void CEditorWnd::OnClickedList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMA = (LPNMITEMACTIVATE)pNMHDR;
	LVHITTESTINFO hti;
	CString str;
	hti.pt = pNMA->ptAction;
	list.SubItemHitTest(&hti);
	HTREEITEM tr = tree.GetSelectedItem();
	str = tree.GetItemText(tr);

	//str.Format(L"Столбец: %d   Строка: %d", hti.iSubItem, hti.iItem);
	//AfxMessageBox(str);	
	if (hti.iSubItem == 1 && hti.iItem >= 0) {
		if (str == L"Оси - Измерительные каналы")
			list.click_PA(hti.iItem);
		else if (str == L"Оси - экран")
			;
	}			

	*pResult = 0;
}
/*
* установка фокуса на List (что бы не было доп щелчка мышью для установки фокуса)
*/
void CEditorWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd* wn = GetFocus();
	if (wn != &list) {
		if (list.IsWindowEnabled()) {
			list.SetFocus();
		}		
	}
}

void CEditorWnd::OnCancel()
{	
	list.Detach();
	tree.Detach();
	this->DestroyWindow();
}

void CEditorWnd::InitTree()
{	
	HTREEITEM  it1 = tree.InsertItem(L"Общие параметры");		// структура элемента дерево
	HTREEITEM  it2 = tree.InsertItem(L"Параметры осей");		// структура элемента дерево	
	HTREEITEM  it3 = tree.InsertItem(L"Смещения координат");	// структура элемента дерево
	tree.InsertItem(L"Оси - Измерительные каналы", it1);			// добавить элемент	
	tree.InsertItem(L"Оси - экран", it1);			// добавить элемент	
	tree.InsertItem(L"Канал P2.0", it2);			// добавить элемент
	tree.InsertItem(L"Канал P2.1", it2);
	tree.InsertItem(L"Канал P2.2", it2);
	tree.InsertItem(L"Канал P2.3", it2);
}
//===========================================================================================================================
   
   
   
