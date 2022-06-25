#include "Param.h"

#define PARAM_DEFAULT_NULL_LEN     (sizeof(PARAM_DEFAULT_NULL) - 1)
#define PARAM_DEFAULT_TRUE_LEN     (sizeof(PARAM_DEFAULT_TRUE) - 1)
#define PARAM_DEFAULT_FALSE_LEN    (sizeof(PARAM_DEFAULT_FALSE) - 1)
#define PARAM_DEFAULT_OFF_LEN      (sizeof(PARAM_DEFAULT_OFF) - 1)
#define PARAM_DEFAULT_ON_LEN       (sizeof(PARAM_DEFAULT_ON) - 1)
#define PARAM_DEFAULT_HIGH_LEN     (sizeof(PARAM_DEFAULT_HIGH) - 1)
#define PARAM_DEFAULT_LOW_LEN      (sizeof(PARAM_DEFAULT_LOW) - 1)
#define PARAM_DEFAULT_HEX_LEN      (sizeof(PARAM_DEFAULT_HEX) - 1)
#define PARAM_DEFAULT_BIN_LEN      (sizeof(PARAM_DEFAULT_BIN) - 1)

#if PARAM_CASE_MODE == PARAM_CASE_HIGHER
    #define __convert(STR, LEN) Str_upperCaseFix((STR), (LEN))
#elif PARAM_CASE_MODE == PARAM_CASE_LOWER || PARAM_CASE_MODE == PARAM_CASE_INSENSITIVE
    #define __convert(STR, LEN) Str_lowerCaseFix((STR), (LEN))
#else
    #error "PARAM_CASE_MODE not defined"
#endif // PARAM_CASE_MODE



/**
 * @brief parse next param and return
 *
 * @param cursor
 * @param param
 * @return Param* return param
 */
Param* Param_next(Param_Cursor* cursor, Param* param) {
    char* pStr = cursor->Ptr;
    Str_LenType tempLen;
    uint8_t res = 0;
    // check cursor is valid
    if (cursor->Ptr == NULL || (*cursor->Ptr == '\0' && cursor->Len == 0)) {
        return NULL;
    }
    // ignore whitspaces
    cursor->Ptr = Str_ignoreWhitespace(cursor->Ptr);
    tempLen = (Str_LenType)(cursor->Ptr - pStr);
    cursor->Len -= tempLen;
    pStr = cursor->Ptr;
    tempLen = cursor->Len;
    // find value type base on first character
    switch (*cursor->Ptr) {
        case '0':
            switch (*(cursor->Ptr + 1)) {
            #if PARAM_CASE_MODE & PARAM_CASE_HIGHER != 0
                case 'b':
            #endif
            #if PARAM_CASE_MODE & PARAM_CASE_HIGHER != 0
                case 'B':
            #endif
                    // binary num
                    res = Param_parseBinary(cursor, param);
                    break;
            #if PARAM_CASE_MODE & PARAM_CASE_LOWER != 0
                case 'x':
            #endif
            #if PARAM_CASE_MODE & PARAM_CASE_HIGHER != 0
                case 'X':
            #endif
                    // hex num
                    res = Param_parseHex(cursor, param);
                    break;
            }
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '-':
            // check for number or its float
            if (!res) {
                res = Param_parseNum(cursor, param);
            }
            break;
    #if PARAM_CASE_MODE & PARAM_CASE_LOWER != 0
        case 't':
        case 'f':
    #endif
    #if PARAM_CASE_MODE & PARAM_CASE_HIGHER != 0
        case 'T':
        case 'F':
    #endif
            // boolean
            res = Param_parseBoolean(cursor, param);
            break;
    #if PARAM_CASE_MODE & PARAM_CASE_LOWER != 0
        case 'o':
    #endif
    #if PARAM_CASE_MODE & PARAM_CASE_HIGHER != 0
        case 'O':
    #endif
            // state
            res = Param_parseStateKey(cursor, param);
            break;
    #if PARAM_CASE_MODE & PARAM_CASE_LOWER != 0
        case 'l':
        case 'h':
    #endif
    #if PARAM_CASE_MODE & PARAM_CASE_HIGHER != 0
        case 'L':
        case 'H':
    #endif
            // state key
            res = Param_parseState(cursor, param);
            break;
        case '"':
            // string
            res = Param_parseString(cursor, param);
            break;
    #if PARAM_CASE_MODE & PARAM_CASE_LOWER != 0
        case 'n':
    #endif
    #if PARAM_CASE_MODE & PARAM_CASE_HIGHER != 0
        case 'N':
    #endif
            res = Param_parseNull(cursor, param);
            break;
        /*default:
            // unknown
            res = Param_parseUnknown(cursor, param);
            break;*/
    }
    // check if param is not valid
    if (!res) {
        cursor->Ptr = pStr;
        cursor->Len = tempLen;
        Param_parseUnknown(cursor, param);
    }
    else if (param->Value.Type != Param_ValueType_Null) {
        // find next seperator
        pStr = Str_indexOf(cursor->Ptr, cursor->ParamSeperator);
        if (pStr != NULL) {
            Str_LenType len = (Str_LenType)(pStr - cursor->Ptr);
            cursor->Ptr = pStr + 1;
            cursor->Len -= len + 1;
        }
        else {
            cursor->Ptr = NULL;
            cursor->Len = 0;
            //param = NULL;
        }
    }
    // return param
    param->Index = ++cursor->Index;
    return param;
}
/**
 * @brief parse binary strings
 * ex: "0b1010" -> 0xA
 *
 * @param cursor
 * @param param
 * @return uint8_t
 */
