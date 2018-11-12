/*
 * Tunes.hpp
 *
 *  Created on: Oct 17, 2018
 *      Author: tamas
 */

#ifndef INC_TUNES_HPP_
#define INC_TUNES_HPP_
#include <inttypes.h>

// Macros for the tune definition
#define BPM 130
#define TIMEBASE 60*256/BPM/4
#define NOTE_E5 659
#define NOTE_C0	16
#define NOTE_C_0 17
#define NOTE_D0	18
#define NOTE_D_0 19
#define NOTE_E0	20
#define NOTE_F0	21
#define NOTE_F_0 23
#define NOTE_G0	24
#define NOTE_G_0 25
#define NOTE_A0	27
#define NOTE_A_0 29
#define NOTE_B0	30
#define NOTE_C1	32
#define NOTE_C_1	34
#define NOTE_D1	36
#define NOTE_D_1	38
#define NOTE_E1	41
#define NOTE_F1	43
#define NOTE_F_1	46
#define NOTE_G1	48
#define NOTE_G_1	51
#define NOTE_A1	55
#define NOTE_A_1	58
#define NOTE_B1	61
#define NOTE_C2	65
#define NOTE_C_2	69
#define NOTE_D2	73
#define NOTE_D_2	77
#define NOTE_E2	82
#define NOTE_F2	87
#define NOTE_F_2	92
#define NOTE_G2	97
#define NOTE_G_2	103
#define NOTE_A2	110
#define NOTE_A_2	116
#define NOTE_B2	123
#define NOTE_C3	130
#define NOTE_C_3	138
#define NOTE_D3	146
#define NOTE_D_3	155
#define NOTE_E3	164
#define NOTE_F3	174
#define NOTE_F_3	184
#define NOTE_G3	195
#define NOTE_G_3	207
#define NOTE_A3	220
#define NOTE_A_3	233
#define NOTE_B3	246
#define NOTE_C4	261
#define NOTE_C_4	277
#define NOTE_D4	293
#define NOTE_D_4	311
#define NOTE_E4	329
#define NOTE_F4	349
#define NOTE_F_4	369
#define NOTE_G4	391
#define NOTE_G_4	415
#define NOTE_A4	440
#define NOTE_A_4	466
#define NOTE_B4	493
#define NOTE_C5	523
#define NOTE_C_5	554
#define NOTE_D5	587
#define NOTE_D_5	622
#define NOTE_E5	659
#define NOTE_F5	698
#define NOTE_F_5	739
#define NOTE_G5	783
#define NOTE_G_5	830
#define NOTE_A5	880
#define NOTE_A_5	932
#define NOTE_B5	987
#define NOTE_C6	1046
#define NOTE_C_6	1108
#define NOTE_D6	1174
#define NOTE_D_6	1244
#define NOTE_E6	1318
#define NOTE_F6	1396
#define NOTE_F_6	1479
#define NOTE_G6	1567
#define NOTE_G_6	1661
#define NOTE_A6	1760
#define NOTE_A_6	1864
#define NOTE_B6	1975
#define NOTE_C7	2093
#define NOTE_C_7	2217
#define NOTE_D7	2349
#define NOTE_D_7	2489
#define NOTE_E7	2637
#define NOTE_F7	2793
#define NOTE_F_7	2959
#define NOTE_G7	3135
#define NOTE_G_7	3322
#define NOTE_A7	3520
#define NOTE_A_7	3729
#define NOTE_B7	3951
#define NOTE_C8	4186
#define NOTE_C_8	4434
#define NOTE_D8	4698
#define NOTE_D_8	4978
#define NOTE_E8	5274
#define NOTE_F8	5587
#define NOTE_F_8	5919
#define NOTE_G8	6271
#define NOTE_G_8	6644
#define NOTE_A8	7040
#define NOTE_A_8	7458
#define NOTE_B8	7902
#define NOTE_C9	8372
#define NOTE_C_9	8869
#define NOTE_D9	9397
#define NOTE_D_9	9956
#define NOTE_E9	10548
#define NOTE_F9	11175
#define NOTE_F_9	11839
#define NOTE_G9	12543
#define NOTE_G_9	13289
#define NOTE_A9	14080
#define NOTE_A_9	14917
#define NOTE_B9	15804
/**
 * @brief defines unit of one note including the pause after it
 */
typedef struct {
	uint8_t on_seconds;
	uint8_t on_sub_seconds;
	uint8_t off_seconds;
	uint8_t off_sub_seconds;
	uint16_t frequecy;
} Note;

static const Note BasicTune[20] = {
		{ 0, TIMEBASE * 1, 0, TIMEBASE * 3, NOTE_B4 }, { 0, TIMEBASE * 1, 0,
				TIMEBASE * 3, NOTE_B4 }, { 0, TIMEBASE * 1, 0, TIMEBASE * 2,
				NOTE_B4 }, { 0, TIMEBASE * 1, 0, TIMEBASE * 2, NOTE_B4 }, { 0,
				TIMEBASE * 1, 0, TIMEBASE * 1, NOTE_E5 },

		{ 0, TIMEBASE * 1, 0, TIMEBASE * 3, NOTE_E5 }, { 0, TIMEBASE * 1, 0,
				TIMEBASE * 3, NOTE_E5 }, { 0, TIMEBASE * 1, 0, TIMEBASE * 2,
				NOTE_D5 }, { 0, TIMEBASE * 1, 0, TIMEBASE * 2, NOTE_D5 }, { 0,
				TIMEBASE * 1, 0, TIMEBASE * 1, NOTE_A4 },

		{ 0, TIMEBASE * 1, 0, TIMEBASE * 3, NOTE_B4 }, { 0, TIMEBASE * 1, 0,
				TIMEBASE * 3, NOTE_B4 }, { 0, TIMEBASE * 1, 0, TIMEBASE * 2,
				NOTE_B4 }, { 0, TIMEBASE * 1, 0, TIMEBASE * 2, NOTE_B4 }, { 0,
				TIMEBASE * 1, 0, TIMEBASE * 1, NOTE_E5 },

		{ 0, TIMEBASE * 1, 0, TIMEBASE * 3, NOTE_B4 }, { 0, TIMEBASE * 1, 0,
				TIMEBASE * 3, NOTE_B4 }, { 0, TIMEBASE * 1, 0, TIMEBASE * 2,
				NOTE_B4 }, { 0, TIMEBASE * 1, 0, TIMEBASE * 2, NOTE_B4 }, { 0,
				TIMEBASE * 1, 0, TIMEBASE * 1, NOTE_E5 }
};

#endif  // INC_TUNES_HPP_
