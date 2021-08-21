/**
 * @file StrStream.h
 * @author your name (you@domain.com)
 * @brief this library provide some of str functions based on Stream library
 * @version 0.1
 * @date 2021-08-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Str.h"
#include "StreamBuffer.h"

Stream* stream       StrStream_findDigit(Stream* stream);
Stream* stream       StrStream_findDigitUntil(Stream* stream, char c);
Stream* stream       StrStream_findDigitFix(Stream* stream, Str_LenType len);

Stream* stream       StrStream_findLastDigit(Stream* stream);
Stream* stream       StrStream_findLastDigitUntil(Stream* stream, char c);
Stream* stream       StrStream_findLastDigitFix(Stream* stream, Str_LenType len);

Stream* stream       StrStream_ignoreWhitespace(Stream* stream);
Stream* stream       StrStream_ignoreCharacters(Stream* stream);
Stream* stream       StrStream_ignoreAlphaNumeric(Stream* stream);
Stream* stream       StrStream_ignoreAlphabet(Stream* stream);
Stream* stream       StrStream_ignoreNumeric(Stream* stream);
Stream* stream       StrStream_ignoreSpecialCharacters(Stream* stream);
Stream* stream       StrStream_ignoreNameCharacters(Stream* stream);
Stream* stream       StrStream_ignoreCommandCharacters(Stream* stream);
Stream* stream       StrStream_ignore(Stream* stream, Str_IgnoreRoleFn cmp);

Str_LenType StrStream_parseNum(int num, Str_Radix base, char len, Stream* stream);
Str_LenType StrStream_parseUNum(unsigned int num, Str_Radix base, char len, Stream* stream);

Str_LenType StrStream_parseString(const char* string, Stream* stream);

Str_Result StrStream_convertNum(Stream* stream, int* num, Str_Radix base);
Str_Result StrStream_convertUNum(Stream* stream, unsigned int* num, Str_Radix base);
Str_Result StrStream_convertNumFix(Stream* stream, int* num, Str_Radix base, Str_LenType len);
Str_Result StrStream_convertUNumFix(Stream* stream, unsigned int* num, Str_Radix base, Str_LenType len);

Stream* stream StrStream_convertString(Stream* stream, char* string);
Stream* stream StrStream_convertStringFix(Stream* stream, char* string, Str_LenType len);

#if STR_ENABLE_LONG_NUMBER

Str_LenType StrStream_parseLong(long num, Str_Radix base, char len, Stream* stream);
Str_LenType StrStream_parseULong(unsigned long num, Str_Radix base, char len, Stream* stream);

Str_Result StrStream_convertLong(Stream* stream, long* num, Str_Radix base);
Str_Result StrStream_convertULong(Stream* stream, unsigned long* num, Str_Radix base);
Str_Result StrStream_convertLongFix(Stream* stream, long* num, Str_Radix base, Str_LenType len);
Str_Result StrStream_convertULongFix(Stream* stream, unsigned long* num, Str_Radix base, Str_LenType len);

#endif // STR_ENABLE_LONG_NUMBER

Str_LenType StrStream_parseFloat(float num, Stream* stream);
Str_LenType StrStream_parseFloatFix(float num, Stream* stream, Str_LenType decimalLen);

Str_Result StrStream_convertFloat(Stream* stream, float* num);
Str_Result StrStream_convertFloatFix(Stream* stream, float* num, Str_LenType len);

#if STR_ENABLE_DOUBLE

Str_LenType StrStream_parseDouble(double num, char* str);
Str_LenType StrStream_parseDoubleFix(double num, char* str, Str_LenType decimalLen);

Str_Result StrStream_convertDouble(Stream* stream, double* num);
Str_Result StrStream_convertDoubleFix(Stream* stream, double* num, Str_LenType len);

#endif // STR_ENABLE_DOUBLE

Str_Result Str_getNum(Stream* stream, int* num, const char** numPos);
Str_Result Str_getUNum(Stream* stream, unsigned int* num, const char** numPos);
Str_Result Str_getFloat(Stream* stream, float* num, const char** numPos);

