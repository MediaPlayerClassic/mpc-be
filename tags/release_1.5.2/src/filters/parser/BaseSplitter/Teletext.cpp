/*
 * (C) 2015-2018 see Authors.txt
 *
 * This file is part of MPC-BE.
 *
 * MPC-BE is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPC-BE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Based on telxcc.c from ccextractor source code
 * https://github.com/CCExtractor/ccextractor
 */

#include "stdafx.h"
#include "Teletext.h"

const uint8_t PARITY_8[256] = {
	0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00,
	0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
	0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
	0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00,
	0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
	0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00,
	0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00,
	0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
	0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
	0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00,
	0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00,
	0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
	0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00,
	0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
	0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
	0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00
};

const uint8_t REVERSE_8[256] = {
	0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
	0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8, 0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
	0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4, 0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
	0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec, 0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
	0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2, 0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
	0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea, 0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
	0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
	0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee, 0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
	0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1, 0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
	0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9, 0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
	0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5, 0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
	0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed, 0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
	0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3, 0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
	0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb, 0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
	0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7, 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
	0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, 0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff
};

const uint8_t UNHAM_8_4[256] = {
	0x01, 0xff, 0x01, 0x01, 0xff, 0x00, 0x01, 0xff, 0xff, 0x02, 0x01, 0xff, 0x0a, 0xff, 0xff, 0x07,
	0xff, 0x00, 0x01, 0xff, 0x00, 0x00, 0xff, 0x00, 0x06, 0xff, 0xff, 0x0b, 0xff, 0x00, 0x03, 0xff,
	0xff, 0x0c, 0x01, 0xff, 0x04, 0xff, 0xff, 0x07, 0x06, 0xff, 0xff, 0x07, 0xff, 0x07, 0x07, 0x07,
	0x06, 0xff, 0xff, 0x05, 0xff, 0x00, 0x0d, 0xff, 0x06, 0x06, 0x06, 0xff, 0x06, 0xff, 0xff, 0x07,
	0xff, 0x02, 0x01, 0xff, 0x04, 0xff, 0xff, 0x09, 0x02, 0x02, 0xff, 0x02, 0xff, 0x02, 0x03, 0xff,
	0x08, 0xff, 0xff, 0x05, 0xff, 0x00, 0x03, 0xff, 0xff, 0x02, 0x03, 0xff, 0x03, 0xff, 0x03, 0x03,
	0x04, 0xff, 0xff, 0x05, 0x04, 0x04, 0x04, 0xff, 0xff, 0x02, 0x0f, 0xff, 0x04, 0xff, 0xff, 0x07,
	0xff, 0x05, 0x05, 0x05, 0x04, 0xff, 0xff, 0x05, 0x06, 0xff, 0xff, 0x05, 0xff, 0x0e, 0x03, 0xff,
	0xff, 0x0c, 0x01, 0xff, 0x0a, 0xff, 0xff, 0x09, 0x0a, 0xff, 0xff, 0x0b, 0x0a, 0x0a, 0x0a, 0xff,
	0x08, 0xff, 0xff, 0x0b, 0xff, 0x00, 0x0d, 0xff, 0xff, 0x0b, 0x0b, 0x0b, 0x0a, 0xff, 0xff, 0x0b,
	0x0c, 0x0c, 0xff, 0x0c, 0xff, 0x0c, 0x0d, 0xff, 0xff, 0x0c, 0x0f, 0xff, 0x0a, 0xff, 0xff, 0x07,
	0xff, 0x0c, 0x0d, 0xff, 0x0d, 0xff, 0x0d, 0x0d, 0x06, 0xff, 0xff, 0x0b, 0xff, 0x0e, 0x0d, 0xff,
	0x08, 0xff, 0xff, 0x09, 0xff, 0x09, 0x09, 0x09, 0xff, 0x02, 0x0f, 0xff, 0x0a, 0xff, 0xff, 0x09,
	0x08, 0x08, 0x08, 0xff, 0x08, 0xff, 0xff, 0x09, 0x08, 0xff, 0xff, 0x0b, 0xff, 0x0e, 0x03, 0xff,
	0xff, 0x0c, 0x0f, 0xff, 0x04, 0xff, 0xff, 0x09, 0x0f, 0xff, 0x0f, 0x0f, 0xff, 0x0e, 0x0f, 0xff,
	0x08, 0xff, 0xff, 0x05, 0xff, 0x0e, 0x0d, 0xff, 0xff, 0x0e, 0x0f, 0xff, 0x0e, 0x0e, 0xff, 0x0e
};

