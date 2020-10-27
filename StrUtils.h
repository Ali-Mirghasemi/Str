#ifndef _STR_UTILS_H_
#define _STR_UTILS_H_
/**
 * StrUtils Options
 *
 **/

#define STR_ENABLE_PARSE

#define STR_ENABLE_CONVERT_STR

#define MEM_MAX_LENGTH                                      255

#define STR_MAX_LENGTH                                      255

#define STR_NUM_TYPE                                        int

#define STR_FLOAT_TYPE                                      float

#define STR_USE_CONST_VARIABLES

#define STR_USE_STRING_LIBRARY

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

typedef STR_NUM_TYPE            Str_NumType;
typedef unsigned STR_NUM_TYPE   Str_UNumType;
typedef STR_FLOAT_TYPE          Str_FloatType;

#ifdef STR_USE_STRING_LIBRARY
#include <string.h>

#define Mem_Copy(SRC, DEST, LEN)                            memcpy((DEST), (SRC), (LEN))
#define Mem_Compare(ARRAY1, ARRAY2, LEN)                    memcmp((ARRAY1), (ARRAY2), (LEN))
#define Mem_Move(SRC, DEST, LEN)                            memmove((DEST), (SRC), (LEN))
#define Mem_IndexOf(ARRAY, Byte, LEN)                       memchr((ARRAY), (Byte), (LEN))
#define Mem_Set(ARRAY, Value, LEN)                          memset((ARRAY), (Value), (LEN))

#define Str_Copy(SRC, DEST)                                 strcpy((DEST), (SRC))
#define Str_CopyFix(SRC, DEST, LEN)                         strncpy((DEST), (SRC), (LEN))
#define Str_Compare(STR1, STR2)                             strcmp((STR1), (STR2))
#define Str_CompareFix(STR1, STR2, LEN)                     strncmp((STR1), (STR2), (LEN))
#define Str_Length(STR)                                     strlen((STR))
#define Str_IndexOf(STR, CHAR)                              strchr((STR), (CHAR))
#define Str_LastIndexOf(STR, CHAR)                          strrchr((STR), (CHAR))
#define Str_IndexOfStr(STR, SUB)                            strstr((STR), (SUB))
#define Str_Append(STR, SUB)                                strcat((STR), (SUB))

#else

void*       Mem_Copy(const void* src, void* dest, Mem_LenType len);
char        Mem_Compare(const void* arr1, const void* arr2, Mem_LenType len);
void*       Mem_Move(const void* src, void* dest, Mem_LenType len);
void*       Mem_IndexOf(const void* arr, unsigned char value, Mem_LenType len);
void*       Mem_Set(void* arr, unsigned char value, Mem_LenType len);



char*       Str_Copy(const char* str, char* dest);
char*       Str_CopyFix(const char* str, char* dest, Str_LenType len);
char        Str_Compare(const char* str1, const char* str2);
char        Str_CompareFix(const char* str1, const char* str2, Str_LenType len);
Str_LenType Str_Length(const char* str);
char*       Str_IndexOf(char* str, char c);
char*       Str_LastIndexOf(char* str, char c);
char*       Str_IndexOfStr(char* str, char* sub);
char*       Str_Append(char* str, char* sub);

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
}  Str_BaseIndex;

void*       Mem_CopyReverse(const void* src, void* dest, Mem_LenType len);
void*       Mem_Reverse(void* arr, Mem_LenType len);

char*       Str_CopyUntil(const char* src, char* dest, char c);
char*       Str_CopyLine(const char* src, char* dest);

char*       Str_IndexOfEnd(const char* str);

char        Str_CompareInverse(const char* str1, const char* str2);
char        Str_CompareWord(const char* str, const char* word);

char*       Str_FindDigit(const char* str);
char*       Str_FindDigitUntil(const char* str, char c);
char*       Str_FindDigitFix(const char* str, Str_LenType len);

char*       Str_FindLastDigit(const char* str);
char*       Str_FindLastDigitUntil(const char* str, char c);
char*       Str_FindLastDigitFix(const char* str, Str_LenType len);

char*       Str_FindReverseDigit(const char* str);
char*       Str_FindReverseDigitFix(const char* str, Str_LenType len);

Str_LenType Str_IndexesOf(const char* str, char c, char const** indexes);
Str_LenType Str_IndexesOfFix(const char* str, char c, char const** indexes, Str_LenType len);
Str_LenType Str_IndexesOfUntil(const char* str, char c, char const** indexes, char end);

