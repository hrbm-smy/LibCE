#ifndef __Encoders_H__
#define __Encoders_H__

/** ------------------------------------------------------------------
 *
 *	@file	Encoders.h
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
#include <stdint.h>

/*----------------------------------------------------------------------
 *  P U B L I C   D E F I N I T I O N S
 */

/*----------------------------------------------------------------------
 *  P U B L I C   I N T E R F A C E S
 */

#ifdef __cplusplus
extern "C"
{
#endif

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
		const void *dest, int32_t destSize);

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
		void *dest);

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
		void *dest);

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
		void *dest);

#ifdef _UNIT_TEST
	void Encoders_UnitTest(void);
#endif

#ifdef __cplusplus
}
#endif

#endif
