#ifndef __Decoders_H__
#define __Decoders_H__

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
#include <stdint.h>

/* --------------------------------------------------------------------------
 *  P U B L I C   D E F I N I T I O N S
 */

/**
 * inline
 */
#define DECODERS_INLINE static inline

/* --------------------------------------------------------------------------
 *  P U B L I C   I N T E R F A C E S
 */

#ifdef __cplusplus
extern "C"
{
#endif

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
		const void *src, int32_t srcSize);

	/**
	 *  @brief 16ビットデコード @n
	 *    16ビットの値をデコードする。 @n
	 *    デコード元バッファは、Decoders_CanDecodeによりチェックしておくこと。
	 *    ここではデコード元バッファのチェックは行わない。
	 *  @param index デコード元のインデックス。
	 *  @param src デコード元バッファ。
	 *  @param bigEndian 非0でBig Endianでエンコードする。
	 *  @return デコードした値。
	 */
	DECODERS_INLINE int32_t Decoders_16At(
		int32_t index,
		const void *src,
		int bigEndian)
	{
		int32_t result = 0L;
		uint8_t *buffer = (uint8_t *)src;
		if (bigEndian != 0)
		{
			result = (buffer[index + 0] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 1] & 0xffL);
		}
		else
		{
			result = (buffer[index + 1] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 0] & 0xffL);
		}
		return result;
	}

	/**
	 *  @brief チェック付き16ビットデコード @n
	 *    16ビットの値をデコードする。 @n
	 *    デコード元バッファのチェックを行い、不正の場合にはデフォルト値を返す。
	 *  @param index デコード元のインデックス。
	 *  @param src デコード元バッファ。
	 *  @param srcSize デコード元バッファのサイズ。
	 *  @param orDefault デコードできない場合のデフォルト値。
	 *  @param bigEndian 非0でBig Endianでエンコードする。
	 *  @return デコードした値。
	 */
	DECODERS_INLINE int32_t Decoders_Defaulted16At(
		int32_t index,
		const void *src, int32_t srcSize,
		int32_t orDefault,
		int bigEndian)
	{
		int32_t result = orDefault;
		if (Decoders_CanDecode(index + 2, src, srcSize))
		{
			result = Decoders_16At(index, src, bigEndian);
		}
		return result;
	}

	/**
	 *  @brief 32ビットデコード @n
	 *    32ビットの値をデコードする。 @n
	 *    デコード元バッファは、Decoders_CanDecodeによりチェックしておくこと。
	 *    ここではデコード元バッファのチェックは行わない。
	 *  @param index デコード元のインデックス。
	 *  @param src デコード元バッファ。
	 *  @param bigEndian 非0でBig Endianでエンコードする。
	 *  @return デコードした値。
	 */
	DECODERS_INLINE int32_t Decoders_32At(
		int32_t index,
		const void *src,
		int bigEndian)
	{
		int32_t result = 0L;
		uint8_t *buffer = (uint8_t *)src;
		if (bigEndian != 0)
		{
			result = (buffer[index + 0] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 1] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 2] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 3] & 0xffL);
		}
		else
		{
			result = (buffer[index + 3] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 2] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 1] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 0] & 0xffL);
		}
		return result;
	}

	/**
	 *  @brief チェック付き32ビットデコード @n
	 *    32ビットの値をデコードする。 @n
	 *    デコード元バッファのチェックを行い、不正の場合にはデフォルト値を返す。
	 *  @param index デコード元のインデックス。
	 *  @param src デコード元バッファ。
	 *  @param srcSize デコード元バッファのサイズ。
	 *  @param orDefault デコードできない場合のデフォルト値。
	 *  @param bigEndian 非0でBig Endianでエンコードする。
	 *  @return デコードした値。
	 */
	DECODERS_INLINE int32_t Decoders_Defaulted32At(
		int32_t index,
		const void *src, int32_t srcSize,
		int32_t orDefault,
		int bigEndian)
	{
		int32_t result = orDefault;
		if (Decoders_CanDecode(index + 4, src, srcSize))
		{
			result = Decoders_32At(index, src, bigEndian);
		}
		return result;
	}

	/**
	 *  @brief 64ビットデコード @n
	 *    64ビットの値をデコードする。 @n
	 *    デコード元バッファは、Decoders_CanDecodeによりチェックしておくこと。
	 *    ここではデコード元バッファのチェックは行わない。
	 *  @param index デコード元のインデックス。
	 *  @param src デコード元バッファ。
	 *  @param bigEndian 非0でBig Endianでエンコードする。
	 *  @return デコードした値。
	 */
	DECODERS_INLINE int64_t Decoders_64At(
		int32_t index,
		const void *src,
		int bigEndian)
	{
		int64_t result = 0L;
		uint8_t *buffer = (uint8_t *)src;
		if (bigEndian != 0)
		{
			result = (buffer[index + 0] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 1] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 2] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 3] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 4] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 5] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 6] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 7] & 0xffL);
		}
		else
		{
			result = (buffer[index + 7] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 6] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 5] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 4] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 3] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 2] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 1] & 0xffL);
			result <<= 8;
			result |= (buffer[index + 0] & 0xffL);
		}
		return result;
	}

	/**
	 *  @brief チェック付き64ビットデコード @n
	 *    64ビットの値をデコードする。 @n
	 *    デコード元バッファのチェックを行い、不正の場合にはデフォルト値を返す。
	 *  @param index デコード元のインデックス。
	 *  @param src デコード元バッファ。
	 *  @param srcSize デコード元バッファのサイズ。
	 *  @param orDefault デコードできない場合のデフォルト値。
	 *  @param bigEndian 非0でBig Endianでエンコードする。
	 *  @return デコードした値。
	 */
	DECODERS_INLINE int64_t Decoders_Defaulted64At(
		int32_t index,
		const void *src, int32_t srcSize,
		int64_t orDefault,
		int bigEndian)
	{
		int64_t result = orDefault;
		if (Decoders_CanDecode(index + 8, src, srcSize))
		{
			result = Decoders_64At(index, src, bigEndian);
		}
		return result;
	}

#ifdef _UNIT_TEST
	void Decoders_UnitTest(void);
#endif

#ifdef __cplusplus
}
#endif

#endif
