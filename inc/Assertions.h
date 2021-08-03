#ifndef Assertions_h
#define Assertions_h
/** ------------------------------------------------------------------
*
*	@file	Assertions.h
*	@brief	Storable assertions
*	@author	H.Someya
*	@date	2021/08/02
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
#include "RingedFrames.h"

/* -------------------------------------------------------------------
*	Definitions
*/

/// <summary>
/// <para>バッファに必要なワード数を取得する。</para>
/// </summary>
/// <param name="capacity">最大蓄積可能フレーム数。</param>
/// <param name="frameSize">最大フレームサイズ。</param>
#define SA_NEEDED_BUFFER_WORDS(capacity) \
	(RF_NEEDED_BUFFER_WORDS(capacity, sizeof(Assertions_Item)))

#ifdef __cplusplus
extern "C"
{
#endif
	/* -------------------------------------------------------------------
	*	Services
	*/

	/// <summary>
	/// <para>Assertion item</para>
	/// </summary>
	typedef struct _Assertions_Item
	{
		/// <summary>行番号</summary>
		int32_t Line;
		/// <summary>ファイル名</summary>
		char FileName[260];
	} Assertions_Item;

	/// <summary>
	/// <para>Storable assertions</para>
	/// </summary>
	typedef struct _Assertions
	{
		/// <summary>Assertion items</summary>
		RingedFrames Items;
	} Assertions;

	/// <summary>
	/// <para>蓄積可能アサーションを初期化する。</para>
	/// </summary>
	/// <param name="capacity">蓄積可能数。</param>
	/// <param name="buffer">動作に必要なバッファ。
	/// SA_NEEDED_BUFFER_WORDS分の要素数を持つ領域を確保して指定すること。</param>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>なし。</returns>
	void Assertions_Init(
		int32_t capacity,
		int32_t* buffer,
		Assertions* ctxt);

	/// <summary>
	/// <para>条件の偽(0)を表示する。</para>
	/// </summary>
	/// <param name="condition">条件。0(偽)の場合に表示される。</param>
	/// <param name="fileName">ファイル名。</param>
	/// <param name="line">行番号。</param>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>なし。</returns>
	void Assertions_AssertWith(
		int condition,
		const char* fileName, int32_t line,
		Assertions* ctxt);
	/// <summary>
	/// <para>条件の偽(0)を表示する。</para>
	/// </summary>
	/// <param name="condition">条件。0(偽)の場合に表示される。</param>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>なし。</returns>
#define Assertions_Assert(condition, ctxt) Assertions_AssertWith( \
		(condition), __FILE__, __LINE__, (ctxt))

	/// <summary>
	/// <para>記憶されている項目の数を取得する。</para>
	/// </summary>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>項目数。</returns>
	int32_t Assertions_Count(
		const Assertions* ctxt);

	/// <summary>
	/// <para>指定されたインデックス位置に記憶されている項目を取得する。</para>
	/// </summary>
	/// <param name="index">インデックス(0～、最古基準)。</param>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>項目。</returns>
	const Assertions_Item* Assertions_Refer(
		int32_t index,
		const Assertions* ctxt);

#ifdef _UNIT_TEST
	void Assertions_UnitTest(void);
#endif

#ifdef __cplusplus
}
#endif

#endif // top