enum g0_charsets_t {
	LATIN = 0,
	CYRILLIC1,
	CYRILLIC2,
	CYRILLIC3,
	GREEK,
	ARABIC,
	HEBREW
};
g0_charsets_t g0_charsets_default = LATIN;

// --- G0 ----------------------------------------------------------------------

// G0 charsets
uint16_t G0[5][96] = {
	{ // Latin G0 Primary Set
		0x0020, 0x0021, 0x0022, 0x00a3, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
		0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
		0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
		0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005a, 0x00ab, 0x00bd, 0x00bb, 0x005e, 0x0023,
		0x002d, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
		0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007a, 0x00bc, 0x00a6, 0x00be, 0x00f7, 0x007f
	},
	{ // Cyrillic G0 Primary Set - Option 1 - Serbian/Croatian
		0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x044b, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
		0x0030, 0x0031, 0x3200, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
		0x0427, 0x0410, 0x0411, 0x0426, 0x0414, 0x0415, 0x0424, 0x0413, 0x0425, 0x0418, 0x0408, 0x041a, 0x041b, 0x041c, 0x041d, 0x041e,
		0x041f, 0x040c, 0x0420, 0x0421, 0x0422, 0x0423, 0x0412, 0x0403, 0x0409, 0x040a, 0x0417, 0x040b, 0x0416, 0x0402, 0x0428, 0x040f,
		0x0447, 0x0430, 0x0431, 0x0446, 0x0434, 0x0435, 0x0444, 0x0433, 0x0445, 0x0438, 0x0428, 0x043a, 0x043b, 0x043c, 0x043d, 0x043e,
		0x043f, 0x042c, 0x0440, 0x0441, 0x0442, 0x0443, 0x0432, 0x0423, 0x0429, 0x042a, 0x0437, 0x042b, 0x0436, 0x0422, 0x0448, 0x042f
	},
	{ // Cyrillic G0 Primary Set - Option 2 - Russian/Bulgarian
		0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x044b, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
		0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
		0x042e, 0x0410, 0x0411, 0x0426, 0x0414, 0x0415, 0x0424, 0x0413, 0x0425, 0x0418, 0x0419, 0x041a, 0x041b, 0x041c, 0x041d, 0x041e,
		0x041f, 0x042f, 0x0420, 0x0421, 0x0422, 0x0423, 0x0416, 0x0412, 0x042c, 0x042a, 0x0417, 0x0428, 0x042d, 0x0429, 0x0427, 0x042b,
		0x044e, 0x0430, 0x0431, 0x0446, 0x0434, 0x0435, 0x0444, 0x0433, 0x0445, 0x0438, 0x0439, 0x043a, 0x043b, 0x043c, 0x043d, 0x043e,
		0x043f, 0x044f, 0x0440, 0x0441, 0x0442, 0x0443, 0x0436, 0x0432, 0x044c, 0x044a, 0x0437, 0x0448, 0x044d, 0x0449, 0x0447, 0x044b
	},
	{ // Cyrillic G0 Primary Set - Option 3 - Ukrainian
		0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x00ef, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
		0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
		0x042e, 0x0410, 0x0411, 0x0426, 0x0414, 0x0415, 0x0424, 0x0413, 0x0425, 0x0418, 0x0419, 0x041a, 0x041b, 0x041c, 0x041d, 0x041e,
		0x041f, 0x042f, 0x0420, 0x0421, 0x0422, 0x0423, 0x0416, 0x0412, 0x042c, 0x0049, 0x0417, 0x0428, 0x042d, 0x0429, 0x0427, 0x00cf,
		0x044e, 0x0430, 0x0431, 0x0446, 0x0434, 0x0435, 0x0444, 0x0433, 0x0445, 0x0438, 0x0439, 0x043a, 0x043b, 0x043c, 0x043d, 0x043e,
		0x043f, 0x044f, 0x0440, 0x0441, 0x0442, 0x0443, 0x0436, 0x0432, 0x044c, 0x0069, 0x0437, 0x0448, 0x044d, 0x0449, 0x0447, 0x00ff
	},
	{ // Greek G0 Primary Set
		0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
		0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
		0x0390, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 0x0398, 0x0399, 0x039a, 0x039b, 0x039c, 0x039d, 0x039e, 0x039f,
		0x03a0, 0x03a1, 0x03a2, 0x03a3, 0x03a4, 0x03a5, 0x03a6, 0x03a7, 0x03a8, 0x03a9, 0x03aa, 0x03ab, 0x03ac, 0x03ad, 0x03ae, 0x03af,
		0x03b0, 0x03b1, 0x03b2, 0x03b3, 0x03b4, 0x03b5, 0x03b6, 0x03b7, 0x03b8, 0x03b9, 0x03ba, 0x03bb, 0x03bc, 0x03bd, 0x03be, 0x03bf,
		0x03c0, 0x03c1, 0x03c2, 0x03c3, 0x03c4, 0x03c5, 0x03c6, 0x03c7, 0x03c8, 0x03c9, 0x03ca, 0x03cb, 0x03cc, 0x03cd, 0x03ce, 0x03cf
	}
	//{ // Arabic G0 Primary Set
	//},
	//{ // Hebrew G0 Primary Set
	//}
};

