#pragma once

#include "afxwin.h" // MFC �������� � ����������� ����������
#include "afxcmn.h"
#include "CEeprom.h"

class CParamList : public CListCtrl {
public:
	class Column{
	public:
		Column(LPCTSTR Colname_, int sz_) {
			Colname = Colname_;
			sz = sz_;
		}
		LPCTSTR Colname;
		int sz;
	};
	int cnt_clm; //������� ��� �� �������
public:
	CEeprom data;

	void CreateHead(Column obj,...);
	void InsertItems(LPCTSTR item0, ...);

	void Enable();
	void Clear();
	void Disable();

	//"����� - ���(PA)"
	void init_PA();
	void click_PA(int str);
	void upd_PA();
	void change_axis_name(const int ch);
	int incdec_axis(const char dir, signed char axis);
	//

	//"��� - �����"
	void init_DA();
	void click_DA();
	void upd_DA();
	//
};