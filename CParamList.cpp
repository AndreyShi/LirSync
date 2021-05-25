#include "CParamList.h"

/*
* LPCTSTR Colname0 - ��� �������0
* int sz0 - ������ �������0
* LPCTSTR Colname1 - ��� �������1
*/
void CParamList::CreateHead(LPCTSTR Colname0, int sz0, LPCTSTR Colname1)
{
	CRect rect;
	GetClientRect(rect);
	SetExtendedStyle(LVS_EX_GRIDLINES);
	InsertColumn(0, Colname0, LVCFMT_LEFT, sz0);
	InsertColumn(1, Colname1, LVCFMT_LEFT, rect.Width() - sz0);
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

void CParamList::Clear()
{
	DeleteColumn(0);
	DeleteColumn(1);
	DeleteColumn(2);
	DeleteAllItems();
}

void CParamList::Disable()
{
	EnableWindow(FALSE);
}

void CParamList::init_PA()
{
	Enable();
	CreateHead(L"����� - ���", 100, L"");
	InsertItems(_T("P2.0"),_T("P2.1"),_T("P2.2"),_T("P2.3"),_T("P2"),nullptr);

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