// array positions where chars from G0_LATIN_NATIONAL_SUBSETS are injected into G0[LATIN]
const uint8_t G0_LATIN_NATIONAL_SUBSETS_POSITIONS[13] = {
	0x03, 0x04, 0x20, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x5b, 0x5c, 0x5d, 0x5e
};

// ETS 300 706, chapter 15.2, table 32: Function of Default G0 and G2 Character Set Designation
// and National Option Selection bits in packets X/28/0 Format 1, X/28/4, M/29/0 and M/29/4

// Latin National Option Sub-sets
struct {
	const char *language;
	uint16_t characters[13];
} const G0_LATIN_NATIONAL_SUBSETS[14] = {
	{ // 0
		"English",
		{ 0x00a3, 0x0024, 0x0040, 0x00ab, 0x00bd, 0x00bb, 0x005e, 0x0023, 0x002d, 0x00bc, 0x00a6, 0x00be, 0x00f7 }
	},
	{ // 1
		"French",
		{ 0x00e9, 0x00ef, 0x00e0, 0x00eb, 0x00ea, 0x00f9, 0x00ee, 0x0023, 0x00e8, 0x00e2, 0x00f4, 0x00fb, 0x00e7 }
	},
	{ // 2
		"Swedish, Finnish, Hungarian",
		{ 0x0023, 0x00a4, 0x00c9, 0x00c4, 0x00d6, 0x00c5, 0x00dc, 0x005f, 0x00e9, 0x00e4, 0x00f6, 0x00e5, 0x00fc }
	},
	{ // 3
		"Czech, Slovak",
		{ 0x0023, 0x016f, 0x010d, 0x0165, 0x017e, 0x00fd, 0x00ed, 0x0159, 0x00e9, 0x00e1, 0x011b, 0x00fa, 0x0161 }
	},
	{ // 4
		"German",
		{ 0x0023, 0x0024, 0x00a7, 0x00c4, 0x00d6, 0x00dc, 0x005e, 0x005f, 0x00b0, 0x00e4, 0x00f6, 0x00fc, 0x00df }
	},
	{ // 5
		"Portuguese, Spanish",
		 { 0x00e7, 0x0024, 0x00a1, 0x00e1, 0x00e9, 0x00ed, 0x00f3, 0x00fa, 0x00bf, 0x00fc, 0x00f1, 0x00e8, 0x00e0 }
	},
	{ // 6
		"Italian",
		{ 0x00a3, 0x0024, 0x00e9, 0x00b0, 0x00e7, 0x00bb, 0x005e, 0x0023, 0x00f9, 0x00e0, 0x00f2, 0x00e8, 0x00ec }
	},
	{ // 7
		"Rumanian",
		{ 0x0023, 0x00a4, 0x0162, 0x00c2, 0x015e, 0x0102, 0x00ce, 0x0131, 0x0163, 0x00e2, 0x015f, 0x0103, 0x00ee }
	},
	{ // 8
		"Polish",
		{ 0x0023, 0x0144, 0x0105, 0x017b, 0x015a, 0x0141, 0x0107, 0x00f3, 0x0119, 0x017c, 0x015b, 0x0142, 0x017a }
	},
	{ // 9
		"Turkish",
		{ 0x0054, 0x011f, 0x0130, 0x015e, 0x00d6, 0x00c7, 0x00dc, 0x011e, 0x0131, 0x015f, 0x00f6, 0x00e7, 0x00fc }
	},
	{ // a
		"Serbian, Croatian, Slovenian",
		{ 0x0023, 0x00cb, 0x010c, 0x0106, 0x017d, 0x0110, 0x0160, 0x00eb, 0x010d, 0x0107, 0x017e, 0x0111, 0x0161 }
	},
	{ // b
		"Estonian",
		{ 0x0023, 0x00f5, 0x0160, 0x00c4, 0x00d6, 0x017e, 0x00dc, 0x00d5, 0x0161, 0x00e4, 0x00f6, 0x017e, 0x00fc }
	},
	{ // c
		"Lettish, Lithuanian",
		{ 0x0023, 0x0024, 0x0160, 0x0117, 0x0119, 0x017d, 0x010d, 0x016b, 0x0161, 0x0105, 0x0173, 0x017e, 0x012f }
	}
};

