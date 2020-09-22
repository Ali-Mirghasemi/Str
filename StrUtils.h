#ifndef _STR_UTILS_H_
#define _STR_UTILS_H_
/**
 * StrUtils Options
 * 
 **/ 

#define STR_ENABLE_PARSE

#define STR_ENABLE_TO_STR

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

#ifdef  __CODEVISIONAVR__ 
    #define Mem_CopyFlash(SRC, DEST, LEN)                   memcpyf((DEST), (SRC), (LEN))
    #define Mem_CompareFlash(ARRAY1, ARRAY2, LEN)           memcmpf((ARRAY1), (ARRAY2), (LEN))

    #define Str_CopyFlash(DEST, SRC)                        strcpyf((DEST), (SRC))
    #define Str_CopyFixFlash(DEST, SRC, LEN)                strncpyf((DEST), (SRC), (LEN))
    #define Str_CompareFlash(STR1, STR2)                    strcmpf((STR1), (STR2))
    #define Str_CompareFixFlash(STR1, STR2, LEN)            strncmpf((STR1), (STR2), (LEN))
    #define Str_LengthFlash(STR)                            strlenf((STR))
    #define Str_IndexOfFlash(STR, CHAR)                     strchrf((STR), (CHAR))
    #define Str_LastIndexOfFlash(STR, CHAR)                 strrchrf((STR), (CHAR))
    #define Str_IndexOfStrFlash(STR, SUB)                   strstrf((STR), (SUB))
    #define Str_AppendFlash(STR, SUB)                       strcatf((STR), (SUB))
#endif

#else

void*       Mem_Copy(const void* src, void* dest, Mem_LenType len);
char        Mem_Compare(const void* arr1, const void* arr2, Mem_LenType len);
void*       Mem_Move(const void* src, void* dest, Mem_LenType len);
void*       Mem_IndexOf(const void* arr, unsigned char value, Mem_LenType len);
void*       Mem_Set(const void* arr, unsigned char value, Mem_LenType len);



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

void*       Mem_CopyReverse(const void* src, void* dest, Mem_LenType len);
void*       Mem_Reverse(const void* arr, Mem_LenType len);

char*       Str_CopyUntil(const char* src, char* dest, char c);
char*       Str_CopyLine(const char* src, char* dest);

char*       Str_IndexOfEnd(char* str);

char        Str_CompareInverse(char* str1, char* str2);
char        Str_CompareLimit(char* str1, char* str2);

char*       Str_FindDigit(const char* str);
char*       Str_FindDigitUntil(const char* str, char c);
char*       Str_FindDigitFix(const char* str, Str_LenType len);

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

char**      Str_Sort(char** strs, Str_LenType len);
char**      Str_QuickSort(char** strs, Str_LenType len);
char**      Str_SortReverse(char** strs, Str_LenType len);
char**      Str_QuickSortReverse(char** strs, Str_LenType len);

Str_LenType Str_Split(const char* src, char c, char** strs);
Str_LenType Str_SplitFix(const char* src, char c, char** strs, Str_LenType len);

Str_LenType Str_PosOf(const char* str, char c);
Str_LenType Str_LastPosOf(const char* str, char c);

Str_LenType Str_MultiCompare(const char** strs, Str_LenType len, const char* str);
Str_LenType Str_MultiCompareSorted(const char** strs, Str_LenType len, const char* str);

typedef struct {
    const char*     Position;
    Str_LenType     Index;
} Str_MultiResult;

const char* Str_FindStrs(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result);
const char* Str_FindStrsSorted(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result);

Str_LenType Str_FromNum(Str_NumType num, char base, char len, char* str);
Str_LenType Str_FromNumUnsigned(Str_UNumType num, char base, char len, char* str);

char        Str_ToNum(const char* str, Str_NumType* num, char base);
char        Str_ToNumUnsigned(const char* str, Str_UNumType* num, char base);
char        Str_ToNumFix(const char* str, Str_NumType* num, char base, Str_LenType len, char pad);
char        Str_ToNumUnsignedFix(const char* str, Str_UNumType* num, char base, Str_LenType len, char pad);

Str_LenType Str_FromFloat(Str_FloatType num, char* str);

Str_LenType Str_ToFloat(const char* str, Str_FloatType* num);
Str_LenType Str_ToFloatFix(const char* str, Str_FloatType* num, Str_LenType dec_len, Str_LenType float_len, char pad);


/**
 * Sorting Functions
 **/

typedef char (*Mem_CompareFunc) (void* itemA, void* ItemB);

void*       Mem_Sort(void* items, Mem_LenType len, Mem_LenType itemLen, Mem_CompareFunc func);
void*       Mem_QuickSort(void* items, Mem_LenType len, Mem_LenType itemLen, Mem_CompareFunc func);

void        Mem_Swap(void* itemA, void* itemB, Mem_LenType item_len);
Mem_LenType Mem_Partition(void* items, Mem_LenType low, Mem_LenType high);
void*       Mem_QuickSortBlock(void* items, Mem_LenType low, Mem_LenType high);

typedef char (*Str_CompareFunc) (char* itemA, char* ItemB);

void        Str_Swap(char** itemA, char** ItemB);
void        Str_Partition(char** items, Str_LenType low, Str_LenType high, Str_CompareFunc cmp);
char**      Str_QuickSortBlock(char** items, Mem_LenType low, Mem_LenType high, Str_CompareFunc cmp);


#endif // _STR_UTILS_H_


