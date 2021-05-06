#pragma once

#include "afxwin.h" // MFC Основные и стандартные компоненты
#include "afxcmn.h"
#include "resource.h"

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
	CStatic* txt;
	CTabCtrl* tab;
	CEditorWnd* ewnd;
};

class CEditorWnd : public CDialog {
public:
	CEditorWnd(CWnd* parent);
	~CEditorWnd();
protected:
	DECLARE_MESSAGE_MAP();
	virtual void OnCancel();
private:
	CTreeCtrl* tree;
	CLinkCtrl* list;
};





