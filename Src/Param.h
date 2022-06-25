/**
 * @file Param.h
 * @author Ali Mirghasemi (ali.mirghasemi1376@gmail.com)
 * @brief This library help you to parse string parameters.
 * @version 0.1
 * @date 2022-06-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _PARAM_H_
#define _PARAM_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define PARAM_VER_MAJOR       0
#define PARAM_VER_MINOR       1
#define PARAM_VER_FIX         0

#include "Str.h"
#include <stdint.h>

/********************************************************************************************/
/*                                     Configuration                                        */
/********************************************************************************************/
#define PARAM_CASE_LOWER        0x01
#define PARAM_CASE_HIGHER       0x02
#define PARAM_CASE_INSENSITIVE  0x03
/**
 * @brief define the case mode of parameter name, just for state, null, stateKey, boolean
 */
#define PARAM_CASE_MODE         PARAM_CASE_INSENSITIVE
/**
 * @brief define toStr decimal length, 0 means all digits
 */
#define PARAM_FLOAT_DECIMAL_LEN 0
/**
 * @brief This macro help you to define the maximum number of parameters.
 */
typedef int16_t Param_LenType;
/**
 * @brief if enable this param, Param_compareValue check teh value of Null
 */
#define PARAM_COMPARE_NULL_VAL      0
/**
 * @brief if enable this param, Param_compareValue check teh value of Unknown
 */
#define PARAM_COMPARE_UNKNOWN_VAL   0

/* Default Values for toStr */
#define PARAM_DEFAULT_NULL          "Null"
#define PARAM_DEFAULT_TRUE          "True"
#define PARAM_DEFAULT_FALSE         "False"
#define PARAM_DEFAULT_OFF           "Off"
#define PARAM_DEFAULT_ON            "On"
#define PARAM_DEFAULT_HIGH          "High"
#define PARAM_DEFAULT_LOW           "Low"
#define PARAM_DEFAULT_HEX           "0x"
#define PARAM_DEFAULT_BIN           "0b"

/********************************************************************************************/

/**
 * @brief show type of param
 */
typedef enum {
  Param_ValueType_Unknown,        /**< first character of value not match with anyone of supported values */
  Param_ValueType_Number,         /**< ex: 13 */
  Param_ValueType_NumberHex,      /**< ex: 0xAB25 */
  Param_ValueType_NumberBinary,   /**< ex: 0b64813 */
  Param_ValueType_Float,          /**< ex: 2.54 */
  Param_ValueType_State,          /**< (high, low), ex: high */
  Param_ValueType_StateKey,       /**< (on, off), ex: off */
  Param_ValueType_Boolean,        /**< (true, false), ex: true */
  Param_ValueType_String,         /**< ex: "Text" */
  Param_ValueType_Null,           /**< ex: null */
} Param_ValueType;
/**
 * @brief hold type of param in same memory
 */
typedef struct {
    union {
        char*           Unknown;
        int32_t         Number;
        uint32_t        NumberHex;
        uint32_t        NumberBinary;
        float           Float;
        uint8_t         State;
        uint8_t         StateKey;
        uint8_t         Boolean;
        char*           String;
        char*           Null;
    };
    Param_ValueType     Type;
} Param_Value;
/**
 * @brief show details of param
 */
typedef struct {
    Param_Value         Value;
    Param_LenType       Index;
} Param;
/**
 * @brief use for handle params and show current pos
 */
typedef struct {
    char*               Ptr;
    Str_LenType         Len;
    char                ParamSeperator;
    Param_LenType       Index;
} Param_Cursor;


Param* Param_next(Param_Cursor* cursor, Param* param);
Str_LenType Param_toStr(char* str, Param_Value* values, Param_LenType len, char* seperator);

Str_LenType Param_valueToStr(char* str, Param_Value* value);

char Param_compareValue(Param_Value* a, Param_Value* b);

uint8_t Param_parseBinary(Param_Cursor* cursor, Param* param);
uint8_t Param_parseHex(Param_Cursor* cursor, Param* param);
uint8_t Param_parseNum(Param_Cursor* cursor, Param* param);
uint8_t Param_parseString(Param_Cursor* cursor, Param* param);
uint8_t Param_parseState(Param_Cursor* cursor, Param* param);
uint8_t Param_parseStateKey(Param_Cursor* cursor, Param* param);
uint8_t Param_parseBoolean(Param_Cursor* cursor, Param* param);
uint8_t Param_parseNull(Param_Cursor* cursor, Param* param);
uint8_t Param_parseUnknown(Param_Cursor* cursor, Param* param);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif // _PARAM_H_
