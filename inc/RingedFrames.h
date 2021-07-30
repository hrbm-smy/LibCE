#ifndef RingedFrames_h
#define RingedFrames_h
/** ------------------------------------------------------------------
*
*	@file	RingedFrames.h
*	@brief	フレームリングバッファ
*	@author	H.Someya
*	@date	2021/07/28
*
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
*
*/
#include <stdint.h>

/* -------------------------------------------------------------------
*	Definitions
*/

/// <summary>
/// <para>フレームヘッダのサイズ。</para>
/// </summary>
#define RF_FRAME_HEADER_SIZE (10)

/// <summary>
/// <para>ストライド幅(切り上げられた1フレームあたりのワード数)を取得する。</para>
/// </summary>
/// <param name="frameSize">最大フレームサイズ。</param>
#define RF_STRIDE_WORDS(frameSize) \
	(((RF_FRAME_HEADER_SIZE + (frameSize) - 1) / 4) + 1)

/// <summary>
/// <para>バッファに必要なワード数を取得する。</para>
/// </summary>
/// <param name="capacity">最大蓄積可能フレーム数。</param>
/// <param name="frameSize">最大フレームサイズ。</param>
#define RF_NEEDED_BUFFER_WORDS(capacity, frameSize) \
	(RF_STRIDE_WORDS(frameSize) * (capacity))

#ifdef __cplusplus
extern "C"
{
#endif
	/* -------------------------------------------------------------------
	*	Services
	*/

	/// <summary>
	/// <para>フレームリングバッファ</para>
	/// </summary>
	typedef struct _RingedFrames
	{
		/// <summary>インデックス位置</summary>
		int32_t Index;
		/// <summary>フレーム蓄積数</summary>
		int32_t Count;
		/// <summary>フレーム更新数(Pushされた数)</summary>
		int64_t UpdateCount;
		/// <summary>最大蓄積可能フレーム数</summary>
		int32_t Capacity;
		/// <summary>最大フレームサイズ</summary>
		int32_t FrameSize;
		/// <summary>蓄積先バッファ</summary>
		int32_t* Buffer;
	} RingedFrames;

	void RingedFrames_UnitTest(void);

#ifdef __cplusplus
}
#endif

#endif // top
