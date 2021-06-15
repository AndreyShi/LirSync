#pragma once

#include "afxwin.h" // MFC Основные и стандартные компоненты
#include "afxcmn.h"
#include "CEeprom.h"

class CParamList : public CListCtrl {
private:
	class Column {
	public:
		Column(LPCTSTR Colname_, int sz_) {
			Colname = Colname_;
			sz = sz_;
		}
		LPCTSTR Colname;
		int sz;
	};
public:
	CEeprom data;

	void CreateHead(Column obj,...);
	void InsertItems(LPCTSTR item0, ...);

	void Enable();
	void Clear(int cnt_clmn);
	void Disable();

	//"ПУЛЬТ - ОСЬ(PA)"
	void init_PA();
	void click_PA(int str);
	void upd_PA();
	void change_axis_name(const int ch);
	int incdec_axis(const char dir, signed char axis);
	//

	//"ОСИ - ЭКРАН"
	void init_DA();
	void click_DA();
	void upd_DA();
	//
};