uint8_t Param_parseBinary(Param_Cursor* cursor, Param* param) {
    char* pStr = cursor->Ptr;
    Str_LenType len;
    cursor->Ptr = Str_ignoreNumeric(cursor->Ptr + 2);
    len = (Str_LenType)(cursor->Ptr - pStr);
    cursor->Len -= len;

    param->Value.Type = Param_ValueType_NumberBinary;
    return Str_convertUNumFix(pStr + 2, (unsigned int*) &param->Value.NumberBinary, Str_Binary, len - 2) == Str_Ok;
}
/**
 * @brief parse hex strings
 * ex: "0xA" -> 0xA
 *
 * @param cursor
 * @param param
 * @return uint8_t
 */
uint8_t Param_parseHex(Param_Cursor* cursor, Param* param) {
    char* pStr = cursor->Ptr;
    Str_LenType len;
    cursor->Ptr = Str_ignoreAlphaNumeric(cursor->Ptr + 2);
    len = (Str_LenType)(cursor->Ptr - pStr);
    cursor->Len -= len;

    param->Value.Type = Param_ValueType_NumberHex;
    return Str_convertUNumFix(pStr + 2, (unsigned int*) &param->Value.NumberHex, Str_Hex, len - 2) == Str_Ok;
}
/**
 * @brief parse number strings
 * ex: "123" -> 123
 *
 * @param cursor
 * @param param
 * @return uint8_t
 */
uint8_t Param_parseNum(Param_Cursor* cursor, Param* param) {
    char* pStr = cursor->Ptr;
    Str_LenType len;

    if (*cursor->Ptr == '-') {
        cursor->Ptr++;
    }
    cursor->Ptr = Str_ignoreNumeric(cursor->Ptr);

    if (*cursor->Ptr == '.') {
        // it's float
        cursor->Ptr = Str_ignoreNumeric(cursor->Ptr + 1);
        len = (Str_LenType)(cursor->Ptr - pStr);
        cursor->Len -= len;

        param->Value.Type = Param_ValueType_Float;
        return Str_convertFloatFix(pStr, &param->Value.Float, len) == Str_Ok;
    }
    else {
        // it's number
        len = (Str_LenType)(cursor->Ptr - pStr);
        cursor->Len -= len;
        param->Value.Type = Param_ValueType_Number;
        return Str_convertNumFix(pStr, (int*) &param->Value.Number, Str_Decimal, len) == Str_Ok;
    }
}
/**
 * @brief parse strings
 * ex: "\"Text\"" -> "Text"
 *
 * @param cursor
 * @param param
 * @return uint8_t
 */
