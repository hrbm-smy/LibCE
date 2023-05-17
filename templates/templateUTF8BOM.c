﻿/** ------------------------------------------------------------------
*
*	@file	templateUTF8BOM.c
*	@brief	新規モジュール作成時のテンプレート
*	@author	H.Someya
*	@date	2021/04/26
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
#include "templateUTF8BOM.h"

/* -------------------------------------------------------------------
*	Privates
*/

/* -------------------------------------------------------------------
*	Services
*/

/// <summary>
/// <para>サンプル関数。</para>
/// <para>パラグラフを分けたパターン。</para>
/// </summary>
/// <param name="src">入力データアドレス。</param>
/// <param name="dst">出力データアドレス。</param>
/// <param name="size">サイズ。</param>
/// <returns>処理したサイズ。</returns>
/// <revisionHistory>
///   <revision date="2020/04/06" version="000-000" author="H.Someya">新規作成</revision>
/// </revisionHistory>
int ExampleFunc(const void *src, void *dst, int size)
{
	return 0;
}


/* -------------------------------------------------------------------
*	Unit Test
*/
#ifdef _UNIT_TEST
#include <assert.h>
void Template_UnitTest(void)
{
	// -----------------------------------------
	// 1-1
}
#endif