// References to the G0_LATIN_NATIONAL_SUBSETS array
const uint8_t G0_LATIN_NATIONAL_SUBSETS_MAP[56] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x01, 0x02, 0x03, 0x04, 0xff, 0x06, 0xff,
	0x00, 0x01, 0x02, 0x09, 0x04, 0x05, 0x06, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x0a, 0xff, 0x07,
	0xff, 0xff, 0x0b, 0x03, 0x04, 0xff, 0x0c, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0x09, 0xff, 0xff, 0xff, 0xff
};

// ETS 300 706, chapter 8.2
static uint8_t unham_8_4(uint8_t a)
{
	uint8_t r = UNHAM_8_4[a];
	if (r == 0xff) {
		DLog(L"unham_8_4() - Unrecoverable data error; UNHAM8/4(%02x)", a);
	}
	return (r & 0x0f);
}

// check parity and translate any reasonable teletext character into ucs2
static uint16_t telx_to_ucs2(uint8_t c)
{
	if (PARITY_8[c] == 0)
	{
		DLog(L"telx_to_ucs2() - Unrecoverable data error; PARITY(%02x)", c);
		return 0x20;
	}

	uint16_t r = c & 0x7f;
	if (r >= 0x20)
		r = G0[g0_charsets_default][r - 0x20];
	return r;
}

// extracts magazine number from teletext page
#define MAGAZINE(p) ((p >> 8) & 0xf)

enum bool_t {
	YES = 1,
	NO = 0,
	UNDEF = 0xff
};

