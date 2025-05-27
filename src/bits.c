/** -------------------------------------------------------------------------
 *
 *	@file	bits.c
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
#include "bits.h"

/* --------------------------------------------------------------------------
 *  P R I V A T E S
 */

/* --------------------------------------------------------------------------
 *  P U B L I C   I N T E R F A C E S
 */

/* -------------------------------------------------------------------
 *	Unit Test
 */
#ifdef _UNIT_TEST
#include "Assertions.h"

void bits_UnitTest(void)
{
	Assertions *assertions = Assertions_Instance();

	// -----------------------------------------
	// 1-1 BITS0700
	Assertions_Assert(BITS0700(0x1234) == 0x34, assertions);
	// -----------------------------------------
	// 2-1 BITS1508
	Assertions_Assert(BITS1508(0x1234) == 0x12, assertions);
	// -----------------------------------------
	// 3-1 FORM16BITS
	Assertions_Assert(FORM16BITS(0x12, 0x34) == 0x1234, assertions);

	// -----------------------------------------
	// 4-1 BITS1500
	Assertions_Assert(BITS1500(0x12345678) == 0x5678, assertions);
	// -----------------------------------------
	// 5-1 BITS3116
	Assertions_Assert(BITS3116(0x12345678) == 0x1234, assertions);
	// -----------------------------------------
	// 6-1 FORM32BITS
	Assertions_Assert(FORM32BITS(0x1234, 0x5678) == 0x12345678, assertions);

	// -----------------------------------------
	// 7-1 BITS0300
	Assertions_Assert(BITS0300(0x12) == 0x2, assertions);
	// -----------------------------------------
	// 8-1 BITS0704
	Assertions_Assert(BITS0704(0x12) == 0x1, assertions);
	// -----------------------------------------
	// 9-1 FORM16BITS
	Assertions_Assert(FORM8BITS(0x1, 0x2) == 0x12, assertions);

	// -----------------------------------------
	// 10-1 BITS3100
	Assertions_Assert(BITS3100(0x0123456789abcdef) == 0x89abcdef, assertions);
	// -----------------------------------------
	// 11-1 BITS6332
	Assertions_Assert(BITS6332(0x0123456789abcdef) == 0x01234567, assertions);
	// -----------------------------------------
	// 12-1 FORM64BITS
	Assertions_Assert(
		FORM64BITS(0x01234567, 0x89abcdef) == 0x0123456789abcdef, assertions);
}

#endif
