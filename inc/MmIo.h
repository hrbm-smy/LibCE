#ifndef __MmIo_H__
#define __MmIo_H__

/** ------------------------------------------------------------------
 *
 *	@file	MmIo.h
 *	@brief	Memory Mapped I/O
 *	@author	H.Someya
 *	@date	2023/05/09
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
#include <stdint.h>

/*----------------------------------------------------------------------
 *  P U B L I C   D E F I N I T I O N S
 */

/**
 * inline definition
 */
#define MMIO_INLINE inline

/*----------------------------------------------------------------------
 *  P U B L I C   I N T E R F A C E S
 */

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     *  @brief 32bits I/O data reader @n
     *    Read 32bits value from base + offset.
     *  @param base Base address.
     *  @param offset Offset to the base address.
     *  @return Read value.
     */
    static MMIO_INLINE uint32_t MmIo_ReadU32(
        uintptr_t base, uintptr_t offset)
    {
        uint32_t result = 0;
        volatile uint32_t *addr = (volatile uint32_t *)(base + offset);
        result = *addr;
        return result;
    }

    /**
     *  @brief 32bits I/O data writer @n
     *    Write 32bits value to base + offset.
     *  @param value Write value.
     *  @param base Base address.
     *  @param offset Offset to the base address.
     *  @return Wrote value, not a device read value.
     */
    static MMIO_INLINE uint32_t MmIo_WriteU32(
        uint32_t value,
        uintptr_t base, uintptr_t offset)
    {
        uint32_t result = 0;
        volatile uint32_t *addr = (volatile uint32_t *)(base + offset);
        *addr = value;
        result = value;
        return result;
    }

    /**
     *  @brief Few bits I/O data writer @n
     *    Write few bits to base + offset.
     *  @param value Write value.
     *  @param bitStart Bit start index.
     *  @param bitCount Bit count.
     *  @param base Base address.
     *  @param offset Offset to the base address.
     *  @return Wrote value, not a device read value.
     */
    uint32_t MmIo_WriteBitsU32(
        uint32_t value,
        int32_t bitStart, int32_t bitCount,
        uintptr_t base, uintptr_t offset);

#ifdef _UNIT_TEST
    void MmIo_UnitTest(void);
#endif

#ifdef __cplusplus
}
#endif

#endif
