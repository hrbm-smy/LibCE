#ifndef template_h
#define template_h
/** ------------------------------------------------------------------
*
*	@file	templateUTF8BOM.h
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

/* -------------------------------------------------------------------
*	Definitions
*/
/// <summary>
/// <para>defineサンプル</para>
/// </summary>
#define EXAPMLE_DEFINITION (0)
/// <summary>
/// <para>defineサンプル2</para>
/// </summary>
/// <param name="a">引数a</param>
/// <param name="b">引数b</param>
#define EXAMPLE_DEFINITION2(a, b)

#ifdef __cplusplus
extern "C"
{
#endif
	/* -------------------------------------------------------------------
	*	Services
	*/

	/// <summary>
	/// <para>enumサンプル</para>
	/// </summary>
	typedef enum _ExampleEnum
	{
		/// <summary>
		/// 1st case of ExampleEnum
		/// </summary>
		Enum1,
		/// <summary>2番目の定義</summary>
		Enum2,
	} ExampleEnum;

	/// <summary>
	/// <para>structサンプル</para>
	/// </summary>
	typedef struct _ExampleStruct
	{
		/// <summary>最初のメンバ</summary>
		int Member1;
		/// <summary>
		/// 2nd member.
		/// <para>Detailed description of 2nd member.</para>
		/// <para>[0]:Key.</para>
		/// <para>[1]:Value.</para>
		/// </summary>
		char Member2[2];
		/// <summary>3番目のメンバ</summary>
		long Member3;
	} ExampleStruct;

	int ExampleFunc(const void *src, void *dst, int size);

#ifdef __cplusplus
}
#endif

#endif // top
