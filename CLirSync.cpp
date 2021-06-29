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
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_MOUSEHOVER()
	ON_BN_CLICKED(IDC_Btn_Editor_Open, &CEditorWnd::OnClickedOpen)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_param, &CEditorWnd::OnClickedTree)
	//ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE_param, &CEditorWnd::OnClickedTree)
	ON_NOTIFY(TVN_SELCHANGING,IDC_TREE_param, &CEditorWnd::OnClickingTree)
	ON_NOTIFY(NM_CLICK, IDC_LIST_param, &CEditorWnd::OnClickedList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_param, &CEditorWnd::OnClickedList)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_param, &CEditorWnd::OnNMCustomdrawList)
END_MESSAGE_MAP()

CEditorWnd::CEditorWnd(int res_id,CWnd* parent, LPCTSTR WndName)
{
	this->Create(res_id,parent);
	this->ShowWindow(SW_SHOW);
	if(WndName != NULL)
		this->SetWindowTextW(WndName);
	tree.Attach(this->GetDlgItem(IDC_TREE_param)->GetSafeHwnd());
	list.Attach(this->GetDlgItem(IDC_LIST_param)->GetSafeHwnd());
	btn_open.Attach(this->GetDlgItem(IDC_Btn_Editor_Open)->GetSafeHwnd());
	InitTree();	
	list.Disable();

	LOGFONT lf;

	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 14;
	wcscpy_s(lf.lfFaceName, 32, _T("Verdana"));
	lf.lfWeight = FW_MEDIUM;
	
	f_list.CreateFontIndirectW(&lf);
	list.SetFont(&f_list, true);


	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = -12;
	wcscpy_s(lf.lfFaceName, 28, _T("Verdana"));
	lf.lfWeight = FW_NORMAL;
	lf.lfItalic = TRUE;
	f_list_param.CreateFontIndirectW(&lf);


	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = -12;
	wcscpy_s(lf.lfFaceName, 32, _T("Verdana"));
	lf.lfWeight = FW_NORMAL; 
	f_tree.CreateFontIndirectW(&lf);
	tree.SetFont(&f_tree, true);

	RECT t_r;
	memset(&t_r, 0, sizeof(t_r));
	if (GetSafeHwnd() == NULL)
		return;
	GetWindowRect(&t_r);

	l_w = t_r.right - t_r.left;
	h_w = t_r.bottom - t_r.top;
	l_m = l_w;
	h_m = h_w;

	r_p.left = 11;
	r_p.top = 11;
	r_p.right = 310;
	r_p.bottom = 226;

	l_t = r_p.right - r_p.left;
	h_t = r_p.bottom - r_p.top;

}

CEditorWnd::~CEditorWnd()
{
	
}

void CEditorWnd::OnMouseHover(UINT uint, CPoint cpoint)
{
	AfxMessageBox(L" ");  //state 98 - раскрыли меню
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

	if (str == L"Оси - Измерительные каналы") {
		list.init_PA();
	}		
	else if (str == L"Оси - экран") {
		list.init_DA();
	}		
	else if (str == L"Параметры осей") {
		;// AfxMessageBox(str);  //state 98 - раскрыли меню
	}
	else if (str == L"Отображение") {
		init_ch(pNMA->itemNew.hItem);
		list.init_PR();
	}
	else if (str == L"Общие функции") {
		if (IO_MainF(pNMA->itemNew.hItem))
			list.init_FINGE();
		else
			list.init_FOUTGE();
	}
	else if (str == L"Шпиндель") {
		if (IO_MainF(pNMA->itemNew.hItem))
			list.init_SINGE();
		else
			list.init_SOUTGE();
	}
	else if (str == L"М-функции входов"){
		list.init_MINGE();
	}		
	else if (str == L"М-функции выходов") {
		list.init_MOUTGE();
	}		
	else if (str == L"Вне допуска") {
		list.init_VNEDK();
	}
	
	*pResult = 0;
}
/*
* Переключения между таблицами ,очищаем поле
*/
void CEditorWnd::OnClickingTree(NMHDR* pNMHDR, LRESULT* pResult)
{	
	list.Clear();
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
	}			

	*pResult = 0;
}

void CEditorWnd::OnNMCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	*pResult = CDRF_DODEFAULT;

	switch (pNMCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;

	case CDDS_ITEMPREPAINT:
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		break;

	case (CDDS_SUBITEM | CDDS_ITEMPREPAINT):
		if (pNMCD->iSubItem == 1) {
			m_oldObj = SelectObject(pNMCD->nmcd.hdc, f_list_param);
			//pNMCD->clrTextBk = GetSysColor(COLOR_BTNFACE);
		}
		//else {
		//	m_oldObj = SelectObject(pNMCD->nmcd.hdc, m_oldObj);
		//}
		break;
	default:
		*pResult = CDRF_DODEFAULT;
	}
}
/*
* установка фокуса на List (что бы не было доп щелчка мышью для установки фокуса)
*/
void CEditorWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd* wn = GetFocus();
	if (wn != &list) {
		if (list.IsWindowEnabled()) {
			;// list.SetFocus();
		}		
	}
}