uint8_t Param_parseString(Param_Cursor* cursor, Param* param) {
    char* pStr = cursor->Ptr;
    Str_LenType len = Str_fromString(cursor->Ptr) + 2;

    if (len != -1) {
        cursor->Ptr += len;
        cursor->Len -= len;

        param->Value.Type = Param_ValueType_String;
        param->Value.String = pStr;

        return 1;
    }
    else {
        return 0;
    }
}
/**
 * @brief parse state strings
 * ex: "high" -> 1 or "low" -> 0
 *
 * @param cursor
 * @param param
 * @return uint8_t
 */
uint8_t Param_parseState(Param_Cursor* cursor, Param* param) {
    char* pStr = cursor->Ptr;
    Str_LenType len;
    cursor->Ptr = Str_ignoreAlphabet(cursor->Ptr);
    len = (Str_LenType)(cursor->Ptr - pStr);
    cursor->Len -= len;

    __convert(pStr, len);
    param->Value.Type = Param_ValueType_State;
    if (len == 4 &&
    #if PARAM_CASE_MODE == PARAM_CASE_LOWER
        Str_compareFix(pStr, "high", len) == 0
    #elif PARAM_CASE_MODE == PARAM_CASE_HIGHER
        Str_compareFix(pStr, "HIGH", len) == 0
    #else
        (Str_compareFix(pStr, "high", len) == 0 || Str_compareFix(pStr, "HIGH", len) == 0)
    #endif
    ) {
        param->Value.State = 1;
        return 1;
    }
    else if (len == 3 &&
    #if PARAM_CASE_MODE == PARAM_CASE_LOWER
        Str_compareFix(pStr, "low", len) == 0
    #elif PARAM_CASE_MODE == PARAM_CASE_HIGHER
        Str_compareFix(pStr, "LOW", len) == 0
    #else
        (Str_compareFix(pStr, "low", len) == 0 || Str_compareFix(pStr, "LOW", len) == 0)
    #endif
    ) {
        param->Value.State = 0;
        return 1;
    }
    else {
        return 0;
    }
}
/**
 * @brief parse state key strings
 * ex: "on" -> 1 or "off" -> 0
 *
 * @param cursor
 * @param param
 * @return uint8_t
 */
uint8_t Param_parseStateKey(Param_Cursor* cursor, Param* param) {
    char* pStr = cursor->Ptr;
    Str_LenType len;
    cursor->Ptr = Str_ignoreAlphabet(cursor->Ptr);
    len = (Str_LenType)(cursor->Ptr - pStr);
    cursor->Len -= len;

    __convert(pStr, len);
    param->Value.Type = Param_ValueType_StateKey;
    if (len == 2 &&
    #if PARAM_CASE_MODE == PARAM_CASE_LOWER
        Str_compareFix(pStr, "on", len) == 0
    #elif PARAM_CASE_MODE == PARAM_CASE_HIGHER
        Str_compareFix(pStr, "ON", len) == 0
    #else
        (Str_compareFix(pStr, "on", len) == 0 || Str_compareFix(pStr, "ON", len) == 0)
    #endif
    ) {
        param->Value.StateKey = 1;
        return 1;
    }
    else if (len == 3 &&
    #if PARAM_CASE_MODE == PARAM_CASE_LOWER
        Str_compareFix(pStr, "off", len) == 0
    #elif PARAM_CASE_MODE == PARAM_CASE_HIGHER
        Str_compareFix(pStr, "OFF", len) == 0
    #else
        (Str_compareFix(pStr, "off", len) == 0 || Str_compareFix(pStr, "OFF", len) == 0)
    #endif
    ) {
        param->Value.StateKey = 0;
        return 1;
    }
    else {
        return 0;
    }
}
/**
 * @brief parse boolean strings
 * ex: "true" -> true or "false" -> false
 *
 * @param cursor
 * @param param
 * @return uint8_t
 */
