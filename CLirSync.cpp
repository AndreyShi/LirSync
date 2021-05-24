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
		data.load(fileDialog.GetPathName());
	}
}

void CEditorWnd::OnClickedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEWW pNMA = (LPNMTREEVIEWW)pNMHDR;
	CString str = tree.GetItemText(pNMA->itemNew.hItem);

	if (str == L"Оси - Измерительные каналы") {
		list.Enable();
		list.CreateHead(L"ПУЛЬТ - ОСЬ",100,L"");
		list.InsertItems(_T("P2.0"),
						 _T("P2.1"),
						 _T("P2.2"),
						 _T("P2.3"),
						 _T("P2"),
						  nullptr);
		list.upd_data_pa(data);	
		SetTimer(IDT_TIMER, 1, [](HWND hwnd, UINT u, UINT_PTR ptr, DWORD dword) {
			::KillTimer(hwnd,IDT_TIMER);
			::SetFocus(::GetDlgItem(hwnd, IDC_LIST_param));
			});
	}
	else {
		if (list.IsWindowEnabled() == TRUE) {
			list.DeleteColumn(0);
			list.DeleteColumn(1);
			list.DeleteColumn(2);
			list.DeleteAllItems();
			list.Disable();
		}
		
		ASSERT(list.GetItemCount() == 0);
	}
	//AfxMessageBox(tmp);

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
	if (str == L"Оси - Измерительные каналы") {
		if (hti.iSubItem == 1 && hti.iItem >= 0) {
			data.P2[hti.iItem]++;
			if (data.P2[hti.iItem] > 13)
				data.P2[hti.iItem] = 0;
			list.upd_data_pa(data);
		}
	}		

	*pResult = 0;
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

void CParamList::upd_data_pa(CEeprom& data)
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

void CParamList::Disable()
{
	EnableWindow(FALSE);
}
//===========================================================================================================================