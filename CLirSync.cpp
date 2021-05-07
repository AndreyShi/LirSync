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
}

CMainWnd::CMainWnd(int res_id, LPCTSTR WndName)
{
	this->Create(res_id, NULL);
	this->ShowWindow(SW_SHOW);
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
	EWindow = new CEditorWnd(this);
}

//===========================================================================================================================



//========================================================CEditorWnd=========================================================
BEGIN_MESSAGE_MAP(CEditorWnd, CDialog)
	ON_BN_CLICKED(IDC_Btn_Editor_Open, &CEditorWnd::OnClickedOpen)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_param, &CEditorWnd::OnClickedTree)
	ON_NOTIFY(NM_CLICK, IDC_LIST_param, &CEditorWnd::OnClickedList)
END_MESSAGE_MAP()

CEditorWnd::CEditorWnd(CWnd* parent)
{
	this->Create(IDD_EditorDlg,parent);
	this->ShowWindow(SW_SHOW);
	tree.Attach(this->GetDlgItem(IDC_TREE_param)->GetSafeHwnd());
	list.Attach(this->GetDlgItem(IDC_LIST_param)->GetSafeHwnd());
	InitTree();
	InitList();
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
	CString tmp = tree.GetItemText(pNMA->itemNew.hItem);
	
	if (tmp == L"Оси - Измерительные каналы") {
		AfxMessageBox(tmp);
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

	//if (hti.iSubItem > 0)
	//{
		//int n = hti.iItem * 10 + (hti.iSubItem - 2);
		str.Format(L"Столбец: %d   Строка: %d", hti.iSubItem, hti.iItem);
		AfxMessageBox(str);
	//}
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

void CEditorWnd::InitList()
{
	CRect rect;
	list.SetExtendedStyle(LVS_EX_GRIDLINES);
	list.InsertColumn(0, _T("Параметр"), LVCFMT_LEFT, 100);
	list.InsertColumn(1, _T("Состояние"), LVCFMT_LEFT, 100);
	/*CString strText;
	int nColumnCount = 5;

	// Insert 10 items in the list view control.
	for (int i = 0; i < 10; i++)
	{
		strText.Format(TEXT("item %d"), i);

		// Insert the item, select every other item.
		list.InsertItem(LVIF_TEXT | LVIF_STATE, i, strText,
			(i % 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED, 0, 0);

		// Initialize the text of the subitems.
		for (int j = 1; j < nColumnCount; j++)
		{
			strText.Format(TEXT("sub-item %d %d"), i, j);
			list.SetItemText(i, j, strText);
		}
	} */
}

//===========================================================================================================================