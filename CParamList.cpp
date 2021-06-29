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
/*
P - байт, состоит из :
Yes/No       Inv      P_or_m    Num
0(0x80)      0(0x40)  0(0x20)   макс 31(0x1F)
*/
void CParamList::show_P(char P, char type, int x, int y, char align)
{
	if (P & YESNO_P_bm) {
		if (align) {
			SetItemText(y, x, L"нет");
		}
		else {
			SetItemText(y, x, L"нет");
		}
	}
	else {
		wchar_t str[8] = { 0 };
		int ptr = 0;
		if (type == IN_P)
			str[ptr++] = L'<'; //'>'
		else if (type == OUT_P)
			str[ptr++] = L'>'; //'<'

		long data = P & DATA_P_bm;
		if (P & P_OR_m_bm) {
			data++;
			str[ptr++] = L'P';
			str[ptr++] = L'1';
			str[ptr++] = L'.';
		}
		else {
			str[ptr++] = L'm';
			if (type == IN_P)
				data += 32;
		}

		_itow_s(data, str + ptr, (sizeof(str)/2) - ptr, 10);

		if (!(P & INVERSE_P_bm))
			 wcscat_s(str, sizeof(str) / 2, L"!");// display.strncatsym_lir(str, sizeof(str), '!');

		if (align) {
			SetItemText(y, x, str);
		}
		else {
			SetItemText(y, x, str);
		}
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

void CParamList::init_FINGE()
{
	Enable();
	CreateHead(Column(L"ОБЩИЕ ФУНКЦИИ ВХОДОВ", 190), Column(L"", 70), nullptr);
	InsertItems(_T("Готовность станка"), _T("Ускоренный ход G0"), _T("Стоп подача"), _T("Смена кадра"),
		_T("Пауза"), _T("Старт программы"), _T("Внешний пульт"), nullptr);
	upd_FINGE();
}

void CParamList::upd_FINGE()
{
	char* p = &data._INGen.gotov_stanok;
	for (int y = 0; y < 7; y++) {
		show_P(*p, IN_P, 1, y, 0);
		p++;
	}
}

void CParamList::init_SINGE()
{
	Enable();
	CreateHead(Column(L"ВХОДЫ УПРАВЛЕНИЯ ШПИНДЕЛЕМ", 240), Column(L"", 70), nullptr);
	InsertItems(_T("По часовой М3"), _T("Против часовой М4"), _T("Стоп М5"), _T("Толчок+"),
		_T("Толчок-"), _T("Шпиндель вращается"), _T("Инструмент зажат"), nullptr);
	upd_SINGE();
}

void CParamList::upd_SINGE()
{
	char* p = &data._INGen.po_chasovoy_M3;
	for (int y = 0; y < 8; y++) {
		show_P(*p, IN_P, 1, y, 0);
		p++;
	}
}

void CParamList::init_MINGE()
{
	Enable();
	CreateHead(Column(L"М-ФУНКЦИИ ВХОДОВ", 190), Column(L"", 70), nullptr);
	InsertItems(_T("М102"), _T("М112"), _T("М122"), _T("М132"),
		_T("М142"), _T("М152"), _T("М162"), _T("М172"), nullptr);
	upd_MINGE();
}

void CParamList::upd_MINGE()
{
	char* p = &data._INGen2.M102;
	for (int y = 0; y < 8; y++) {
		show_P(*p, IN_P, 1, y, 0);
		p++;
	}
}

void CParamList::init_FOUTGE()
{
	Enable();
	CreateHead(Column(L"ОБЩИЕ ФУНКЦИИ ВЫХОДОВ", 200), Column(L"", 70), nullptr);
	InsertItems(_T("Ускоренный ход G0"), _T("Подача G1"), _T("Технол. останов M0"), _T("Конец программы M2"),
		_T("Ручной режим"), _T("Автоматический режим"), _T("Позиционирование"), _T("Готовность УЦИПУ"), nullptr);
}

void CParamList::init_SOUTGE()
{
	Enable();
	CreateHead(Column(L"ВЫХОДЫ УПРАВЛЕНИЯ ШПИНДЕЛЕМ", 250), Column(L"", 70), nullptr);
	InsertItems(_T("По часовой М3"), _T("Против часовой М4"), _T("Стоп М5"), _T("Толчок"),
		_T("М3,М4 через М5"), _T("Время для М5, сек"),nullptr);
}

void CParamList::init_MOUTGE()
{
	Enable();
	CreateHead(Column(L"М-ФУНКЦИИ ВЫХОДОВ", 190), Column(L"", 70), nullptr);
	InsertItems(_T("М100-выкл М101-вкл"), _T("М110-выкл М111-вкл"), _T("М120-выкл М121-вкл"), _T("М130-выкл М131-вкл"),
		_T("М140-выкл М141-вкл"), _T("М150-выкл М151-вкл"), _T("М160-выкл М161-вкл"), _T("М170-выкл М171-вкл"), nullptr);
}

void CParamList::init_VNEDK()
{
	Enable();
	CreateHead(Column(L"", 120), Column(L"", 70), nullptr);
	InsertItems(_T("Вне допуска"), nullptr);
}



