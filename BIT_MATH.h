/*
 * File:   BIT_MATH.h
 * Author: Ali Mohamed
 *
 * Created on March 2, 2024, 8:08 AM
 */

#ifndef BIT_MATH_H
#define	BIT_MATH_H

/*****************************INCLUDES*********************************/
#include "PLATFORM_TYPES.h"

/**********************************************************************/
#define CLEAR             0
#define SET               1


/**********************************************************************/

#define _8_BIT_ARCHI             8
#define _16_BIT_ARCHI            16
#define _32_BIT_ARCHI            32

/**********************************************************************/

#define MC_ARCHI                 _8_BIT_ARCHI
/*CHOOSE OPTION : _8_BIT_ARCHI
 *                _16_BIT_ARCHI
 *                _32_BIT_ARCHI
 */
/**********************************************************************/

#if (MC_ARCHI == _8_BIT_ARCHI || \
     MC_ARCHI == _16_BIT_ARCHI || \
     MC_ARCHI == _32_BIT_ARCHI  )
	#define _0TH_BIT                  0x0
    #define _1st_BIT                  0x1
    #define _2nd_BIT                  0x2
    #define _3rd_BIT                  0x3
    #define _4TH_BIT                  0x4
    #define _5TH_BIT                  0x5
    #define _6TH_BIT                  0x6
    #define _7TH_BIT                  0x7


    #define _0TH_BIT_MASK             0x1
    #define _1st_BIT_MASK             0x2
    #define _2nd_BIT_MASK             0x4
    #define _3rd_BIT_MASK             0x8
    #define _4TH_BIT_MASK             0x10
    #define _5TH_BIT_MASK             0x20
    #define _6TH_BIT_MASK             0x40
    #define _7TH_BIT_MASK             0x80

#endif

#if (MC_ARCHI == _16_BIT_ARCHI || \
     MC_ARCHI == _32_BIT_ARCHI  )
	#define _8TH_BIT                  0x8
    #define _9TH_BIT                  0x9
    #define _10TH_BIT                 0xA
    #define _11TH_BIT                 0xB
    #define _12TH_BIT                 0xC
    #define _13TH_BIT                 0xD
    #define _14TH_BIT                 0xE
    #define _15TH_BIT                 0xF

    #define _8TH_BIT_MASK             0x100
    #define _9TH_BIT_MASK             0x200
    #define _10TH_BIT_MASK            0x400
    #define _11TH_BIT_MASK            0x800
    #define _12TH_BIT_MASK            0x1000
    #define _13TH_BIT_MASK            0x2000
    #define _14TH_BIT_MASK            0x4000
    #define _15TH_BIT_MASK            0x8000
#endif

#if(MC_ARCHI == _32_BIT_ARCHI)
	#define _16TH_BIT                 0x10
    #define _17TH_BIT                 0x11
    #define _18TH_BIT                 0x12
    #define _19TH_BIT                 0x13
    #define _20TH_BIT                 0x14
    #define _21TH_BIT                 0x15
    #define _22TH_BIT                 0x16
    #define _23TH_BIT                 0x17
    #define _24TH_BIT                 0x18
    #define _25TH_BIT                 0x19
    #define _26TH_BIT                 0x1A
    #define _27TH_BIT                 0x1B
    #define _28TH_BIT                 0x1C
    #define _29TH_BIT                 0x1D
    #define _30TH_BIT                 0x1E
    #define _31TH_BIT                 0x1F

    #define _16TH_BIT_MASK            0x10000
    #define _17TH_BIT_MASK            0x20000
    #define _18TH_BIT_MASK            0x40000
    #define _19TH_BIT_MASK            0x80000
    #define _20TH_BIT_MASK            0x100000
    #define _21TH_BIT_MASK            0x200000
    #define _22TH_BIT_MASK            0x400000
    #define _23TH_BIT_MASK            0x800000
    #define _24TH_BIT_MASK            0x1000000
    #define _25st_BIT_MASK            0x2000000
    #define _26nd_BIT_MASK            0x4000000
    #define _27rd_BIT_MASK            0x8000000
    #define _28TH_BIT_MASK            0x10000000
    #define _29TH_BIT_MASK            0x20000000
    #define _30TH_BIT_MASK            0x40000000
    #define _31TH_BIT_MASK            0x80000000
#endif

/***********************MULTI BITS AT TIME BIT MASK**********************/

#define SET_N_BITS(REG, BIT_MASK)     (REG |= (BIT_MASK))
#define CLEAR_N_BITS(REG, BIT_MASK)   (REG &= (~(BIT_MASK)))
#define TOGGLE_N_BITS(REG, BIT_MASK)  (REG ^= (BIT_MASK))


/***********************ONE BIT AT TIME BIT MASK************************/

#define SET_BIT(REG, BIT_NUM)         (REG |= (1 << BIT_NUM))
#define CLEAR_BIT(REG, BIT_NUM)       (REG &= (~(1 << BIT_NUM)))
#define TOGGLE_BIT(REG, BIT_NUM)      (REG ^= (1 << BIT_NUM))
#define GET_BIT(REG, BIT_NUM)        ((REG >> BIT_NUM) & 1)

#endif	/* BIT_MATH_H */

