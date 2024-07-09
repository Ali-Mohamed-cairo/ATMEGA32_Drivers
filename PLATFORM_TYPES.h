/************************************************************/
/*Author    : Ali Mohamed************************************/
/*File_Name : Platform_Types.h*******************************/
/*Date      : 23/2/2024**************************************/
/************************************************************/
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*******************************General Info*********************************/
/*
Pointer sizes in different CPU architectures:
8-bit architecture CPU  -> 1 Byte
16-bit architecture CPU -> 2 Byte
32-bit architecture CPU -> 4 Byte
64-bit architecture CPU -> 8 Byte
*/
#define NULL_PTR ((void*)0)


/**********In all cases "char" -> 1 Byte*********************/
typedef unsigned char uint8;

typedef signed   char sint8;

typedef uint8 Std_ReturnType;
/******************************MACROS****************************************/
#define _8_BIT_CPU                     0 //Doesn't depend on the compiler
#define _16_BIT_CPU                    1 //Doesn't depend on the compiler
#define MPLAP_XC8_PIC18F               2
/*The following choice is also chosen for the following compilers operating on 32-bit systems:
        Clang / ICC(Intel C++ Compiler) / ARM Compiler / TCC(Tiny C compiler)
*/
#define GCC_COMPILER_SIZES_32_BIT_CPU  3
/*The following choice is also chosen for the following compilers operating on 64-bit systems:
        Clang / ICC(Intel C++ Compiler) / ARM Compiler / TCC(Tiny C compiler)
*/
#define GCC_COMPILER_SIZES_64_BIT_CPU  4
#define MSVC_32_BIT_CPU                5 //Microsoft visual C++(MSVC)
#define MSVC_64_BIT_CPU                6

#define E_NOT_OK          (Std_ReturnType)0x00
#define E_OK              (Std_ReturnType)0x01

/******************************************************************************/

#define DATA_TYPES_SIZES  GCC_COMPILER_SIZES_64_BIT_CPU
/*OPTIONS : _8_BIT_CPU
            _16_BIT_CPU
            MPLAP_XC8_PIC18F
            GCC_COMPILER_SIZES_32_BIT_CPU
            GCC_COMPILER_SIZES_64_BIT_CPU
            MSVC_32_BIT_CPU
            MSVC_64_BIT_CPU
*/

/******************************************************************************/

#if (DATA_TYPES_SIZES == _8_BIT_CPU)
    //Both un/signed "short" and "int" are 8 bits(u/sint8) similar to "char"
    typedef unsigned long  uint16;

    typedef signed   long  sint16;

#elif (DATA_TYPES_SIZES == _16_BIT_CPU || DATA_TYPES_SIZES == MPLAP_XC8_PIC18F)
    //Both un/signed "short" and "int" are 16 bits(u/sint16)"
    typedef unsigned int   uint16;
    typedef unsigned long  uint32;

    typedef signed   int   sint16;
    typedef signed   long  sint32;

#elif (DATA_TYPES_SIZES == GCC_COMPILER_SIZES_32_BIT_CPU   \
       || DATA_TYPES_SIZES == GCC_COMPILER_SIZES_64_BIT_CPU\
       || DATA_TYPES_SIZES == MSVC_32_BIT_CPU              \
       || DATA_TYPES_SIZES == MSVC_64_BIT_CPU)
    typedef unsigned short      uint16;
    typedef unsigned int        uint32;

    typedef signed   short      sint16;
    typedef signed   int        sint32;

    typedef          float      float32;
    typedef          double     float64;
#else
    #error "Not supported platform"
#endif //DATA_TYPES_SIZES_1

#if (DATA_TYPES_SIZES == MPLAP_XC8_PIC18F)
    typedef          float      float24;
    typedef          double     float32;

#elif (DATA_TYPES_SIZES == GCC_COMPILER_SIZES_32_BIT_CPU)
    typedef unsigned long            uint32;

    typedef signed   long            sint32;

    typedef          long double     float96;

#elif (DATA_TYPES_SIZES == GCC_COMPILER_SIZES_64_BIT_CPU)
    typedef unsigned long            uint64;

    typedef signed   long            sint64;

    typedef          long double     float128;

#elif (DATA_TYPES_SIZES == MSVC_32_BIT_CPU)
    typedef unsigned long            uint32;

    typedef signed   long            sint32;

    typedef          long double     float72;

#elif (DATA_TYPES_SIZES == MSVC_64_BIT_CPU)
    typedef unsigned long            uint32;

    typedef signed   long            sint32;

    typedef          long double     float72;

#endif //DATA_TYPES_SIZES_2


#endif // PLATFORM_TYPES_H

