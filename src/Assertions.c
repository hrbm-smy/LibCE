/** ------------------------------------------------------------------
*
*	@file	Assertions.c
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
#include "Assertions.h"
#include <string.h>
#include "nullptr.h"
#include "ArrayCap.h"

/* -------------------------------------------------------------------
*	Privates
*/
#define SA_CAP_INSTANCE (100)
Assertions m_instance = { 0 };
int32_t m_instanceBuffer[SA_NEEDED_BUFFER_WORDS(SA_CAP_INSTANCE)];

/* -------------------------------------------------------------------
*	Services
*/

/// <summary>
/// <para>共有インスタンスを取得する。</para>
/// <para>共有インスタンスは初回取得時に初期化される。明示的な初期化は不要。</para>
/// </summary>
/// <returns>共有インスタンス。</returns>
Assertions* Assertions_Instance(void)
{
	if (m_instance.Items.Buffer == nullptr)
	{
		Assertions_Init(SA_CAP_INSTANCE, m_instanceBuffer, &m_instance);
	}
	return &m_instance;
}

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
	Assertions* ctxt)
{
	if (ctxt != nullptr)
	{
		memset(ctxt, 0, sizeof(Assertions));

		RingedFrames_Init(
			capacity, sizeof(Assertions_Item), buffer,
			&ctxt->Items);
	}
}

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
	Assertions* ctxt)
{
	if ((ctxt != nullptr) &&
		(condition == 0))
	{
		// Assertionは、最古を上書きしない、最初のn個を記録するものとする
		if (RingedFrames_Count(&ctxt->Items) <
			RingedFrames_Capacity(&ctxt->Items))
		{
			// アイテムを作成
			Assertions_Item item;
			item.Line = line;
			// ターミネータを含めたサイズをコピー
			size_t fnl = strlen(fileName) + 1;
			if (fnl > sizeof item.FileName)
			{
				fnl = sizeof item.FileName;
			}
			memcpy(item.FileName, fileName, fnl);
			// バッファ末尾のターミネータは常時つけてしまう
			item.FileName[CAPACITY_OF(item.FileName) - 1] = '\0';

			// リングバッファに追加
			RingedFrames_Push(&item, sizeof item, 0, &ctxt->Items);
		}
	}
}

/// <summary>
/// <para>記憶されている項目の数を取得する。</para>
/// </summary>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>項目数。</returns>
int32_t Assertions_Count(
	const Assertions* ctxt)
{
	int32_t result = 0;
	if (ctxt != nullptr)
	{
		result = RingedFrames_Count(&ctxt->Items);
	}
	return result;
}

/// <summary>
/// <para>指定されたインデックス位置に記憶されている項目を取得する。</para>
/// </summary>
/// <param name="index">インデックス(0～、最古基準)。</param>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>項目。</returns>
const Assertions_Item* Assertions_Refer(
	int32_t index,
	const Assertions* ctxt)
{
	const Assertions_Item* result = nullptr;
	if (ctxt != nullptr)
	{
		result = RingedFrames_ReferWithOld(
			index, nullptr, nullptr, &ctxt->Items);
	}
	return result;
}

/* -------------------------------------------------------------------
*	Unit Test
*/
#ifdef _UNIT_TEST
#include <assert.h>
void Assertions_UnitTest(void)
{
	Assertions assertions;
	int32_t assBuffer[SA_NEEDED_BUFFER_WORDS(3)];
	int32_t lines[4];
	const Assertions_Item* assItem;


	// -----------------------------------------
	// 1-1 Init(self==nullptr)
	Assertions_Init(0, nullptr, nullptr);

	// -----------------------------------------
	// 1-2 Init
	memset(&assertions, -1, sizeof assertions);
	Assertions_Init(3, assBuffer, &assertions);
	assert(Assertions_Count(&assertions) == 0);
	assItem = Assertions_Refer(0, &assertions);
	assert(assItem == nullptr);

	// -----------------------------------------
	// 2-1 Assert(self==nullptr)
	Assertions_Assert(1, nullptr);
	assert(Assertions_Count(&assertions) == 0);
	assItem = Assertions_Refer(0, &assertions);
	assert(assItem == nullptr);

	// -----------------------------------------
	// 2-2 Assert(condition!=0)
	Assertions_Assert(1, &assertions);
	assert(Assertions_Count(&assertions) == 0);
	assItem = Assertions_Refer(0, &assertions);
	assert(assItem == nullptr);

	// -----------------------------------------
	// 2-3 Assert 1st item
	lines[0] = __LINE__;
	Assertions_Assert(0, &assertions);
	assert(Assertions_Count(&assertions) == 1);
	assItem = Assertions_Refer(0, &assertions);
	assert(assItem != nullptr);
	assert(assItem->Line == lines[0] + 1);
	assert(strcmp(assItem->FileName, __FILE__) == 0);

	// -----------------------------------------
	// 2-4 Assert 2nd item
	char tooLongFileName[261] =
		"01234567890123456789012345678901234567890123456789"	//  50
		"01234567890123456789012345678901234567890123456789"	// 100
		"01234567890123456789012345678901234567890123456789"	// 150
		"01234567890123456789012345678901234567890123456789"	// 200
		"01234567890123456789012345678901234567890123456789"	// 250
		"0123456789\0"	// 261
		;
	lines[1] = __LINE__;
	Assertions_AssertWith(0, tooLongFileName, __LINE__, &assertions);
	assert(Assertions_Count(&assertions) == 2);
	assItem = Assertions_Refer(1, &assertions);
	assert(assItem != nullptr);
	assert(assItem->Line == lines[1] + 1);
	tooLongFileName[259] = '\0';
	assert(strcmp(assItem->FileName, tooLongFileName) == 0);

	// -----------------------------------------
	// 2-5 Assert 3rd item
	lines[2] = __LINE__;
	Assertions_Assert(0, &assertions);
	assert(Assertions_Count(&assertions) == 3);
	assItem = Assertions_Refer(2, &assertions);
	assert(assItem != nullptr);
	assert(assItem->Line == lines[2] + 1);
	assert(strcmp(assItem->FileName, __FILE__) == 0);

	// -----------------------------------------
	// 2-6 Assert 4th item, but ignored
	lines[3] = __LINE__;
	Assertions_Assert(0, &assertions);
	assert(Assertions_Count(&assertions) == 3);
	assItem = Assertions_Refer(3, &assertions);
	assert(assItem == nullptr);

	// -----------------------------------------
	// 3-1 Count(self==nullptr)
	assert(Assertions_Count(nullptr) == 0);

	// -----------------------------------------
	// 4-1 Refer(self==nullptr)
	assert(Assertions_Refer(0, nullptr) == nullptr);
}
#endif
