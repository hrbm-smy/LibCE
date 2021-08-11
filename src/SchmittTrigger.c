/** ------------------------------------------------------------------
*
*	@file	SchmittTrigger.c
*	@brief	Schmitt Trigger Circuit
*	@author	H.Someya
*	@date	2021/08/11
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
#include "SchmittTrigger.h"
#include <string.h>
#include "nullptr.h"
#include "Indices.h"

/* -------------------------------------------------------------------
*	Privates
*/

/* -------------------------------------------------------------------
*	Services
*/

/// <summary>
/// <para>シュミットトリガを初期化する。</para>
/// </summary>
/// <param name="initialState">初期状態。非0:ON / 0:OFF</param>
/// <param name="onThreshold">ONしきい値。</param>
/// <param name="onPeriod">ON確定期間。</param>
/// <param name="offThreshold">OFFしきい値。</param>
/// <param name="offPeriod">OFF確定期間。</param>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>なし。</returns>
void SchmittTrigger_Init(
	int initialState,
	int32_t onThreshold,
	int32_t onPeriod,
	int32_t offThreshold,
	int32_t offPeriod,
	SchmittTrigger* ctxt)
{
	if (nullptr != ctxt)
	{
		memset(ctxt, 0, sizeof(SchmittTrigger));
		ctxt->State = initialState;
		ctxt->OnThreshold = onThreshold;
		ctxt->OnPeriod = onPeriod;
		ctxt->OffThreshold = offThreshold;
		ctxt->OffPeriod = offPeriod;
	}
}

/// <summary>
/// <para>シュミットトリガをリセットする。</para>
/// </summary>
/// <param name="state">リセット状態。非0:ON / 0:OFF</param>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>なし。</returns>
void SchmittTrigger_Reset(
	int state,
	SchmittTrigger* ctxt)
{
	if (nullptr != ctxt)
	{
		ctxt->State = state;
		ctxt->OnCounter = 0;
		ctxt->OffCounter = 0;
	}
}

/// <summary>
/// <para>シュミットトリガを駆動する。</para>
/// <para>入力値 &gt;= ONしきい値でON、入力値 &lt; OFFしきい値でOFF。</para>
/// <para>更新された状態(非0:ON / 0:OFF)を返す。</para>
/// </summary>
/// <param name="input">入力値。</param>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>非0:ON / 0:OFF。</returns>
int SchmittTrigger_Drive(
	int32_t input,
	SchmittTrigger* ctxt)
{
	int state = 0;
	if (nullptr != ctxt)
	{
		// ON側のカウンタを更新
		if (input >= ctxt->OnThreshold)
		{
			ctxt->OnCounter = Inc2Max(ctxt->OnCounter, ctxt->OnPeriod);
		}
		else
		{
			ctxt->OnCounter = 0;
		}
		// OFF側のカウンタを更新
		if (input < ctxt->OffThreshold)
		{
			ctxt->OffCounter = Inc2Max(ctxt->OffCounter, ctxt->OffPeriod);
		}
		else
		{
			ctxt->OffCounter = 0;
		}

		// ON側の状態を更新
		if ((input >= ctxt->OnThreshold) &&
			(ctxt->OnCounter >= ctxt->OnPeriod))
		{
			ctxt->State = 1;
		}
		// OFF側の状態を更新
		if ((input < ctxt->OffThreshold) &&
			(ctxt->OffCounter >= ctxt->OffPeriod))
		{
			ctxt->State = 0;
		}

		// 報告
		state = ctxt->State;
	}

	return state;
}

/// <summary>
/// <para>シュミットトリガの状態を取得する。</para>
/// <para>非0:ON / 0:OFF。</para>
/// </summary>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>非0:ON / 0:OFF。</returns>
int SchmittTrigger_State(
	SchmittTrigger* ctxt)
{
	int state = 0;
	if (nullptr != ctxt)
	{
		state = ctxt->State;
	}
	return state;
}

