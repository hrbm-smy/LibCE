#ifndef SchmittTrigger_h
#define SchmittTrigger_h
/** ------------------------------------------------------------------
*
*	@file	SchmittTrigger.h
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
#include <stdint.h>

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
	/// <para>シュミットトリガ</para>
	/// </summary>
	typedef struct _SchmittTrigger
	{
		/// <summary>状態。非0:ON / 0:OFF</summary>
		int State;
		/// <summary>ONカウンタ</summary>
		int32_t OnCounter;
		/// <summary>OFFカウンタ</summary>
		int32_t OffCounter;

		/// <summary>ONしきい値</summary>
		int32_t OnThreshold;
		/// <summary>ON確定回数</summary>
		int32_t OnPeriod;
		/// <summary>OFFしきい値</summary>
		int32_t OffThreshold;
		/// <summary>OFF確定回数</summary>
		int32_t OffPeriod;
	} SchmittTrigger;


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
		SchmittTrigger* ctxt);

	/// <summary>
	/// <para>シュミットトリガをリセットする。</para>
	/// </summary>
	/// <param name="state">リセット状態。非0:ON / 0:OFF</param>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>なし。</returns>
	void SchmittTrigger_Reset(
		int state,
		SchmittTrigger* ctxt);

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
		SchmittTrigger* ctxt);

	/// <summary>
	/// <para>シュミットトリガの状態を取得する。</para>
	/// <para>非0:ON / 0:OFF。</para>
	/// </summary>
	/// <param name="ctxt">コンテキスト。</param>
	/// <returns>非0:ON / 0:OFF。</returns>
	int SchmittTrigger_State(
		SchmittTrigger* ctxt);

#ifdef _UNIT_TEST
	void SchmittTrigger_UnitTest(void);
#endif

#ifdef __cplusplus
}
#endif

#endif // top
