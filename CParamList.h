#pragma once

#include "afxwin.h" // MFC нЯМНБМШЕ Х ЯРЮМДЮПРМШЕ ЙНЛОНМЕМРШ
#include "afxcmn.h"
#include "CEeprom.h"
#include <string.h>

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
	int cnt_clm; //РЕЙСЫЕЕ ЙНК БН ЙНКНМНЙ
public:
	CEeprom data;
	int ch;

	void CreateHead(Column obj,...);
	void InsertItems(LPCTSTR item0, ...);
	void show_P(char P, char type, int x, int y, char align);

	void Enable();
	void Clear();
	void Disable();

	//"оскэр - няэ(PA)"
	void init_PA();
	void click_PA(int str);
	void upd_PA();
	void change_axis_name(const int ch);
	int incdec_axis(const char dir, signed char axis);
	//

	//"нях - щйпюм"
	void init_DA();
	void click_DA();
	void upd_DA();
	//

	//оюпюлерпш нях
	void init_PR();
	void click_PR();
	void upd_PR();
	//

	//лемч "наыхе тсмйжхх бунднб FINGE"
	void init_FINGE();
	void upd_FINGE();
	//

	//лемч "бундш сопюбкемхъ ьохмдекел SINGE"
	void init_SINGE();
	void upd_SINGE();
	//

	//лемч "M-тсмйжхх бунднб MINGE"
	void init_MINGE();
	void upd_MINGE();
	//

	//лемч "наыхе тсмйжхх бшунднб FOUTGE"
	void init_FOUTGE();
	//

	//лемч "бшундш сопюбкемхъ ьохмдекел SOUTGE"
	void init_SOUTGE();
	//

	//лемч "M-тсмйжхх бшунднб MOUTGE"
	void init_MOUTGE();
	//

	//лемч "бме дносяйю VNEDK"
	void init_VNEDK();
	//
};