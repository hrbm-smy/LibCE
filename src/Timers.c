/** -------------------------------------------------------------------------
 *
 *	@file	Timers.c
 *	@brief	Software timers
 *	@author	H.Someya
 *	@date	2025/05/28
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
#include "Timers.h"

/* --------------------------------------------------------------------------
 *  P R I V A T E S
 */

/* --------------------------------------------------------------------------
 *  P U B L I C   I N T E R F A C E S
 */

/**
 *  @brief ダウンカウントタイマ。 @n
 *    指定した間隔分減算する。0で停止する。(0未満にしない。)
 *  @param timer 更新前のタイマ値。
 *  @param interval 減算する間隔。
 *  @return 更新されたタイマ値。
 *    0以下:カウントアップした。 / 正:未カウントアップ。
 */
int32_t Countdown(int32_t timer, int32_t interval)
{
	timer -= interval;
	if (timer < 0)
	{
		timer = 0;
	}
	return timer;
}

/* -------------------------------------------------------------------
 *	Unit Test
 */
#ifdef _UNIT_TEST
#include "Assertions.h"

void Timers_UnitTest(void)
{
	Assertions *assertions = Assertions_Instance();
	int32_t timer;

	timer = 33;
	// -----------------------------------------
	// 1-1 Countdown, still not countup
	timer = Countdown(timer, 10);
	Assertions_Assert(timer > 0, assertions);
	// -----------------------------------------
	// 1-2 Countdown, still not countup
	timer = Countdown(timer, 10);
	Assertions_Assert(timer > 0, assertions);
	// -----------------------------------------
	// 1-3 Countdown, still not countup
	timer = Countdown(timer, 10);
	Assertions_Assert(timer > 0, assertions);
	// -----------------------------------------
	// 1-4 Countdown, counted up
	timer = Countdown(timer, 10);
	Assertions_Assert(timer == 0, assertions);
	Assertions_Assert(timer <= 0, assertions);
}

#endif
