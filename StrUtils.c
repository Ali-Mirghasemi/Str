#include "StrUtils.h"


/**
 * variables
 **/

#ifdef STR_USE_CONST_VARIABLES
    const char __Str_Decimal             = 10;
    const char __Str_0                   = '0';
    const char __Str_9                   = '9';
    const char __Str_Zero                = 0;
    const char __Str_One                 = 1;
    const Str_LenType __Str_MaxLength    = STR_MAX_LENGTH;
#else
    #define __Str_Decimal                10
    #define __Str_MaxLength              STR_MAX_LENGTH
    #define __Str_0                      '0'
    #define __Str_9                      '9'
    #define __Str_Zero                   0
    #define __Str_One                    1
#endif // STR_USE_CONST_VARIABLES

#ifndef NULL
    #define NULL                         ((const void*) 0)
#endif


void*       Mem_CopyReverse(const void* src, void* dest, Mem_LenType len) {
    unsigned char* pD = dest;
	while (len-- > 0){
		*pD-- = *((const unsigned char*)src)++;
	}
	return dest;
}

void*       Mem_Reverse(const void* arr, Mem_LenType len) {
    unsigned char* pStart = arr;
	unsigned char* pEnd = &((unsigned char*)arr)[len - 1];
	unsigned char temp;
	len >>= 1;
	while (len-- > 0){
		temp = *pEnd;
		*pEnd-- = *pStart;
		*pStart++ = temp;
	}
	return arr;
}

char*       Str_IndexOfEnd(char* str) {
    return &str[Str_Length(str) - 1];
}

char        Str_CompareInverse(char* str1, char* str2) {
    return -Str_Compare(str1, str2);
}

char        Str_CompareLimit(char* str1, char* str2) {
    char res;
	while (*str2 != '\0'){
		res = *str1++ - *str2++;
		if (res != 0){
			break;
		}
	}
	return res;
}

char*       Str_FindDigit(const char* str) {
    while ((*str < __Str_0 || *str > __Str_9) && 
            *str != '\0'){
		str++;
	}
	return *str == '\0' ? NULL : str;
}

char*       Str_FindDigitUntil(const char* str, char c) {
    while ((*str < __Str_0 || *str > __Str_9) && 
            *str != '\0' && 
            *str != c){
		str++;
	}
	return *str == '\0' || *str == c ? NULL : str;
}

char*       Str_FindDigitFix(const char* str, Str_LenType len) {
    while ((*str < __Str_0 || *str > __Str_9) && 
            *str != '\0' && 
            len-- > 0){
		str++;
	}
	return *str == '\0' || len == 0 ? NULL : str;
}

char*       Str_FindReverseDigit(const char* str) {
    return Str_FindReverseDigitFix(str, Str_Length(str));
}

char*       Str_FindReverseDigitFix(const char* str, Str_LenType len) {
    str = &str[len - 1];
    while ((*str < __Str_0 || *str > __Str_9) && 
            len-- > 0){
		str--;
	}
	return *str == '\0' || len == 0 ? NULL : str;
}

Str_LenType Str_IndexesOf(const char* str, char c, char const** indexes) {
    Str_LenType count = 0;
	while (*str != '\0'){
		if (c == *str){
			*indexes++ = str;
			count++;
		}
		str++;
	}
	return count;
}

Str_LenType Str_IndexesOfFix(const char* str, char c, char const** indexes, Str_LenType len) {
    Str_LenType count = 0;
	while (*str != '\0' && len-- > 0){
		if (c == *str){
			*indexes++ = str;
			count++;
		}
		str++;
	}
	return count;
}

Str_LenType Str_IndexesOfUntil(const char* str, char c, char const** indexes, char end) {
    Str_LenType count = 0;
	while (*str != '\0' && *str != end){
		if (c == *str){
			*indexes++ = str;
			count++;
		}
		str++;
	}
	return count;
}


char*       Str_IndexOfAt(const char* str, char c, Str_LenType num) {
    while (num-- > 0) {
        if (!(str = Str_IndexeOf(str, c))){
            break;
        }
    }
    return str;
}

char*       Str_IndexOfAtUntil(const char* str, char c, Str_LenType num, char end) {
    return Str_IndexOfAtFix(str, c, num, Str_PosOf(str, end));
}

char*       Str_IndexOfAtFix(const char* str, char c, Str_LenType num, Str_LenType len) {
    char* temp;
    while (num-- > 0) {
        temp = Mem_IndexOf(str, c, len);
        if (!temp) {
            break;
        }
        len -= temp - str;
        str = temp;
    }
    return temp;
}

