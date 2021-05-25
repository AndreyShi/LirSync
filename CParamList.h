#pragma once

#include "afxwin.h" // MFC ќсновные и стандартные компоненты
#include "afxcmn.h"
#include "CEeprom.h"

class CParamList : public CListCtrl {
public:
	CEeprom data;

	void CreateHead(LPCTSTR Colname0, int sz0, LPCTSTR Colname1);
	void InsertItems(LPCTSTR item0, ...);

	void Enable();
	void Clear();
	void Disable();

	//"ѕ”Ћ№“ - ќ—№(PA)"
	void init_PA();
	void click_PA(int str);
	void upd_PA();
	void change_axis_name(const int ch);
	int incdec_axis(const char dir, signed char axis);
	//
};