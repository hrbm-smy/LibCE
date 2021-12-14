/** ------------------------------------------------------------------
*
*	@file	RingedFrames.c
*	@brief	フレームリングバッファ
*	@author	H.Someya
*	@date	2021/07/28
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
#include "RingedFrames.h"
#include <string.h>
#include "nullptr.h"
#include "Indices.h"

/* -------------------------------------------------------------------
*	Privates
*/

/* -------------------------------------------------------------------
*	Services
*/

/// <summary>
/// <para>フレームリングバッファを初期化する。</para>
/// </summary>
/// <param name="capacity">最大蓄積可能フレーム数。</param>
/// <param name="frameSize">最大フレームサイズ。</param>
/// <param name="buffer">動作に必要なバッファ。
/// RF_NEEDED_BUFFER_WORDS分の要素数を持つ領域を確保して指定すること。</param>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>なし。</returns>
void RingedFrames_Init(
	int32_t capacity, int32_t frameSize,
	int32_t* buffer,
	RingedFrames* ctxt)
{
	if (ctxt != nullptr)
	{
		memset(ctxt, 0, sizeof(RingedFrames));
		ctxt->Capacity = capacity;
		ctxt->FrameSize = frameSize;
		ctxt->Buffer = buffer;
	}
}

/// <summary>
/// <para>クリアする。</para>
/// </summary>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>なし。</returns>
void RingedFrames_Clear(
	RingedFrames* ctxt)
{
	if (ctxt != nullptr)
	{
		ctxt->Index = 0;
		ctxt->Count = 0;
		ctxt->UpdateCount = 0;
	}
}

/// <summary>
/// <para>現在のフレーム蓄積数を取得する。</para>
/// </summary>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>現在のフレーム蓄積数。</returns>
int32_t RingedFrames_Count(
	const RingedFrames* ctxt)
{
	int32_t result = 0;
	if (ctxt != nullptr)
	{
		result = ctxt->Count;
	}
	return result;
}

/// <summary>
/// <para>現在のフレーム更新数を取得する。</para>
/// <para>フレームリングバッファは最古を上書きするが、蓄積数は最大で停止する。</para>
/// <para>更新数は、最大蓄積数を蓄積した後でも更新される。</para>
/// </summary>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>現在のフレーム更新数。</returns>
int64_t RingedFrames_UpdateCount(
	const RingedFrames* ctxt)
{
	int64_t result = 0;
	if (ctxt != nullptr)
	{
		result = ctxt->UpdateCount;
	}
	return result;
}

/// <summary>
/// <para>最大蓄積可能フレーム数を取得する。</para>
/// </summary>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>最大蓄積可能フレーム数。</returns>
int32_t RingedFrames_Capacity(
	const RingedFrames* ctxt)
{
	int32_t result = 0;
	if (ctxt != nullptr)
	{
		result = ctxt->Capacity;
	}
	return result;
}

/// <summary>
/// <para>最大フレームサイズを取得する。</para>
/// </summary>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>最大フレームサイズ。</returns>
int32_t RingedFrames_FrameSize(
	const RingedFrames* ctxt)
{
	int32_t result = 0;
	if (ctxt != nullptr)
	{
		result = ctxt->FrameSize;
	}
	return result;
}

/// <summary>
/// <para>フレームをPushする。</para>
/// <para>最大蓄積可能フレーム数まで蓄積されていると、最古を上書きする。</para>
/// </summary>
/// <param name="frame">フレーム。</param>
/// <param name="length">フレームの長さ。</param>
/// <param name="timestamp">タイムスタンプ。</param>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>なし。</returns>
void RingedFrames_Push(
	const void* frame, int32_t length,
	int64_t timestamp,
	RingedFrames* ctxt)
{
	if (ctxt != nullptr)
	{
		// 保存先バッファ位置を計算
		int32_t fi = ctxt->Index;
		int32_t bi = RF_STRIDE_WORDS(ctxt->FrameSize) * fi;
		int32_t* bp = &ctxt->Buffer[bi];

		// ヘッダを記録
		uint8_t* header = (uint8_t*)bp;
		// 0～7バイト目にタイムスタンプを記録
		int64_t* tsp = (int64_t*)&header[0];
		*tsp = timestamp;
		// 8～9バイト目に長さを記録
		int16_t* lenp = (int16_t*)&header[sizeof(int64_t)];
		*lenp = length;

		// フレームを記録
		uint8_t* fp = &header[RF_FRAME_HEADER_SIZE];
		if ((frame != nullptr) &&
			(0 < length) && (length <= ctxt->FrameSize))
		{
			memcpy(fp, frame, length);
		}
		else
		{
			// フレームが記録されない場合は長さを0にする
			*lenp = 0;
		}

		// インデックス、カウンタを更新
		ctxt->Index = NextIndex(ctxt->Index, ctxt->Capacity, 0);
		ctxt->Count = Inc2Max(ctxt->Count, ctxt->Capacity);
		ctxt->UpdateCount += 1;
	}
}

