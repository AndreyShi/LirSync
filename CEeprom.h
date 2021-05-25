#pragma once

#include "afxwin.h" // MFC Основные и стандартные компоненты
#include "afxcmn.h"
#include <stdint.h>
#include <fstream>

#define N_AXIS 4  // кол - во каналов, в циклах использовать 'с'
#define N_STR  4  // кол - во отображаемых строк, в циклах использовать 's'

#define N_SA   1  // кол - во скрытых(Shadow) осей
#define SW_AXIS0 ((N_AXIS + N_SA) - 1) //скрытая ось в массиве

#define MAX_INSTR 10  //кол -во инструмента


class CEeprom {
private:
	CString file_path;
	void read(uint32_t address,int sz, void* buf);
	void write(uint32_t address, int sz, void* buf);
public:	
	void load(const CString& _file_path);
	void save(const CString& _file_path);

	struct _AXIS_CFG {
		//02.03.2018 sum of these fields must be 32 (4 bytes) (29.03.2018)+8=12	
		unsigned int type : 3;
		unsigned int format : 5;
		unsigned int r_d : 1;
		unsigned int direction : 1;
		unsigned int save : 1;
		unsigned int encoder_fault : 1;
		unsigned int readout_speed : 1;
		unsigned int rezerv1 : 4;
		unsigned int rezerv2 : 4;
		unsigned int rezerv3 : 1;
		unsigned int rezerv4 : 1;
		unsigned int rezerv5 : 1;
		unsigned int rezerv6 : 1;
		unsigned int is_correction : 1;
		unsigned int is_coded_ref : 1;
		unsigned int interval_to_measure_speed : 2;
		unsigned int rezerv7 : 3;
		long gap;
		char ref_pulse_zone;
		char extern_to_zero;
		short rezerv8;
	}axis_cfg[N_AXIS];

	struct _AXIS_CFG2 {
		char bit_enc; //кол-во бит
		char HZ_enc;  //частота опроса
		short rezerv0;
		long rezerv1;
		long rezerv2;
		long rezerv3;
		long rezerv4;
		long rezerv5;
		long rezerv6;
		long rezerv7;
	}axis_cfg2[N_AXIS];

	//== параметры дискретного задания скорости Allp_param
	struct Allp_param {
		char start_G1; //4 bits
		char spd01_G1;//4 bits
		char spd02_G1;//4 bits
		char spd03_G1;//4 bits
		char spd04_G1;//4 bits
		char stop_G1;//4 bits

		char start_G0;//4 bits
		char spd01_G0;//4 bits
		char spd02_G0;//4 bits
		char spd03_G0;//4 bits
		char spd04_G0;//4 bits
		char stop_G0;//4 bits

		char start_PM;//4 bits
		char limit_PM;//4 bits
		char zone_PM;//4 bits
		char stop_PM;//4 bits

		char start_LUFT;//4 bits
		char rezerv;//4 bits
		short rezerv1;
		long rezerv2;
		long rezerv3;
		long rezerv4;
	}_Allp_param[N_AXIS + N_SA];
	//==
	//==параметры настройки Управления осью
	struct Allp_param2 {
		unsigned  long ref_dir : 2;  //2 - выбор
		unsigned  long dovodka : 1;
		unsigned  long viborka_lufta : 1;
		unsigned  long VNE_DOPUSKA : 1;
		unsigned  long rezerv : 27;
		long dopusk;
		long limit_plus;
		long limit_minus;
		short delay_VIBOR_PUSK;
		short v_Pozition;
		long rezerv2;
		long rezerv3;
		long rezerv4;
	}_Allp_param2[N_AXIS];
	//==
	//==параметры зоны торможения оси
	struct Allp_param3 {
		long Zone_brake01;
		long Zone_brake02;
		long Zone_brake03;
		long Zone_brake04;
		long Zone_brakeStop;
		long rezerv;
		long rezerv1;
		long rezerv2;
	}_Allp_param3[N_AXIS];
	//==
	//==группа параметров аналогового задания скорости c Allp_param4 по Allp_param6
	struct Allp_param4 {
		long start_G1;
		long spd01_G1;
		long spd02_G1;
		long spd03_G1;
		long spd04_G1;
		long stop_G1;
	}_Allp_param4[N_AXIS + N_SA];

