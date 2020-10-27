#include "StrUtils.h"

#ifdef STR_USE_STRING_LIBRARY
    #include <string.h>
#endif

/**
 * variables
 **/

#ifdef STR_USE_CONST_VARIABLES
    const char __Str_Decimal            = 10;
    const char __Str_0                  = '0';
    const char __Str_9                  = '9';
    const char __Str_Zero               = 0;
    const char __Str_One                = 1;
    const char __Str_Null               = '\0';
    const Str_LenType __Str_MaxLength   = STR_MAX_LENGTH;
#else
    #define __Str_Decimal               10
    #define __Str_MaxLength             STR_MAX_LENGTH
    #define __Str_0                     '0'
    #define __Str_9                     '9'
    #define __Str_Zero                  0
    #define __Str_One                   1
    #define __Str_Null                  '\0'
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
	while (*word != __Str_Null){
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
            *str != __Str_Null){
		str++;
	}
	return *str == __Str_Null ? NULL : str;
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
            *str != __Str_Null &&
            *str != endChar){
		str++;
	}
	return *str == __Str_Null || *str == endChar ? NULL : str;
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
            *str != __Str_Null &&
            len-- > 0){
		str++;
	}
	return *str == __Str_Null || len == 0 ? NULL : (char*) str;
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
	return *str == __Str_Null || len == 0 ? NULL : (char*) str;
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
	while (*str != __Str_Null){
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
	while (*str != __Str_Null && len-- > 0){
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
	while (*str != __Str_Null && *str != endChar){
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
 * @brief copy source string in reverse order into destination string
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
 * @param len length of characters to be copy
 * @return char* address of dest
 */
char*       Str_SubstrFix(const char* str, char* dest, Str_LenType start, Str_LenType len) {
    Str_CopyFix(&str[start], dest, len);
    dest[len] = __Str_Null;
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
    dest[len] = __Str_Null;
    return dest;
}
/**
 * @brief replace first word that find in string with a another word
 *
 * @param str address of string
 * @param word addres of word
 * @param replacement address of replacement
 * @return char* return address of str if word found otherwise return null
 */
char*       Str_Replace(char* str, const char* word, const char* replacement) {
    char* pWord = Str_IndexOfStr(str, word);
    if (pWord != NULL) {
        Str_LenType wordLen = Str_Length(word);
        Str_LenType repLen = Str_Length(replacement);
        if (wordLen != repLen){
            char* pEndOfWord = pWord + wordLen;
            int len = (Str_LenType) ((char*) Mem_IndexOf(str, __Str_Null, __Str_MaxLength) - pEndOfWord) + 1;
            Mem_Move(pEndOfWord, pEndOfWord + (repLen - wordLen), len);
        }
        Str_CopyFix(replacement, pWord, repLen);
        return str;
    }
    return NULL;
}
/**
 * @brief copy sourc string into destination string until reach ending char
 *
 * @param src address of source string
 * @param dest address of destination string
 * @param endChar ending character
 * @return char* return null if source not contain ending character otherwise return destination
 */
char*       Str_CopyUntil(const char* src, char* dest, char endChar) {
    char* pStr = Str_IndexOf(src, endChar);
	if (pStr != NULL){
        Str_CopyFix(src, dest, pStr - src);
        return dest;
	}
	return pStr;
}
/**
 * @brief read a line form source and copy it into destination
 *
 * @param src address of source string
 * @param dest address of destination string
 * @return char* return null if source not contain ending character otherwise return destination
 */
char*       Str_CopyLine(const char* src, char* dest) {
    return Str_CopyUntil(src, dest, '\n');
}
/**
 * @brief sort array of strings with selection sort algorithm
 *
 * @param strs array of strings
 * @param len length of array
 * @return char** return address of strs
 */
const char** Str_Sort(const char** strs, Str_LenType len) {
    return Str_SelectionSortBlock(strs, (Mem_LenType) len, (Str_CompareFunc) __Str_Compare);
}
/**
 * @brief sort array of strings with quick sort algorithm
 *
 * @param strs array of strings
 * @param len length of array
 * @return const char** return address of strs
 */
const char** Str_QuickSort(const char** strs, Str_LenType len) {
    return Str_QuickSortBlock(strs, 0, (Mem_LenType) len - 1, (Str_CompareFunc) __Str_Compare);
}
/**
 * @brief sort array of strings in reverse order, use selection sort algorithm
 *
 * @param strs array of strings
 * @param len length of array
 * @return char** return address of strs
 */
const char** Str_SortReverse(const char** strs, Str_LenType len) {
    return Str_SelectionSortBlock(strs, (Mem_LenType) len, (Str_CompareFunc) Str_CompareInverse);
}
/**
 * @brief sort array of strings in reverse order, use quick sort algorithm
 *
 * @param strs array of strings
 * @param len length of array
 * @return char** return address of strs
 */
const char** Str_QuickSortReverse(const char** strs, Str_LenType len) {
    return Str_QuickSortBlock(strs, 0, (Mem_LenType) len - 1, (Str_CompareFunc) Str_CompareInverse);
}
/**
 * @brief splite a strings into multiple addresses, it's unsafe function
 *
 * @param src address of main string
 * @param seperator seperator character
 * @param strs array of strings addresses
 * @return Str_LenType number of strings that splitted
 */
Str_LenType Str_Split(const char* src, char seperator, char** strs) {
    Str_LenType count = 0;
    Str_LenType len;
    char* index = Str_IndexOf(src, seperator);
    if (index) {
        while (index) {
            len = index - src;
            Str_CopyFix(src, *strs, len);
            *strs[len] = __Str_Null;
            count++;
            strs++;
            src = index + 1;
            index = Str_IndexOf(src, seperator);
        }
    }
    Str_Copy(src, *strs);
    count++;
    return count;
}
/**
 * @brief splite a strings into multiple addresses with max number of strings
 *
 * @param src address of main string
 * @param seperator seperator character
 * @param strs array of strings addresses
 * @param len length of strs array
 * @return Str_LenType number of strings that splitted
 */
Str_LenType Str_SplitFix(const char* src, char seperator, char** strs, Str_LenType len) {
    Str_LenType count = 0;
    Str_LenType strLen;
    char* index = Str_IndexOf(src, seperator);
    if (index) {
        while (index && --len > 0) {
            strLen = index - src;
            Str_CopyFix(src, *strs, strLen);
            *strs[strLen] = __Str_Null;
            count++;
            strs++;
            src = index + 1;
            index = Str_IndexOf(src, seperator);
        }
    }
    Str_Copy(src, *strs);
    count++;
    return count;
}
/**
 * @brief find position of a character in string
 *
 * @param str address of string
 * @param c searching character
 * @return Str_LenType position of character
 */
Str_LenType Str_PosOf(const char* str, char c) {
    return (Str_LenType) (Str_IndexOf(str, c) - str);
}
/**
 * @brief find position of a character in string with reverse search
 *
 * @param str address of string
 * @param c searching character
 * @return Str_LenType position of charachter
 */
Str_LenType Str_LastPosOf(const char* str, char c) {
    return (Str_LenType) (Str_LastIndexOf(str, c) - str);
}
/**
 * @brief find string in array of strings with linear search algorithm
 *
 * @param strs array of strings
 * @param len length of strs
 * @param str searching string
 * @return Str_LenType position of str in strs
 */
Str_LenType Str_MultiCompare(const char** strs, Str_LenType len, const char* str) {
    return Str_LinearSearch(strs, len, str, (Str_CompareFunc) __Str_Compare);
}
/**
 * @brief find string in array of strings with binary search algorithm
 *
 * @param strs array of strings
 * @param len length of strs
 * @param str searching string
 * @return Str_LenType position of str in strs
 */
Str_LenType Str_MultiCompareSorted(const char** strs, Str_LenType len, const char* str) {
    return Str_BinarySearch(strs, len, str, (Str_CompareFunc) __Str_Compare);
}
/**
 * @brief find first string that found in array of strings
 *
 * @param src addres of source string
 * @param strs array of strings that we want find in source string
 * @param len length of strs
 * @param result index and position of finded string
 * @return const char* address of finded string in source string
 */
const char* Str_FindStrs(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result) {
    Str_LenType index;

    while (*src != __Str_Null) {
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
/**
 * @brief find first string that found in array of strings with binary search algorithm
 *
 * @param src addres of source string
 * @param strs array of strings that we want find in source string
 * @param len length of strs
 * @param result index and position of finded string
 * @return const char* address of finded string in source string
 */
const char* Str_FindStrsSorted(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result) {
    Str_LenType index;
    Str_LenType pos;

    while (*src != __Str_Null) {
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
/**
 * @brief find first string that found in array of strings
 *
 * @param src addres of source string
 * @param strs array of strings that we want find in source string
 * @param len length of strs
 * @param result index and position of finded string
 * @param srcLen len of source string
 * @return const char* address of finded string in source string
 */
const char* Str_FindStrsFix(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result, Str_LenType srcLen) {
    Str_LenType index;

    while (*src != __Str_Null && srcLen-- > 0) {
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
/**
 * @brief find first string that found in array of strings with binary search algorithm
 *
 * @param src addres of source string
 * @param strs array of strings that we want find in source string
 * @param len length of strs
 * @param result index and position of finded string
 * @param srcLen len of source string
 * @return const char* address of finded string in source string
 */
const char* Str_FindStrsSortedFix(const char* src, const char** strs, Str_LenType len, Str_MultiResult* result, Str_LenType srcLen) {
    Str_LenType index;
    Str_LenType pos;

    while (*src != __Str_Null && srcLen-- > 0) {
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
/**
 * @brief convert a number into string with specific base index and length
 *
 * @param num number that we want convert
 * @param base base index
 * @param minLen minimum length of result string
 * @param str address destination string
 * @return Str_LenType return length of str
 */
Str_LenType Str_ParseNum(Str_NumType num, Str_BaseIndex base, char minLen, char* str) {
    if (num < 0){
		*str++ = '-';
		num *= -1;
		return Str_ParseUNum((Str_NumType) num, base, minLen, str) + 1;
	}
	else {
		return Str_ParseUNum((Str_NumType) num, base, minLen, str);
	}
}
/**
 * @brief convert a unsigned number into string with specific base index and length
 *
 * @param num number that we want convert
 * @param base base index
 * @param minLen minimum length of result string
 * @param str address destination string
 * @return Str_LenType return length of str
 */
Str_LenType Str_ParseUNum(Str_UNumType num, Str_BaseIndex base, char minLen, char* str) {
    Str_LenType count = 0;
	char* pStr = str;
	char temp;
	do {
		temp = num % (Str_LenType) base;
		*pStr++ = temp < __Str_Decimal ? (temp + __Str_0) : (temp + 0x37);
		count++;
		num /= base;
	} while (num != 0 || count < minLen);
	Mem_Reverse(str, (Mem_LenType) count);
	*pStr = __Str_Null;
	return count;
}
/**
 * @brief convert a string into number
 *
 * @param str address of source string
 * @param num address of output number
 * @param base base index
 * @return Str_Result result of convert
 */
Str_Result Str_ConvertNum(const char* str, Str_NumType* num, Str_BaseIndex base) {
    return Str_ConvertNumFix(str, num, base, __Str_MaxLength);
}
/**
 * @brief convert a string into unsigned number
 *
 * @param str address of source string
 * @param num address of output number
 * @param base base index
 * @return Str_Result result of convert
 */
Str_Result Str_ConvertUNum(const char* str, Str_UNumType* num, Str_BaseIndex base) {
    return Str_ConvertUNumFix(str, num, base, __Str_MaxLength);
}
/**
 * @brief convert a string into number with fixed length
 *
 * @param str address of source string
 * @param num address of output number
 * @param base base index
 * @return Str_Result result of convert
 */
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
/**
 * @brief convert a string into unsigned number with fixed length
 *
 * @param str address of source string
 * @param num address of output number
 * @param base base index
 * @return Str_Result result of convert
 */
Str_Result Str_ConvertUNumFix(const char* str, Str_UNumType* num, Str_BaseIndex base, Str_LenType len) {
    Str_UNumType temp;
	*num = 0;
	while (*str != __Str_Null && len-- > 0){
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
/**
 * @brief convert float number into string
 *
 * @param num float number
 * @param str address of output string
 * @return Str_LenType
 */
Str_LenType Str_ParseFloat(Str_FloatType num, char* str) {
	Str_NumType numInt = (Str_NumType) num;
	Str_LenType len;
	len = Str_ParseNum(numInt, __Str_Decimal, STR_NORMAL_LEN, str);
    str = str + len;
    num = num - numInt;
    if (num != 0) {
        *str++ = '.';
        len++;
        if (num < 0){
            num *= -1;
        }
        numInt = (Str_NumType) num;
        while (num != 0) {
            num *= __Str_Decimal;
            numInt = (int) num;
            *str++ = numInt + __Str_0;
            len++;
            num -= numInt;
        }
    }
    *str = __Str_Null;
	return len;
}
/**
 * @brief convert float number into string
 *
 * @param num float number
 * @param str address of output string
 * @param decimalLen resolution of floating part
 * @return Str_LenType
 */
Str_LenType Str_ParseFloatFix(Str_FloatType num, char* str, Str_LenType decimalLen) {
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
/**
 * @brief convert a string into float number
 *
 * @param str address of source string
 * @param num address of output number
 * @return Str_Result result of convert
 */
Str_Result Str_ConvertFloat(const char* str, Str_FloatType* num) {
    return Str_ConvertFloatFix(str, num, Str_Length(str));
}
/**
 * @brief convert a string into float number with fixed length
 *
 * @param str address of source string
 * @param num address of output number
 * @return Str_Result result of convert
 */
Str_Result Str_ConvertFloatFix(const char* str, Str_FloatType* num, Str_LenType len) {
    const char* pDot = Str_IndexOf(str, '.');
	Str_FloatType temp;
	Str_NumType numInt;
	Str_LenType strLen;
	if (pDot == NULL){
		pDot = Mem_IndexOf(str, __Str_Null, __Str_MaxLength);
	}
	strLen = (Str_LenType)(pDot - str);
	if (strLen > len){
		strLen = len;
	}
	if (Str_ConvertNumFix(str, &numInt, __Str_Decimal, strLen) == Str_Ok){
		*num = numInt;
		if (*pDot != __Str_Null){
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
/**
 * @brief get first number that found in string
 *
 * @param str address of source string
 * @param num number that found
 * @param numPos index of number that found
 * @return Str_Result result of searching for number
 */
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
/**
 * @brief get first unsigned number that found in string
 *
 * @param str address of source string
 * @param num number that found
 * @param numPos index of number that found
 * @return Str_Result result of searching for number
 */
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
/**
 * @brief get first float number that found in string
 *
 * @param str address of source string
 * @param num number that found
 * @param numPos index of number that found
 * @return Str_Result result of searching for number
 */
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
 * @brief swap address of two string
 *
 * @param itemA string 1
 * @param itemB string 2
 */
void Str_Swap(const char** itemA, const char** itemB) {
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
/**
 * @brief run quick sort algorithm for items with given compare function
 *
 * @param items array of strings
 * @param low position of start
 * @param high position of end
 * @param cmp address of compare function
 * @return char** return items
 */
const char** Str_QuickSortBlock(const char** items, Mem_LenType low, Mem_LenType high, Str_CompareFunc cmp) {
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
    return items;
}
/**
 * @brief run selection sort algorithm for item with given compare function
 *
 * @param items array of strings
 * @param len length of array
 * @param cmp address of compare function
 * @return char**
 */
const char** Str_SelectionSortBlock(const char** items, Mem_LenType len, Str_CompareFunc cmp) {
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
    return items;
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

#ifndef STR_USE_STRING_LIBRARY

void*       Mem_Copy(const void* src, void* dest, Mem_LenType len) {
    unsigned char* pDest = (unsigned char*) dest;
    const unsigned char* pSrc = (const unsigned char*) src;
    while (len-- > 0) {
        *pDest++ = *pSrc++;
    }
    return dest;
}
char        Mem_Compare(const void* arr1, const void* arr2, Mem_LenType len) {
    const unsigned char* pArr1 = (const unsigned char*) arr1;
    const unsigned char* pArr2 = (const unsigned char*) arr2;
    char result;
    while (len-- > 0) {
        if((result = *pArr1++ - *pArr2++)) {
            break;
        }
    }
    return result;
}
void*       Mem_Move(const void* src, void* dest, Mem_LenType len) {
    unsigned char* pDest = (unsigned char*) dest;
    const unsigned char* pSrc = (const unsigned char*) src;
    if (len <= 0 || src == dest) {
        return NULL;
    }
    if (pDest < pSrc) {
        while (len-- > 0) {
            *pDest++ = *pSrc++;
        }
    }
    else {
        const unsigned char* lastSrc = (const unsigned char*) (pSrc + (len - 1));
        unsigned char* lastDest = (unsigned char*) (pDest + (len - 1));
        while (len-- > 0) {
            *lastDest-- = *lastSrc--;
        }
    }
    return dest;
}
void*       Mem_IndexOf(const void* arr, unsigned char value, Mem_LenType len) {
    const unsigned char* pArr = (const unsigned char*) arr;

    while (len-- > 0) {
        if (*pArr == value) {
            return (void*) pArr;;
        }
        pArr++;
    }
    return NULL;
}
void*       Mem_Set(void* arr, unsigned char value, Mem_LenType len) {
    unsigned char* pArr = (unsigned char*) arr;

    while (len-- > 0) {
        *pArr++ = value;
    }
    return arr;
}



char*       Str_Copy(const char* src, char* dest) {
    char* pDest = dest;
    while (*src != __Str_Null) {
        *pDest++ = *src++;
    }
    *pDest = __Str_Null;
    return dest;
}
char*       Str_CopyFix(const char* src, char* dest, Str_LenType len) {
    return Mem_Copy(src, dest, len);
}
char        Str_Compare(const char* str1, const char* str2) {
    char result;
    while (*str1 != __Str_Null) {
        if ((result = *str1++ - *str2++)) {
            break;
        }
    }
    return result;
}
char        Str_CompareFix(const char* str1, const char* str2, Str_LenType len) {
    return Mem_Compare(str1, str2, len);
}
Str_LenType Str_Length(const char* str) {
    char* pStr = str;
    while (*pStr != __Str_Null) {
        pStr++;
    }
    return (Str_LenType) (pStr - str);
}
char*       Str_IndexOf(char* str, char c) {
    while (*str != __Str_Null) {
        if (*str == c) {
            return str;
        }
        str++;
    }
    return NULL;
}
char*       Str_LastIndexOf(char* str, char c) {
    char* pStr = (char*) Mem_IndexOf(str, '\'0', __Str_MaxLength) - 1;
    while (pStr >= str) {
        if (*pStr == c) {
            return pStr;
        }
        pStr--;
    }
    return NULL;
}
char*       Str_IndexOfStr(char* str, char* sub) {
    while (*str != __Str_Null && str != NULL) {
        str = Str_IndexOf(str, *sub);
        if (Str_CompareWord(str, sub) == 0) {
            return str;
        }
    }
    return NULL;
}
char*       Str_Append(char* str, char* sub) {
    char* pStr = (char*) Mem_IndexOf(str, '\'0', __Str_MaxLength);
    Str_Copy(sub, pStr);
    return str;
}

#endif // STR_USE_STRING_LIBRARY
