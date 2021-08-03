#ifndef AvlTree_h
#define AvlTree_h
/** ------------------------------------------------------------------
*
*	@file	AvlTree.h
*	@brief	AVL Tree (32bits key, without deletion)
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
	/// <para>AVLキー</para>
	/// </summary>
	typedef int32_t AvlKey_t;

	/// <summary>
	/// <para>AVL内容</para>
	/// </summary>
	typedef struct _AvlContent
	{
		/// <summary>Key</summary>
		AvlKey_t Key;
		/// <summary>Value</summary>
		const void* Value;
	} AvlContent;

	/// <summary>
	/// <para>AVLノード</para>
	/// </summary>
	typedef struct _AvlNode AvlNode;

	/// <summary>
	/// <para>AVLノード</para>
	/// </summary>
	typedef struct _AvlNode
	{
		/// <summary>この部分木の高さ</summary>
		int32_t Height;
		/// <summary>親ノード</summary>
		AvlNode* Parent;
		/// <summary>左部分木</summary>
		AvlNode* Left;
		/// <summary>右部分木</summary>
		AvlNode* Right;
		/// <summary>内容</summary>
		AvlContent Content;
	} AvlNode;

	/// <summary>
	/// <para>AVLノードを初期化する。</para>
	/// </summary>
	/// <param name="key">内容のKey。</param>
	/// <param name="value">内容のValue。</param>
	/// <param name="node">ノード。</param>
	/// <returns>なし。</returns>
	void AvlNode_Init(
		AvlKey_t key, const void* value,
		AvlNode* node);

	/// <summary>
	/// <para>Keyに該当するノードを検索する。</para>
	/// </summary>
	/// <param name="key">検索する内容のKey。</param>
	/// <param name="root">検索開始rootノード。</param>
	/// <returns>該当するノード。</returns>
	AvlNode* AvlTree_Search(
		AvlKey_t key,
		AvlNode* root);

	/// <summary>
	/// <para>ノードを挿入する。</para>
	/// </summary>
	/// <param name="node">挿入するノード。</param>
	/// <param name="root">挿入先treeのrootノード。</param>
	/// <returns>更新されたtreeのrootノード。</returns>
	AvlNode* AvlTree_Insert(
		AvlNode* node,
		AvlNode* root);

#ifdef _UNIT_TEST
#include "Assertions.h"
	void AvlTree_UnitTest(Assertions* assertions);
#endif

#ifdef __cplusplus
}
#endif

#endif // top
