/** ------------------------------------------------------------------
*
*	@file	AvlTree.c
*	@brief	AVL Tree (subset, without deletion)
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
#include "AvlTree.h"
#include <string.h>
#include "nullptr.h"

/* -------------------------------------------------------------------
*	Privates
*/
/// <summary>
/// <para>親を取得する。</para>
/// </summary>
static AvlNode* ParentOf(const AvlNode* node)
{
	AvlNode* result = nullptr;
	if (node != nullptr)
	{
		result = node->Parent;
	}
	return result;
}
/// <summary>
/// <para>左の子を取得する。</para>
/// </summary>
static AvlNode* LeftOf(const AvlNode* node)
{
	AvlNode* result = nullptr;
	if (node != nullptr)
	{
		result = node->Left;
	}
	return result;
}
/// <summary>
/// <para>右の子を取得する。</para>
/// </summary>
static AvlNode* RightOf(const AvlNode* node)
{
	AvlNode* result = nullptr;
	if (node != nullptr)
	{
		result = node->Right;
	}
	return result;
}
/// <summary>
/// <para>高さを取得する。</para>
/// </summary>
static int32_t HeightOf(const AvlNode* node)
{
	int32_t result = 0;
	if (node != nullptr)
	{
		result = node->Height;
	}
	return result;
}
/// <summary>
/// <para>子の最大の高さを取得する。</para>
/// </summary>
static int32_t ChildrenMaxHeightOf(const AvlNode* node)
{
	int32_t result = 0;
	if (node != nullptr)
	{
		int32_t lh = HeightOf(node->Left);
		int32_t rh = HeightOf(node->Right);
		if (lh > rh)
		{
			result = lh;
		}
		else
		{
			result = rh;
		}
	}
	return result;
}
/// <summary>
/// <para>平衡値(左の高さ - 右の高さ)を取得する。</para>
/// </summary>
static int32_t ChildrenBalanceOf(const AvlNode* node)
{
	int32_t result = 0;
	if (node != nullptr)
	{
		int32_t lh = HeightOf(node->Left);
		int32_t rh = HeightOf(node->Right);
		result = lh - rh;
	}
	return result;
}
/// <summary>
/// <para>高さを更新する。</para>
/// </summary>
static void UpdateHeight(AvlNode* node)
{
	if (node != nullptr)
	{
		node->Height = ChildrenMaxHeightOf(node) + 1;
	}
}

/// <summary>
/// <para>左の子として縁組を行う。</para>
/// </summary>
static void AdoptAsLeft(AvlNode* child, AvlNode* parent)
{
	// Link with parent -> child
	if (parent != nullptr)
	{
		parent->Left = child;
	}
	// Link with child -> parent
	if (child != nullptr)
	{
		child->Parent = parent;
	}
}
/// <summary>
/// <para>右の子として縁組を行う。</para>
/// </summary>
static void AdoptAsRight(AvlNode* child, AvlNode* parent)
{
	// Link with parent -> child
	if (parent != nullptr)
	{
		parent->Right = child;
	}
	// Link with child -> parent
	if (child != nullptr)
	{
		child->Parent = parent;
	}
}
/// <summary>
/// <para>子ノードを置き換える。</para>
/// </summary>
static void ReplaceChild(const AvlNode* from, AvlNode* to)
{
	// 親を取得
	AvlNode* parent = ParentOf(from);
	if (parent == nullptr)
	{
		// 親->子はつなぐことが出来ないが、子->親はつなげられるならつなげる(親なし)
		if (to != nullptr)
		{
			to->Parent = parent;
		}
	}
	else if (parent->Left == from)
	{
		// 左につながれていた場合は左につなぐ
		AdoptAsLeft(to, parent);
	}
	else if (parent->Right == from)
	{
		// 右につながれていた場合は右につなぐ
		AdoptAsRight(to, parent);
	}
}
/// <summary>
/// <para>ノードを置き換える。</para>
/// </summary>
static void Replace(const AvlNode* from, AvlNode* to)
{
	// 親との縁組
	ReplaceChild(from, to);

	// 左との縁組
	AvlNode* left = LeftOf(from);
	AdoptAsLeft(left, to);

	// 右との縁組
	AvlNode* right = RightOf(from);
	AdoptAsRight(right, to);

	// Heightを引き継ぐ
	if (to != nullptr)
	{
		to->Height = HeightOf(from);
	}
}

