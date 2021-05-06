#pragma once
#include "afxwin.h" // MFC Основные и стандартные компоненты

class CMainWnd : public CFrameWnd
{
public:
	CMainWnd();
	~CMainWnd();
	CMainWnd(LPCTSTR WndName, int x, int y);
protected:
	DECLARE_MESSAGE_MAP();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
private:
	CStatic* txt;
};

class CLirSync : public CWinApp
{
public:
	CLirSync();			//конструктор по умолчанию
	virtual BOOL InitInstance();//стандартная инициализация
};