/** ------------------------------------------------------------------
 *
 *	@file	Encoders.c
 *	@brief	Encoders
 *	@author	H.Someya
 *	@date	2023/05/12
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
#include "Encoders.h"

#include "nullptr.h"

/*----------------------------------------------------------------------
 *  P R I V A T E S
 */
/*----------------------------------------------------------------------
 *  P U B L I C   I N T E R F A C E S
 */

/**
 *  @brief エンコード可能判定 @n
 *    編集先のバッファがエンコード可能か判定する。
 *  @param neededSize エンコードに必要なサイズ。
 *  @param dest エンコード先バッファ。
 *  @param destSize エンコード先バッファのサイズ。
 *  @return 0:不可、非0:可能。
 */
int Encoders_CanEncode(
	int32_t neededSize,
	const void *dest, int32_t destSize)
{
	int result = 0;
	if ((dest != nullptr) &&
		(destSize >= neededSize))
	{
		result = 1;
	}
	return result;
}

/**
 *  @brief 16ビットエンコード @n
 *    16ビットの値をエンコードする。 @n
 *    エンコード先バッファは、Encoders_CanEncodeによりチェックしておくこと。
 *    ここではエンコード先バッファのチェックは行わない。
 *  @param index エンコード先のインデックス。
 *  @param value エンコードする値。
 *  @param bigEndian 非0でBig Endianでエンコードする。
 *  @param dest エンコード先バッファ。
 *  @return なし。
 */
void Encoders_Encode16At(
	int32_t index,
	int32_t value,
	int bigEndian,
	void *dest)
{
	uint8_t *buffer = (uint8_t *)dest;
	if (bigEndian != 0)
	{
		buffer[index + 1] = (uint8_t)value;
		value >>= 8;
		buffer[index + 0] = (uint8_t)value;
	}
	else
	{
		buffer[index + 0] = (uint8_t)value;
		value >>= 8;
		buffer[index + 1] = (uint8_t)value;
	}
}

/**
 *  @brief 32ビットエンコード @n
 *    32ビットの値をエンコードする。 @n
 *    エンコード先バッファは、Encoders_CanEncodeによりチェックしておくこと。
 *    ここではエンコード先バッファのチェックは行わない。
 *  @param index エンコード先のインデックス。
 *  @param value エンコードする値。
 *  @param bigEndian 非0でBig Endianでエンコードする。
 *  @param dest エンコード先バッファ。
 *  @return なし。
 */
void Encoders_Encode32At(
	int32_t index,
	int32_t value,
	int bigEndian,
	void *dest)
{
	uint8_t *buffer = (uint8_t *)dest;
	if (bigEndian != 0)
	{
		buffer[index + 3] = (uint8_t)value;
		value >>= 8;
		buffer[index + 2] = (uint8_t)value;
		value >>= 8;
		buffer[index + 1] = (uint8_t)value;
		value >>= 8;
		buffer[index + 0] = (uint8_t)value;
	}
	else
	{
		buffer[index + 0] = (uint8_t)value;
		value >>= 8;
		buffer[index + 1] = (uint8_t)value;
		value >>= 8;
		buffer[index + 2] = (uint8_t)value;
		value >>= 8;
		buffer[index + 3] = (uint8_t)value;
	}
}

/**
 *  @brief 64ビットエンコード @n
 *    64ビットの値をエンコードする。 @n
 *    エンコード先バッファは、Encoders_CanEncodeによりチェックしておくこと。
 *    ここではエンコード先バッファのチェックは行わない。
 *  @param index エンコード先のインデックス。
 *  @param value エンコードする値。
 *  @param bigEndian 非0でBig Endianでエンコードする。
 *  @param dest エンコード先バッファ。
 *  @return なし。
 */
void Encoders_Encode64At(
	int32_t index,
	int64_t value,
	int bigEndian,
	void *dest)
{
	uint8_t *buffer = (uint8_t *)dest;
	if (bigEndian != 0)
	{
		buffer[index + 7] = (uint8_t)value;
		value >>= 8;
		buffer[index + 6] = (uint8_t)value;
		value >>= 8;
		buffer[index + 5] = (uint8_t)value;
		value >>= 8;
		buffer[index + 4] = (uint8_t)value;
		value >>= 8;
		buffer[index + 3] = (uint8_t)value;
		value >>= 8;
		buffer[index + 2] = (uint8_t)value;
		value >>= 8;
		buffer[index + 1] = (uint8_t)value;
		value >>= 8;
		buffer[index + 0] = (uint8_t)value;
	}
	else
	{
		buffer[index + 0] = (uint8_t)value;
		value >>= 8;
		buffer[index + 1] = (uint8_t)value;
		value >>= 8;
		buffer[index + 2] = (uint8_t)value;
		value >>= 8;
		buffer[index + 3] = (uint8_t)value;
		value >>= 8;
		buffer[index + 4] = (uint8_t)value;
		value >>= 8;
		buffer[index + 5] = (uint8_t)value;
		value >>= 8;
		buffer[index + 6] = (uint8_t)value;
		value >>= 8;
		buffer[index + 7] = (uint8_t)value;
	}
}