char*       Str_Reverse(char* str) {
    return Mem_Reverse(str, Str_Length(str));
}

char*       Str_CopyReverse(const char* src, char* dest) {
    return Mem_CopyReverse(src, dest, Str_Length(src));
}

char*       Str_Substr(const char* str, char* dest, Str_LenType start) {
    return Str_Copy(&str[start], dest);
}

char*       Str_SubstrFix(const char* str, char* dest, Str_LenType start, Str_LenType len) {
    Str_CopyFix(&str[start], dest, len);
    dest[len] = '\0';
    return dest;
}

char*       Str_SubstrUntil(const char* str, char* dest, Str_LenType start, char c) {
    Str_LenType len = Str_PosOf(str, c);
    Str_CopyFix(&str[start], dest, len);
    dest[len] = '\0';
    return dest;
}

char*       Str_Replace(char* str, const char* word, const char* replacement) {
    char* word = Str_IndexOfStr(str, word);
    if (word) {
        Str_LenType wordLen = Str_Length(word);
        Str_LenType repLen = Str_Length(replacement);
         if (wordLen != repLen){
			Mem_Move(&str[wordLen], &str[repLen], Str_Length(str) - wordLen);
        }
        Str_CopyFix(str, replacement, repLen);
        return str;
    }
    return NULL;
}

char*       Str_CopyUntil(const char* src, char* dest, char c) {
    char* pStr = String_FindChar(src, c);
	if (pStr != 0){
        Str_CopyFix(src, dest, pStr - src);
        return dest;
	}
	return pStr;
}

char*       Str_CopyLine(const char* src, char* dest) {
    return Str_CopyUntil(src, dest, '\n');
}

char**      Str_Sort(char** strs, Str_LenType len) {

}
char**      Str_QuickSort(char** strs, Str_LenType len) {
    return Str_QuickSortBlock(strs, 0, len - 1, (Str_CompareFunc) Str_Compare);
}
char**      Str_SortReverse(char** strs, Str_LenType len) {

}
char**      Str_QuickSortReverse(char** strs, Str_LenType len) {
    return Str_QuickSortBlock(strs, 0, len - 1, (Str_CompareFunc) Str_CompareInverse);
}

Str_LenType Str_Split(const char* src, char c, char** strs) {
    Str_LenType count = 0;
    Str_LenType len;
    char* index = Str_IndexeOf(src, c);
    if (index) {
        while (index) {
            len = index - src;
            Str_CopyFix(src, *strs, len);
            *strs[len] = '\0';
            count++;
            strs++;
            src = index + 1;
            index = Str_IndexeOf(src, c);
        }
    }
    Str_Copy(src, *strs);
    count++;
    return count;
}

Str_LenType Str_SplitFix(const char* src, char c, char** strs, Str_LenType len) {
    Str_LenType count = 0;
    Str_LenType len;
    char* index = Str_IndexeOf(src, c);
    if (index) {
        while (index && --len > 0) {
            len = index - src;
            Str_CopyFix(src, *strs, len);
            *strs[len] = '\0';
            count++;
            strs++;
            src = index + 1;
            index = Str_IndexeOf(src, c);
        }
    }
    Str_Copy(src, *strs);
    count++;
    return count;
}

Str_LenType Str_PosOf(const char* str, char c) {
    return (Str_LenType) Str_IndexeOf(str, c) - (Str_LenType) str;
}

Str_LenType Str_LastPosOf(const char* str, char c) {
    return (Str_LenType) Str_LastIndexeOf(str, c) - (Str_LenType) str;
}

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

void        Str_Swap(char** itemA, char** itemB) {
    char* temp = *itemA;
    *itemA = *itemB;
    *itemB = temp;
}

Str_LenType Str_Partition(char** items, Str_LenType low, Str_LenType high, Str_CompareFunc cmp) {
    char* pivot = items[high];    // pivot 
    Str_LenType i = (low - 1);  // Index of smaller element 
    Str_LenType j;
    for (j = low; j <= high - 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (cmp(items[j], pivot) < 0) 
        { 
            i++;    // increment index of smaller element 
            Str_Swap(&items[i], &items[j]); 
        } 
    } 
    Str_Swap(&items[i + 1], &items[high]); 
    return (i + 1); 
}
char**      Str_QuickSortBlock(char** items, Mem_LenType low, Mem_LenType high, Str_CompareFunc cmp) {
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        Str_LenType pi = Str_Partition(items, low, high, cmp); 
  
        // Separately sort elements before 
        // partition and after partition 
        Str_QuickSortBlock(items, low, pi - 1, cmp); 
        Str_QuickSortBlock(items, pi + 1, high, cmp); 
    } 
}

