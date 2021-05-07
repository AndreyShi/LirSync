﻿
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
#include "CEeprom.h"

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
	CMainWnd();
	~CMainWnd();
	CMainWnd(LPCTSTR WndName, int x, int y);
	CMainWnd(int res_id, LPCTSTR WndName);

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
	CEditorWnd(CWnd* parent);
	~CEditorWnd();

	afx_msg void OnClickedOpen();	
	afx_msg void OnClickedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedList(NMHDR* pNMHDR, LRESULT* pResult);
protected:
	DECLARE_MESSAGE_MAP();
	virtual void OnCancel();
private:
	CTreeCtrl tree;
	CListCtrl list;
	CEeprom data;

	void InitTree();
	void InitList();
};