/// <summary>
/// <para>右回転を行う。</para>
/// <para>更新されたrootを返す。</para>
/// </summary>
static AvlNode* RotateRight(AvlNode* node)
{
	// 回転中心(pivot)は左の子ノード
	AvlNode* pivot = LeftOf(node);

	// 回転中心と親を縁組
	ReplaceChild(node, pivot);

	// 移動する子ノードを取得
	AvlNode* moveChild = RightOf(pivot);
	// 移動する子ノードを、左の子として縁組
	AdoptAsLeft(moveChild, node);
	// 移動なので移動元はクリア
	if (pivot != nullptr)
	{
		pivot->Right = nullptr;
	}

	// 回転中心の右の子ノードとして再縁組
	AdoptAsRight(node, pivot);

	// 縁組したので高さを更新(子から親へ)
	UpdateHeight(node);
	UpdateHeight(pivot);
	UpdateHeight(ParentOf(pivot));

	// 新たなrootを返す
	return pivot;
}
/// <summary>
/// <para>左回転を行う。</para>
/// <para>更新されたrootを返す。</para>
/// </summary>
static AvlNode* RotateLeft(AvlNode* node)
{
	// 回転中心(pivot)は右の子ノード
	AvlNode* pivot = RightOf(node);

	// 回転中心と親を縁組
	ReplaceChild(node, pivot);

	// 移動する子ノードを取得
	AvlNode* moveChild = LeftOf(pivot);
	// 移動する子ノードを、右の子として縁組
	AdoptAsRight(moveChild, node);
	// 移動なので移動元はクリア
	if (pivot != nullptr)
	{
		pivot->Left = nullptr;
	}

	// 回転中心の左の子ノードとして再縁組
	AdoptAsLeft(node, pivot);

	// 縁組したので高さを更新(子から親へ)
	UpdateHeight(node);
	UpdateHeight(pivot);
	UpdateHeight(ParentOf(pivot));

	// 新たなrootを返す
	return pivot;
}
/// <summary>
/// <para>右-左 2重回転を行う。</para>
/// <para>更新されたrootを返す。</para>
/// </summary>
static AvlNode* RotateRightLeft(AvlNode* node)
{
	RotateRight(RightOf(node));
	return RotateLeft(node);
}
/// <summary>
/// <para>左-右 2重回転を行う。</para>
/// <para>更新されたrootを返す。</para>
/// </summary>
static AvlNode* RotateLeftRight(AvlNode* node)
{
	RotateLeft(LeftOf(node));
	return RotateRight(node);
}

/// <summary>
/// <para>treeにノードを挿入する。</para>
/// <para>ここでは挿入するのみで、バランスはとらない。</para>
/// </summary>
static void Insert(
	AvlNode* node,
	AvlNode* root)
{
	if (node != nullptr)
	{
		AvlNode* parent = root;
		while (parent != nullptr)
		{
			if (node->Content.Key < parent->Content.Key)
			{
				// 親のKeyより小さい -> 左に入れようとする
				if (parent->Left != nullptr)
				{
					// 左がある -> さらに左を見る
					parent = parent->Left;
				}
				else
				{
					// 左がない -> 見つかった。ここに挿入
					AdoptAsLeft(node, parent);
					node->Height = 1;
					node->Left = nullptr;
					node->Right = nullptr;

					break;
				}
			}
			else if (node->Content.Key > parent->Content.Key)
			{
				// 親のKeyより大きい -> 右に入れようとする
				if (parent->Right != nullptr)
				{
					// 右がある -> さらに右を見る
					parent = parent->Right;
				}
				else
				{
					// 右がない -> 見つかった。ここに挿入
					AdoptAsRight(node, parent);
					node->Height = 1;
					node->Left = nullptr;
					node->Right = nullptr;

					break;
				}
			}
			else
			{
				// 同じKey -> 上書き(入れ替え、これまでの親は勘当)
				Replace(parent, node);
				// 親子関係だけ成り代わる、内容は新しく追加するノードのものを使う

				break;
			}
		}
	}
}