// current charset (charset can be -- and always is -- changed during transmission)
struct s_primary_charset {
	uint8_t current;
	uint8_t g0_m29;
	uint8_t g0_x28;
} primary_charset = {
	0x00, UNDEF, UNDEF
};

static void remap_g0_charset(uint8_t c)
{
	if (c != primary_charset.current) {
		uint8_t m = G0_LATIN_NATIONAL_SUBSETS_MAP[c];
		if (m == 0xff) {
			DLog(L"remap_g0_charset() - G0 Latin National Subset ID 0x%1x.%1x is not implemented", (c >> 3), (c & 0x7));
		} else {
			for (uint8_t j = 0; j < 13; j++) {
				G0[LATIN][G0_LATIN_NATIONAL_SUBSETS_POSITIONS[j]] = G0_LATIN_NATIONAL_SUBSETS[m].characters[j];
			}
			primary_charset.current = c;
		}
	}
}

static const wchar_t* TTXT_COLOURS[8] = {
	//black,    red,        green,      yellow,     blue,       magenta,    cyan,       white
	L"#000000", L"#ff0000", L"#00ff00", L"#ffff00", L"#0000ff", L"#ff00ff", L"#00ffff", L"#ffffff"
};

void CTeletext::ProcessTeletextPage()
{
	// optimization: slicing column by column -- higher probability we could find boxed area start mark sooner
	uint8_t page_is_empty = YES;
	for (uint8_t col = 0; col < 40; col++) {
		for (uint8_t row = 1; row < 25; row++) {
			if (m_page_buffer.text[row][col] == 0x0b) {
				page_is_empty = NO;
				goto page_is_empty;
			}
		}
	}
	page_is_empty:
	if (page_is_empty == YES) {
		return;
	}

	uint8_t line_count = 0;
	CString str;

	// process data
	for (uint8_t row = 1; row < 25; row++) {
		// anchors for string trimming purpose
		uint8_t col_start = 40;
		uint8_t col_stop = 40;

		uint8_t box_open = NO;
		for (int8_t col = 0; col < 40; col++) {
			// replace all 0/B and 0/A characters with 0/20, as specified in ETS 300 706:
			// Unless operating in "Hold Mosaics" mode, each character space occupied by a
			// spacing attribute is displayed as a SPACE
			if (m_page_buffer.text[row][col] == 0xb) { // open the box
				if (col_start == 40) {
					col_start = col;
					line_count++;
				} else {
					m_page_buffer.text[row][col] = 0x20;
				}
				box_open = YES;
			} else if (m_page_buffer.text[row][col] == 0xa) { // close the box
				m_page_buffer.text[row][col] = 0x20;
				box_open = NO;
			} else if (!box_open && col_start < 40 && m_page_buffer.text[row][col] > 0x20) {
				// characters between 0xA and 0xB shouldn't be displayed
				// m_page_buffer.text[row][col] > 0x20 added to preserve color information
				m_page_buffer.text[row][col] = 0x20;
			}
		}
		// line is empty
		if (col_start > 39) {
			continue;
		}

		if (line_count > 1 && !str.IsEmpty()) {
			str += L"\r\n";
		}

		for (uint8_t col = col_start + 1; col <= 39; col++) {
			if (m_page_buffer.text[row][col] > 0x20) {
				if (col_stop > 39) {
					col_start = col;
				}
				col_stop = col;
			}
		}

		// line is empty
		if (col_stop > 39) {
			continue;
		}

		// ETS 300 706, chapter 12.2: Alpha White ("Set-After") - Start-of-row default condition.
		// used for colour changes _before_ start box mark
		// white is default as stated in ETS 300 706, chapter 12.2
		// black(0), red(1), green(2), yellow(3), blue(4), magenta(5), cyan(6), white(7)
		uint8_t foreground_color = 0x7;
		uint8_t font_tag_opened = NO;

		for (uint8_t col = 0; col <= col_stop; col++) {
			// v is just a shortcut
			uint16_t v = m_page_buffer.text[row][col];

			if (col < col_start) {
				if (v <= 0x7) {
					foreground_color = (uint8_t)v;
				}
			}

			if (col == col_start) {
				if (foreground_color != 0x7) {
					str.AppendFormat(L"<font color=\"%s\">", TTXT_COLOURS[foreground_color]);
					font_tag_opened = YES;
				}
			}

			if (col >= col_start) {
				if (v <= 0x7) {
					// ETS 300 706, chapter 12.2: Unless operating in "Hold Mosaics" mode,
					// each character space occupied by a spacing attribute is displayed as a SPACE.
					if (font_tag_opened == YES) {
						str += L"</font>";
						font_tag_opened = NO;
					}

					str.AppendChar(L' ');

					// black is considered as white for telxcc purpose
					// telxcc writes <font/> tags only when needed
					if ((v > 0x0) && (v < 0x7)) {
						str.AppendFormat(L"<font color=\"%s\">", TTXT_COLOURS[v]);
						font_tag_opened = YES;
					}
				}

				if (v >= 0x20) {
					str.AppendChar(v);
				}
			}
		}

		if (font_tag_opened == YES) {
			str += L"</font>";
		}
	}

	if (!str.IsEmpty()) {
		TeletextData tData;
		tData.rtStart = m_page_buffer.rtStart;
		tData.rtStop  = m_page_buffer.rtStop;
		tData.str     = str;
		m_output.emplace_back(tData);
	}
}

