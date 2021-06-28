#include "CParamList.h"


void CParamList::CreateHead(Column obj0,...)
{
	SetExtendedStyle(LVS_EX_GRIDLINES);
	Column* pp = &obj0;
	cnt_clm = 0;
	while (pp->Colname != nullptr) {
		InsertColumn(cnt_clm, pp->Colname, LVCFMT_CENTER , pp->sz);
		pp++;
		cnt_clm++;
	}
}

void CParamList::InsertItems(LPCTSTR item0, ...)
{
	LPCTSTR* pp = &item0;
	int cnt = 0;
	while (*pp != nullptr) {
		InsertItem(cnt, *pp);
		pp++;
		cnt++;
	}
}

void CParamList::Enable()
{
	EnableWindow(TRUE);
}
/*
* удаление столбцов
* int cnt_clmn - кол во столбцов для удаления
*/
void CParamList::Clear()
{	
	while (cnt_clm) {
		DeleteColumn(0);
		cnt_clm--;
	}
	if (GetItemCount()) {
		DeleteAllItems();
		ASSERT(GetItemCount() == 0);
	}	
}

void CParamList::Disable()
{
	EnableWindow(FALSE);
}

void CParamList::init_PA()
{
	Enable();
	CreateHead(Column(L"       ПУЛЬТ", 100), Column(L"ОСЬ", 100),nullptr);
	InsertItems(_T("        P2.0"), _T("        P2.1"), _T("        P2.2"), _T("        P2.3"), _T("        P2"),nullptr);
	upd_PA();
}

void CParamList::click_PA(int str)
{
	return;
	if (str >= 0 && str < N_AXIS + N_SA) {
		change_axis_name(str);
		//UpdateTypeAxis(str);
		//UpdateFormatAxis2(str);
	}
	if(str == 4)
		SetItemText(str, 1, data.sAxis_symbol_sw[data.P2[str]]);
	else
		SetItemText(str, 1, data.sAxis_symbol[data.P2[str]]);//upd_PA(data);
}

void CParamList::upd_PA()
{
	SetItemText(0, 1, data.sAxis_symbol[data.P2[0]]);
	SetItemText(1, 1, data.sAxis_symbol[data.P2[1]]);
	SetItemText(2, 1, data.sAxis_symbol[data.P2[2]]);
	SetItemText(3, 1, data.sAxis_symbol[data.P2[3]]);
	SetItemText(4, 1, data.sAxis_symbol_sw[data.P2[4]]);
}

void CParamList::change_axis_name(const int ch)
{
	if (ch >= N_AXIS + N_SA)
		return;

	data.P2[ch] = incdec_axis(1, data.P2[ch]);
	if (data.P2[ch] == CInit::NO_AXIS)
		return;

	for (int c = 0; c < N_AXIS + N_SA; c++) {
		if (ch == c)
			continue;
		if (data.P2[ch] == data.P2[c]) {
			data.P2[ch] = incdec_axis(1, data.P2[ch]);
			if (data.P2[ch] == CInit::NO_AXIS)
				return;
			else
				c = -1;
		}
	}
}

int CParamList::incdec_axis(const char dir, signed char axis)
{
	if (dir)
	{
		if (axis >= CInit::NO_AXIS)
			axis = CInit::AXIS_X;
		else
			axis++;
	}
	else {
		if (axis <= CInit::AXIS_X)
			axis = CInit::NO_AXIS;
		else
			axis--;
	}
	return axis;
}

void CParamList::init_DA()
{
	Enable();
	CreateHead(Column(L"СТРОКА ИНДИКАЦИИ", 145), Column(L"", 90), Column(L"", 90),nullptr);
	InsertItems(_T("              1"), _T("              2"), _T("              3"), _T("              4"), nullptr);
	upd_DA();
}

void CParamList::click_DA()
{

}

void CParamList::upd_DA()
{
	SetItemText(0, 1, data.sAxis_screen[data.Str[0]]);
	SetItemText(1, 1, data.sAxis_screen[data.Str[1]]);
	SetItemText(2, 1, data.sAxis_screen[data.Str[2]]);
	SetItemText(3, 1, data.sAxis_screen[data.Str[3]]);

	SetItemText(0, 2, data.sPosition_to_see[data.position_to_see[0]]);
	SetItemText(1, 2, data.sPosition_to_see[data.position_to_see[1]]);
	SetItemText(2, 2, data.sPosition_to_see[data.position_to_see[2]]);
	SetItemText(3, 2, data.sPosition_to_see[data.position_to_see[3]]);

}

void CParamList::init_PR()
{
	Enable();
	CString head;
	wchar_t axis = data.sAxis_screen[data.P2[ch]][2];
	head.Format(L"ПАРАМЕТРЫ ОСИ %c P2.%d", axis, ch);
	CreateHead(Column(head, 190), Column(L"", 150),nullptr);
	InsertItems(_T("Формат"), _T("Токарный режим"), _T("Направление"), _T("Коэффициент"),
		_T("Люфт"), _T("Контроль датчика"), _T("Сохранение счетчиков"), _T("Отображение скорости"),
		_T("Зона референтной метки"), _T("Внешнее обнуление"), _T("Интервал измер.скорости"),
		_T("Коррекция"), _T("Кодированные метки"), nullptr);
	upd_PR();
}

void CParamList::click_PR()
{
}

void CParamList::upd_PR()
{
}



