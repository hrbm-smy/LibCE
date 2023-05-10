/** ------------------------------------------------------------------
 *
 *	@file	MmIo.c
 *	@brief	Memory Mapped I/O
 *	@author	H.Someya
 *	@date	2023/05/09
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
#include "MmIo.h"

/*----------------------------------------------------------------------
 *  P R I V A T E S
 */
/*----------------------------------------------------------------------
 *  P U B L I C   I N T E R F A C E S
 */

/**
 *  @brief Few bits I/O data writer @n
 *    Write few bits to base + offset.
 *  @param value Write value.
 *  @param bitStart Bit start index.
 *  @param bitCount Bit count.
 *  @param base Base address.
 *  @param offset Offset to the base address.
 *  @return Wrote value, not a device read value.
 */
uint32_t MmIo_WriteBitsU32(
	uint32_t value,
	int32_t bitStart, int32_t bitCount,
	uintptr_t base, uintptr_t offset)
{
	uint32_t result = 0;

	uint32_t mask = ~0;
	mask <<= (32 - bitCount);
	mask >>= ((32 - bitCount) - bitStart);

	uint32_t d = MmIo_ReadU32(base, offset);
	d &= ~mask;
	d |= ((value << bitStart) & mask);
	MmIo_WriteU32(d, base, offset);
	result = d;

	return result;
}

#ifdef _UNIT_TEST
#include "Assertions.h"
void MmIo_UnitTest(void)
{
	Assertions *ast = Assertions_Instance();

	uint32_t ioArea[4];
#define IOBASE (uintptr_t)(&ioArea[0])

	ioArea[0] = 0x11223344;
	ioArea[1] = 0x55667788;
	ioArea[2] = 0x99aabbcc;
	ioArea[3] = 0xddeeff00;

	/*
	1-x MmIo_ReadU32
	*/
	/*
	1-1 MmIo_ReadU32
	*/
	Assertions_Assert(MmIo_ReadU32(IOBASE, 0) == 0x11223344, ast);
	/*
	1-2 MmIo_ReadU32
	*/
	Assertions_Assert(MmIo_ReadU32(IOBASE, 0xc) == 0xddeeff00, ast);

	/*
	2-x MmIo_WriteU32
	*/
	/*
	2-1 MmIo_WriteU32
	*/
	MmIo_WriteU32(0x01234567, IOBASE, 0);
	Assertions_Assert(MmIo_ReadU32(IOBASE, 0) == 0x01234567, ast);
	/*
	2-2 MmIo_WriteU32
	*/
	MmIo_WriteU32(0xfedcba98, IOBASE, 0x8);
	Assertions_Assert(MmIo_ReadU32(IOBASE, 0x8) == 0xfedcba98, ast);

	/*
	3-x MmIo_WriteBitsU32
	*/
	/*
	3-1 MmIo_WriteBitsU32
	*/
	MmIo_WriteBitsU32(0xab, 24, 8, IOBASE, 0x8);
	Assertions_Assert(MmIo_ReadU32(IOBASE, 0x8) == 0xabdcba98, ast);
	/*
	3-2 MmIo_WriteBitsU32
	*/
	MmIo_WriteBitsU32(0xef, 8, 8, IOBASE, 0x8);
	Assertions_Assert(MmIo_ReadU32(IOBASE, 0x8) == 0xabdcef98, ast);
	/*
	3-2 MmIo_WriteBitsU32
	*/
	MmIo_WriteBitsU32(0x89, 4, 8, IOBASE, 0x8);
	Assertions_Assert(MmIo_ReadU32(IOBASE, 0x8) == 0xabdce898, ast);
}
#endif
