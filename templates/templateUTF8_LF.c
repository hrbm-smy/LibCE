/** ------------------------------------------------------------------
 *
 *	@file	templateUTF8_LF.c
 *	@brief	新規モジュール作成時のテンプレート
 *	@author	H.Someya
 *	@date	2023/04/14
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
#include "templateUTF8_LF.h"

/*----------------------------------------------------------------------
 *  P R I V A T E S
 */
/*----------------------------------------------------------------------
 *  P U B L I C   I N T E R F A C E S
 */

/**
 *  @brief 関数の名称 @n
 *    概要説明(～する)。
 *  @param buffer 入力データが入ったバッファ。
 *  @param size 入力データバッファのサイズ。
 *  @param info 処理途中情報の出力先。
 *  @return 動作結果。
 *		0:正常。
 *		1:受信なし。
 *		2:受信データ破棄。
 *		マイナス値:ドライバエラー。
 */
int ExampleFuncUTF8_LF(
	const unsigned char *buffer, int size,
	unsigned int *info)
{
	int a = TEMPLATE_DEFINE;
	int b = TEMPLATE_PARAMETERIZED_DEFINE(1, 2);
	TemplateStruct ts;
	ts.Member1 = a + b;
	ts.Member2[0] = TEMPLATE_GROUP1_VALUE1;
	return a + b;
}
