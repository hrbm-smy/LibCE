/** ------------------------------------------------------------------
*
*	@file	Map.c
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
#include "Map.h"
#include <string.h>
#include "nullptr.h"

/* -------------------------------------------------------------------
*	Privates
*/

/* -------------------------------------------------------------------
*	Services
*/

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
	Map* ctxt)
{
	if (ctxt != nullptr)
	{
		memset(ctxt, 0, sizeof(Map));
		ctxt->Elements = elements;
		ctxt->Capacity = capacity;
	}
}

/// <summary>
/// <para>Mapの最大要素数を取得する。</para>
/// </summary>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>最大要素数。</returns>
int32_t Map_Capacity(
	const Map* ctxt)
{
	int32_t result = 0;
	if (ctxt != nullptr)
	{
		result = ctxt->Capacity;
	}
	return result;
}

/// <summary>
/// <para>Mapの蓄積済み要素数を取得する。</para>
/// </summary>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>蓄積済み要素数。</returns>
int32_t Map_Count(
	const Map* ctxt)
{
	int32_t result = 0;
	if (ctxt != nullptr)
	{
		result = ctxt->Count;
	}
	return result;
}

/// <summary>
/// <para>Mapをクリアする。</para>
/// </summary>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>なし。</returns>
void Map_Clear(
	Map* ctxt)
{
	if (ctxt != nullptr)
	{
		ctxt->Count = 0;
		ctxt->Root = nullptr;
	}
}

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
	Map* ctxt)
{
	int32_t result = 0;
	if (ctxt != nullptr)
	{
		AvlNode* existing = AvlTree_Search(key, ctxt->Root);
		if (existing != nullptr)
		{
			existing->Content.Value = value;

			result = ctxt->Count;
		}
		else if (ctxt->Count < ctxt->Capacity)
		{
			MapElm* elm = &ctxt->Elements[ctxt->Count];
			AvlNode_Init(key, value, &elm->Node);
			ctxt->Root = AvlTree_Insert(&elm->Node, ctxt->Root);
			ctxt->Count += 1;

			result = ctxt->Count;
		}
	}
	return result;
}

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
	const Map* ctxt)
{
	void* result = nullptr;
	if (ctxt != nullptr)
	{
		AvlNode* node = AvlTree_Search(key, ctxt->Root);
		if (node != nullptr)
		{
			result = (void*)node->Content.Value;
		}
	}
	return result;
}

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
	const Map* ctxt)
{
	void* result = nullptr;
	if ((ctxt != nullptr) &&
		(0 <= index) && (index < ctxt->Count))
	{
		MapElm* elm = &ctxt->Elements[index];
		result = (void*)elm->Node.Content.Value;
	}
	return result;
}

/// <summary>
/// <para>指定したインデックス位置のkeyを取得する。</para>
/// <para>※　Relateで関連付けたkeyを返すものである。
/// 従って、keyのスコープは、
/// Relateと合わせ、ユーザーが考慮しなければならない。　※</para>
/// </summary>
/// <param name="index">インデックス位置(0～)。</param>
/// <param name="orDefault">取得できない場合のデフォルト値。</param>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>インデックス位置のkey。</returns>
MapKey_t Map_KeyAt(
	int32_t index,
	MapKey_t orDefault,
	const Map* ctxt)
{
	MapKey_t result = orDefault;
	if ((ctxt != nullptr) &&
		(0 <= index) && (index < ctxt->Count))
	{
		MapElm* elm = &ctxt->Elements[index];
		result = elm->Node.Content.Key;
	}
	return result;
}

/* -------------------------------------------------------------------
 *	Unit Test
 */
#ifdef _UNIT_TEST
#include "Assertions.h"

typedef struct _Map_UnitTest_Value {
	int Member1;
	char Member2;
	short Member3[4];
} Map_UnitTest_Value;