void CTeletext::ProcessTeletextPacket(teletext_packet_payload* packet, REFERENCE_TIME rtStart)
{
	// variable names conform to ETS 300 706, chapter 7.1.2
	uint8_t address, m, line;
	address = (unham_8_4(packet->address[1]) << 4) | unham_8_4(packet->address[0]);
	m = address & 0x7;
	if (m == 0) m = 8;
	line = (address >> 3) & 0x1f;

	if (line == 0) {
		uint8_t i = (unham_8_4(packet->data[1]) << 4) | unham_8_4(packet->data[0]);
		uint8_t flag_subtitle = (unham_8_4(packet->data[5]) & 0x08) >> 3;

		// Page number and control bits
		uint16_t page_number = (m << 8) | i;
		uint8_t charset = ((unham_8_4(packet->data[7]) & 0x08) | (unham_8_4(packet->data[7]) & 0x04) | (unham_8_4(packet->data[7]) & 0x02)) >> 1;

		if ((m_nSuitablePage == 0) && (flag_subtitle == YES) && (i < 0xff)) {
			m_nSuitablePage = page_number;
			DLog(L"ProcessTeletextPacket() - No teletext page specified, first received suitable page is %03x, not guaranteed", m_nSuitablePage);
		}

		// Page transmission is terminated, however now we are waiting for our new page
		if (page_number != m_nSuitablePage) {
			m_bReceivingData = NO;
			return;
		}

		// Now we have the begining of page transmission; if there is page_buffer pending, process it
		if (m_page_buffer.tainted == YES) {
			m_page_buffer.rtStop = rtStart;
			ProcessTeletextPage();
		}

		m_page_buffer.rtStart = rtStart == INVALID_TIME ? 0 : rtStart;
		m_page_buffer.rtStop = rtStart + 1;

		if ((packet->data[3] & 0x80) == 0x80) {
			// erase page
			ZeroMemory(m_page_buffer.text, sizeof(m_page_buffer.text));
		}
		m_page_buffer.tainted = NO;
		m_bReceivingData = YES;

		if (g0_charsets_default == LATIN) { // G0 Character National Option Sub-sets selection required only for Latin Character Sets
			//primary_charset.g0_x28 = UNDEF;
			uint8_t c = /*(primary_charset.g0_m29 != UNDEF) ? primary_charset.g0_m29 : */charset;
			remap_g0_charset(c);
		}
	} else if ((m == MAGAZINE(m_nSuitablePage)) && (line >= 1) && (line <= 23) && (m_bReceivingData == YES)) {
		for (uint8_t i = 0; i < 40; i++) {
			m_page_buffer.text[line][i] = telx_to_ucs2(packet->data[i]);
		}
		m_page_buffer.tainted = YES;
	}
}