uint8_t Param_parseBoolean(Param_Cursor* cursor, Param* param) {
    char* pStr = cursor->Ptr;
    Str_LenType len;
    cursor->Ptr = Str_ignoreAlphabet(cursor->Ptr);
    len = (Str_LenType)(cursor->Ptr - pStr);
    cursor->Len -= len;

    __convert(pStr, len);
    param->Value.Type = Param_ValueType_Boolean;
    if (len == 4 &&
    #if PARAM_CASE_MODE == PARAM_CASE_LOWER
        Str_compareFix(pStr, "true", len) == 0
    #elif PARAM_CASE_MODE == PARAM_CASE_HIGHER
        Str_compareFix(pStr, "TRUE", len) == 0
    #else
        (Str_compareFix(pStr, "true", len) == 0 || Str_compareFix(pStr, "TRUE", len) == 0)
    #endif
    ) {
        param->Value.Boolean = 1;
        return 1;
    }
    else if (len == 5 &&
    #if PARAM_CASE_MODE == PARAM_CASE_LOWER
        Str_compareFix(pStr, "false", len) == 0
    #elif PARAM_CASE_MODE == PARAM_CASE_HIGHER
        Str_compareFix(pStr, "FALSE", len) == 0
    #else
        (Str_compareFix(pStr, "false", len) == 0 || Str_compareFix(pStr, "FALSE", len) == 0)
    #endif
    ) {
        param->Value.Boolean = 0;
        return 1;
    }
    else {
        return 0;
    }
}
/**
 * @brief parse null
 * ex: "null" -> NULL
 *
 * @param cursor
 * @param param
 * @return uint8_t
 */
uint8_t Param_parseNull(Param_Cursor* cursor, Param* param) {
    char* pStr = cursor->Ptr;
    Str_LenType len;
    cursor->Ptr = Str_ignoreAlphabet(cursor->Ptr);
    len = (Str_LenType)(cursor->Ptr - pStr);
    cursor->Len -= len;

    __convert(pStr, len);
    if (len == 4 &&
    #if PARAM_CASE_MODE == PARAM_CASE_LOWER
        Str_compareFix(pStr, "null", len) == 0
    #elif PARAM_CASE_MODE == PARAM_CASE_HIGHER
        Str_compareFix(pStr, "NULL", len) == 0
    #else
        (Str_compareFix(pStr, "null", len) == 0 || Str_compareFix(pStr, "NULL", len) == 0)
    #endif
    ) {
        param->Value.Type = Param_ValueType_Null;
        param->Value.Null = pStr;
        if (cursor->Len != 0) {
            *cursor->Ptr++ = '\0';
            cursor->Len--;
        }
        return 1;
    }
    else {
        return 0;
    }
}
/**
 * @brief parse unknown type
 *
 * @param cursor
 * @param param
 * @return uint8_t
 */
uint8_t Param_parseUnknown(Param_Cursor* cursor, Param* param) {
    char* pTemp;
    param->Value.Type = Param_ValueType_Unknown;
    param->Value.Unknown = cursor->Ptr;

    pTemp = Str_indexOf(cursor->Ptr, cursor->ParamSeperator);
    if (pTemp) {
        Str_LenType len;
        cursor->Ptr = pTemp;
        len = (Str_LenType)(pTemp - param->Value.Unknown);
        cursor->Len -= len;
        if (cursor->Len != 0) {
            *cursor->Ptr++ = '\0';
            cursor->Len--;
        }
    }
    else {
        cursor->Ptr = NULL;
        cursor->Len = 0;
    }

    return 1;
}
/**
 * @brief compare param values, first ValueType and second Value
 *
 * @param a
 * @param b
 * @return char return 0 if not equal otherwise return 1
 */
