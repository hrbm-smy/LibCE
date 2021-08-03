// LibCE_UnitTester.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "RingedFrames.h"
#include "Assertions.h"
#include "AvlTree.h"

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

int main()
{
	int result = 0;

	// テストをするためにはAssertionsが必要
	// <-AssertionsにはRingedFramesが必要
	RingedFrames_UnitTest();
	Assertions_UnitTest();

	// 100個もエラーが出ればおよそげんなりできるのでこんなものでOK
	// 割とスタック少な目っぽいのでstatic
	static Assertions assertions;
	static int32_t assBuffer[SA_NEEDED_BUFFER_WORDS(100)];
	Assertions_Init(100, assBuffer, &assertions);

	// ここに単体テストを追加していく。

	AvlTree_UnitTest(&assertions);








	// 結果を表示する
	result = ShowResults(&assertions);

	return result;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
