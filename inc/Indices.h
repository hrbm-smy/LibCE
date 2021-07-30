#ifndef Indices_h
#define Indices_h
/** ------------------------------------------------------------------
*
*	@file	Indices.h
*	@brief	Index Operations
*	@author	H.Someya
*	@date	2019/12/12
*
MIT License

Copyright (c) 2019 Hirobumi Someya

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
	/// 次インデックス取得
	/// </summary>
	/// <param name="index">現在インデックス</param>
	/// <param name="max">最大インデックス</param>
	/// <param name="min">最小インデックス</param>
	/// <returns>次インデックス</returns>
	int32_t NextIndex(int32_t index, int32_t max, int32_t min);

	/// <summary>
	/// 前インデックス取得
	/// </summary>
	/// <param name="index">現在インデックス</param>
	/// <param name="max">最大インデックス</param>
	/// <param name="min">最小インデックス</param>
	/// <returns>前インデックス</returns>
	int32_t PreviousIndex(int32_t index, int32_t max, int32_t min);

	/// <summary>
	/// 巡回インデックス取得
	/// </summary>
	/// <param name="index">現在インデックス</param>
	/// <param name="max">最大インデックス</param>
	/// <param name="min">最小インデックス</param>
	/// <returns>巡回インデックス</returns>
	int32_t RoundIndex(int32_t index, int32_t max, int32_t min);

	/// <summary>
	/// 最大まで増加させる。
	/// </summary>
	/// <param name="d">現在値</param>
	/// <param name="max">最大値</param>
	/// <returns>更新された値</returns>
	int32_t Inc2Max(int32_t d, int32_t max);

	/// <summary>
	/// 最小まで減算する。
	/// </summary>
	/// <param name="d">現在値</param>
	/// <param name="min">最小値</param>
	/// <returns>更新された値</returns>
	int32_t Dec2Min(int32_t d, int32_t min);

	/// <summary>
	/// <para>最小～最大の間で次の値を得る。</para>
	/// <para>最大は含まれる。</para>
	/// </summary>
	/// <param name="minimum">最小値</param>
	/// <param name="maximum">最大値</param>
	/// <param name="value">現在値</param>
	/// <returns>更新された値</returns>
	int32_t NextWithin(int32_t minimum, int32_t maximum, int32_t value);


	void Indices_UnitTest(void);

#ifdef __cplusplus
}
#endif

#endif // top
