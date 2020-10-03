#include "StrUtils.h"

#ifdef STR_USE_STRING_LIBRARY
    #include <string.h>
#endif

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

#ifdef STR_USE_STRING_LIBRARY
    #define __Str_Compare               strcmp
#else
    #define __Str_Compare               Str_Compare
#endif // STR_USE_STRING_LIBRARY


/**
 * @brief thie function can use for copy array into another array with reverse order
 *
 * @param src address of source array that we want copy from
 * @param dest address of destination array that we want copy into
 * @param len number of bytes
 * @return void* address of destination array
 */
void*       Mem_CopyReverse(const void* src, void* dest, Mem_LenType len) {
    unsigned char* pD = (unsigned char*) dest;
    unsigned char* pS = (unsigned char*) src;
	while (len-- > 0){

		*pD-- = *pS++;
	}
	return dest;
}
/**
 * @brief reverse order of bytes in array
 *
 * @param arr address of array that we want reverse order
 * @param len number of byte
 * @return void* address of array
 */
void*       Mem_Reverse(void* arr, Mem_LenType len) {
    unsigned char* pStart = (unsigned char*) arr;
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
/**
 * @brief this function return end of string (Null charachter)
 *
 * @param str address of string must include 'null' in end of it
 * @return char* address of null charachter
 */
char*       Str_IndexOfEnd(const char* str) {
    return (char*) &str[Str_Length(str) - 1];
}
/**
 * @brief compare two string and result is opposite of Str_Compare
 *
 * @param str1 address of string 1
 * @param str2 address of string 2
 * @return char result of compare,
 *      str1 > str2 -> result < 0
 *      str1 == str2 -> result == 0
 *      str1 < str2 -> result > 0
 */
char        Str_CompareInverse(const char* str1, const char* str2) {
    return Str_Compare(str2, str1);
}
/**
 * @brief compare word in str, with priority of word and continue until word reach null
 *
 * @param str address of base string
 * @param word address of word that we want compare with str
 * @return char result of compare,
 *      str > word -> result > 0
 *      str == word -> result == 0
 *      str < word -> result < 0
 */
char        Str_CompareWord(const char* str, const char* word) {
    char res;
	while (*word != '\0'){
		res = *str++ - *word++;
		if (res != 0){
			break;
		}
	}
	return res;
}
/**
 * @brief find first digit in string and return address of digit
 *
 * @param str address of string
 * @return char* address of digit in str, return null if nothing found
 */
char*       Str_FindDigit(const char* str) {
    while ((*str < __Str_0 || *str > __Str_9) &&
            *str != '\0'){
		str++;
	}
	return *str == '\0' ? NULL : (char*) str;
}
/**
 * @brief find first digit in string and return address of digit, keep search until reach null or reach end charachter
 *
 * @param str address of string
 * @param endChar ending charachter
 * @return char* address of digit in str, return null if nothing found
 */
char*       Str_FindDigitUntil(const char* str, char endChar) {
    while ((*str < __Str_0 || *str > __Str_9) &&
            *str != '\0' &&
            *str != endChar){
		str++;
	}
	return *str == '\0' || *str == endChar ? NULL : (char*) str;
}
/**
 * @brief find first digit in string and return address of digit, keep search until reach null or pass the length limit
 *
 * @param str address of string
 * @param len length of string
 * @return char* address of digit in str, return null if nothing found
 */
char*       Str_FindDigitFix(const char* str, Str_LenType len) {
    while ((*str < __Str_0 || *str > __Str_9) &&
            *str != '\0' &&
            len-- > 0){
		str++;
	}
	return *str == '\0' || len == 0 ? NULL : (char*) str;
}
/**
 * @brief find a number and return last digit of it
 *
 * @param str address of string
 * @return char* address of digit in str, return null if nothing found
 */
char*       Str_FindLastDigit(const char* str) {
    str = Str_FindDigit(str);
    if (str != NULL) {
        while (*str >= __Str_0 && *str <= __Str_9){
            str++;
        }
        str--;
    }
	return (char*) str;
}
/**
 * @brief find a number and return last digit of it with ending charachter condition
 *
 * @param str address of string
 * @param endChar ending charachter
 * @return char* address of digit in str, return null if nothing found
 */
char*       Str_FindLastDigitUntil(const char* str, char endChar) {
    str = Str_FindDigitUntil(str, endChar);
    if (str != NULL) {
        while (*str >= __Str_0 && *str <= __Str_9){
            str++;
        }
        str--;
    }
	return (char*) str;
}
/**
 * @brief find a number and return last digit of it with length condition
 *
 * @param str address of string
 * @param len length of string
 * @return char* address of digit in str, return null if nothing found
 */
char*       Str_FindLastDigitFix(const char* str, Str_LenType len) {
    str = Str_FindDigitFix(str, len);
    if (str != NULL) {
        while (*str >= __Str_0 && *str <= __Str_9){
            str++;
        }
        str--;
    }
	return (char*) str;
}
/**
 * @brief find digit from end of string in backward
 *
 * @param str address of string, must include null
 * @return char* address of digit in str, return null if nothing found
 */
char*       Str_FindReverseDigit(const char* str) {
    return Str_FindReverseDigitFix(str, Str_Length(str));
}
/**
 * @brief find digit from end of string in backward with fixed string length
 *
 * @param str address of string
 * @param len lenght of string
 * @return char* address of digit in str, return null if nothing found
 */
char*       Str_FindReverseDigitFix(const char* str, Str_LenType len) {
    str = &str[len - 1];
    while ((*str < __Str_0 || *str > __Str_9) &&
            len-- > 0){
		str--;
	}
	return *str == '\0' || len == 0 ? NULL : (char*) str;
}
/**
 * @brief find multiple indexes of 'c' in string
 *
 * @param str address of strings
 * @param c charachter that we want search for indexes
 * @param indexes a pointer array that will hold our indexes
 * @return Str_LenType number of indexes that found
 */
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
/**
 * @brief find multiple indexes of 'c' in string until reach null or pass the limit
 *
 * @param str address of strings
 * @param c charachter that we want search for indexes
 * @param indexes a pointer array that will hold our indexes
 * @param len lenght of string
 * @return Str_LenType number of indexes that found
 */
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
/**
 * @brief find multiple indexes of 'c' in string until reach null or ending charachter
 *
 * @param str address of strings
 * @param c charachter that we want search for indexes
 * @param indexes a pointer array that will hold our indexes
 * @param endChar ending charachter
 * @return Str_LenType number of indexes that found
 */
Str_LenType Str_IndexesOfUntil(const char* str, char c, char const** indexes, char endChar) {
    Str_LenType count = 0;
	while (*str != '\0' && *str != endChar){
		if (c == *str){
			*indexes++ = str;
			count++;
		}
		str++;
	}
	return count;
}
/**
 * @brief This function finds the address of a character in a given number and returns the last one
 *
 * @param str address of string
 * @param c charachter that we want to search
 * @param num The number of times the function looks for a character
 * @return char* address of charachter, return null if not found
 */
char*       Str_IndexOfAt(const char* str, char c, Str_LenType num) {
    while (num-- > 0) {
        if (!(str = Str_IndexOf(str, c))){
            break;
        }
    }
    return (char*) str;
}
/**
 * @brief This function finds the address of a character in a given number and returns the last one until reach null or ending charachter
 *
 * @param str address of string
 * @param c charachter that we want to search
 * @param num The number of times the function looks for a character
 * @param end ending charachter
 * @return char* address of charachter, return null if not found
 */
char*       Str_IndexOfAtUntil(const char* str, char c, Str_LenType num, char end) {
    return Str_IndexOfAtFix(str, c, num, Str_PosOf(str, end));
}
/**
 * @brief This function finds the address of a character in a given number and returns the last one until reach null or pass the limit
 *
 * @param str address of string
 * @param c charachter that we want to search
 * @param num The number of times the function looks for a character
 * @param len length of string
 * @return char* address of charachter, return null if not found
 */
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
/**
 * @brief revesre order of charachter in string
 *
 * @param str address of string
 * @return char* address of str
 */
char*       Str_Reverse(char* str) {
    return Mem_Reverse(str, Str_Length(str));
}
/**
 * @brief copy sorce string in revesre order into destination string
 *
 * @param src address of source string
 * @param dest address of destination string
 * @return char* address of dest
 */
char*       Str_CopyReverse(const char* src, char* dest) {
    return Mem_CopyReverse(src, dest, Str_Length(src));
}
/**
 * @brief copy a string into dest from given start position
 *
 * @param str address of base string
 * @param dest address of destination string
 * @param start Copy start location
 * @return char* address of dest
 */
char*       Str_Substr(const char* str, char* dest, Str_LenType start) {
    return Str_Copy(&str[start], dest);
}
/**
 * @brief copy a string into dest from given start position
 *
 * @param str address of base string
 * @param dest address of destination string
 * @param start Copy start location
 * @param len length of charachters to be copy
 * @return char* address of dest
 */
char*       Str_SubstrFix(const char* str, char* dest, Str_LenType start, Str_LenType len) {
    Str_CopyFix(&str[start], dest, len);
    dest[len] = '\0';
    return dest;
}
/**
 * @brief copy a string into dest from given start position until reach ending charachter
 *
 * @param str address of base string
 * @param dest address of destination string
 * @param start Copy start location
 * @param endChar ending charachter
 * @return char* address of dest
 */
char*       Str_SubstrUntil(const char* str, char* dest, Str_LenType start, char endChar) {
    Str_LenType len = Str_PosOf(str, endChar);
    Str_CopyFix(&str[start], dest, len);
    dest[len] = '\0';
    return dest;
}

char*       Str_Replace(char* str, const char* word, const char* replacement) {
    char* pWord = Str_IndexOfStr(str, word);
    if (pWord != NULL) {
        Str_LenType wordLen = Str_Length(word);
        Str_LenType repLen = Str_Length(replacement);
        if (wordLen != repLen){
            char* pEndOfWord = pWord + wordLen;
            int len = (Str_LenType) ((char*) Mem_IndexOf(str, '\0', __Str_MaxLength) - pEndOfWord) + 1;
            Mem_Move(pEndOfWord, pEndOfWord + (repLen - wordLen), len);
        }
        Str_CopyFix(replacement, pWord, repLen);
        return str;
    }
    return NULL;
}

char*       Str_CopyUntil(const char* src, char* dest, char c) {
    char* pStr = Str_IndexOf(src, c);
	if (pStr != NULL){
        Str_CopyFix(src, dest, pStr - src);
        return dest;
	}
	return pStr;
}

char*       Str_CopyLine(const char* src, char* dest) {
    return Str_CopyUntil(src, dest, '\n');
}

char**      Str_Sort(const char** strs, Str_LenType len) {
    return Str_SelectionSortBlock(strs, (Mem_LenType) len, (Str_CompareFunc) __Str_Compare);
}
char**      Str_QuickSort(const char** strs, Str_LenType len) {
    return Str_QuickSortBlock(strs, 0, (Mem_LenType) len - 1, (Str_CompareFunc) __Str_Compare);
}
char**      Str_SortReverse(const char** strs, Str_LenType len) {
    return Str_SelectionSortBlock(strs, (Mem_LenType) len, (Str_CompareFunc) Str_CompareInverse);
}
char**      Str_QuickSortReverse(const char** strs, Str_LenType len) {
    return Str_QuickSortBlock(strs, 0, (Mem_LenType) len - 1, (Str_CompareFunc) Str_CompareInverse);
}

Str_LenType Str_Split(const char* src, char c, char** strs) {
    Str_LenType count = 0;
    Str_LenType len;
    char* index = Str_IndexOf(src, c);
    if (index) {
        while (index) {
            len = index - src;
            Str_CopyFix(src, *strs, len);
            *strs[len] = '\0';
            count++;
            strs++;
            src = index + 1;
            index = Str_IndexOf(src, c);
        }
    }
    Str_Copy(src, *strs);
    count++;
    return count;
}

Str_LenType Str_SplitFix(const char* src, char c, char** strs, Str_LenType len) {
    Str_LenType count = 0;
    Str_LenType strLen;
    char* index = Str_IndexOf(src, c);
    if (index) {
        while (index && --len > 0) {
            strLen = index - src;
            Str_CopyFix(src, *strs, strLen);
            *strs[strLen] = '\0';
            count++;
            strs++;
            src = index + 1;
            index = Str_IndexOf(src, c);
        }
    }
    Str_Copy(src, *strs);
    count++;
    return count;
}

Str_LenType Str_PosOf(const char* str, char c) {
    return (Str_LenType) (Str_IndexOf(str, c) - str);
}

Str_LenType Str_LastPosOf(const char* str, char c) {
    return (Str_LenType) (Str_LastIndexOf(str, c) - str);
}

Str_LenType Str_MultiCompare(const char** strs, Str_LenType len, const char* str) {
    return Str_LinearSearch(strs, len, str, (Str_CompareFunc) __Str_Compare);
}
Str_LenType Str_MultiCompareSorted(const char** strs, Str_LenType len, const char* str) {
    return Str_BinarySearch(strs, len, str, (Str_CompareFunc) __Str_Compare);
}

const char* Str_FindStrs(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result) {
    Str_LenType index;

    while (*src != '\0') {
        for (index = 0; index < len; index++) {
            if (Str_CompareWord(src, strs[index]) == 0) {
                result->IndexOf = src;
                result->Position = index;
                return src;
            }
        }
        src++;
    }
    return NULL;
}

const char* Str_FindStrsSorted(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result) {
    Str_LenType index;
    Str_LenType pos;

    while (*src != '\0') {
        for (index = 0; index < len; index++) {
            if ((pos = Str_BinarySearch(strs, len, src, (Str_CompareFunc) Str_CompareWord)) != -1) {
                result->IndexOf = src;
                result->Position = pos;
                return src;
            }
        }
        src++;
    }
    return NULL;
}

Str_LenType Str_ParseNum(Str_NumType num, char base, char len, char* str) {
    if (num < 0){
		*str++ = '-';
		num *= -1;
		return Str_ParseUNum((Str_NumType) num, base, len, str) + 1;
	}
	else {
		return Str_ParseUNum((Str_NumType) num, base, len, str);
	}
}

Str_LenType Str_ParseUNum(Str_UNumType num, char base, char len, char* str) {
    Str_LenType count = 0;
	char* pStr = str;
	char temp;
	do {
		temp = num % base;
		*pStr++ = temp < __Str_Decimal ? (temp + __Str_0) : (temp + 0x37);
		count++;
		num /= base;
	} while (num != 0 || count < len);
	Mem_Reverse(str, (Mem_LenType) count);
	*pStr = '\0';
	return count;
}

Str_Result Str_ConvertNum(const char* str, Str_NumType* num, Str_BaseIndex base) {
    return Str_ConvertNumFix(str, num, base, __Str_MaxLength);
}
Str_Result Str_ConvertUNum(const char* str, Str_UNumType* num, Str_BaseIndex base) {
    return Str_ConvertUNumFix(str, num, base, __Str_MaxLength);
}
Str_Result Str_ConvertNumFix(const char* str, Str_NumType* num, Str_BaseIndex base, Str_LenType len) {
    if (*str == '-'){
		char res;
		res = Str_ConvertUNumFix(++str, num, base, --len);
		*num *= -1;
		return res;
	}
	else {
		return Str_ConvertUNumFix(str, num, base, len);
	}
}
Str_Result Str_ConvertUNumFix(const char* str, Str_UNumType* num, Str_BaseIndex base, Str_LenType len) {
    Str_UNumType temp;
	*num = 0;
	while (*str != '\0' && len-- > 0){
		if (*str >= __Str_0 && *str <= __Str_9){
			temp = *str - __Str_0;
		}
		else if (*str >= 'A' && *str <= 'Z'){
			temp = *str - 0x37;
		}
		else if (*str >= 'a' && *str <= 'z'){
			temp = *str - 0x57;
		}
		else {
			return Str_Error;
		}
		if (temp >= base){
			return Str_Error;
		}
		*num = *num * base + temp;
		str++;
	}
	return Str_Ok;
}

Str_LenType Str_ParseFloat(Str_FloatType num, char* str, Str_LenType decimalLen) {
    Str_NumType pow = decimalLen;
	Str_NumType numInt = (Str_NumType) num;
	Str_LenType len;
	len = Str_ParseNum(numInt, __Str_Decimal, STR_NORMAL_LEN, str);
    if (decimalLen != 0) {
        str = str + len;
        *str++ = '.';
        num = num - numInt;
        if (num < 0){
            num *= -1;
        }
        while (pow-- != 0){
            num *= __Str_Decimal;
        }
	    len += Str_ParseNum((Str_NumType) num, __Str_Decimal, STR_NORMAL_LEN, str) + 1;
    }
	return len;
}

Str_Result Str_ConvertFloat(const char* str, Str_FloatType* num) {
    return Str_ConvertFloatFix(str, num, Str_Length(str));
}
Str_Result Str_ConvertFloatFix(const char* str, Str_FloatType* num, Str_LenType len) {
    const char* pDot = Str_IndexOf(str, '.');
	Str_FloatType temp;
	Str_NumType numInt;
	Str_LenType strLen;
	if (pDot == NULL){
		pDot = Mem_IndexOf(str, '\0', __Str_MaxLength);
	}
	strLen = (Str_LenType)(pDot - str);
	if (strLen > len){
		strLen = len;
	}
	if (Str_ConvertNumFix(str, &numInt, __Str_Decimal, strLen) == Str_Ok){
		*num = numInt;
		if (*pDot != '\0'){
			len -= strLen + 1;
			if (Str_ConvertNumFix(++pDot, &numInt, __Str_Decimal, len) != Str_Ok){
				return Str_Error;
			}
			temp = numInt;
            while (len-- > 0) {
                temp /= __Str_Decimal;
            }
            *num = *num < 0 ? *num - temp : *num + temp;
		}
		return Str_Ok;
	}
	return Str_Error;
}


Str_Result Str_GetNum(const char* str, Str_NumType* num, const char** numPos) {
    const char* baseStr = str;
	str = Str_FindDigit(str);
	if (str != NULL){
		if (baseStr < str && *(str - 1) == '-'){
			str--;
		}
		*numPos = str;
		if (Str_ConvertNumFix(str, num, __Str_Decimal, (Str_LenType) (Str_FindLastDigit(str) - str + 1)) == Str_Ok){
			return Str_Ok;
		}
	}
	return Str_Error;
}
Str_Result Str_GetUNum(const char* str, Str_UNumType* num, const char** numPos) {
	str = Str_FindDigit(str);
	if (str != 0){
		*numPos = str;
		if (Str_ConvertUNumFix(str, num, __Str_Decimal, (Str_LenType) (Str_FindLastDigit(str) - str + 1)) == Str_Ok){
			return Str_Ok;
		}
	}
	return Str_Error;
}

Str_Result Str_GetFloat(const char* str, Str_FloatType* num, const char** numPos) {
	const char* pDot = str;
	str = Str_FindDigit(str);
	if (str != NULL){
		if (pDot < str && *(str - 1) == '-'){
			str--;
		}
		pDot = Str_FindLastDigit(str) + 1;
		if (*(pDot) == '.'){
			pDot = Str_FindLastDigit(pDot);
            pDot = pDot == NULL ? Str_IndexOfEnd(str) : pDot + 1;
		}
		*numPos = str;
		if (Str_ConvertFloatFix(str, num, pDot - str) == Str_Ok){
			return Str_Ok;
		}
	}
	return Str_Error;
}

/**
 * Sorting Functions
 **/

void        Str_Swap(const char** itemA, const char** itemB) {
    char* temp = *itemA;
    *itemA = *itemB;
    *itemB = temp;
}

Str_LenType Str_Partition(const char** items, Str_LenType low, Str_LenType high, Str_CompareFunc cmp) {
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
char**      Str_QuickSortBlock(const char** items, Mem_LenType low, Mem_LenType high, Str_CompareFunc cmp) {
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

char**      Str_SelectionSortBlock(const char** items, Mem_LenType len, Str_CompareFunc cmp) {
    Mem_LenType i, j, min_idx;

    // One by one move boundary of unsorted sub-array
    for (i = 0; i < len-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < len; j++) {
          if (cmp(items[j], items[min_idx]) < 0) {
            min_idx = j;
          }
        }
        // Swap the found minimum element with the first element
        Str_Swap(&items[min_idx], &items[i]);
    }
}

Str_LenType Str_LinearSearch(const char** strs, Str_LenType len, const char* str, Str_CompareFunc cmp) {
    Str_LenType tempLen = len;
    while (len--) {
        if (cmp(*strs++, str) == 0) {
            return tempLen - len - 1;
        }
    }
    return -1;
}

Str_LenType Str_BinarySearch(const char** strs, Str_LenType len, const char* str, Str_CompareFunc cmp) {
    Str_LenType left = 0;
    Str_LenType mid;
    char result;

    len--;

    while (left <= len) {
        mid = (len + left) >> 1;
        result = cmp(str, strs[mid]);
        // Check if str is present at mid
        if (result == 0) {
            return mid;
        }
        // If str greater, ignore left half
        else if (result > 0) {
            left = mid + 1;
        }
        // If x is smaller, ignore right half
        else {
            len = mid - 1;
        }
    }
    // if we reach here, then element was
    // not present
    return -1;
}
