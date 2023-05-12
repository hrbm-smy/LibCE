#ifndef __templateUTF8_LF_H__
#define __templateUTF8_LF_H__

/** ------------------------------------------------------------------
 *
 *	@file	templateUTF8_LF.h
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

/*----------------------------------------------------------------------
 *  P U B L I C   D E F I N I T I O N S
 */
/**
 * 普通のdefine
 */
#define TEMPLATE_DEFINE (100)
#define TEMPLATE_DEFINE2 (200) /**< 普通のdefineその2 */

/**
 * パラメータ付きdefine
 * @param p1 パラメータ1
 * @param p2 パラメータ2
 */
#define TEMPLATE_PARAMETERIZED_DEFINE(p1, p2) \
	((p1) + (p2))

/**
 * @name defineグループ
 *
 * 複数のdefineをグループにする。
 * enumでいいんではないか、という気もするが、何かに使えるかもしれない。
 *
 * @{
 */
#define TEMPLATE_GROUP1_VALUE1 (0) /**< 値1 */
#define TEMPLATE_GROUP1_VALUE2 (2) /**< 値2 */
#define TEMPLATE_GROUP1_VALUE3 (3) /**< 値3 */

/** @}*/

/**
 * @name defineグループ2
 *
 * グループ2。
 *
 * @{
 */
#define TEMPLATE_GROUP2_VALUE1 (0) /**< 値1 */
#define TEMPLATE_GROUP2_VALUE2 (2) /**< 値2 */

/** @}*/

/*----------------------------------------------------------------------
 *  P U B L I C   I N T E R F A C E S
 */

#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 * 構造体サンプル
	 */
	typedef struct
	{
		int Member1; /**< メンバ1 短い説明で済む場合 */
		/**
		 * メンバ2
		 * 長めの説明をつけたい場合
		 */
		char Member2[10];
	} TemplateStruct;

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
		unsigned int *info);

#ifdef __cplusplus
}
#endif

#endif