void CEditorWnd::OnSize(UINT uint, int ix, int iy)
{
	return;
	//AfxMessageBox(L"OnSize");
	RECT t_r;
	memset(&t_r, 0, sizeof(t_r));
	if (tree.GetSafeHwnd() == NULL)
		return;
	tree.GetWindowRect(&t_r);
	//t_r.right += 30;
	//t_r.bottom += 30;
	//tree.MoveWindow(&t_r,1); 
	//tree.SetWindowPos();
}

void CEditorWnd::OnSizing(UINT uint, LPRECT rect)
{
	return;
	CRect r_p;
	long l; // длина
	long h; // высота
	long l_t_;
	long h_t_;
	

	if (tree.GetSafeHwnd() == NULL)
		return;
	tree.GetWindowRect(&r_p);

	l = rect->right - rect->left;
	h = rect->bottom - rect->top;

	l_t_ = r_p.Width();
	h_t_ = r_p.Height();

	long delta = l - l_m;

	if (l_t_ >= 299 && l_t_ <= 350) {
		l_t_ += delta;
		if (l_t_ > 350)
			l_t_ = 350;
		if (l_t_ < 299)
			l_t_ = 299;
	}

	if (h_t_ >= 215 ) {
		h_t_ += h - h_m;
	}

	tree.MoveWindow(11, 11, l_t_, h_t_, TRUE);

		

	if (btn_open.GetSafeHwnd() == NULL)
		return;

	btn_open.GetWindowRect(&r_p);
	static long y_btn = 325;
	y_btn += h - h_m;
	btn_open.MoveWindow(11, y_btn, r_p.Width(), r_p.Height(), TRUE);


	if (list.GetSafeHwnd() == NULL)
		return;
	list.GetWindowRect(&r_p);
	static long x_list = 342;
	//if(l_t_ < 350 )
	x_list += l - l_m;
	list.MoveWindow(x_list, 11, r_p.Width(), r_p.Height() + (h - h_m), TRUE);


	l_m = l;
	h_m = h;
}

void CEditorWnd::OnGetMinMaxInfo(MINMAXINFO* p)
{
	p->ptMinTrackSize.x = 687;
	p->ptMinTrackSize.y = 398;

	//p->ptMaxTrackSize.x = 887;
	//p->ptMaxTrackSize.y = 598;
}

void CEditorWnd::OnCancel()
{	
	list.Detach();
	tree.Detach();
	this->DestroyWindow();
}
/*
* функция определяет текущий номер канала
*/
void CEditorWnd::init_ch(HTREEITEM it)
{
	HTREEITEM root = tree.GetParentItem(it);
	CString tmp = tree.GetItemText(root);  
	tmp = tmp.Right(1);
	list.ch = _ttoi(tmp);//получаем номер канала
}
/*
* функция определяет родительское меню входы или выходы
*/
bool CEditorWnd::IO_MainF(HTREEITEM it)
{
	HTREEITEM root = tree.GetParentItem(it);
	CString tmp = tree.GetItemText(root);
	if (tmp == L"Конфигурация входов")
		return true;
	else if (tmp == L"Конфигурация выходов")
		return false;
	return false;//если что пойдет не так будет как выходы)
}

void CEditorWnd::InitTree()
{	
	HTREEITEM  it1 = tree.InsertItem(L"Общие параметры");		// структура элемента дерево
	tree.InsertItem(L"Оси - Измерительные каналы", it1);			
	tree.InsertItem(L"Оси - экран", it1);			
	HTREEITEM  it1_sub = tree.InsertItem(L"Конфигурация входов", it1);
		tree.InsertItem(L"Общие функции", it1_sub);
		tree.InsertItem(L"Шпиндель", it1_sub);
		tree.InsertItem(L"М-функции входов", it1_sub);

	it1_sub = tree.InsertItem(L"Конфигурация выходов", it1);
		tree.InsertItem(L"Общие функции", it1_sub);
		tree.InsertItem(L"Шпиндель", it1_sub);
		tree.InsertItem(L"М-функции выходов", it1_sub);

	tree.InsertItem(L"Вне допуска", it1);
	HTREEITEM it2 = tree.InsertItem(L"Параметры осей");		// структура элемента дерево	
	HTREEITEM it2_sub;
	it2_sub = tree.InsertItem(L"Канал P2.0", it2);
	addBranch_CHPA(it2_sub);
	it2_sub = tree.InsertItem(L"Канал P2.1", it2);
	addBranch_CHPA(it2_sub);
	it2_sub = tree.InsertItem(L"Канал P2.2", it2);
	addBranch_CHPA(it2_sub);
	it2_sub = tree.InsertItem(L"Канал P2.3", it2);
	addBranch_CHPA(it2_sub);
	it2_sub = tree.InsertItem(L"Канал P2  ", it2);
	addBranch_CHPA(it2_sub);
	tree.InsertItem(L"Смещения координат");	// структура элемента дерево
	tree.InsertItem(L"Таблица инструментов");	// структура элемента дерево
	tree.InsertItem(L"Настройки");	// структура элемента дерево
	
	
}
void CEditorWnd::addBranch_CHPA(HTREEITEM it)
{
	tree.InsertItem(L"Отображение", it);
	tree.InsertItem(L"Управление", it);
	tree.InsertItem(L"Конфигурация входов", it);
	tree.InsertItem(L"Конфигурация выходов", it);
	tree.InsertItem(L"Зоны торможения", it);
	tree.InsertItem(L"Зоны скорости", it);
}
//===========================================================================================================================
   
   
   
