#ifndef RingedFrames_h
#define RingedFrames_h
/** ------------------------------------------------------------------
*
*	@file	RingedFrames.h
*	@brief	Frame ring buffer
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
#define RF_FRAME_HEADER_SIZE (12)

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

	/// <summary>
	/// <para>フレームリングバッファを初期化する。</para>
	/// </summary>
	/// <param name="capacity">最大蓄積可能フレーム数。</param>
	/// <param name="frameSize">最大フレームサイズ。</param>
	/// <param name="buffer">動作に必要なバッファ。
	/// RF_NEEDED_BUFFER_WORDS分の要素数を持つ領域を確保して指定すること。</param>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>なし。</returns>
	void RingedFrames_Init(
		int32_t capacity, int32_t frameSize,
		int32_t* buffer,
		RingedFrames* ctxt);

	/// <summary>
	/// <para>クリアする。</para>
	/// </summary>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>なし。</returns>
	void RingedFrames_Clear(
		RingedFrames* ctxt);

	/// <summary>
	/// <para>現在のフレーム蓄積数を取得する。</para>
	/// </summary>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>現在のフレーム蓄積数。</returns>
	int32_t RingedFrames_Count(
		const RingedFrames* ctxt);

	/// <summary>
	/// <para>現在のフレーム更新数を取得する。</para>
	/// <para>フレームリングバッファは最古を上書きするが、蓄積数は最大で停止する。</para>
	/// <para>更新数は、最大蓄積数を蓄積した後でも更新される。</para>
	/// </summary>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>現在のフレーム更新数。</returns>
	int64_t RingedFrames_UpdateCount(
		const RingedFrames* ctxt);

	/// <summary>
	/// <para>最大蓄積可能フレーム数を取得する。</para>
	/// </summary>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>最大蓄積可能フレーム数。</returns>
	int32_t RingedFrames_Capacity(
		const RingedFrames* ctxt);

	/// <summary>
	/// <para>最大フレームサイズを取得する。</para>
	/// </summary>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>最大フレームサイズ。</returns>
	int32_t RingedFrames_FrameSize(
		const RingedFrames* ctxt);

	/// <summary>
	/// <para>フレームをPushする。</para>
	/// <para>最大蓄積可能フレーム数まで蓄積されていると、最古を上書きする。</para>
	/// </summary>
	/// <param name="frame">フレーム。</param>
	/// <param name="length">フレームの長さ。</param>
	/// <param name="timestamp">タイムスタンプ。</param>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>なし。</returns>
	void RingedFrames_Push(
		const void* frame, int32_t length,
		int64_t timestamp,
		RingedFrames* ctxt);

	/// <summary>
	/// <para>最古を0としたインデックスで、フレームを参照する。</para>
	/// <para>コピーせず、内部メモリを直接参照する。</para>
	/// </summary>
	/// <param name="index">最古を0としたインデックス。</param>
	/// <param name="length">フレーム長の格納先。</param>
	/// <param name="timestamp">タイムスタンプの格納先。</param>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>フレーム。nullでなし。</returns>
	const void* RingedFrames_ReferWithOld(
		int32_t index,
		int32_t* length,
		int64_t* timestamp,
		const RingedFrames* ctxt);

	/// <summary>
	/// <para>最新を0としたインデックスで、フレームを参照する。</para>
	/// <para>コピーせず、内部メモリを直接参照する。</para>
	/// </summary>
	/// <param name="index">最新を0としたインデックス。</param>
	/// <param name="length">フレーム長の格納先。</param>
	/// <param name="timestamp">タイムスタンプの格納先。</param>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>フレーム。nullでなし。</returns>
	const void* RingedFrames_ReferWithNew(
		int32_t index,
		int32_t* length,
		int64_t* timestamp,
		const RingedFrames* ctxt);

	/// <summary>
	/// <para>最古のフレームをPopする。</para>
	/// <para>フレームが無い場合は負を返す。</para>
	/// <para>格納先が足りない場合は、格納できる分だけ返す。</para>
	/// </summary>
	/// <param name="buffer">フレームの格納先バッファ。</param>
	/// <param name="bufferSize">フレーム格納先バッファのサイズ。</param>
	/// <param name="timestamp">タイムスタンプの格納先。</param>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>フレーム長。</returns>
	int32_t RingedFrames_Pop(
		void* buffer, int32_t bufferSize,
		int64_t* timestamp,
		RingedFrames* ctxt);

#ifdef _UNIT_TEST
	void RingedFrames_UnitTest(void);
#endif

#ifdef __cplusplus
}
#endif

#endif // top