char*       Str_IndexOfAt(const char* str, char c, Str_LenType num);
char*       Str_IndexOfAtUntil(const char* str, char c, Str_LenType num, char end);
char*       Str_IndexOfAtFix(const char* str, char c, Str_LenType num, Str_LenType len);

char*       Str_Reverse(char* str);

char*       Str_CopyReverse(const char* src, char* dest);

char*       Str_Substr(const char* str, char* dest, Str_LenType start);
char*       Str_SubstrFix(const char* str, char* dest, Str_LenType start, Str_LenType len);
char*       Str_SubstrUntil(const char* str, char* dest, Str_LenType start, char c);

char*       Str_Replace(char* str, const char* word, const char* replacement);

const char** Str_Sort(const char** strs, Str_LenType len);
const char** Str_QuickSort(const char** strs, Str_LenType len);
const char** Str_SortReverse(const char** strs, Str_LenType len);
const char** Str_QuickSortReverse(const char** strs, Str_LenType len);

Str_LenType Str_Split(const char* src, char c, char** strs);
Str_LenType Str_SplitFix(const char* src, char c, char** strs, Str_LenType len);

Str_LenType Str_PosOf(const char* str, char c);
Str_LenType Str_LastPosOf(const char* str, char c);

Str_LenType Str_MultiCompare(const char** strs, Str_LenType len, const char* str);
Str_LenType Str_MultiCompareSorted(const char** strs, Str_LenType len, const char* str);

const char* Str_FindStrs(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result);
const char* Str_FindStrsSorted(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result);

const char* Str_FindStrsFix(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result, Str_LenType srcLen);
const char* Str_FindStrsSortedFix(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result, Str_LenType srcLen);

Str_LenType Str_ParseNum(Str_NumType num, Str_BaseIndex base, char len, char* str);
Str_LenType Str_ParseUNum(Str_UNumType num, Str_BaseIndex base, char len, char* str);

Str_Result Str_ConvertNum(const char* str, Str_NumType* num, Str_BaseIndex base);
Str_Result Str_ConvertUNum(const char* str, Str_UNumType* num, Str_BaseIndex base);
Str_Result Str_ConvertNumFix(const char* str, Str_NumType* num, Str_BaseIndex base, Str_LenType len);
Str_Result Str_ConvertUNumFix(const char* str, Str_UNumType* num, Str_BaseIndex base, Str_LenType len);

Str_LenType Str_ParseFloat(Str_FloatType num, char* str);
Str_LenType Str_ParseFloatFix(Str_FloatType num, char* str, Str_LenType decimalLen);

Str_Result Str_ConvertFloat(const char* str, Str_FloatType* num);
Str_Result Str_ConvertFloatFix(const char* str, Str_FloatType* num, Str_LenType len);

Str_Result Str_GetNum(const char* str, Str_NumType* num, const char** numPos);
Str_Result Str_GetUNum(const char* str, Str_UNumType* num, const char** numPos);
Str_Result Str_GetFloat(const char* str, Str_FloatType* num, const char** numPos);

/**
 * Sorting Functions
 **/

typedef char (*Mem_CompareFunc) (const void* itemA, const void* ItemB, Mem_LenType itemLen);

void*       Mem_Sort(void* items, Mem_LenType len, Mem_LenType itemLen, Mem_CompareFunc func);
void*       Mem_QuickSort(void* items, Mem_LenType len, Mem_LenType itemLen, Mem_CompareFunc func);

void        Mem_Swap(void* itemA, void* itemB, Mem_LenType item_len);
Mem_LenType Mem_Partition(void* items, Mem_LenType low, Mem_LenType high);
void*       Mem_QuickSortBlock(void* items, Mem_LenType low, Mem_LenType high);

typedef char (*Str_CompareFunc) (const char* itemA, const char* ItemB);

void        Str_Swap(const char** itemA, const char** ItemB);
Str_LenType Str_Partition(const char** items, Str_LenType low, Str_LenType high, Str_CompareFunc cmp);
const char** Str_QuickSortBlock(const char** items, Mem_LenType low, Mem_LenType high, Str_CompareFunc cmp);

const char** Str_SelectionSortBlock(const char** items, Mem_LenType len, Str_CompareFunc cmp);

Str_LenType Str_LinearSearch(const char** strs, Str_LenType len, const char* str, Str_CompareFunc cmp);
Str_LenType Str_BinarySearch(const char** strs, Str_LenType len, const char* str, Str_CompareFunc cmp);

#endif // _STR_UTILS_H_