/// <summary>
/// <para>treeのバランスをとる。</para>
/// <para>更新されたrootを返す。</para>
/// </summary>
static AvlNode* Balance(AvlNode* node)
{
	AvlNode* target = node;
	AvlNode* parent = ParentOf(target);
	while (parent != nullptr)
	{
		// 平衡処理を行う前の高さをとっておく
		int32_t parentHeight = HeightOf(parent);

		// 平衡処理
		if (target == LeftOf(parent))
		{
			// 左の子である場合
			int32_t parentBalance = ChildrenBalanceOf(parent);
			if (parentBalance >= 2)
			{
				int32_t targetBalance = ChildrenBalanceOf(target);
				if (targetBalance >= 0)
				{
					parent = RotateRight(parent);
				}
				else
				{
					parent = RotateLeftRight(parent);
				}
			}
			else
			{
				UpdateHeight(parent);
			}
		}
		else
		{
			// 右の子である場合
			int32_t parentBalance = ChildrenBalanceOf(parent);
			if (parentBalance <= -2)
			{
				int32_t targetBalance = ChildrenBalanceOf(target);
				if (targetBalance <= 0)
				{
					parent = RotateLeft(parent);
				}
				else
				{
					parent = RotateRightLeft(parent);
				}
			}
			else
			{
				UpdateHeight(parent);
			}
		}

		// 平衡処理の前後で高さが変わらない場合、終わり
		if (HeightOf(parent) == parentHeight)
		{
			break;
		}

		// 次へ
		target = parent;
		parent = ParentOf(target);
	}

	// 新しいrootを探す
	AvlNode* root = target;
	AvlNode* rootParent = ParentOf(root);
	while (rootParent != nullptr)
	{
		root = rootParent;
		rootParent = ParentOf(root);
	}

	return root;
}

/* -------------------------------------------------------------------
*	Services
*/

/// <summary>
/// <para>AVLノードを初期化する。</para>
/// </summary>
/// <param name="key">内容のKey。</param>
/// <param name="value">内容のValue。</param>
/// <param name="node">ノード。</param>
/// <returns>なし。</returns>
void AvlNode_Init(
	AvlKey_t key, const void* value,
	AvlNode* node)
{
	if (node != nullptr)
	{
		memset(node, 0, sizeof(AvlNode));

		node->Height = 1;
		node->Content.Key = key;
		node->Content.Value = value;
	}
}

/// <summary>
/// <para>Keyに該当するノードを検索する。</para>
/// </summary>
/// <param name="key">検索する内容のKey。</param>
/// <param name="root">検索開始rootノード。</param>
/// <returns>該当するノード。</returns>
AvlNode* AvlTree_Search(
	AvlKey_t key,
	AvlNode* root)
{
	AvlNode* result = nullptr;
	AvlNode* node = root;
	while (node != nullptr)
	{
		if (key < node->Content.Key)
		{
			node = node->Left;
		}
		else if (key > node->Content.Key)
		{
			node = node->Right;
		}
		else
		{
			// HIT!
			result = node;
			break;
		}
	}
	return result;
}

/// <summary>
/// <para>ノードを挿入する。</para>
/// </summary>
/// <param name="node">挿入するノード。</param>
/// <param name="root">挿入先treeのrootノード。</param>
/// <returns>更新されたtreeのrootノード。</returns>
AvlNode* AvlTree_Insert(
	AvlNode* node,
	AvlNode* root)
{
	// まずは挿入
	Insert(node, root);

	// バランスをとる
	AvlNode* newRoot = Balance(node);

	return newRoot;
}

/* -------------------------------------------------------------------
*	Unit Test
*/
#ifdef _UNIT_TEST
#include <stdlib.h>

typedef struct _AvlTree_UnitTest_Value
{
	int32_t Member1;
	int8_t Member2[4];
} AvlTree_UnitTest_Value;

static int32_t AvlTree_TracedHeightOf(const AvlNode* node)
{
	int32_t height = 0;
	if (node != nullptr)
	{
		height += 1;
		int32_t lh = AvlTree_TracedHeightOf(node->Left);
		int32_t rh = AvlTree_TracedHeightOf(node->Right);
		int32_t mh = (lh < rh) ? rh : lh;
		height += mh;
	}
	return height;
}

