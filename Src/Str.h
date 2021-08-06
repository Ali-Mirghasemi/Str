#ifndef _STR_UTILS_H_
#define _STR_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/********************************************************************************************/
/*                                     Configuration                                        */
/********************************************************************************************/
#define STR_ENABLE_PARSE                                    1

#define STR_ENABLE_CONVERT_STR                              1

#define MEM_MAX_LENGTH                                      255

#define STR_MAX_LENGTH                                      255

#define STR_ENABLE_LONG_NUMBER                              1

#define STR_ENABLE_DOUBLE                                   1

#define STR_USE_CONST_VARIABLES                             0

#define STR_USE_STRING_LIBRARY                              1

/********************************************************************************************/

#if STR_MAX_LENGTH < 0x7F
    typedef char Str_LenType;
#elif STR_MAX_LENGTH < 0x7FFF
    typedef short Str_LenType;
#else
    typedef int Str_LenType;
#endif // STR_MAX_Length

#if MEM_MAX_LENGTH < 0x7F
    typedef char Mem_LenType;
#elif STR_MAX_LENGTH < 0x7FFF
    typedef short Mem_LenType;
#else
    typedef int Mem_LenType;
#endif // STR_MAX_Length

#if STR_USE_STRING_LIBRARY
#include <string.h>

#define Mem_copy                            memcpy
#define Mem_compare                         memcmp
#define Mem_move                            memmove
#define Mem_indexOf                         memchr
#define Mem_set                             memset

#define Str_copy                            strcpy
#define Str_copyFix                         strncpy
#define Str_compare                         strcmp
#define Str_compareFix                      strncmp
#define Str_len                             strlen
#define Str_indexOf                         strchr
#define Str_lastIndexOf                     strrchr
#define Str_indexOfStr                      strstr
#define Str_append                          strcat

#else

void*       Mem_copy(void* dest, const void* src, Mem_LenType len);
char        Mem_compare(const void* arr1, const void* arr2, Mem_LenType len);
void*       Mem_move(void* dest, const void* src, Mem_LenType len);
void*       Mem_indexOf(const void* arr, unsigned char value, Mem_LenType len);
void*       Mem_set(void* arr, unsigned char value, Mem_LenType len);



char*       Str_copy(char* dest, const char* str);
char*       Str_copyFix(char* dest, const char* str, Str_LenType len);
char        Str_compare(const char* str1, const char* str2);
char        Str_compareFix(const char* str1, const char* str2, Str_LenType len);
Str_LenType Str_len(const char* str);
char*       Str_indexOf(char* str, char c);
char*       Str_lastIndexOf(char* str, char c);
char*       Str_indexOfStr(char* str, char* sub);
char*       Str_append(char* str, char* sub);

#endif // STR_USE_STRING_LIBRARY

#define STR_NORMAL_LEN      0

typedef enum {
    Str_Ok,
    Str_Error
} Str_Result;

typedef struct {
    const char*     IndexOf;
    Str_LenType     Position;
} Str_MultiResult;

typedef enum {
    Str_Binary      = 2,
    Str_Nibble      = 4,
    Str_Octal       = 8,
    Str_Decimal     = 10,
    Str_Hex         = 16,
}  Str_Radix;

void*       Mem_copyReverse(void* dest, const void* src, Mem_LenType len);
void*       Mem_reverse(void* arr, Mem_LenType len);

char*       Str_copyUntil(char* dest, const char* src, char c);
char*       Str_copyLine(char* dest, const char* src);

char*       Str_reverseIndexOf(const char* str, char c, const char* startOfStr);
char*       Str_reverseIndexOfFix(const char* str, char c, int length);

char*       Str_indexOfEnd(const char* str);

char        Str_compareInverse(const char* str1, const char* str2);
char        Str_compareWord(const char* str, const char* word);

char*       Str_findDigit(const char* str);
char*       Str_findDigitUntil(const char* str, char c);
char*       Str_findDigitFix(const char* str, Str_LenType len);

char*       Str_findLastDigit(const char* str);
char*       Str_findLastDigitUntil(const char* str, char c);
char*       Str_findLastDigitFix(const char* str, Str_LenType len);

char*       Str_ignoreWhitespace(const char* str);
char*       Str_ignoreCharacters(const char* str);

char*       Str_ignoreWhitespaceReverse(const char* str);
char*       Str_ignoreCharactersReverse(const char* str);

char*       Str_trimLeft(char* str);
char*       Str_trimRight(char* str);
char*       Str_trim(char* str);

char*       Str_findReverseDigit(const char* str);
char*       Str_findReverseDigitFix(const char* str, Str_LenType len);

Str_LenType Str_indexesOf(const char* str, char c, char const** indexes);
Str_LenType Str_indexesOfFix(const char* str, char c, char const** indexes, Str_LenType len);
Str_LenType Str_indexesOfUntil(const char* str, char c, char const** indexes, char end);

char*       Str_indexOfAt(const char* str, char c, Str_LenType num);
char*       Str_indexOfAtUntil(const char* str, char c, Str_LenType num, char end);
char*       Str_indexOfAtFix(const char* str, char c, Str_LenType num, Str_LenType len);

char*       Str_reverse(char* str);

char*       Str_copyReverse(char* dest, const char* src);

char*       Str_substr(char* dest, const char* str, Str_LenType start);
char*       Str_substrFix(char* dest, const char* str, Str_LenType start, Str_LenType len);
char*       Str_substrUntil(char* dest, const char* str, Str_LenType start, char c);

