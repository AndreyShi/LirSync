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

void CEditorWnd::OnClickedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEWW pNMA = (LPNMTREEVIEWW)pNMHDR;
	CString str = tree.GetItemText(pNMA->itemNew.hItem);

	if (str == L"Оси - Измерительные каналы") {
		list.init_PA();					
	}
	else {
		if (list.IsWindowEnabled() == TRUE) {
			list.Clear();			
			list.Disable();
		}
		
		ASSERT(list.GetItemCount() == 0);
	}

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
		if (str == L"Оси - Измерительные каналы") {
			list.click_PA(hti.iItem);
		}
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
	tree.InsertItem(L"Канал P2.0", it2);			// добавить элемент
	tree.InsertItem(L"Канал P2.1", it2);
	tree.InsertItem(L"Канал P2.2", it2);
	tree.InsertItem(L"Канал P2.3", it2);
}
//===========================================================================================================================
   
   
   
//========================================================CParamList=========================================================
/*
* LPCTSTR Colname0 - имя колонки0
* int sz0 - размер колонки0
* LPCTSTR Colname1 - имя колонки1
*/
void CParamList::CreateHead(LPCTSTR Colname0, int sz0, LPCTSTR Colname1)
{
	CRect rect;
	GetClientRect(rect);
	SetExtendedStyle(LVS_EX_GRIDLINES);
	InsertColumn(0, Colname0, LVCFMT_LEFT, sz0);
	InsertColumn(1, Colname1, LVCFMT_LEFT, rect.Width() - sz0);
}

void CParamList::InsertItems(LPCTSTR item0, ...)
{
	LPCTSTR* pp = &item0;
	int cnt = 0;
	while (*pp != nullptr) {
		InsertItem(cnt, *pp);
		pp++;
		cnt++;
	}
}

void CParamList::init_PA()
{
	Enable();
	CreateHead(L"ПУЛЬТ - ОСЬ", 100, L"");
	InsertItems(_T("P2.0"),
		_T("P2.1"),
		_T("P2.2"),
		_T("P2.3"),
		_T("P2"),
		nullptr);

	upd_PA();
}

void CParamList::click_PA(int str)
{
	data.P2[str]++;
	if (data.P2[str] > 13)
		data.P2[str] = 0;

	SetItemText(str, 1, data.sAxis_symbol[data.P2[str]]);//upd_PA(data);
}

void CParamList::upd_PA()
{
	SetItemText(0, 1, data.sAxis_symbol[data.P2[0]]);
	SetItemText(1, 1, data.sAxis_symbol[data.P2[1]]);
	SetItemText(2, 1, data.sAxis_symbol[data.P2[2]]);
	SetItemText(3, 1, data.sAxis_symbol[data.P2[3]]);
	SetItemText(4, 1, data.sAxis_symbol_sw[data.P2[4]]);
}

void CParamList::Enable()
{
	EnableWindow(TRUE);
}

void CParamList::Clear()
{
	DeleteColumn(0);
	DeleteColumn(1);
	DeleteColumn(2);
	DeleteAllItems();
}

void CParamList::Disable()
{
	EnableWindow(FALSE);
}
//===========================================================================================================================