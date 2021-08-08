#ifndef Map_h
#define Map_h
/** ------------------------------------------------------------------
*
*	@file	Map.h
*	@brief	Map
*	@author	H.Someya
*	@date	2021/08/06
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
#include "AvlTree.h"

/* -------------------------------------------------------------------
*	Definitions
*/

#ifdef __cplusplus
extern "C"
{
#endif
	/* -------------------------------------------------------------------
	*	Services
	*/

	/// <summary>
	/// <para>MapのKey</para>
	/// </summary>
	typedef AvlKey_t MapKey_t;

	/// <summary>
	/// <para>Map要素</para>
	/// </summary>
	typedef struct _MapElm
	{
		/// <summary>木ノード</summary>
		AvlNode Node;
	} MapElm;

	/// <summary>
	/// <para>Map</para>
	/// </summary>
	typedef struct _Map
	{
		/// <summary>要素数</summary>
		int32_t Count;
		/// <summary>木の根</summary>
		AvlNode* Root;
		/// <summary>最大要素数</summary>
		int32_t Capacity;
		/// <summary>要素リスト</summary>
		MapElm* Elements;
	} Map;

	/// <summary>
	/// <para>Mapを初期化する。</para>
	/// </summary>
	/// <param name="capacity">最大要素数。</param>
	/// <param name="elements">動作に必要な要素バッファ。
	/// 最大要素数分確保して指定すること。</param>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>なし。</returns>
	void Map_Init(
		int32_t capacity,
		MapElm* elements,
		Map* ctxt);

	/// <summary>
	/// <para>Mapの最大要素数を取得する。</para>
	/// </summary>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>最大要素数。</returns>
	int32_t Map_Capacity(
		const Map* ctxt);

	/// <summary>
	/// <para>Mapの蓄積済み要素数を取得する。</para>
	/// </summary>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>蓄積済み要素数。</returns>
	int32_t Map_Count(
		const Map* ctxt);

	/// <summary>
	/// <para>Mapをクリアする。</para>
	/// </summary>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>なし。</returns>
	void Map_Clear(
		Map* ctxt);

	/// <summary>
	/// <para>valueをkeyに関連付ける。</para>
	/// <para>同じkeyが既にある場合、関連付けを上書きする。</para>
	/// <para>※　keyとvalueを関連付けるだけであって、valueのスコープと定数/変数は、
	/// ValueFor/ValueAtと合わせ、ユーザーが考慮しなければならない。　※</para>
	/// <para>関連付けできた場合、蓄積済み要素数を返す。</para>
	/// <para>関連付けできなかった場合は0または負。</para>
	/// </summary>
	/// <param name="value">値。</param>
	/// <param name="key">キー。</param>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>蓄積済み要素数。</returns>
	int32_t Map_Relate(
		const void* value, MapKey_t key,
		Map* ctxt);

	/// <summary>
	/// <para>keyに対応するvalueを取得する。</para>
	/// <para>※　Relateで関連付けたアドレスを返すものである。
	/// 従って、valueのスコープと定数/変数は、
	/// Relateと合わせ、ユーザーが考慮しなければならない。　※</para>
	/// </summary>
	/// <param name="key">キー。</param>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>keyに対応するvalue。</returns>
	void* Map_ValueFor(
		MapKey_t key,
		const Map* ctxt);

	/// <summary>
	/// <para>指定したインデックス位置のvalueを取得する。</para>
	/// <para>※　Relateで関連付けたアドレスを返すものである。
	/// 従って、valueのスコープと定数/変数は、
	/// Relateと合わせ、ユーザーが考慮しなければならない。　※</para>
	/// </summary>
	/// <param name="index">インデックス位置(0～)。</param>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>インデックス位置のvalue。</returns>
	void* Map_ValueAt(
		int32_t index,
		const Map* ctxt);


#ifdef _UNIT_TEST
	void Map_UnitTest(void);
#endif

#ifdef __cplusplus
}
#endif

#endif // top
