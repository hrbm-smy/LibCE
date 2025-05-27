#ifndef __bits_H__
#define __bits_H__

/** -------------------------------------------------------------------------
 *
 *	@file	bits.h
 *	@brief	Bit width operations
 *	@author	H.Someya
 *	@date	2025/05/26
 *
 */
/*
MIT License

Copyright (c) 2021 Hirobumi Someya

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdint.h>

/* --------------------------------------------------------------------------
 *  P U B L I C   D E F I N I T I O N S
 */

/**
 * bit 7 - 0 を取得する。
 */
#define BITS0700(v) ((uint8_t)(((v) >> 0) & 0xff))
/**
 * bit 15 - 8 を取得する。
 */
#define BITS1508(v) ((uint8_t)(((v) >> 8) & 0xff))
/**
 * 16ビット値にする。
 * @param h High側8ビット。D15-D8に配置される。
 * @param l Low側8ビット。D7-D0に配置される。
 */
#define FORM16BITS(h, l) (                         \
	(uint16_t)(((((uint16_t)(h)) << 8) & 0xff00) | \
			   ((((uint16_t)(l)) << 0) & 0x00ff)))

/**
 * bit 15 - 0 を取得する。
 */
#define BITS1500(v) (uint16_t)(((v) >> 0) & 0xffff)
/**
 * bit 31 - 16 を取得する。
 */
#define BITS3116(v) (uint16_t)(((v) >> 16) & 0xffff)
/**
 * 32ビットにする。
 * @param h High側16ビット。D31-D16に配置される。
 * @param l Low側16ビット。D15-D0に配置される。
 */
#define FORM32BITS(h, l) (                              \
	(uint32_t)(((((uint32_t)(h)) << 16) & 0xffff0000) | \
			   ((((uint32_t)(l)) << 0) & 0x0000ffff)))

/**
 * bit 3 - 0 を取得する。
 */
#define BITS0300(v) (uint8_t)(((v) >> 0) & 0x0f)
/**
 * bit 7 - 4 を取得する。
 */
#define BITS0704(v) (uint8_t)(((v) >> 4) & 0x0f)
/**
 * 8ビットにする。
 * @param h High側4ビット。D7-D4に配置される。
 * @param l Low側4ビット。D3-D0に配置される。
 */
#define FORM8BITS(h, l) (                      \
	(uint8_t)(((((uint8_t)(h)) << 4) & 0xf0) | \
			  ((((uint8_t)(l)) << 0) & 0x0f)))

/**
 * bit 31 - 0 を取得する。
 */
#define BITS3100(v) ((uint32_t)(((v) >> 0) & 0xffffffff))
/**
 * bit 63 - 32 を取得する。
 */
#define BITS6332(v) ((uint32_t)(((v) >> 32) & 0xffffffff))
/**
 * 64ビット値にする。
 * @param h High側32ビット。D63-D32配置される。
 * @param l Low側32ビット。D31-D0に配置される。
 */
#define FORM64BITS(h, l) (                                         \
	(uint64_t)(((((uint64_t)(h)) << 32) & 0xffffffff00000000ULL) | \
			   ((((uint64_t)(l)) << 0) & 0x00000000ffffffffULL)))

/* --------------------------------------------------------------------------
 *  P U B L I C   I N T E R F A C E S
 */

#ifdef __cplusplus
extern "C"
{
#endif
#ifdef _UNIT_TEST
	void bits_UnitTest(void);
#endif

#ifdef __cplusplus
}
#endif

#endif
