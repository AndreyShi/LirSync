#pragma once

#include "afxwin.h" // MFC �������� � ����������� ����������
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
	int cnt_clm; //������� ��� �� �������
public:
	CEeprom data;
	int ch;

	void CreateHead(Column obj,...);
	void InsertItems(LPCTSTR item0, ...);
	void show_P(char P, char type, int x, int y, char align);

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

	//��������� ���
	void init_PR();
	void click_PR();
	void upd_PR();
	//

	//���� "����� ������� ������ FINGE"
	void init_FINGE();
	void upd_FINGE();
	//

	//���� "����� ���������� ��������� SINGE"
	void init_SINGE();
	void upd_SINGE();
	//

	//���� "M-������� ������ MINGE"
	void init_MINGE();
	void upd_MINGE();
	//

	//���� "����� ������� ������� FOUTGE"
	void init_FOUTGE();
	//

	//���� "������ ���������� ��������� SOUTGE"
	void init_SOUTGE();
	//

	//���� "M-������� ������� MOUTGE"
	void init_MOUTGE();
	//

	//���� "��� ������� VNEDK"
	void init_VNEDK();
	//
};