char*       Str_replace(char* str, const char* word, const char* replacement);
int         Str_replaceAll(char* str, const char* word, const char* replacement);

const char** Str_sort(const char** strs, Str_LenType len);
const char** Str_quickSort(const char** strs, Str_LenType len);
const char** Str_sortReverse(const char** strs, Str_LenType len);
const char** Str_quickSortReverse(const char** strs, Str_LenType len);

Str_LenType Str_split(const char* src, char c, char** strs);
Str_LenType Str_splitFix(const char* src, char c, char** strs, Str_LenType len);

Str_LenType Str_posOf(const char* str, char c);
Str_LenType Str_lastPosOf(const char* str, char c);

Str_LenType Str_multiCompare(const char** strs, Str_LenType len, const char* str);
Str_LenType Str_multiCompareSorted(const char** strs, Str_LenType len, const char* str);

const char* Str_findStrs(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result);
const char* Str_findStrsSorted(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result);

const char* Str_findStrsFix(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result, Str_LenType srcLen);
const char* Str_findStrsSortedFix(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result, Str_LenType srcLen);

Str_LenType Str_parseNum(int num, Str_Radix base, char len, char* str);
Str_LenType Str_parseUNum(unsigned int num, Str_Radix base, char len, char* str);

Str_Result Str_convertNum(const char* str, int* num, Str_Radix base);
Str_Result Str_convertUNum(const char* str, unsigned int* num, Str_Radix base);
Str_Result Str_convertNumFix(const char* str, int* num, Str_Radix base, Str_LenType len);
Str_Result Str_convertUNumFix(const char* str, unsigned int* num, Str_Radix base, Str_LenType len);

#if STR_ENABLE_LONG_NUMBER

Str_LenType Str_parseLong(long num, Str_Radix base, char len, char* str);
Str_LenType Str_parseULong(unsigned long num, Str_Radix base, char len, char* str);

Str_Result Str_convertLong(const char* str, long* num, Str_Radix base);
Str_Result Str_convertULong(const char* str, unsigned long* num, Str_Radix base);
Str_Result Str_convertLongFix(const char* str, long* num, Str_Radix base, Str_LenType len);
Str_Result Str_convertULongFix(const char* str, unsigned long* num, Str_Radix base, Str_LenType len);

#endif // STR_ENABLE_LONG_NUMBER

Str_LenType Str_parseFloat(float num, char* str);
Str_LenType Str_parseFloatFix(float num, char* str, Str_LenType decimalLen);

Str_Result Str_convertFloat(const char* str, float* num);
Str_Result Str_convertFloatFix(const char* str, float* num, Str_LenType len);

#if STR_ENABLE_DOUBLE

Str_LenType Str_parseDouble(double num, char* str);
Str_LenType Str_parseDoubleFix(double num, char* str, Str_LenType decimalLen);

Str_Result Str_convertDouble(const char* str, double* num);
Str_Result Str_convertDoubleFix(const char* str, double* num, Str_LenType len);

#endif // STR_ENABLE_DOUBLE

Str_Result Str_getNum(const char* str, int* num, const char** numPos);
Str_Result Str_getUNum(const char* str, unsigned int* num, const char** numPos);
Str_Result Str_getFloat(const char* str, float* num, const char** numPos);

/**
 * Sorting Functions
 **/

typedef char (*Mem_CompareFn) (const void* itemA, const void* itemB, Mem_LenType itemLen);
typedef void (*Mem_SwapFn) (const void* itemA, const void* itemB, Mem_LenType itemLen);

void*       Mem_sort(void* items, Mem_LenType len, Mem_LenType itemLen, Mem_CompareFn cmp, Mem_SwapFn swap);
void*       Mem_quickSort(void* items, Mem_LenType len, Mem_LenType itemLen, Mem_CompareFn cmp, Mem_SwapFn swap);

Mem_LenType Mem_partition(void* items, Mem_LenType low, Mem_LenType high, Mem_LenType itemLen, Mem_CompareFn cmp, Mem_SwapFn swap);
void*       Mem_quickSortBlock(void* items, Mem_LenType low, Mem_LenType high, Mem_LenType itemLen, Mem_CompareFn cmp, Mem_SwapFn swap);

Mem_LenType Mem_linearSearch(const void* items, Mem_LenType len, Mem_LenType itemLen, const void* item, Mem_CompareFn cmp);
Mem_LenType Mem_binarySearch(const void* items, Mem_LenType len, Mem_LenType itemLen, const void* item, Mem_CompareFn cmp);

typedef char (*Str_CompareFn) (const char* itemA, const char* ItemB);

void        Str_swap(const char** itemA, const char** ItemB);
Str_LenType Str_partition(const char** items, Str_LenType low, Str_LenType high, Str_CompareFn cmp);
const char** Str_quickSortBlock(const char** items, Mem_LenType low, Mem_LenType high, Str_CompareFn cmp);

const char** Str_selectionSortBlock(const char** items, Mem_LenType len, Str_CompareFn cmp);

Str_LenType Str_linearSearch(const char** strs, Str_LenType len, const char* str, Str_CompareFn cmp);
Str_LenType Str_binarySearch(const char** strs, Str_LenType len, const char* str, Str_CompareFn cmp);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // _STR_UTILS_H_

