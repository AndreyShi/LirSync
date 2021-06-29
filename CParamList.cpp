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
P - ����, ������� �� :
Yes/No       Inv      P_or_m    Num
0(0x80)      0(0x40)  0(0x20)   ���� 31(0x1F)
*/
void CParamList::show_P(char P, char type, int x, int y, char align)
{
	if (P & YESNO_P_bm) {
		if (align) {
			SetItemText(y, x, L"���");
		}
		else {
			SetItemText(y, x, L"���");
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
* �������� ��������
* int cnt_clmn - ��� �� �������� ��� ��������
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
	CreateHead(Column(L"       �����", 100), Column(L"���", 100),nullptr);
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
	CreateHead(Column(L"������ ���������", 145), Column(L"", 90), Column(L"", 90),nullptr);
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
	head.Format(L"��������� ��� %c P2.%d", axis, ch);
	CreateHead(Column(head, 190), Column(L"", 150),nullptr);
	InsertItems(_T("������"), _T("�������� �����"), _T("�����������"), _T("�����������"),
		_T("����"), _T("�������� �������"), _T("���������� ���������"), _T("����������� ��������"),
		_T("���� ����������� �����"), _T("������� ���������"), _T("�������� �����.��������"),
		_T("���������"), _T("������������ �����"), nullptr);
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
	CreateHead(Column(L"����� ������� ������", 190), Column(L"", 70), nullptr);
	InsertItems(_T("���������� ������"), _T("���������� ��� G0"), _T("���� ������"), _T("����� �����"),
		_T("�����"), _T("����� ���������"), _T("������� �����"), nullptr);
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
	CreateHead(Column(L"����� ���������� ���������", 240), Column(L"", 70), nullptr);
	InsertItems(_T("�� ������� �3"), _T("������ ������� �4"), _T("���� �5"), _T("������+"),
		_T("������-"), _T("�������� ���������"), _T("���������� �����"), nullptr);
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
	CreateHead(Column(L"�-������� ������", 190), Column(L"", 70), nullptr);
	InsertItems(_T("�102"), _T("�112"), _T("�122"), _T("�132"),
		_T("�142"), _T("�152"), _T("�162"), _T("�172"), nullptr);
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
	CreateHead(Column(L"����� ������� �������", 200), Column(L"", 70), nullptr);
	InsertItems(_T("���������� ��� G0"), _T("������ G1"), _T("������. ������� M0"), _T("����� ��������� M2"),
		_T("������ �����"), _T("�������������� �����"), _T("����������������"), _T("���������� �����"), nullptr);
}

void CParamList::init_SOUTGE()
{
	Enable();
	CreateHead(Column(L"������ ���������� ���������", 250), Column(L"", 70), nullptr);
	InsertItems(_T("�� ������� �3"), _T("������ ������� �4"), _T("���� �5"), _T("������"),
		_T("�3,�4 ����� �5"), _T("����� ��� �5, ���"),nullptr);
}

void CParamList::init_MOUTGE()
{
	Enable();
	CreateHead(Column(L"�-������� �������", 190), Column(L"", 70), nullptr);
	InsertItems(_T("�100-���� �101-���"), _T("�110-���� �111-���"), _T("�120-���� �121-���"), _T("�130-���� �131-���"),
		_T("�140-���� �141-���"), _T("�150-���� �151-���"), _T("�160-���� �161-���"), _T("�170-���� �171-���"), nullptr);
}

void CParamList::init_VNEDK()
{
	Enable();
	CreateHead(Column(L"", 120), Column(L"", 70), nullptr);
	InsertItems(_T("��� �������"), nullptr);
}



