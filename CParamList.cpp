#include "CParamList.h"

void CParamList::CreateHead(Column obj,...)
{
	SetExtendedStyle(LVS_EX_GRIDLINES);
	Column* pp = &obj;
	int cnt = 0;
	while (pp->Colname != nullptr) {
		InsertColumn(cnt, pp->Colname, LVCFMT_LEFT, pp->sz);
		pp++;
		cnt++;
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
* �������� ��������
* int cnt_clmn - ��� �� �������� ��� ��������
*/
void CParamList::Clear(int cnt_clmn)
{	
	for(int c = 0; c < cnt_clmn;c++)
		DeleteColumn(0);

	DeleteAllItems();
}

void CParamList::Disable()
{
	EnableWindow(FALSE);
}

void CParamList::init_PA()
{
	Enable();
	CreateHead(Column(L"����� - ���", 100), Column(L"", 100),nullptr);
	InsertItems(_T("        P2.0"), _T("        P2.1"), _T("        P2.2"), _T("        P2.3"), _T("        P2"),nullptr);
	upd_PA();
}

void CParamList::click_PA(int str)
{
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
	CreateHead(Column(L"������ ���������", 130),nullptr);
	InsertItems(_T("              1"), _T("              2"), _T("              3"), _T("              4"), nullptr);
	upd_DA();
}

void CParamList::click_DA()
{
}

void CParamList::upd_DA()
{
}


