
#pragma once
//==Visual Styles
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
//==
#include "afxwin.h" // MFC Основные и стандартные компоненты
#include "afxcmn.h"
#include "afxdlgs.h"
#include <stdint.h>
#include <fstream>
#include "resource.h"
#include "CParamList.h"


class CLirSync;
class CMainWnd;
class CEditorWnd;


class CLirSync : public CWinApp
{
public:
	CLirSync();			//конструктор по умолчанию
	virtual BOOL InitInstance();//стандартная инициализация
};

class CMainWnd : public CDialog
{
public:
	CMainWnd(int res_id, CWnd* parent, LPCTSTR WndName);
	~CMainWnd();
	
	afx_msg void OnMenuClickedEditor();
protected:
	DECLARE_MESSAGE_MAP();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnCancel();
private:
	CTabCtrl tab;
	CEditorWnd* EWindow;
};

class CEditorWnd : public CDialog {
public:
	CEditorWnd(int res_id,CWnd* parent, LPCTSTR WndName);
	~CEditorWnd();

	afx_msg void OnMouseHover(UINT uint, CPoint cpoint);
	afx_msg void OnClickedOpen();	
	afx_msg void OnClickedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickingTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT, int, int);
	afx_msg void OnSizing(UINT, LPRECT);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO*p);
protected:
	DECLARE_MESSAGE_MAP();
	virtual void OnCancel();
private:
	CTreeCtrl tree;
	CParamList list;
	CButton btn_open;
	HGDIOBJ m_oldObj;
	CFont f_tree;
	CFont f_list;
	CFont f_list_param;

	void init_ch(HTREEITEM it);
	bool IO_MainF(HTREEITEM it);

	long l_w; //длина окна
	long h_w; //высота окна
	long l_m; // длина
	long h_m; // высота
	RECT r_p; //координаты положения дерева
	long l_t; //длина дерева
	long h_t; //высота дерева
	
	void InitTree();
	void addBranch_CHPA(HTREEITEM it); //МЕНЮ Выбора параметров ЛИР541 CHPA
};






