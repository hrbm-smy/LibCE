﻿#ifndef ArrayCap_h
#define ArrayCap_h
/** ------------------------------------------------------------------
*
*	@file	ArrayCap.h
*	@brief	Array capacity
*	@author	H.Someya
*	@date	2021/08/02
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
/// <para>Capacity of array in item count</para>
/// </summary>
/// <param name="a">array</param>
#define CAPACITY_OF(a) (sizeof(a) / sizeof((a)[0]))

#ifdef __cplusplus
extern "C"
{
#endif
	/* -------------------------------------------------------------------
	*	Services
	*/

#ifdef __cplusplus
}
#endif

#endif // top