enum data_unit {
	DATA_UNIT_EBU_TELETEXT_NONSUBTITLE = 0x02,
	DATA_UNIT_EBU_TELETEXT_SUBTITLE = 0x03,
	DATA_UNIT_EBU_TELETEXT_INVERTED = 0x0c,
	DATA_UNIT_VPS = 0xc3,
	DATA_UNIT_CLOSED_CAPTIONS = 0xc5
};

CTeletext::CTeletext()
{
	ZeroMemory(&m_page_buffer, sizeof(m_page_buffer));
}

void CTeletext::ProcessData(uint8_t* buffer, uint16_t size, REFERENCE_TIME rtStart, WORD tlxPage)
{
	if (tlxPage) {
		m_nSuitablePage = tlxPage;
	}

	if (size > 6) {
		uint16_t i = 1;
		while (i <= size - 6) {
			uint8_t data_unit_id  = buffer[i++];
			uint8_t data_unit_len = buffer[i++];
			if ((data_unit_id == DATA_UNIT_EBU_TELETEXT_NONSUBTITLE) || (data_unit_id == DATA_UNIT_EBU_TELETEXT_SUBTITLE)) {
				if (data_unit_len == 44 && i + data_unit_len <= size) {
					for (uint8_t j = 0; j < data_unit_len; j++) {
						buffer[i + j] = REVERSE_8[buffer[i + j]];
					}

					ProcessTeletextPacket((teletext_packet_payload *)&buffer[i], rtStart);
				}
			}
			i += data_unit_len;
		}
	}
}

void CTeletext::Flush()
{
	ZeroMemory(&m_page_buffer, sizeof(m_page_buffer));
	m_bReceivingData = NO;

	EraseOutput();
}

void CTeletext::SetLCID(const LCID lcid)
{
	static const LCID LCID_BULGARIAN = MAKELCID( MAKELANGID(LANG_BULGARIAN, SUBLANG_DEFAULT), SORT_DEFAULT);
	static const LCID LCID_GREEK     = MAKELCID( MAKELANGID(LANG_GREEK, SUBLANG_DEFAULT), SORT_DEFAULT);
	static const LCID LCID_RUSSIAN   = MAKELCID( MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT), SORT_DEFAULT);
	static const LCID LCID_SERBIAN   = MAKELCID( MAKELANGID(LANG_SERBIAN, SUBLANG_DEFAULT), SORT_DEFAULT);
	static const LCID LCID_UKRAINIAN = MAKELCID( MAKELANGID(LANG_UKRAINIAN, SUBLANG_DEFAULT), SORT_DEFAULT);

	g0_charsets_default = LATIN;
	switch (lcid) {
		case LCID_BULGARIAN:
		case LCID_RUSSIAN:
			g0_charsets_default = CYRILLIC2;
			break;
		case LCID_SERBIAN:
			g0_charsets_default = CYRILLIC1;
			break;
		case LCID_UKRAINIAN:
			g0_charsets_default = CYRILLIC3;
			break;
		case LCID_GREEK:
			g0_charsets_default = GREEK;
			break;
	}
}

void CTeletext::GetOutput(std::vector<TeletextData>& output)
{
	output = m_output;
}

void CTeletext::EraseOutput()
{
	m_output.clear();
}

BOOL CTeletext::ProcessRemainingData()
{
	if (m_page_buffer.tainted == YES) {
		m_page_buffer.rtStop = m_page_buffer.rtStart + 10 * UNITS; // 10 seconds
		ProcessTeletextPage();
	}

	return IsOutputPresent();
}