/* -------------------------------------------------------------------
*	Unit Test
*/
#ifdef _UNIT_TEST
#include "Assertions.h"
void SchmittTrigger_UnitTest(void)
{
	Assertions* assertions = Assertions_Instance();
	int state;
	int32_t onThreshold = 10;
	int32_t offThreshold = -5;
	SchmittTrigger st;
	SchmittTrigger_Init(0, onThreshold, 2, offThreshold, 3, &st);

	// -----------------------------------------
	// 1-1
	// 1度、ON未満とし、OFFのままである
	state = SchmittTrigger_Drive(onThreshold - 1, &st);
	Assertions_Assert(state == 0, assertions);
	// -----------------------------------------
	// 1-2
	// 2回設定で、1回だけON以上になっても、まだONしない
	state = SchmittTrigger_Drive(onThreshold, &st);
	Assertions_Assert(state == 0, assertions);
	// -----------------------------------------
	// 1-3
	// 2回設定で、一度ON未満になる
	state = SchmittTrigger_Drive(onThreshold - 1, &st);
	Assertions_Assert(state == 0, assertions);
	// -----------------------------------------
	// 1-4
	// 2回設定で、1回だけON以上になっても、まだONしない
	state = SchmittTrigger_Drive(onThreshold, &st);
	Assertions_Assert(state == 0, assertions);
	// -----------------------------------------
	// 1-5
	// 2回設定で、2回連続ON以上になれば、ONになる
	state = SchmittTrigger_Drive(onThreshold, &st);
	Assertions_Assert(state != 0, assertions);

	// -----------------------------------------
	// 2-1
	// 2回設定で、OFF未満に飛ぶが、ここではまだONを維持する
	state = SchmittTrigger_Drive(offThreshold - 1, &st);
	Assertions_Assert(state != 0, assertions);
	// -----------------------------------------
	// 2-2
	// 2回設定で、OFF以上に1回戻る
	state = SchmittTrigger_Drive(offThreshold, &st);
	Assertions_Assert(state != 0, assertions);
	// -----------------------------------------
	// 2-3
	// 2回設定で、OFF未満1回目
	state = SchmittTrigger_Drive(offThreshold - 1, &st);
	Assertions_Assert(state != 0, assertions);
	// -----------------------------------------
	// 2-4
	// 2回設定で、OFF未満2回目
	state = SchmittTrigger_Drive(offThreshold - 1, &st);
	Assertions_Assert(state != 0, assertions);
	// -----------------------------------------
	// 2-5
	// 2回設定で、OFF未満3回目、OFFになる
	state = SchmittTrigger_Drive(offThreshold - 1, &st);
	Assertions_Assert(state == 0, assertions);

	// -----------------------------------------
	// 3-1
	// ON側に暴れる、1回目
	state = SchmittTrigger_Drive(onThreshold, &st);
	Assertions_Assert(state == 0, assertions);
	// -----------------------------------------
	// 3-2
	// ON側に暴れる、2回目でON
	state = SchmittTrigger_Drive(onThreshold, &st);
	Assertions_Assert(state != 0, assertions);

	// -----------------------------------------
	// 4-1
	// State
	int gstate = SchmittTrigger_State(&st);
	Assertions_Assert(state == gstate, assertions);

	// -----------------------------------------
	// 5-1
	// Reset
	SchmittTrigger_Reset(0, &st);
	state = SchmittTrigger_State(&st);
	Assertions_Assert(state == 0, assertions);

	// -----------------------------------------
	// 6-1
	SchmittTrigger_Init(0, onThreshold, 1, onThreshold, 1, &st);
	// ヒステリシスなし用途、ON
	state = SchmittTrigger_Drive(onThreshold, &st);
	Assertions_Assert(state != 0, assertions);
	// -----------------------------------------
	// 6-2
	// ヒステリシスなし用途、OFF
	state = SchmittTrigger_Drive(onThreshold - 1, &st);
	Assertions_Assert(state == 0, assertions);
}
#endif
