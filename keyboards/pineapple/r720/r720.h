#pragma once

#include "quantum.h"

#define LAYOUT_pa( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010,       K012, K013, K014, K015, \
	K100,       K102, K103,       K105, K106, K107, K108, K109, K110,       K112, K113, K114,       \
	K200, K201, K202,       K204, K205, K206, K207, K208,       K210, K211,       K213,       K215, \
	K300, K301, K302,       K304, K305, K306, K307, K308,       K310, K311,       K313,       K315, \
	K400, K401, K402,       K404, K405, K406, K407, K408,       K410,             K413, K414, K415, \
	K500,       K502,       K504, K505, K506, K507, K508,       K510,             K513, K514, K515, \
	K600,                   K604, K605, K606, K607, K608,       K610, K611,       K613, K614, K615, \
	      K701, K702,             K705, K706, K707, K708,       K710, K711,       K713, K714, K715  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  KC_NO, K012,  K013,  K014,  K015 }, \
	{ K100,  KC_NO, K102,  K103,  KC_NO, K105,  K106,  K107,  K108,  K109,  K110,  KC_NO, K112,  K113,  K114,  KC_NO }, \
	{ K200,  K201,  K202,  KC_NO, K204,  K205,  K206,  K207,  K208,  KC_NO, K210,  K211,  KC_NO, K213,  KC_NO, K215 }, \
	{ K300,  K301,  K302,  KC_NO, K304,  K305,  K306,  K307,  K308,  KC_NO, K310,  K311,  KC_NO, K313,  KC_NO, K315 }, \
	{ K400,  K401,  K402,  KC_NO, K404,  K405,  K406,  K407,  K408,  KC_NO, K410,  KC_NO, KC_NO, K413,  K414,  K415 }, \
	{ K500,  KC_NO, K502,  KC_NO, K504,  K505,  K506,  K507,  K508,  KC_NO, K510,  KC_NO, KC_NO, K513,  K514,  K515 }, \
	{ K600,  KC_NO, KC_NO, KC_NO, K604,  K605,  K606,  K607,  K608,  KC_NO, K610,  K611,  KC_NO, K613,  K614,  K615 }, \
	{ KC_NO, K701,  K702,  KC_NO, KC_NO, K705,  K706,  K707,  K708,  KC_NO, K710,  K711,  KC_NO, K713,  K714,  K715 }  \
}


/* 	{ KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO }, \
	{ KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO }, \
	{ KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO, KC_NO }, \
	{ KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO, KC_NO }, \
	{ KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO }, \
	{ KC_NO,  KC_NO, KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO }, \
	{ KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO }, \
	{ KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO }  \ */
