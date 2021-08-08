#include <iostream>
#include "Indices.h"
#include "RingedFrames.h"
#include "Assertions.h"
#include "AvlTree.h"
#include "Map.h"

static int32_t ShowResults(const Assertions* assertions)
{
	int32_t result = 0;

	// 溜まっているアサーションを表示する
	int32_t assCount = Assertions_Count(assertions);
	for (int32_t ai = 0; ai < assCount; ai++)
	{
		const Assertions_Item* assItem = Assertions_Refer(ai, assertions);
		if (assItem != nullptr)
		{
			std::cout
				<< "Assertion failed at "
				<< assItem->FileName
				<< ":"
				<< assItem->Line
				<< std::endl;
		}
	}

	// 何もなかった場合は正常終了表示
	if (assCount <= 0)
	{
		std::cout << "Normally completed." << std::endl;;
	}

	// 結果コードはとりあえずエラー数とする
	result = assCount;

	return result;
}

int main(int argc, char** argv)
{
	int result = 0;

	// テストをするためにはAssertionsが必要
	// <-AssertionsにはRingedFramesが必要
	// <-RingedFramesにはIndicesが必要
	Indices_UnitTest();
	RingedFrames_UnitTest();
	Assertions_UnitTest();

	// ここに単体テストを追加していく。

	AvlTree_UnitTest();
	Map_UnitTest();







	// 結果を表示する
	Assertions* assertions = Assertions_Instance();
	result = ShowResults(assertions);

	return result;
}