/// <summary>
/// <para>最古を0としたインデックスで、フレームを参照する。</para>
/// <para>コピーせず、内部メモリを直接参照する。</para>
/// </summary>
/// <param name="index">最古を0としたインデックス。</param>
/// <param name="length">フレーム長の格納先。</param>
/// <param name="timestamp">タイムスタンプの格納先。</param>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>フレーム。nullでなし。</returns>
const void* RingedFrames_ReferWithOld(
	int32_t index,
	int32_t* length,
	int64_t* timestamp,
	const RingedFrames* ctxt)
{
	// 結果を初期化
	const void* frame = nullptr;
	if (length != nullptr)
	{
		*length = 0;
	}
	if (timestamp != nullptr)
	{
		*timestamp = 0LL;
	}

	if ((ctxt != nullptr) &&
		(ctxt->Count > 0) &&
		((0 <= index) && (index < ctxt->Count)))
	{
		// 保存先バッファ位置を計算
		int32_t fi = RoundIndex(
			ctxt->Index - ctxt->Count + index, ctxt->Capacity, 0);
		int32_t bi = RF_STRIDE_WORDS(ctxt->FrameSize) * fi;
		int32_t* bp = &ctxt->Buffer[bi];

		// ヘッダを取得
		uint8_t* header = (uint8_t*)bp;
		// 0～7バイト目にタイムスタンプが記録されている
		if (timestamp != nullptr)
		{
			int64_t* tsp = (int64_t*)&header[0];
			*timestamp = *tsp;
		}
		// 8～9バイト目に長さが記録されている
		if (length != nullptr)
		{
			int16_t* lenp = (int16_t*)&header[sizeof(int64_t)];
			*length = *lenp;
		}

		// フレームを取得
		uint8_t* fp = &header[RF_FRAME_HEADER_SIZE];
		frame = fp;
	}

	return frame;
}

/// <summary>
/// <para>最新を0としたインデックスで、フレームを参照する。</para>
/// <para>コピーせず、内部メモリを直接参照する。</para>
/// </summary>
/// <param name="index">最新を0としたインデックス。</param>
/// <param name="length">フレーム長の格納先。</param>
/// <param name="timestamp">タイムスタンプの格納先。</param>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>フレーム。nullでなし。</returns>
const void* RingedFrames_ReferWithNew(
	int32_t index,
	int32_t* length,
	int64_t* timestamp,
	const RingedFrames* ctxt)
{
	return RingedFrames_ReferWithOld(
		RingedFrames_Count(ctxt) - 1 - index,
		length, timestamp,
		ctxt);
}

/// <summary>
/// <para>最古のフレームをPopする。</para>
/// <para>フレームが無い場合は負を返す。</para>
/// <para>格納先が足りない場合は、格納できる分だけ返す。</para>
/// </summary>
/// <param name="buffer">フレームの格納先バッファ。</param>
/// <param name="bufferSize">フレーム格納先バッファのサイズ。</param>
/// <param name="timestamp">タイムスタンプの格納先。</param>
/// <param name="ctxt">コンテキスト。</param>
/// <returns>フレーム長。</returns>
int32_t RingedFrames_Pop(
	void* buffer, int32_t bufferSize,
	int64_t* timestamp,
	RingedFrames* ctxt)
{
	// 結果を初期化
	int32_t length = -1;
	if (timestamp != nullptr)
	{
		*timestamp = 0LL;
	}

	// 最古のフレームを取得
	int32_t len;
	int64_t ts;
	const void* frame = RingedFrames_ReferWithOld(0, &len, &ts, ctxt);
	if (frame != nullptr)
	{
		// データ長を補正して報告
		length = len;
		if (length > bufferSize)
		{
			length = bufferSize;
		}

		// フレームを報告
		if ((buffer != nullptr) &&
			(length > 0))
		{
			memcpy(buffer, frame, length);
		}

		// タイムスタンプを報告
		if (timestamp != nullptr)
		{
			*timestamp = ts;
		}

		// 最古を削除
		ctxt->Count = Dec2Min(ctxt->Count, 0);
	}

	return length;
}