static void AvlTree_Check(const AvlNode* root, Assertions* assertions)
{
	if (root != nullptr)
	{
		// 実際に構造を辿った高さと、記憶されている高さを取得
		int32_t tlh = AvlTree_TracedHeightOf(root->Left);
		int32_t trh = AvlTree_TracedHeightOf(root->Right);
		int32_t slh = HeightOf(root->Left);
		int32_t srh = HeightOf(root->Right);

		// 左右の部分木の高さの差が1以下であること
		Assertions_Assert(abs(tlh - trh) <= 1, assertions);

		// 記憶された高さと、実際に辿った高さが同じであること
		Assertions_Assert(tlh == slh, assertions);
		Assertions_Assert(trh == srh, assertions);

		// 部分木を再帰チェック
		AvlTree_Check(root->Left, assertions);
		AvlTree_Check(root->Right, assertions);
	}
}

void AvlTree_UnitTest(Assertions* assertions)
{
	AvlNode* root;
	AvlNode* searched;
	AvlNode nodes[30];
	AvlTree_UnitTest_Value values[30];
	AvlKey_t dupKey;
	const AvlTree_UnitTest_Value* foundValue;

	// -----------------------------------------
	// 1-1 Init(self==nullptr)
	AvlNode_Init(0, nullptr, nullptr);

	// -----------------------------------------
	// 1-2 Init
	AvlNode_Init(0, &values[0], &nodes[0]);
	Assertions_Assert(nodes[0].Content.Key == 0, assertions);
	Assertions_Assert(nodes[0].Content.Value == &values[0], assertions);

	// -----------------------------------------
	// 2-1 Insert(node==nullptr)
	root = nullptr;
	root = AvlTree_Insert(nullptr, root);
	Assertions_Assert(root == nullptr, assertions);

	// -----------------------------------------
	// 2-2 Insert 1st node, become a root
	root = nullptr;
	AvlNode_Init(0, &values[0], &nodes[0]);
	root = AvlTree_Insert(&nodes[0], root);
	// Check structure
	AvlTree_Check(root, assertions);
	// Check searches
	Assertions_Assert(root == &nodes[0], assertions);
	searched = AvlTree_Search(0, root);
	Assertions_Assert(searched == &nodes[0], assertions);
	searched = AvlTree_Search(1, root);
	Assertions_Assert(searched == nullptr, assertions);

	// -----------------------------------------
	// 3-1 Insert sequential nodes
	for (int32_t i = 1; i < 10; i++)
	{
		AvlKey_t key = (i * 2) + 1;
		AvlNode_Init(key, &values[i], &nodes[i]);
		root = AvlTree_Insert(&nodes[i], root);
	}
	// Check structure
	AvlTree_Check(root, assertions);
	// Check searches
	for (int32_t i = 1; i < 10; i++)
	{
		AvlKey_t key = (i * 2) + 1;
		searched = AvlTree_Search(key, root);
		Assertions_Assert(searched == &nodes[i], assertions);
		searched = AvlTree_Search(key - 1, root);
		Assertions_Assert(searched == nullptr, assertions);
	}

	// -----------------------------------------
	// 3-2 Insert sequential nodes (descent order)
	for (int32_t i = 11; i < 20; i++)
	{
		AvlKey_t key = -((i * 2) + 1);
		AvlNode_Init(key, &values[i], &nodes[i]);
		root = AvlTree_Insert(&nodes[i], root);
	}
	// Check structure
	AvlTree_Check(root, assertions);
	// Check searches
	for (int32_t i = 11; i < 20; i++)
	{
		AvlKey_t key = -((i * 2) + 1);
		searched = AvlTree_Search(key, root);
		Assertions_Assert(searched == &nodes[i], assertions);
		searched = AvlTree_Search(key - 1, root);
		Assertions_Assert(searched == nullptr, assertions);
	}

	// -----------------------------------------
	// 3-3 Re-Insert sequential nodes (descent order)
	root = nullptr;
	for (int32_t i = 11; i < 20; i++)
	{
		AvlKey_t key = -((i * 2) + 1);
		AvlNode_Init(key, &values[i], &nodes[i]);
		root = AvlTree_Insert(&nodes[i], root);
	}
	// Check structure
	AvlTree_Check(root, assertions);
	// Check searches
	for (int32_t i = 11; i < 20; i++)
	{
		AvlKey_t key = -((i * 2) + 1);
		searched = AvlTree_Search(key, root);
		Assertions_Assert(searched == &nodes[i], assertions);
		searched = AvlTree_Search(key - 1, root);
		Assertions_Assert(searched == nullptr, assertions);
	}

	// -----------------------------------------
	// 4-1 Insert oscillated nodes
	for (int32_t i = 1; i < 10; i++)
	{
		AvlKey_t key = (i * 2) + 1;
		if ((i % 2) != 0)
		{
			key = -key;
		}
		AvlNode_Init(key, &values[i], &nodes[i]);
		root = AvlTree_Insert(&nodes[i], root);
	}
	// Check structure
	AvlTree_Check(root, assertions);
	// Check searches
	for (int32_t i = 1; i < 10; i++)
	{
		AvlKey_t key = (i * 2) + 1;
		if ((i % 2) != 0)
		{
			key = -key;
		}
		searched = AvlTree_Search(key, root);
		Assertions_Assert(searched == &nodes[i], assertions);
		searched = AvlTree_Search(key - 1, root);
		Assertions_Assert(searched == nullptr, assertions);
	}

	// -----------------------------------------
	// 4-2 Insert oscillated nodes
	root = nullptr;
	for (int32_t i = 11; i < 20; i++)
	{
		AvlKey_t key = ((i * 2) + 1);
		AvlNode_Init(key, &values[i], &nodes[i]);
		root = AvlTree_Insert(&nodes[i], root);
	}
	for (int32_t i = 1; i < 10; i++)
	{
		AvlKey_t key = (i * 2) + 1;
		if ((i % 2) != 0)
		{
			key = -key;
		}
		AvlNode_Init(key, &values[i], &nodes[i]);
		root = AvlTree_Insert(&nodes[i], root);
	}
	// Check structure
	AvlTree_Check(root, assertions);
	// Check searches
	for (int32_t i = 1; i < 10; i++)
	{
		AvlKey_t key = (i * 2) + 1;
		if ((i % 2) != 0)
		{
			key = -key;
		}
		searched = AvlTree_Search(key, root);
		Assertions_Assert(searched == &nodes[i], assertions);
		searched = AvlTree_Search(key - 1, root);
		Assertions_Assert(searched == nullptr, assertions);
	}

	// -----------------------------------------
	// 5-1 Insert duplicated node
	root = nullptr;
	memset(values, 0, sizeof values);
	// まず、いくつかノードを挿入する
	for (int32_t i = 0; i < 5; i++)
	{
		AvlKey_t key = (i * 2) + 1;
		AvlNode_Init(key, &values[i], &nodes[i]);
		root = AvlTree_Insert(&nodes[i], root);
	}
	// 上書きされるノードを挿入する
	dupKey = (5 * 2) + 1;
	values[5].Member1 = (5 * 2) + 1 + 1;
	AvlNode_Init(dupKey, &values[5], &nodes[5]);
	root = AvlTree_Insert(&nodes[5], root);
	// さらにノードを挿入して、木を変形させる
	for (int32_t i = 6; i < 10; i++)
	{
		AvlKey_t key = (i * 2) + 1;
		AvlNode_Init(key, &values[i], &nodes[i]);
		root = AvlTree_Insert(&nodes[i], root);
	}
	// いったん構造をチェック
	AvlTree_Check(root, assertions);
	// この時点では上書きされる前のノードが検索できるはず
	searched = AvlTree_Search(dupKey, root);
	Assertions_Assert(searched != nullptr, assertions);
	foundValue = searched->Content.Value;
	Assertions_Assert(foundValue != nullptr, assertions);
	Assertions_Assert(foundValue->Member1 == (5 * 2) + 1 + 1, assertions);

	// 上書きするノードを挿入する
	values[10].Member1 = (10 * 2) + 1 + 1;
	AvlNode_Init(dupKey, &values[10], &nodes[10]);
	root = AvlTree_Insert(&nodes[10], root);
	// さらにノードを挿入して、木を変形させる
	for (int32_t i = 11; i < 20; i++)
	{
		AvlKey_t key = (i * 2) + 1;
		AvlNode_Init(key, &values[i], &nodes[i]);
		root = AvlTree_Insert(&nodes[i], root);
	}

	// 構造をチェック
	AvlTree_Check(root, assertions);
	// 上書きされた後のノードが検索できるはず
	searched = AvlTree_Search(dupKey, root);
	Assertions_Assert(searched != nullptr, assertions);
	foundValue = searched->Content.Value;
	Assertions_Assert(foundValue != nullptr, assertions);
	Assertions_Assert(foundValue->Member1 == (10 * 2) + 1 + 1, assertions);

}
#endif
