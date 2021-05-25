#include "CEeprom.h"

void CEeprom::read(uint32_t address,  int sz, void* buf)
{
	//системная функция чтения с файла
	std::ifstream file;
	file.open(file_path);
	if (!file) {
		//Lir.MB("ошибка открытия at45_flash.bin");
		return;
	}
	file.seekg(address);
	file.read((char*)buf, sz);
	file.close();
}

void CEeprom::write(uint32_t address,  int sz, void* buf)
{
	//системная функция записи в файл
	std::fstream file;
	file.open(file_path, std::ios::out | std::ios::in | std::ios::binary);// ставим атрибут std::ios::out | std::ios::in что бы файл не обрезался
	if (!file) {
		//Lir.MB("ошибка открытия at45_flash.bin");
		return;
	}
	file.seekp(address);
	file.write((char*)buf, sz);
	file.close(); 
}

void CEeprom::load(const CString& _file_path)
{
	file_path = _file_path;
	//next
	read(0, sizeof(P2[0]) * N_AXIS, &P2);
	read(4, sizeof(Str), &Str);
	read(8, sizeof(axis_cfg[0]) * N_AXIS, &axis_cfg);
	//read coeff
	read(56, 4, &new_coeff_[0].binary);
	read(60, 1, &new_coeff_[0].n_after_dot);

	read(61, 4, &new_coeff_[1].binary);
	read(65, 1, &new_coeff_[1].n_after_dot);

	read(66, 4, &new_coeff_[2].binary);
	read(70, 1, &new_coeff_[2].n_after_dot);

	read(71, 4, &new_coeff_[3].binary);
	read(75, 1, &new_coeff_[3].n_after_dot);
	//
	read(76, sizeof(offset_g5x), &offset_g5x);
	read(172, sizeof(position_to_see), &position_to_see);
	read(176, sizeof(contrast_value), &contrast_value);
	read(177, sizeof(to_see_time), &to_see_time);
	read(178, sizeof(baudrate), &baudrate);
	read(179, sizeof(submode_mode_REF), &submode_mode_REF);
	read(180, sizeof(invert_display), &invert_display);
	read(181, sizeof(_CH_LH_axis), &_CH_LH_axis);
	read(185, sizeof(sound_and_other), &sound_and_other);
	read(186, sizeof(LH_CH_setup), &LH_CH_setup);
	read(188, sizeof(_Allp_param[0]) * N_AXIS, &_Allp_param);// Зоны скорости
	read(316, sizeof(_Allp_param2), &_Allp_param2);// Параметры оси - Управление
	read(444, sizeof(_INAxis[0]) * N_AXIS, &_INAxis);// Входы осевые
	read(572, sizeof(_OUTAxis[0]) * N_AXIS, &_OUTAxis);// Выходы осевые
	read(700, sizeof(_INGen), &_INGen);// Входы общие
	read(732, sizeof(_OUTGen), &_OUTGen);// Выходы общие
	read(764, sizeof(_Allp_param3), &_Allp_param3);// Зоны торможения
	read(796, sizeof(axis_cfg2),&axis_cfg2); // Настройки абсолютных датчиков
	read(924, sizeof(T_instr[0]) * MAX_INSTR, &T_instr);
	read(1052, sizeof(_INAxis[SW_AXIS0]), &_INAxis[SW_AXIS0]);
	read(1084, sizeof(_OUTAxis[SW_AXIS0]), &_OUTAxis[SW_AXIS0]);
	read(1116, sizeof(_Allp_param[SW_AXIS0]), &_Allp_param[SW_AXIS0]);
	read(1148, sizeof(_OUTGen2), &_OUTGen2);
	read(1180, sizeof(_INGen2), &_INGen2);
	read(1212, sizeof(char), &P2[SW_AXIS0]);
	read(1213, sizeof(_OUTAxis2), &_OUTAxis2);
	read(1373, sizeof(_Allp_param4), &_Allp_param4);
	read(1493, sizeof(_Allp_param5), &_Allp_param5);
	read(1613, sizeof(_Allp_param6), &_Allp_param6);
	read(1713, sizeof(_Allp_param7), &_Allp_param7);
	// 20следующие c 1745
}

void CEeprom::save(const CString& _file_path)
{
	file_path = _file_path;
	//next
	write(0, sizeof(P2[0]) * N_AXIS, &P2);
	write(4, sizeof(Str), &Str);
	write(8, sizeof(axis_cfg[0]) * N_AXIS, &axis_cfg);
	//write coeff
	write(56, 4, &new_coeff_[0].binary);
	write(60, 1, &new_coeff_[0].n_after_dot);

	write(61, 4, &new_coeff_[1].binary);
	write(65, 1, &new_coeff_[1].n_after_dot);

	write(66, 4, &new_coeff_[2].binary);
	write(70, 1, &new_coeff_[2].n_after_dot);

	write(71, 4, &new_coeff_[3].binary);
	write(75, 1, &new_coeff_[3].n_after_dot);
	//
	write(76, sizeof(offset_g5x), &offset_g5x);
	write(172, sizeof(position_to_see), &position_to_see);
	write(176, sizeof(contrast_value), &contrast_value);
	write(177, sizeof(to_see_time), &to_see_time);
	write(178, sizeof(baudrate), &baudrate);
	write(179, sizeof(submode_mode_REF), &submode_mode_REF);
	write(180, sizeof(invert_display), &invert_display);
	write(181, sizeof(_CH_LH_axis), &_CH_LH_axis);
	write(185, sizeof(sound_and_other), &sound_and_other);
	write(186, sizeof(LH_CH_setup), &LH_CH_setup);
	write(188, sizeof(_Allp_param[0]) * N_AXIS, &_Allp_param);// Зоны скорости
	write(316, sizeof(_Allp_param2), &_Allp_param2);// Параметры оси - Управление
	write(444, sizeof(_INAxis[0]) * N_AXIS, &_INAxis);// Входы осевые
	write(572, sizeof(_OUTAxis[0]) * N_AXIS, &_OUTAxis);// Выходы осевые
	write(700, sizeof(_INGen), &_INGen);// Входы общие
	write(732, sizeof(_OUTGen), &_OUTGen);// Выходы общие
	write(764, sizeof(_Allp_param3), &_Allp_param3);// Зоны торможения
	write(796, sizeof(axis_cfg2), &axis_cfg2); // Настройки абсолютных датчиков
	write(924, sizeof(T_instr[0]) * MAX_INSTR, &T_instr);
	write(1052, sizeof(_INAxis[SW_AXIS0]), &_INAxis[SW_AXIS0]);
	write(1084, sizeof(_OUTAxis[SW_AXIS0]), &_OUTAxis[SW_AXIS0]);
	write(1116, sizeof(_Allp_param[SW_AXIS0]), &_Allp_param[SW_AXIS0]);
	write(1148, sizeof(_OUTGen2), &_OUTGen2);
	write(1180, sizeof(_INGen2), &_INGen2);
	write(1212, sizeof(char), &P2[SW_AXIS0]);
	write(1213, sizeof(_OUTAxis2), &_OUTAxis2);
	write(1373, sizeof(_Allp_param4), &_Allp_param4);
	write(1493, sizeof(_Allp_param5), &_Allp_param5);
	write(1613, sizeof(_Allp_param6), &_Allp_param6);
	write(1713, sizeof(_Allp_param7), &_Allp_param7);
	// 20следующие c 1745
}