/* -------------------------------------------------------------------
*	Unit Test
*/
#ifdef _UNIT_TEST
#include <assert.h>
void RingedFrames_UnitTest(void)
{
	// -----------------------------------------
	// 1-1
	RingedFrames ring;
	int32_t buffer[1 + RF_NEEDED_BUFFER_WORDS(3, 8) + 1];
	uint8_t frame[8];
	int32_t length;
	int64_t timestamp;
	const uint8_t* referer;
	uint8_t dataBuffer[8];
	int64_t updateCount;

	// -----------------------------------------
	// 1-1 Init
	memset(buffer, -1, sizeof buffer);
	RingedFrames_Init(3, 8, &buffer[1], &ring);
	assert(RingedFrames_Count(&ring) == 0);
	assert(RingedFrames_UpdateCount(&ring) == 0);
	// -----------------------------------------
	// 1-2 Init(self==nullptr)
	RingedFrames_Init(5, 8, &buffer[1], nullptr);
	assert(RingedFrames_Capacity(&ring) == 3);

	// -----------------------------------------
	// 2-1 Capacity(self==nullptr)
	assert(RingedFrames_Capacity(nullptr) == 0);
	// -----------------------------------------
	// 2-2 Capacity
	assert(RingedFrames_Capacity(&ring) == 3);

	// -----------------------------------------
	// 3-1 FrameSize(self==nullptr)
	assert(RingedFrames_FrameSize(nullptr) == 0);
	// -----------------------------------------
	// 3-2 FrameSize
	assert(RingedFrames_FrameSize(&ring) == 8);

	// -----------------------------------------
	// 4-1 Count(self==nullptr)
	assert(RingedFrames_Count(nullptr) == 0);
	// -----------------------------------------
	// 4-2 Count
	memset(frame, 0, sizeof frame);
	frame[0] = 4;
	frame[7] = 2;
	assert(RingedFrames_Count(&ring) == 0);
	RingedFrames_Push(frame, 8, 42LL, &ring);
	assert(RingedFrames_Count(&ring) == 1);

	// -----------------------------------------
	// 5-1 UpdateCount(self==nullptr)
	assert(RingedFrames_UpdateCount(nullptr) == 0);
	// -----------------------------------------
	// 5-2 UpdateCount
	memset(frame, 0, sizeof frame);
	frame[0] = 5;
	frame[7] = 2;
	updateCount = RingedFrames_UpdateCount(&ring);
	RingedFrames_Push(frame, 8, 52LL, &ring);
	assert(RingedFrames_UpdateCount(&ring) != updateCount);

	// -----------------------------------------
	// 6-1 Clear(self==nullptr)
	RingedFrames_Clear(nullptr);
	assert(RingedFrames_Count(&ring) == 2);
	assert(RingedFrames_UpdateCount(&ring) != 0);
	// -----------------------------------------
	// 6-2 Clear
	RingedFrames_Clear(&ring);
	assert(RingedFrames_Count(&ring) == 0);
	assert(RingedFrames_UpdateCount(&ring) == 0);

	// -----------------------------------------
	// 7-xx Push, Refer, Pop
	memset(buffer, -1, sizeof buffer);
	RingedFrames_Init(3, 8, &buffer[1], &ring);

	// -----------------------------------------
	// 7-01 Empty
	RingedFrames_Clear(&ring);

	// Check
	assert(RingedFrames_Count(&ring) == 0);
	referer = RingedFrames_ReferWithOld(0, &length, &timestamp, &ring);
	assert(referer == nullptr);
	assert(length == 0);
	assert(timestamp == 0LL);
	referer = RingedFrames_ReferWithNew(0, &length, &timestamp, &ring);
	assert(referer == nullptr);
	assert(length == 0);
	assert(timestamp == 0LL);
	length = RingedFrames_Pop(dataBuffer, sizeof dataBuffer, &timestamp, &ring);
	assert(length < 0);
	assert(timestamp == 0LL);

	// -----------------------------------------
	// 7-02 Push(self==nullptr)
	memset(frame, 0, sizeof frame);
	frame[0] = 7;
	frame[7] = 2;
	RingedFrames_Push(frame, 8, 72LL, nullptr);

	// Check
	assert(RingedFrames_Count(&ring) == 0);
	referer = RingedFrames_ReferWithOld(0, &length, &timestamp, &ring);
	assert(referer == nullptr);
	assert(length == 0);
	assert(timestamp == 0LL);
	referer = RingedFrames_ReferWithNew(0, &length, &timestamp, &ring);
	assert(referer == nullptr);
	assert(length == 0);
	assert(timestamp == 0LL);

	// -----------------------------------------
	// 7-03 Push 1st frame
	updateCount = RingedFrames_UpdateCount(&ring);
	memset(frame, 0, sizeof frame);
	frame[0] = 7;
	frame[7] = 3;
	RingedFrames_Push(frame, 8, 73LL, &ring);

	// Check
	assert(RingedFrames_Count(&ring) == 1);
	assert(RingedFrames_UpdateCount(&ring) != updateCount);
	// Index -1 is not valid
	referer = RingedFrames_ReferWithOld(-1, &length, &timestamp, &ring);
	assert(referer == nullptr);
	assert(length == 0);
	assert(timestamp == 0LL);
	// Index 0 is valid
	referer = RingedFrames_ReferWithOld(0, &length, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[7] == 3);
	assert(length == 8);
	assert(timestamp == 73LL);
	// Index 1 is not valid
	referer = RingedFrames_ReferWithOld(1, &length, &timestamp, &ring);
	assert(referer == nullptr);
	assert(length == 0);
	assert(timestamp == 0LL);
	// Index -1 is not valid
	referer = RingedFrames_ReferWithNew(-1, &length, &timestamp, &ring);
	assert(referer == nullptr);
	assert(length == 0);
	assert(timestamp == 0LL);
	// Index 0 is valid
	referer = RingedFrames_ReferWithNew(0, &length, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[7] == 3);
	assert(length == 8);
	assert(timestamp == 73LL);
	// Index 1 is not valid
	referer = RingedFrames_ReferWithNew(1, &length, &timestamp, &ring);
	assert(referer == nullptr);
	assert(length == 0);
	assert(timestamp == 0LL);

	// -----------------------------------------
	// 7-04 Push 2nd frame
	updateCount = RingedFrames_UpdateCount(&ring);
	memset(frame, 0, sizeof frame);
	frame[0] = 7;
	frame[6] = 4;
	RingedFrames_Push(frame, 7, 74LL, &ring);

	// Check
	assert(RingedFrames_Count(&ring) == 2);
	assert(RingedFrames_UpdateCount(&ring) != updateCount);
	// Index 0 is valid
	referer = RingedFrames_ReferWithOld(0, &length, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[7] == 3);
	assert(length == 8);
	assert(timestamp == 73LL);
	// Index 1 is valid
	referer = RingedFrames_ReferWithOld(1, &length, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[6] == 4);
	assert(length == 7);
	assert(timestamp == 74LL);
	// Index 2 is not valid
	referer = RingedFrames_ReferWithOld(2, &length, &timestamp, &ring);
	assert(referer == nullptr);
	assert(length == 0);
	assert(timestamp == 0LL);
	// Index 0 is valid
	referer = RingedFrames_ReferWithNew(0, &length, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[6] == 4);
	assert(length == 7);
	assert(timestamp == 74LL);
	// Index 1 is valid
	referer = RingedFrames_ReferWithNew(1, &length, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[7] == 3);
	assert(length == 8);
	assert(timestamp == 73LL);
	// Index 2 is not valid
	referer = RingedFrames_ReferWithNew(2, &length, &timestamp, &ring);
	assert(referer == nullptr);
	assert(length == 0);
	assert(timestamp == 0LL);

	// -----------------------------------------
	// 7-05 Push 3rd frame
	updateCount = RingedFrames_UpdateCount(&ring);
	memset(frame, 0, sizeof frame);
	frame[0] = 7;
	frame[7] = 5;
	RingedFrames_Push(frame, 8, 75LL, &ring);

	// Check
	assert(RingedFrames_Count(&ring) == 3);
	assert(RingedFrames_UpdateCount(&ring) != updateCount);
	// Index 0 is valid
	referer = RingedFrames_ReferWithOld(0, &length, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[7] == 3);
	assert(length == 8);
	assert(timestamp == 73LL);
	// Index 2 is valid
	referer = RingedFrames_ReferWithOld(2, &length, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[7] == 5);
	assert(length == 8);
	assert(timestamp == 75LL);
	// Index 3 is not valid
	referer = RingedFrames_ReferWithOld(3, &length, &timestamp, &ring);
	assert(referer == nullptr);
	assert(length == 0);
	assert(timestamp == 0LL);
	// Index 0 is valid
	referer = RingedFrames_ReferWithNew(0, &length, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[7] == 5);
	assert(length == 8);
	assert(timestamp == 75LL);
	// Index 2 is valid
	referer = RingedFrames_ReferWithNew(2, &length, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[7] == 3);
	assert(length == 8);
	assert(timestamp == 73LL);
	// Index 3 is not valid
	referer = RingedFrames_ReferWithNew(3, &length, &timestamp, &ring);
	assert(referer == nullptr);
	assert(length == 0);
	assert(timestamp == 0LL);

	// -----------------------------------------
	// 7-06 Push 4th frame, lost 1st frame
	updateCount = RingedFrames_UpdateCount(&ring);
	memset(frame, 0, sizeof frame);
	frame[0] = 7;
	frame[6] = 6;
	RingedFrames_Push(frame, 7, 76LL, &ring);

	// Check
	assert(RingedFrames_Count(&ring) == 3);
	assert(RingedFrames_UpdateCount(&ring) != updateCount);
	// Index 0 is valid, but moved
	referer = RingedFrames_ReferWithOld(0, &length, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[6] == 4);
	assert(length == 7);
	assert(timestamp == 74LL);
	// Index 2 is valid, but moved
	referer = RingedFrames_ReferWithOld(2, &length, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[6] == 6);
	assert(length == 7);
	assert(timestamp == 76LL);
	// Index 0 is valid
	referer = RingedFrames_ReferWithNew(0, &length, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[6] == 6);
	assert(length == 7);
	assert(timestamp == 76LL);
	// Index 2 is valid
	referer = RingedFrames_ReferWithNew(2, &length, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[6] == 4);
	assert(length == 7);
	assert(timestamp == 74LL);

	// Do not destroy memories
	assert(buffer[0] == -1);
	assert(buffer[((sizeof buffer) / sizeof buffer[0]) - 1] == -1);

	// -----------------------------------------
	// 7-07 Pop
	length = RingedFrames_Pop(dataBuffer, sizeof dataBuffer, &timestamp, &ring);
	assert(dataBuffer[0] == 7);
	assert(dataBuffer[6] == 4);
	assert(length == 7);
	assert(timestamp == 74LL);

	assert(RingedFrames_Count(&ring) == 2);

	// -----------------------------------------
	// 7-08 Refer length only
	referer = RingedFrames_ReferWithNew(0, &length, nullptr, &ring);
	assert(referer[0] == 7);
	assert(referer[6] == 6);
	assert(length == 7);

	// -----------------------------------------
	// 7-09 Refer timestamp only
	referer = RingedFrames_ReferWithNew(0, nullptr, &timestamp, &ring);
	assert(referer[0] == 7);
	assert(referer[6] == 6);
	assert(timestamp == 76LL);

	// -----------------------------------------
	// 7-10 Push zero length frame
	updateCount = RingedFrames_UpdateCount(&ring);
	RingedFrames_Push(nullptr, 0, 710LL, &ring);

	// Check
	assert(RingedFrames_Count(&ring) == 3);
	assert(RingedFrames_UpdateCount(&ring) != updateCount);
	// Index 0 is valid, but length is zero
	referer = RingedFrames_ReferWithNew(0, &length, &timestamp, &ring);
	assert(referer != nullptr);
	assert(length == 0);
	assert(timestamp == 710LL);

	// -----------------------------------------
	// 7-11 Push oversized frame
	updateCount = RingedFrames_UpdateCount(&ring);
	RingedFrames_Push(frame, 9, 711LL, &ring);

	// Check
	assert(RingedFrames_Count(&ring) == 3);
	assert(RingedFrames_UpdateCount(&ring) != updateCount);
	// Index 0 is valid, but length is zero
	referer = RingedFrames_ReferWithNew(0, &length, &timestamp, &ring);
	assert(referer != nullptr);
	assert(length == 0);
	assert(timestamp == 711LL);

	// -----------------------------------------
	// 7-12 Push null frame
	updateCount = RingedFrames_UpdateCount(&ring);
	RingedFrames_Push(nullptr, 0, 712LL, &ring);

	// Check
	assert(RingedFrames_Count(&ring) == 3);
	assert(RingedFrames_UpdateCount(&ring) != updateCount);
	// Index 0 is valid, but length is zero
	referer = RingedFrames_ReferWithNew(0, &length, &timestamp, &ring);
	assert(referer != nullptr);
	assert(length == 0);
	assert(timestamp == 712LL);

	// -----------------------------------------
	// 7-13 Refer(self==nullptr)
	updateCount = RingedFrames_UpdateCount(&ring);
	memset(frame, 0, sizeof frame);
	frame[0] = 7;
	frame[6] = 13;
	RingedFrames_Push(frame, 7, 713LL, &ring);

	// Check
	assert(RingedFrames_Count(&ring) == 3);
	assert(RingedFrames_UpdateCount(&ring) != updateCount);
	referer = RingedFrames_ReferWithNew(0, &length, &timestamp, nullptr);
	assert(referer == nullptr);
	assert(length == 0);
	assert(timestamp == 0LL);

	// -----------------------------------------
	// 7-14 Pop but not enough buffer
	updateCount = RingedFrames_UpdateCount(&ring);
	memset(frame, 0, sizeof frame);
	frame[0] = 7;
	frame[5] = 1;
	frame[6] = 141;
	RingedFrames_Push(frame, 7, 7141LL, &ring);
	memset(frame, 0, sizeof frame);
	frame[0] = 7;
	frame[7] = 142;
	RingedFrames_Push(frame, 8, 7142LL, &ring);
	memset(frame, 0, sizeof frame);
	frame[0] = 7;
	frame[5] = 143;
	RingedFrames_Push(frame, 6, 7143LL, &ring);

	length = RingedFrames_Pop(dataBuffer, 6, &timestamp, &ring);

	// Check
	assert(RingedFrames_Count(&ring) == 2);
	assert(RingedFrames_UpdateCount(&ring) != updateCount);
	assert(length == 6);
	assert(timestamp == 7141LL);
	assert(dataBuffer[0] == 7);
	assert(dataBuffer[5] == 1);

	// -----------------------------------------
	// 7-14 Pop only timestamp
	length = RingedFrames_Pop(nullptr, 0, &timestamp, &ring);

	// Check
	assert(RingedFrames_Count(&ring) == 1);
	assert(length == 0);
	assert(timestamp == 7142LL);

	// -----------------------------------------
	// 7-15 Pop without timestamp
	length = RingedFrames_Pop(dataBuffer, sizeof dataBuffer, nullptr, &ring);

	// Check
	assert(RingedFrames_Count(&ring) == 0);
	assert(length == 6);
	assert(dataBuffer[0] == 7);
	assert(dataBuffer[5] == 143);

	// -----------------------------------------
	// 7-16 Pop zero length frame
	updateCount = RingedFrames_UpdateCount(&ring);
	RingedFrames_Push(nullptr, 0, 716LL, &ring);

	length = RingedFrames_Pop(dataBuffer, sizeof dataBuffer, &timestamp, &ring);

	// Check
	assert(RingedFrames_Count(&ring) == 0);
	assert(RingedFrames_UpdateCount(&ring) != updateCount);
	assert(length == 0);
	assert(timestamp == 716LL);
}
#endif
