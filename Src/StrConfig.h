/**
 * @file StrConfig.h
 * @author Ali Mirghasemi (ali.mirghasemi1376@gmail.com)
 * @brief This is configuration file for Str library
 * @version 0.1
 * @date 2025-11-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _STR_CONFIG_H_
#define _STR_CONFIG_H_

#include <stdint.h>

/* Check User Config file exists to include it or not */
#ifndef __has_include
    #define __has_include(X)    0
#endif

#if defined(STR_USER_CONFIG) || __has_include("StrUserConfig.h")
    #include "StrUserConfig.h"
#endif

/********************************************************************************************/
/*                                     Configuration                                        */
/********************************************************************************************/
#ifndef STR_ENABLE_PARSE
    #define STR_ENABLE_PARSE                                    1
#endif

#ifndef STR_ENABLE_CONVERT_STR
    #define STR_ENABLE_CONVERT_STR                              1
#endif

#ifndef STR_MAX_LENGTH
    #define STR_MAX_LENGTH                                      32767
#endif

#ifndef STR_ENABLE_LONG_NUMBER
    #define STR_ENABLE_LONG_NUMBER                              1
#endif

#ifndef STR_ENABLE_DOUBLE
    #define STR_ENABLE_DOUBLE                                   1
#endif

#ifndef STR_USE_CONST_VARIABLES
    #define STR_USE_CONST_VARIABLES                             0
#endif

#ifndef STR_USE_STRING_LIBRARY
    #define STR_USE_STRING_LIBRARY                              1
#endif

#ifndef MEM_CMP_RESULT
    #define MEM_CMP_RESULT                                      Int16
    typedef int16_t Mem_CmpResult;
#endif

#ifndef STR_CMP_RESULT
    #define STR_CMP_RESULT                                      Int16
    typedef int16_t Str_CmpResult;
#endif

#ifndef STR_NUM
    #define STR_NUM                                             Int32
    typedef int32_t  Str_Num;
#endif

#ifndef STR_UNUM
    #define STR_UNUM                                            UInt32
    typedef uint32_t Str_UNum;
#endif

#if STR_ENABLE_LONG_NUMBER

#ifndef STR_LONG
    #define STR_LONG                                            Int64
    typedef int64_t  Str_Long;
#endif

#ifndef STR_ULONG
    #define STR_ULONG                                           UInt64
    typedef uint64_t Str_ULong;
#endif

#endif

#ifndef STR_LEN_TYPE
    #define STR_LEN_TYPE                                        Int32
    typedef int32_t Str_LenType;
#endif

#ifndef MEM_LEN_TYPE
    #define MEM_LEN_TYPE                                        Int32
    typedef int32_t Mem_LenType;
#endif

/********************************************************************************************/

#endif // _STR_CONFIG_H_