	struct Allp_param5 {
		long start_G0;
		long spd01_G0;
		long spd02_G0;
		long spd03_G0;
		long spd04_G0;
		long stop_G0;
	}_Allp_param5[N_AXIS + N_SA];

	struct Allp_param6 {
		long start_PM;
		long limit_PM;
		long zone_PM;
		long stop_PM;
		long start_LUFT;
	}_Allp_param6[N_AXIS + N_SA];
	//==
	struct INAxis {
		char axis_on_brake;
		char vibor_axis;
		char otmena_vibor_axis;
		char Pusk_plus;
		char Pusk_minus;
		char Tolchok_plus;
		char Tolchok_minus;
		char Ogranichitel_plus;
		char Ogranichitel_minus;
		char rezerv0;
		char rezerv1;
		char rezerv2;
		long rezerv3;
		long rezerv4;
		long rezerv5;
		long rezerv6;
		long rezerv7;
	}_INAxis[N_AXIS + N_SA];

	struct OUTAxis {
		char vibor_axis;
		char Pusk_plus;
		char Pusk_minus;
		char Pusk;
		char Smazka;
		char Out_A;
		char Out_B;
		char Out_C;
		char Out_D;
		int8_t typeZ; //тип задания: дискретное/аналоговое/частотное/импульсное
		int8_t time_lubr;
		int8_t rezerv2;
		long dist_lubr;
		long rezerv4;
		long rezerv5;
		long rezerv6;
		long rezerv7;
	}_OUTAxis[N_AXIS + N_SA];

	struct OUTAxis2 {
		int8_t AnalOut;
		int8_t Polar;
		char rezerv0;
		char rezerv1;
		long MaxSpdG1;
		long MaxUG1;
		long MaxSpdG0;
		long MaxUG0;
		long rezerv2;
		long rezerv3;
		long rezerv4;
	}_OUTAxis2[N_AXIS + N_SA];

	struct INGen {
		char gotov_stanok;
		char yskorenniy_xod_G0;
		char stop_podacha;
		char smena_kadra;
		char pause;
		char start_prog;
		char vneshnee_ypravlenie; //внешний пульт
		char po_chasovoy_M3;
		char protiv_chasovoy_M4;
		char stop_M5;
		char tolchok_plus;
		char tolchok_minus;
		char shpindel_vrashaetsia;
		char instrum_zajat;
		short rezerv0;
		long rezerv1;
		long rezerv2;
		long rezerv3;
		long rezerv4;
	}_INGen;

	struct INGen2 {
		char M102;
		char M112;
		char M122;
		char M132;
		char M142;
		char M152;
		char M162;
		char M172;
		long rezerv0;
		long rezerv1;
		long rezerv2;
		long rezerv3;
		long rezerv4;
		long rezerv5;
	}_INGen2;

	struct OUTGen {
		char yskorenniy_xod_G0;
		char podacha_G1;
		char texnolog_stop_M0;
		char konec_program_M2;
		char rychnoy_rejim;
		char auto_rejim;
		char pozitionirovanie;
		char gotovnostbUCIPU;
		char po_chasovoy_M3;
		char protiv_chasovoy_M4;
		char stop_M5;
		char Tolchok;
		char M3_M4_cherez_M5 : 1;
		char rezerv0 : 7;//13
		char rezerv1;
		short pause_M5;
		long rezerv2;
		long rezerv3;
		long rezerv4;
		long rezerv5;
	}_OUTGen;

