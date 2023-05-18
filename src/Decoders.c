/** -------------------------------------------------------------------------
 *
 *	@file	Decoders.h
 *	@brief	Decoders
 *	@author	H.Someya
 *	@date	2023/05/18
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
#include "Decoders.h"

#include "nullptr.h"

/* --------------------------------------------------------------------------
 *  P R I V A T E S
 */

/* --------------------------------------------------------------------------
 *  P U B L I C   I N T E R F A C E S
 */

/**
 *  @brief デコード可能判定 @n
 *    デコード元のバッファがデコード可能か判定する。
 *  @param neededSize デコードに必要なサイズ。
 *  @param src デコード元バッファ。
 *  @param srcSize デコード元バッファのサイズ。
 *  @return 0:不可、非0:可能。
 */
int Decoders_CanDecode(
	int32_t neededSize,
	const void *src, int32_t srcSize)
{
	int result = 0;
	if ((src != nullptr) &&
		(srcSize >= neededSize))
	{
		result = 1;
	}
	return result;
}

/* --------------------------------------------------------------------------
 *  Unit Test
 */
#ifdef _UNIT_TEST

#include <string.h>
#include "Assertions.h"

void Decoders_UnitTest(void)
{
	Assertions *ast = Assertions_Instance();

	int canDecode;
	uint8_t src[11];
	int32_t val32;
	int64_t val64;

	// -----------------------------------------
	// 1-x Decoders_CanDecode
	// -----------------------------------------
	// 1-1 srcがnullだと不可
	canDecode = Decoders_CanDecode(0, nullptr, 0);
	Assertions_Assert(canDecode == 0, ast);
	// -----------------------------------------
	// 1-2 サイズが足りないと不可
	canDecode = Decoders_CanDecode((sizeof src) + 1, &src[0], sizeof src);
	Assertions_Assert(canDecode == 0, ast);
	// -----------------------------------------
	// 1-3 サイズ足りればOK
	canDecode = Decoders_CanDecode(sizeof src, &src[0], sizeof src);
	Assertions_Assert(canDecode != 0, ast);

	// -----------------------------------------
	// 2-x Decoders_16At
	// -----------------------------------------
	// 2-1 リトルエンディアン
	src[3] = 0x12;
	src[4] = 0x34;
	val32 = Decoders_16At(3, src, 0);
	Assertions_Assert(val32 == 0x3412, ast);
	// -----------------------------------------
	// 2-2 ビッグエンディアン
	src[3] = 0x12;
	src[4] = 0x34;
	val32 = Decoders_16At(3, src, 1);
	Assertions_Assert(val32 == 0x1234, ast);

	// -----------------------------------------
	// 3-x Decoders_Defaulted16At
	// -----------------------------------------
	// 3-1 リトルエンディアン
	src[9] = 0xab;
	src[10] = 0xcd;
	val32 = Decoders_Defaulted16At(9, src, sizeof src, -1, 0);
	Assertions_Assert(val32 == 0xcdab, ast);
	// -----------------------------------------
	// 3-2 ビッグエンディアン
	src[9] = 0xab;
	src[10] = 0xcd;
	val32 = Decoders_Defaulted16At(9, src, sizeof src, -1, 1);
	Assertions_Assert(val32 == 0xabcd, ast);
	// -----------------------------------------
	// 3-3 srcがnull
	src[9] = 0xab;
	src[10] = 0xcd;
	val32 = Decoders_Defaulted16At(9, nullptr, sizeof src, -1, 1);
	Assertions_Assert(val32 == -1, ast);
	// -----------------------------------------
	// 3-4 サイズが足りない
	src[9] = 0xab;
	src[10] = 0xcd;
	val32 = Decoders_Defaulted16At(10, src, sizeof src, -1, 1);
	Assertions_Assert(val32 == -1, ast);

	// -----------------------------------------
	// 4-x Decoders_32At
	// -----------------------------------------
	// 4-1 リトルエンディアン
	src[6] = 0x12;
	src[7] = 0x34;
	src[8] = 0x56;
	src[9] = 0x78;
	val32 = Decoders_32At(6, src, 0);
	Assertions_Assert(val32 == 0x78563412, ast);
	// -----------------------------------------
	// 4-2 ビッグエンディアン
	src[6] = 0x12;
	src[7] = 0x34;
	src[8] = 0x56;
	src[9] = 0x78;
	val32 = Decoders_32At(6, src, 1);
	Assertions_Assert(val32 == 0x12345678, ast);

	// -----------------------------------------
	// 5-x Decoders_Defaulted32At
	// -----------------------------------------
	// 5-1 リトルエンディアン
	src[7] = 0x12;
	src[8] = 0x34;
	src[9] = 0x56;
	src[10] = 0x78;
	val32 = Decoders_Defaulted32At(7, src, sizeof src, -1, 0);
	Assertions_Assert(val32 == 0x78563412, ast);
	// -----------------------------------------
	// 5-2 ビッグエンディアン
	src[7] = 0x12;
	src[8] = 0x34;
	src[9] = 0x56;
	src[10] = 0x78;
	val32 = Decoders_Defaulted32At(7, src, sizeof src, -1, 1);
	Assertions_Assert(val32 == 0x12345678, ast);
	// -----------------------------------------
	// 5-3 srcがnull
	src[7] = 0x12;
	src[8] = 0x34;
	src[9] = 0x56;
	src[10] = 0x78;
	val32 = Decoders_Defaulted32At(7, nullptr, sizeof src, -1, 1);
	Assertions_Assert(val32 == -1, ast);
	// -----------------------------------------
	// 5-4 サイズが足りない
	src[7] = 0x12;
	src[8] = 0x34;
	src[9] = 0x56;
	src[10] = 0x78;
	val32 = Decoders_Defaulted32At(8, src, sizeof src, -1, 1);
	Assertions_Assert(val32 == -1, ast);

	// -----------------------------------------
	// 6-x Decoders_64At
	// -----------------------------------------
	// 6-1 リトルエンディアン
	src[1] = 0x12;
	src[2] = 0x34;
	src[3] = 0x56;
	src[4] = 0x78;
	src[5] = 0x9a;
	src[6] = 0xbc;
	src[7] = 0xde;
	src[8] = 0xf0;
	val64 = Decoders_64At(1, src, 0);
	Assertions_Assert(val64 == 0xf0debc9a78563412LL, ast);
	// -----------------------------------------
	// 6-2 ビッグエンディアン
	src[1] = 0x12;
	src[2] = 0x34;
	src[3] = 0x56;
	src[4] = 0x78;
	src[5] = 0x9a;
	src[6] = 0xbc;
	src[7] = 0xde;
	src[8] = 0xf0;
	val64 = Decoders_64At(1, src, 1);
	Assertions_Assert(val64 == 0x123456789abcdef0LL, ast);

	// -----------------------------------------
	// 7-x Decoders_Defaulted64At
	// -----------------------------------------
	// 7-1 リトルエンディアン
	src[3] = 0xab;
	src[4] = 0xcd;
	src[5] = 0xef;
	src[6] = 0x01;
	src[7] = 0x23;
	src[8] = 0x45;
	src[9] = 0x67;
	src[10] = 0x89;
	val64 = Decoders_Defaulted64At(3, src, sizeof src, -1, 0);
	Assertions_Assert(val64 == 0x8967452301efcdabLL, ast);
	// -----------------------------------------
	// 7-2 ビッグエンディアン
	src[3] = 0xab;
	src[4] = 0xcd;
	src[5] = 0xef;
	src[6] = 0x01;
	src[7] = 0x23;
	src[8] = 0x45;
	src[9] = 0x67;
	src[10] = 0x89;
	val64 = Decoders_Defaulted64At(3, src, sizeof src, -1, 1);
	Assertions_Assert(val64 == 0xabcdef0123456789LL, ast);
	// -----------------------------------------
	// 7-3 srcがnull
	src[3] = 0xab;
	src[4] = 0xcd;
	src[5] = 0xef;
	src[6] = 0x01;
	src[7] = 0x23;
	src[8] = 0x45;
	src[9] = 0x67;
	src[10] = 0x89;
	val64 = Decoders_Defaulted64At(3, nullptr, sizeof src, -1, 1);
	Assertions_Assert(val64 == -1, ast);
	// -----------------------------------------
	// 7-4 サイズが足りない
	src[3] = 0xab;
	src[4] = 0xcd;
	src[5] = 0xef;
	src[6] = 0x01;
	src[7] = 0x23;
	src[8] = 0x45;
	src[9] = 0x67;
	src[10] = 0x89;
	val64 = Decoders_Defaulted64At(4, src, sizeof src, -1, 1);
	Assertions_Assert(val64 == -1, ast);
}
#endif