/* -------------------------------------------------------------------
 *	Unit Test
 */
#ifdef _UNIT_TEST

#include <string.h>
#include "Assertions.h"

void Encoders_UnitTest(void)
{
	Assertions *ast = Assertions_Instance();

	int canEncode;
	uint8_t dest[15];

	// -----------------------------------------
	// 1-x Encoders_CanEncode
	// -----------------------------------------
	// 1-1 destがNULLだと不可
	canEncode = Encoders_CanEncode(0, nullptr, 0);
	Assertions_Assert(canEncode == 0, ast);
	// -----------------------------------------
	// 1-2 サイズが足りないと不可
	canEncode = Encoders_CanEncode((sizeof dest) + 1, &dest[0], sizeof dest);
	Assertions_Assert(canEncode == 0, ast);
	// -----------------------------------------
	// 1-3 サイズ足りればOK
	canEncode = Encoders_CanEncode(sizeof dest, &dest[0], sizeof dest);
	Assertions_Assert(canEncode != 0, ast);

	// -----------------------------------------
	// 2-x Encoders_Encode16At
	// -----------------------------------------
	// 2-1 リトルエンディアン
	memset(dest, 0, sizeof dest);
	Encoders_Encode16At(1, 0x1234, 0, dest);
	Assertions_Assert(dest[0] == 0x00, ast);
	Assertions_Assert(dest[1] == 0x34, ast);
	Assertions_Assert(dest[2] == 0x12, ast);
	Assertions_Assert(dest[3] == 0x00, ast);
	// -----------------------------------------
	// 2-2 ビッグエンディアン
	memset(dest, 0, sizeof dest);
	Encoders_Encode16At(1, 0x1234, 1, dest);
	Assertions_Assert(dest[0] == 0x00, ast);
	Assertions_Assert(dest[1] == 0x12, ast);
	Assertions_Assert(dest[2] == 0x34, ast);
	Assertions_Assert(dest[3] == 0x00, ast);

	// -----------------------------------------
	// 3-x Encoders_Encode32At
	// -----------------------------------------
	// 3-1 リトルエンディアン
	memset(dest, 0, sizeof dest);
	Encoders_Encode32At(1, 0x1234abcd, 0, dest);
	Assertions_Assert(dest[0] == 0x00, ast);
	Assertions_Assert(dest[1] == 0xcd, ast);
	Assertions_Assert(dest[2] == 0xab, ast);
	Assertions_Assert(dest[3] == 0x34, ast);
	Assertions_Assert(dest[4] == 0x12, ast);
	Assertions_Assert(dest[5] == 0x00, ast);
	// -----------------------------------------
	// 3-2 ビッグエンディアン
	memset(dest, 0, sizeof dest);
	Encoders_Encode32At(1, 0x1234abcd, 1, dest);
	Assertions_Assert(dest[0] == 0x00, ast);
	Assertions_Assert(dest[1] == 0x12, ast);
	Assertions_Assert(dest[2] == 0x34, ast);
	Assertions_Assert(dest[3] == 0xab, ast);
	Assertions_Assert(dest[4] == 0xcd, ast);
	Assertions_Assert(dest[5] == 0x00, ast);

	// -----------------------------------------
	// 4-x Encoders_Encode64At
	// -----------------------------------------
	// 4-1 リトルエンディアン
	memset(dest, 0, sizeof dest);
	Encoders_Encode64At(1, 0x1234abcd5678fedcLL, 0, dest);
	Assertions_Assert(dest[0] == 0x00, ast);
	Assertions_Assert(dest[1] == 0xdc, ast);
	Assertions_Assert(dest[2] == 0xfe, ast);
	Assertions_Assert(dest[3] == 0x78, ast);
	Assertions_Assert(dest[4] == 0x56, ast);
	Assertions_Assert(dest[5] == 0xcd, ast);
	Assertions_Assert(dest[6] == 0xab, ast);
	Assertions_Assert(dest[7] == 0x34, ast);
	Assertions_Assert(dest[8] == 0x12, ast);
	Assertions_Assert(dest[9] == 0x00, ast);
	// -----------------------------------------
	// 4-2 ビッグエンディアン
	memset(dest, 0, sizeof dest);
	Encoders_Encode64At(1, 0x1234abcd5678fedcLL, 1, dest);
	Assertions_Assert(dest[0] == 0x00, ast);
	Assertions_Assert(dest[1] == 0x12, ast);
	Assertions_Assert(dest[2] == 0x34, ast);
	Assertions_Assert(dest[3] == 0xab, ast);
	Assertions_Assert(dest[4] == 0xcd, ast);
	Assertions_Assert(dest[5] == 0x56, ast);
	Assertions_Assert(dest[6] == 0x78, ast);
	Assertions_Assert(dest[7] == 0xfe, ast);
	Assertions_Assert(dest[8] == 0xdc, ast);
	Assertions_Assert(dest[9] == 0x00, ast);
}
#endif