	struct OUTGen2 {
		char M100off_M101on;
		char M110off_M111on;
		char M120off_M121on;
		char M130off_M131on;
		char M140off_M141on;
		char M150off_M151on;
		char M160off_M161on;
		char M170off_M171on;
		long rezerv0;
		long rezerv1;
		long rezerv2;
		long rezerv3;
		long rezerv4;
		long rezerv5;
	}_OUTGen2;

	struct Allp_param7 {
		long U_off_a[2];//смещение напряжения [0]-a1 , [1]-a2
		short min_percent_feed;
		short MAX_percent_feed;
		long rezerv1;
		long rezerv2;
		long rezerv3;
		long rezerv4;
		long rezerv5;
	}_Allp_param7;

	struct _T_instr {
		long r;// радиус инструмента
		long l;// длина инструмента
	}T_instr[MAX_INSTR];

	uint8_t P2[N_AXIS + N_SA];// ОСИ ПУЛЬТА (линейные ,круговые, слепые)
	uint8_t Str[N_STR];	   // ОСЕВЫЕ СТРОКИ ПУЛЬТА

	struct COEFF_NEW {
		long binary;
		char n_after_dot;
	} new_coeff_[N_AXIS];

	long offset_g5x[5][N_AXIS]; //G53 - G58

	enum _STR_MODE :uint8_t {
		SPEED,     // скорость
		COORDINATE,// координаты (функций нет)
		PLUS,      // суммируемая ось
		RESULT,    // результат вычислений
		TIME,      // время
	}position_to_see[N_STR];

	uint8_t contrast_value;
	bool to_see_time;
	uint8_t baudrate;
	uint8_t submode_mode_REF;
	uint8_t invert_display;

	struct CH_LH_axis {
		uint8_t tmp_primary_axis_lh;
		uint8_t tmp_secondary_axis_lh;
		uint8_t tmp_primary_axis_ch;
		uint8_t tmp_secondary_axis_ch;
	}_CH_LH_axis;

	/*
	sound_and_other - переменная хранящая в себе всякие настройки в битовом виде
	0x01 - звук, 0x02 - обновление координат, 0x04 - захват ошибки датчика ,0x08 - внешний ПЛК
	0x10 - очистка преднабора
	*/
	uint8_t sound_and_other;

	struct _LH_CH_setup {
		unsigned char sound : 1;
		unsigned char rezerv : 7;
	}LH_CH_setup[2];

	//================================================СТРОКИ===============================================================
	const wchar_t sAxis_symbol_sw[14][13] = {
	{L" X(слепая)  "},
	{L" Y(слепая)  "},
	{L" Z(слепая)  "},
	{L" U(слепая)  "},
	{L" V(слепая)  "},
	{L" W(слепая)  "},
	{L" P(слепая)  "},
	{L" Q(слепая)  "},
	{L" R(слепая)  "},
	{L" A(слепая)  "},
	{L" B(слепая)  "},
	{L" C(слепая)  "},
	{L" D(слепая)  "},
	{L"    нет     "}
	};

	const wchar_t sAxis_symbol[14][13] = { {L" X(линейная)"},
										 {L" Y(линейная)"},
										 {L" Z(линейная)"},
										 {L" U(линейная)"},
										 {L" V(линейная)"},
										 {L" W(линейная)"},
										 {L" P(линейная)"},
										 {L" Q(линейная)"},
										 {L" R(линейная)"},
										 {L" A(круговая)"},
										 {L" B(круговая)"},
										 {L" C(круговая)"},
										 {L" D(круговая)"},
										 {L"    нет     "} };
	//=====================================================================================================================
	
};

class CInit {
public:
	enum AXIS_NAME {
		AXIS_X,
		AXIS_Y,
		AXIS_Z,
		AXIS_U,
		AXIS_V,
		AXIS_W,
		AXIS_P,
		AXIS_Q,
		AXIS_R,
		AXIS_A,
		AXIS_B,
		AXIS_C,
		AXIS_D,
		NO_AXIS,
	};
};