char Param_compareValue(Param_Value* a, Param_Value* b) {
    if (a->Type != b->Type) {
        return 0;
    }
    switch (a->Type) {
        case Param_ValueType_NumberBinary:
            return a->NumberBinary == b->NumberBinary;
        case Param_ValueType_NumberHex:
            return a->NumberHex == b->NumberHex;
        case Param_ValueType_Number:
            return a->Number == b->Number;
        case Param_ValueType_Float:
            return a->Float == b->Float;
        case Param_ValueType_String:
            return Str_compare(a->String, b->String) == 0;
        case Param_ValueType_State:
            return a->State == b->State;
        case Param_ValueType_StateKey:
            return a->StateKey == b->StateKey;
        case Param_ValueType_Boolean:
            return a->Boolean == b->Boolean;
        case Param_ValueType_Null:
        #if PARAM_COMPARE_NULL_VAL
            return Str_compare(a->Null, b->Null) == 0;
        #else
            return 1;
        #endif // PARAM_COMPARE_NULL_VAL
        case Param_ValueType_Unknown:
        #if PARAM_COMPARE_UNKNOWN_VAL
            return Str_compare(a->Unknown, b->Unknown) == 0;
        #else
            return 1;
        #endif // PARAM_COMPARE_UNKNOWN_VAL
        default:
            return 0;
    }
}
/**
 * @brief convert array of values to string
 *
 * @param str
 * @param values
 * @param len
 * @param seperator
 * @return Str_LenType
 */
Str_LenType Param_toStr(char* str, Param_Value* values, Param_LenType len, char* seperator) {
    char* base = str;
    Str_LenType sepLen = Str_len(seperator);
    while (--len > 0) {
        // convert value
        str += Param_valueToStr(str, values++);
        // add seperator
        if (seperator) {
            Str_copy(str, seperator);
            str += sepLen;
        }
    }
    // convert value
    str += Param_valueToStr(str, values++);
    return (Str_LenType)(str - base);
}
/**
 * @brief convert value to string and return string length
 *
 * @param str
 * @param value
 * @return Str_LenType
 */
Str_LenType Param_valueToStr(char* str, Param_Value* value) {
    char* pStr;
    switch (value->Type) {
        case Param_ValueType_Number:
            return Str_parseNum(value->Number, Str_Decimal, STR_NORMAL_LEN, str);
        case Param_ValueType_NumberHex:
            Str_copy(str, PARAM_DEFAULT_HEX);
            return Str_parseNum(value->NumberHex, Str_Hex, STR_NORMAL_LEN, str + PARAM_DEFAULT_HEX_LEN) + PARAM_DEFAULT_HEX_LEN;
        case Param_ValueType_NumberBinary:
            Str_copy(str, PARAM_DEFAULT_BIN);
            return Str_parseNum(value->NumberBinary, Str_Binary, STR_NORMAL_LEN, str + PARAM_DEFAULT_BIN_LEN) + PARAM_DEFAULT_BIN_LEN;
        case Param_ValueType_Float:
        #if PARAM_FLOAT_DECIMAL_LEN != 0
            return Str_parseFloatFix(value->Float, str, PARAM_FLOAT_DECIMAL_LEN);
        #else
            return Str_parseFloat(value->Float, str);
        #endif
        case Param_ValueType_String:
            pStr = Str_convertString(value->String, str);
            return (Str_LenType)(pStr - str);
        case Param_ValueType_State:
            if (value->State != 0) {
                Str_copy(str, PARAM_DEFAULT_HIGH);
                return PARAM_DEFAULT_HIGH_LEN;
            }
            else {
                Str_copy(str, PARAM_DEFAULT_LOW);
                return PARAM_DEFAULT_LOW_LEN;
            }
            break;
        case Param_ValueType_StateKey:
            if (value->StateKey != 0) {
                Str_copy(str, PARAM_DEFAULT_ON);
                return PARAM_DEFAULT_ON_LEN;
            }
            else {
                Str_copy(str, PARAM_DEFAULT_OFF);
                return PARAM_DEFAULT_OFF_LEN;
            }
            break;
        case Param_ValueType_Boolean:
            if (value->Boolean != 0) {
                Str_copy(str, PARAM_DEFAULT_TRUE);
                return PARAM_DEFAULT_TRUE_LEN;
            }
            else {
                Str_copy(str, PARAM_DEFAULT_FALSE);
                return PARAM_DEFAULT_FALSE_LEN;
            }
            break;
        case Param_ValueType_Null:
            Str_copy(str, PARAM_DEFAULT_NULL);
            return PARAM_DEFAULT_NULL_LEN;
        case Param_ValueType_Unknown:
            Str_copy(str, value->Unknown);
            return Str_len(value->Unknown);
        default:
            return 0;
    }
}