void Map_UnitTest(void)
{
	Assertions* assertions = Assertions_Instance();
	const Map_UnitTest_Value* value = nullptr;
	MapElm mapElms[3];
	Map_UnitTest_Value values[5];
	memset(values, 0, sizeof values);
	Map map;
	MapKey_t key;

	// -----------------------------------------
	// 1-1 Init(ctxt==nullptr)
	Map_Init(3, mapElms, nullptr);
	// -----------------------------------------
	// 1-2 Init
	Map_Init(3, mapElms, &map);
	Assertions_Assert(Map_Capacity(&map) == 3, assertions);
	Assertions_Assert(Map_Count(&map) == 0, assertions);

	// -----------------------------------------
	// 2-1 Capacity(ctxt==nullptr)
	Assertions_Assert(Map_Capacity(nullptr) == 0, assertions);
	// -----------------------------------------
	// 2-2 Capacity
	Assertions_Assert(Map_Capacity(&map) == 3, assertions);

	// -----------------------------------------
	// 3-1 Count(ctxt==nullptr)
	values[2].Member1 = 1000;
	values[2].Member2 = 10;
	values[2].Member3[0] = 100;
	values[2].Member3[2] = 102;
	Map_Relate(&values[2], 12345, &map);
	Assertions_Assert(Map_Count(nullptr) == 0, assertions);
	// -----------------------------------------
	// 3-2 Count
	Assertions_Assert(Map_Count(&map) == 1, assertions);

	// -----------------------------------------
	// 4-1 Clear(ctxt==nullptr)
	Map_Clear(nullptr);
	Assertions_Assert(Map_Count(&map) == 1, assertions);
	// -----------------------------------------
	// 4-2 Clear
	Map_Clear(&map);
	Assertions_Assert(Map_Count(&map) == 0, assertions);

	// -----------------------------------------
	// 5-1 Relate(ctxt==nullptr)
	values[2].Member1 = 1000;
	values[2].Member2 = 10;
	values[2].Member3[0] = 100;
	values[2].Member3[2] = 102;
	Assertions_Assert(Map_Relate(&values[2], 12345, nullptr) == 0, assertions);
	value = Map_ValueFor(12345, &map);
	Assertions_Assert(value == nullptr, assertions);
	// -----------------------------------------
	// 5-2 Relate
	values[2].Member1 = 1000;
	values[2].Member2 = 10;
	values[2].Member3[0] = 100;
	values[2].Member3[2] = 102;
	Assertions_Assert(Map_Relate(&values[2], 12345, &map) == 1, assertions);
	value = Map_ValueFor(12345, &map);
	Assertions_Assert(value != nullptr, assertions);
	Assertions_Assert(value->Member1 == 1000, assertions);
	Assertions_Assert(value->Member2 == 10, assertions);
	Assertions_Assert(value->Member3[0] == 100, assertions);
	Assertions_Assert(value->Member3[2] == 102, assertions);
	Assertions_Assert(Map_Count(&map) == 1, assertions);
	// -----------------------------------------
	// 5-3 Relate
	values[0].Member1 = 2000;
	values[0].Member2 = 20;
	values[0].Member3[0] = 200;
	values[0].Member3[2] = 202;
	Assertions_Assert(Map_Relate(&values[0], 12345678, &map) == 2, assertions);
	value = Map_ValueFor(12345678, &map);
	Assertions_Assert(value != nullptr, assertions);
	Assertions_Assert(value->Member1 == 2000, assertions);
	Assertions_Assert(value->Member2 == 20, assertions);
	Assertions_Assert(value->Member3[0] == 200, assertions);
	Assertions_Assert(value->Member3[2] == 202, assertions);
	Assertions_Assert(Map_Count(&map) == 2, assertions);
	// -----------------------------------------
	// 5-4 Relate
	values[1].Member1 = 3000;
	values[1].Member2 = 30;
	values[1].Member3[0] = 300;
	values[1].Member3[2] = 302;
	Assertions_Assert(Map_Relate(&values[1], 0x80000000, &map) == 3, assertions);
	value = Map_ValueFor(0x80000000, &map);
	Assertions_Assert(value != nullptr, assertions);
	Assertions_Assert(value->Member1 == 3000, assertions);
	Assertions_Assert(value->Member2 == 30, assertions);
	Assertions_Assert(value->Member3[0] == 300, assertions);
	Assertions_Assert(value->Member3[2] == 302, assertions);
	Assertions_Assert(Map_Count(&map) == 3, assertions);
	// -----------------------------------------
	// 5-5 Relate いっぱいの場合には新たなキーは挿入できない
	values[3].Member1 = 3000;
	values[3].Member2 = 30;
	values[3].Member3[0] = 300;
	values[3].Member3[2] = 302;
	Assertions_Assert(Map_Relate(&values[1], 98765, &map) == 0, assertions);
	value = Map_ValueFor(98765, &map);
	Assertions_Assert(value == nullptr, assertions);
	// -----------------------------------------
	// 5-6 Relate 同じキーは上書き
	values[4].Member1 = 4000;
	values[4].Member2 = 40;
	values[4].Member3[0] = 400;
	values[4].Member3[2] = 402;
	Assertions_Assert(Map_Relate(&values[4], 12345678, &map) == 3, assertions);
	value = Map_ValueFor(12345678, &map);
	Assertions_Assert(value != nullptr, assertions);
	Assertions_Assert(value->Member1 == 4000, assertions);
	Assertions_Assert(value->Member2 == 40, assertions);
	Assertions_Assert(value->Member3[0] == 400, assertions);
	Assertions_Assert(value->Member3[2] == 402, assertions);
	Assertions_Assert(Map_Count(&map) == 3, assertions);

	// -----------------------------------------
	// 6-x ValueAt
	Map_Clear(&map);
	values[2].Member1 = 1000;
	values[2].Member2 = 10;
	values[2].Member3[0] = 100;
	values[2].Member3[2] = 102;
	Map_Relate(&values[2], 12345, &map);
	values[4].Member1 = 4000;
	values[4].Member2 = 40;
	values[4].Member3[0] = 400;
	values[4].Member3[2] = 402;
	Map_Relate(&values[4], 12345678, &map);
	// -----------------------------------------
	// 6-1 ValueAt(ctxt==nullptr)
	value = Map_ValueAt(0, nullptr);
	Assertions_Assert(value == nullptr, assertions);
	// -----------------------------------------
	// 6-2 ValueAt(index < 0)
	value = Map_ValueAt(-1, &map);
	Assertions_Assert(value == nullptr, assertions);
	// -----------------------------------------
	// 6-3 ValueAt(index >= Count)
	value = Map_ValueAt(2, &map);
	Assertions_Assert(value == nullptr, assertions);
	// -----------------------------------------
	// 6-4 ValueAt
	value = Map_ValueAt(0, &map);
	Assertions_Assert(value != nullptr, assertions);
	Assertions_Assert(value->Member1 == 1000, assertions);
	Assertions_Assert(value->Member2 == 10, assertions);
	Assertions_Assert(value->Member3[0] == 100, assertions);
	Assertions_Assert(value->Member3[2] == 102, assertions);
	// -----------------------------------------
	// 6-5 ValueAt
	value = Map_ValueAt(1, &map);
	Assertions_Assert(value != nullptr, assertions);
	Assertions_Assert(value->Member1 == 4000, assertions);
	Assertions_Assert(value->Member2 == 40, assertions);
	Assertions_Assert(value->Member3[0] == 400, assertions);
	Assertions_Assert(value->Member3[2] == 402, assertions);

	// -----------------------------------------
	// 7-x KeyAt
	Map_Clear(&map);
	values[2].Member1 = 1070;
	values[2].Member2 = 17;
	values[2].Member3[0] = 170;
	values[2].Member3[2] = 172;
	Map_Relate(&values[2], 54321, &map);
	values[4].Member1 = 4070;
	values[4].Member2 = 47;
	values[4].Member3[0] = 470;
	values[4].Member3[2] = 472;
	Map_Relate(&values[4], 87654321, &map);
	// -----------------------------------------
	// 7-1 KeyAt(ctxt==nullptr)
	key = Map_KeyAt(0, -1, nullptr);
	Assertions_Assert(key == -1, assertions);
	// -----------------------------------------
	// 7-2 KeyAt(index < 0)
	key = Map_KeyAt(-1, 0, &map);
	Assertions_Assert(key == 0, assertions);
	// -----------------------------------------
	// 7-3 KeyAt(index >= Count)
	key = Map_KeyAt(2, 0, &map);
	Assertions_Assert(key == 0, assertions);
	// -----------------------------------------
	// 7-4 KeyAt
	key = Map_KeyAt(0, 0, &map);
	Assertions_Assert(key == 54321, assertions);
	// -----------------------------------------
	// 7-5 KeyAt
	key = Map_KeyAt(1, 0, &map);
	Assertions_Assert(key == 87654321, assertions);
}
#endif
