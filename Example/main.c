#include <stdio.h>
#include <stdint.h>
#include "..\Src\Str.h"

#define PRINTLN						puts
#define PRINTF						printf

typedef struct {
	const char* Name;
	int			Age;
	int 		Height;
} ItemUser;
#define ItemUser_init(NAME, AGE, HEIGHT)		{(NAME), (AGE), (HEIGHT)}

uint32_t Assert_Str(const char* str1, const char* str2, uint32_t line);
uint32_t Assert_Num(int num1, int num2, uint32_t line);
uint32_t Assert_Float(float num1, float num2, uint32_t line);
uint32_t Assert_Strs(const char** strs1, const char** strs2, int len, uint32_t line);
uint32_t Assert_Ptr(const void* ptr1, const void* ptr2, uint32_t line);
uint32_t Assert_ItemUsers(const ItemUser* items1, const ItemUser* items2, int len, uint32_t line);

uint32_t assertResult = 0;
#define assert(TYPE, ...)			if((assertResult = Assert_ ##TYPE (__VA_ARGS__, __LINE__)) != Str_Ok) return assertResult

#define ARRAY_LEN(ARR)			(sizeof(ARR) / sizeof(ARR[0]))

void printStrs(const char** strs, int len);
void printItemUsers(const ItemUser* items, int len);

typedef uint32_t (*TestFunc)(void);

uint32_t Test_basic(void);
uint32_t Test_parse(void);
uint32_t Test_convert(void);
uint32_t Test_get(void);
uint32_t Test_replace(void);
uint32_t Test_sort(void);
uint32_t Test_quickSort(void);
uint32_t Test_multiCompare(void);
uint32_t Test_multiCompareSorted(void);
uint32_t Test_findStrs(void);
uint32_t Test_findStrsSorted(void);
uint32_t Test_memSort(void);
uint32_t Test_memQuickSort(void);
uint32_t Test_memLinearSearch(void);
uint32_t Test_memBinarySearch(void);
uint32_t Test_trim(void);

const TestFunc Tests[] = {
    Test_basic,
	Test_parse,
	Test_convert,
	Test_get,
	Test_replace,
	Test_sort,
	Test_quickSort,
	Test_multiCompare,
	Test_multiCompareSorted,
	Test_findStrs,
	Test_findStrsSorted,
	Test_memSort,
	Test_memQuickSort,
	Test_memLinearSearch,
	Test_memBinarySearch,
	Test_trim,
};
const int Tests_Length = ARRAY_LEN(Tests);

int main(void) {
	int testIndex;
	int countTestError = 0;
	Str_Result res;

	for (testIndex = 0; testIndex < Tests_Length; testIndex++) {
		PRINTF("---------------- Begining Test[%d]------------ \r\n", testIndex);
		res = Tests[testIndex]();
		PRINTF("Test Result: %s\r\n", res & 0x01 ? "Error" : "Ok");
		if (res & 1) {
			PRINTF("Error in Line: %d\r\n", res >> 1);
		}
		countTestError += (int) res & 1;
		PRINTF("---------------------------------------------- \r\n", testIndex);
	}
	PRINTLN("Test Done\r\n");
	PRINTF("Tests Errors: %d\r\n", countTestError);
}
// -------------------------------------------------------------------------------
uint32_t Test_basic(void) {
    const char temp1[] = "ABCD";
    const char temp2[] = "XYZ";
    const char temp3[] = "StrLine\n Test2";
    char temp[32] = "";
    char* pChar;

    PRINTLN("Basic:");

    Str_copy(temp, temp1);
    assert(Str, temp, "ABCD");

    Str_copyFix(temp, temp2, 2);
    assert(Str, temp, "XYCD");

    pChar = Str_indexOf(temp1, 'C');
    assert(Ptr, pChar, &temp1[2]);

    Str_copy(temp, "ABC");
    pChar = Str_indexOfEnd(temp);
    assert(Ptr, pChar, &temp[2]);

    Str_copy(temp, "");
    pChar = Str_indexOfEnd(temp);
    assert(Ptr, pChar, NULL);

    Str_copyLine(temp, temp3);
    assert(Str, temp, "StrLine");

    Str_copyReverse(temp, temp2);
    assert(Str, temp, "ZYX");

    return (uint32_t) Str_Ok;
}
// -------------------------------------------------------------------------------
uint32_t Test_parse(void) {
	char tempStr[32];
	PRINTLN("Parse:");

	Str_parseNum(5, Str_Decimal, STR_NORMAL_LEN, tempStr);
	assert(Str, tempStr, "5");

	Str_parseNum(10, Str_Decimal, STR_NORMAL_LEN, tempStr);
	assert(Str, tempStr, "10");

	Str_parseNum(1234, Str_Decimal, 2, tempStr);
	assert(Str, tempStr, "1234");

	Str_parseNum(12, Str_Binary, 4, tempStr);
	assert(Str, tempStr, "1100");

	Str_parseNum(255, Str_Hex, 4, tempStr);
	assert(Str, tempStr, "00FF");

	Str_parseFloatFix(2.45f, tempStr, 2);
	assert(Str, tempStr, "2.45");

	Str_parseFloatFix(5.75f, tempStr, 1);
	assert(Str, tempStr, "5.7");

	Str_parseFloatFix(-5.75f, tempStr, 1);
	assert(Str, tempStr, "-5.7");

	Str_parseFloatFix(5.75f, tempStr, 3);
	assert(Str, tempStr, "5.750");

	Str_parseFloatFix(5.754f, tempStr, 0);
	assert(Str, tempStr, "5");

	Str_parseFloatFix(-5.754f, tempStr, 0);
	assert(Str, tempStr, "-5");

	Str_parseFloatFix(10.456f, tempStr, 3);
	assert(Str, tempStr, "10.456");

	Str_parseFloat(10.5f, tempStr);
	assert(Str, tempStr, "10.5");

	Str_parseFloat(10.75f, tempStr);
	assert(Str, tempStr, "10.75");

	Str_parseFloat(10.125f, tempStr);
	assert(Str, tempStr, "10.125");

	return Str_Ok;
}
// -------------------------------------------------------------------------------
uint32_t Test_convert(void) {
	int tempNum;
	float tempFloat;
	PRINTLN("Convert:");

	Str_convertNum("123", &tempNum, Str_Decimal);
	assert(Num, tempNum, 123);

	Str_convertNum("-431", &tempNum, Str_Decimal);
	assert(Num, tempNum, -431);

	Str_convertNum("1", &tempNum, Str_Decimal);
	assert(Num, tempNum, 1);

	Str_convertNumFix("1234", &tempNum, Str_Decimal, 2);
	assert(Num, tempNum, 12);

	Str_convertNum("4756", &tempNum, Str_Decimal);
	assert(Num, tempNum, 4756);

	Str_convertFloat("5.5", &tempFloat);
	assert(Float, tempFloat, 5.5f);

	Str_convertFloat("-5.5", &tempFloat);
	assert(Float, tempFloat, -5.5f);

	Str_convertFloat("-5", &tempFloat);
	assert(Float, tempFloat, -5.0f);

	Str_convertFloat("3.", &tempFloat);
	assert(Float, tempFloat, 3.0f);

	Str_convertFloat("123.45", &tempFloat);
	assert(Float, tempFloat, 123.45f);

	Str_convertFloatFix("5.575", &tempFloat, 3);
	assert(Float, tempFloat, 5.5f);

	return Str_Ok;
}
// -------------------------------------------------------------------------------
uint32_t Test_get(void) {
	int tempNum;
	float tempFloat;
	const char* numPos;
	PRINTLN("Get:");

	Str_getNum("This is my number: 1234", &tempNum, &numPos);
	assert(Num, tempNum, 1234);

	Str_getNum("34 is Number", &tempNum, &numPos);
	assert(Num, tempNum, 34);

	Str_getNum("ABC,-47,25", &tempNum, &numPos);
	assert(Num, tempNum, -47);

	Str_getNum("-- 88 --", &tempNum, &numPos);
	assert(Num, tempNum, 88);

	Str_getFloat("-- 2. --", &tempFloat, &numPos);
	assert(Float, tempFloat, 2.0f);

	Str_getFloat("-- 45 abc", &tempFloat, &numPos);
	assert(Float, tempFloat, 45.0f);

	Str_getFloat("-- 3.5 --", &tempFloat, &numPos);
	assert(Float, tempFloat, 3.5f);

	return Str_Ok;
}
// -------------------------------------------------------------------------------
uint32_t Test_replace(void) {
	char tempStr[64];
	PRINTLN("Replace:");

	Str_copy(tempStr, "Hello my name is Ali");
	Str_replace(tempStr, "Ali", "Reza");
	assert(Str, tempStr, "Hello my name is Reza");

	Str_copy(tempStr, "I Lost");
	Str_replace(tempStr, "I", "We");
	assert(Str, tempStr, "We Lost");

	Str_copy(tempStr, "AAA BBB CCC");
	Str_replace(tempStr, "BBB", "X");
	assert(Str, tempStr, "AAA X CCC");

	Str_copy(tempStr, "111 2 333");
	Str_replace(tempStr, "2", "222");
	assert(Str, tempStr, "111 222 333");

	Str_copy(tempStr, "This is My life");
	Str_replace(tempStr, "This ", "");
	assert(Str, tempStr, "is My life");

	return Str_Ok;
}
// -------------------------------------------------------------------------------
uint32_t Test_sort(void) {
	const char* tempStrs[] = {
		"ABCD",
		"123",
		"abcd",
		"9876",
		"-w-",
	};
	const int tempStrs_Length = ARRAY_LEN(tempStrs);

	const char* tempStrs2[] = {
		"",
		"=",
		"?",
		"=?",
		":",
	};
	const int tempStrs2_Length = ARRAY_LEN(tempStrs);

	const char* sortedStrs[] = {
		"-w-",
		"123",
		"9876",
		"ABCD",
		"abcd",
	};

	const char* sortedStrs2[] = {
		"",
		":",
		"=",
		"=?",
		"?",
	};

	PRINTLN("Sort:");

	Str_sort(tempStrs, tempStrs_Length);
	assert(Strs, tempStrs, sortedStrs, tempStrs_Length);

	Str_sort(tempStrs2, tempStrs2_Length);
	assert(Strs, tempStrs2, sortedStrs2, tempStrs2_Length);

	return (uint32_t) Str_Ok;
}
// -------------------------------------------------------------------------------
uint32_t Test_quickSort(void) {
	const char* tempStrs[] = {
		"red",
		"blue",
		"yellow",
		"mine",
		"your",
		"Here"
	};
	const int tempStrs_Length = ARRAY_LEN(tempStrs);

	const char* sortedStrs[] = {
		"Here",
		"blue",
		"mine",
		"red",
		"yellow",
		"your",
	};
	const int sortedStrs_Length = ARRAY_LEN(sortedStrs);

	PRINTLN("Quick Sort:");

	Str_quickSort(tempStrs, tempStrs_Length);
	assert(Strs, tempStrs, sortedStrs, tempStrs_Length);

	return (uint32_t) Str_Ok;
}
// -------------------------------------------------------------------------------
uint32_t Test_multiCompare(void) {
	const char* tempStrs[] = {
		"AAA",
		"BBB",
		"CCC",
		"DDD",
		"aaa",
		"bbb",
		"ccc",
		"ddd"
	};
	const Str_LenType tempStrs_Length = ARRAY_LEN(tempStrs);
	Str_LenType result;

	PRINTLN("MultiCompare:");

	result = Str_multiCompare(tempStrs, tempStrs_Length, "AAA");
	assert(Num, result, 0);

	result = Str_multiCompare(tempStrs, tempStrs_Length, "ddd");
	assert(Num, result, 7);

	result = Str_multiCompare(tempStrs, tempStrs_Length, "CCC");
	assert(Num, result, 2);

	result = Str_multiCompare(tempStrs, tempStrs_Length, "bbb");
	assert(Num, result, 5);

	result = Str_multiCompare(tempStrs, tempStrs_Length, "XXX");
	assert(Num, result, -1);

	return (uint32_t) Str_Ok;
}
// -------------------------------------------------------------------------------
uint32_t Test_multiCompareSorted(void) {
	const char* sortedStrs[] = {
		"AAA",
		"BBB",
		"CCC",
		"DDD",
		"aaa",
		"bbb",
		"ccc",
		"ddd"
	};
	const Str_LenType sortedStrs_Length = ARRAY_LEN(sortedStrs);
	Str_LenType result;

	PRINTLN("MultiCompare Sorted:");

	result = Str_multiCompareSorted(sortedStrs, sortedStrs_Length, "AAA");
	assert(Num, result, 0);

	result = Str_multiCompareSorted(sortedStrs, sortedStrs_Length, "ddd");
	assert(Num, result, 7);

	result = Str_multiCompareSorted(sortedStrs, sortedStrs_Length, "CCC");
	assert(Num, result, 2);

	result = Str_multiCompareSorted(sortedStrs, sortedStrs_Length, "bbb");
	assert(Num, result, 5);

	result = Str_multiCompareSorted(sortedStrs, sortedStrs_Length, "XXX");
	assert(Num, result, -1);

	return (uint32_t) Str_Ok;
}
// -------------------------------------------------------------------------------
uint32_t Test_findStrs(void) {
	const char* Text1 = "AAA BBB CCC DDD EEE FFF GGG";
	const char* Text2 = "XXX YYY ZZZ DDD EEE FFF GGG";
	const char* Text3 = "--- ||| --- WWW EEE FFF GGG";
	const char* tempStrs[] = {
		"AAA",
		"BBB",
		"CCC",
		"DDD",
		"GGG",
	};
	const Str_LenType tempStrs_Length = ARRAY_LEN(tempStrs);
	Str_MultiResult result;

	PRINTLN("Find Strs:");

	Str_findStrs(Text1, tempStrs, tempStrs_Length, &result);
	assert(Num, result.Position, 0);
	assert(Num, result.IndexOf, &Text1[0]);

	Str_findStrs(Text2, tempStrs, tempStrs_Length, &result);
	assert(Num, result.Position, 3);
	assert(Num, result.IndexOf, &Text2[12]);

	Str_findStrs(Text3, tempStrs, tempStrs_Length, &result);
	assert(Num, result.Position, 4);
	assert(Num, result.IndexOf, &Text3[24]);

	return (uint32_t) Str_Ok;
}
// -------------------------------------------------------------------------------
uint32_t Test_findStrsSorted(void) {
	const char* Text1 = "AAA BBB CCC DDD EEE FFF GGG";
	const char* Text2 = "XXX YYY ZZZ DDD EEE FFF GGG";
	const char* Text3 = "--- ||| --- WWW EEE FFF GGG";
	const char* tempStrs[] = {
		"AAA",
		"BBB",
		"CCC",
		"DDD",
		"GGG",
	};
	const Str_LenType tempStrs_Length = ARRAY_LEN(tempStrs);
	Str_MultiResult result;

	PRINTLN("Find Strs Sorted:");

	Str_findStrsSorted(Text1, tempStrs, tempStrs_Length, &result);
	assert(Num, result.Position, 0);
	assert(Num, result.IndexOf, &Text1[0]);

	Str_findStrsSorted(Text2, tempStrs, tempStrs_Length, &result);
	assert(Num, result.Position, 3);
	assert(Num, result.IndexOf, &Text2[12]);

	Str_findStrsSorted(Text3, tempStrs, tempStrs_Length, &result);
	assert(Num, result.Position, 4);
	assert(Num, result.IndexOf, &Text3[24]);

	return (uint32_t) Str_Ok;
}
// -------------------------------------------------------------------------------

void ItemUser_swap(const void* itemA, const void* itemB, Mem_LenType itemLen) {
	ItemUser temp;
	Mem_copy(&temp, itemA, itemLen);
	Mem_copy(itemA, itemB, itemLen);
	Mem_copy(itemB, &temp, itemLen);
}

char ItemUser_compareName(const void* itemA, const void* itemB, Mem_LenType itemLen) {
	return Str_compare(((ItemUser*) itemA)->Name, ((ItemUser*) itemB)->Name);
}

char ItemUser_compareAge(const void* itemA, const void* itemB, Mem_LenType itemLen) {
	return Mem_compare(&((ItemUser*) itemA)->Age, &((ItemUser*) itemB)->Age, sizeof(int));
}

uint32_t Test_memSort(void) {
	ItemUser users[10] = {
		ItemUser_init("Ali", 10, 190),
		ItemUser_init("your", 16, 199),
		ItemUser_init("mine", 19, 150),
		ItemUser_init("Bob", 20, 180),
		ItemUser_init("yellow", 24, 145),
		ItemUser_init("blue", 5, 200),
		ItemUser_init("Here", 30, 175),
		ItemUser_init("red", 18, 155),
		ItemUser_init("Jack", 25, 165),
		ItemUser_init("Zzz", 26, 165),
	};
	int usersLen = ARRAY_LEN(users);

	ItemUser usersSortedByName[10] = {
		ItemUser_init("Ali", 10, 190),
		ItemUser_init("Bob", 20, 180),
		ItemUser_init("Here", 30, 175),
		ItemUser_init("Jack", 25, 165),
		ItemUser_init("Zzz", 26, 165),
		ItemUser_init("blue", 5, 200),
		ItemUser_init("mine", 19, 150),
		ItemUser_init("red", 18, 155),
		ItemUser_init("yellow", 24, 145),
		ItemUser_init("your", 16, 199),
	};
	int usersSortedByNameLen = ARRAY_LEN(usersSortedByName);

	ItemUser usersSortedByAge[10] = {
		ItemUser_init("blue", 5, 200),
		ItemUser_init("Ali", 10, 190),
		ItemUser_init("your", 16, 199),
		ItemUser_init("red", 18, 155),
		ItemUser_init("mine", 19, 150),
		ItemUser_init("Bob", 20, 180),
		ItemUser_init("yellow", 24, 145),
		ItemUser_init("Jack", 25, 165),
		ItemUser_init("Zzz", 26, 165),
		ItemUser_init("Here", 30, 175),
	};
	int usersSortedByAgeLen = ARRAY_LEN(usersSortedByAge);

	PRINTLN("Mem Sort:");

	//Mem_sort(users, usersLen, sizeof(ItemUser), ItemUser_compareName, ItemUser_swap);
    //assert(ItemUsers, users, usersSortedByName, usersLen);

    Mem_sort(users, usersLen, sizeof(ItemUser), ItemUser_compareAge, ItemUser_swap);
    assert(ItemUsers, users, usersSortedByAge, usersLen);

    return (uint32_t) Str_Ok;
}

uint32_t Test_memQuickSort(void) {
	ItemUser users[10] = {
		ItemUser_init("Ali", 10, 190),
		ItemUser_init("your", 16, 199),
		ItemUser_init("mine", 19, 150),
		ItemUser_init("Bob", 20, 180),
		ItemUser_init("yellow", 24, 145),
		ItemUser_init("blue", 5, 200),
		ItemUser_init("Here", 30, 175),
		ItemUser_init("red", 18, 155),
		ItemUser_init("Jack", 25, 165),
		ItemUser_init("Zzz", 26, 165),
	};
	int usersLen = ARRAY_LEN(users);

	ItemUser usersSortedByName[10] = {
		ItemUser_init("Ali", 10, 190),
		ItemUser_init("Bob", 20, 180),
		ItemUser_init("Here", 30, 175),
		ItemUser_init("Jack", 25, 165),
		ItemUser_init("Zzz", 26, 165),
		ItemUser_init("blue", 5, 200),
		ItemUser_init("mine", 19, 150),
		ItemUser_init("red", 18, 155),
		ItemUser_init("yellow", 24, 145),
		ItemUser_init("your", 16, 199),
	};
	int usersSortedByNameLen = ARRAY_LEN(usersSortedByName);

	ItemUser usersSortedByAge[10] = {
		ItemUser_init("blue", 5, 200),
		ItemUser_init("Ali", 10, 190),
		ItemUser_init("your", 16, 199),
		ItemUser_init("red", 18, 155),
		ItemUser_init("mine", 19, 150),
		ItemUser_init("Bob", 20, 180),
		ItemUser_init("yellow", 24, 145),
		ItemUser_init("Jack", 25, 165),
		ItemUser_init("Zzz", 26, 165),
		ItemUser_init("Here", 30, 175),
	};
	int usersSortedByAgeLen = ARRAY_LEN(usersSortedByAge);

	PRINTLN("Mem Quick Sort:");

	Mem_quickSort(users, usersLen, sizeof(ItemUser), ItemUser_compareName, ItemUser_swap);
    assert(ItemUsers, users, usersSortedByName, usersLen);

    Mem_quickSort(users, usersLen, sizeof(ItemUser), ItemUser_compareAge, ItemUser_swap);
    assert(ItemUsers, users, usersSortedByAge, usersLen);

    return (uint32_t) Str_Ok;
}
// -------------------------------------------------------------------------------
char ItemUser_compareByName(const void* name, const void* item, Mem_LenType itemLen) {
	return Str_compare((const char*) name, ((ItemUser*) item)->Name);
}

char ItemUser_compareByAge(const void* age, const void* item, Mem_LenType itemLen) {
	return Mem_compare((const int*) age, &((ItemUser*) item)->Age, sizeof(int));
}

uint32_t Test_memLinearSearch(void) {
	ItemUser usersSortedByName[10] = {
		ItemUser_init("Ali", 10, 190),
		ItemUser_init("Bob", 20, 180),
		ItemUser_init("Here", 30, 175),
		ItemUser_init("Jack", 25, 165),
		ItemUser_init("Zzz", 26, 165),
		ItemUser_init("blue", 5, 200),
		ItemUser_init("mine", 19, 150),
		ItemUser_init("red", 18, 155),
		ItemUser_init("yellow", 24, 145),
		ItemUser_init("your", 16, 199),
	};
	int usersSortedByNameLen = ARRAY_LEN(usersSortedByName);

	ItemUser usersSortedByAge[10] = {
		ItemUser_init("blue", 5, 200),
		ItemUser_init("Ali", 10, 190),
		ItemUser_init("your", 16, 199),
		ItemUser_init("red", 18, 155),
		ItemUser_init("mine", 19, 150),
		ItemUser_init("Bob", 20, 180),
		ItemUser_init("yellow", 24, 145),
		ItemUser_init("Jack", 25, 165),
		ItemUser_init("Zzz", 26, 165),
		ItemUser_init("Here", 30, 175),
	};
	int usersSortedByAgeLen = ARRAY_LEN(usersSortedByAge);

	int age;
	Mem_LenType index;

	PRINTLN("Mem Linear Search:");

	index = Mem_linearSearch(usersSortedByName, usersSortedByNameLen, sizeof(ItemUser), "Ali", ItemUser_compareByName);
	assert(Num, index, 0);

	index = Mem_linearSearch(usersSortedByName, usersSortedByNameLen, sizeof(ItemUser), "blue", ItemUser_compareByName);
	assert(Num, index, 5);

	index = Mem_linearSearch(usersSortedByName, usersSortedByNameLen, sizeof(ItemUser), "red", ItemUser_compareByName);
	assert(Num, index, 7);

	age = 25;
	index = Mem_linearSearch(usersSortedByAge, usersSortedByAgeLen, sizeof(ItemUser), &age, ItemUser_compareByAge);
	assert(Num, index, 7);

	age = 10;
	index = Mem_linearSearch(usersSortedByAge, usersSortedByAgeLen, sizeof(ItemUser), &age, ItemUser_compareByAge);
	assert(Num, index, 1);

	age = 18;
	index = Mem_linearSearch(usersSortedByAge, usersSortedByAgeLen, sizeof(ItemUser), &age, ItemUser_compareByAge);
	assert(Num, index, 3);

	age = 100;
	index = Mem_linearSearch(usersSortedByAge, usersSortedByAgeLen, sizeof(ItemUser), &age, ItemUser_compareByAge);
	assert(Num, index, -1);

	return (uint32_t) Str_Ok;
}
uint32_t Test_memBinarySearch(void) {
	ItemUser usersSortedByName[10] = {
		ItemUser_init("Ali", 10, 190),
		ItemUser_init("Bob", 20, 180),
		ItemUser_init("Here", 30, 175),
		ItemUser_init("Jack", 25, 165),
		ItemUser_init("Zzz", 26, 165),
		ItemUser_init("blue", 5, 200),
		ItemUser_init("mine", 19, 150),
		ItemUser_init("red", 18, 155),
		ItemUser_init("yellow", 24, 145),
		ItemUser_init("your", 16, 199),
	};
	int usersSortedByNameLen = ARRAY_LEN(usersSortedByName);

	ItemUser usersSortedByAge[10] = {
		ItemUser_init("blue", 5, 200),
		ItemUser_init("Ali", 10, 190),
		ItemUser_init("your", 16, 199),
		ItemUser_init("red", 18, 155),
		ItemUser_init("mine", 19, 150),
		ItemUser_init("Bob", 20, 180),
		ItemUser_init("yellow", 24, 145),
		ItemUser_init("Jack", 25, 165),
		ItemUser_init("Zzz", 26, 165),
		ItemUser_init("Here", 30, 175),
	};
	int usersSortedByAgeLen = ARRAY_LEN(usersSortedByAge);

	int age;
	Mem_LenType index;

	PRINTLN("Mem Binary Search:");

	index = Mem_binarySearch(usersSortedByName, usersSortedByNameLen, sizeof(ItemUser), "Ali", ItemUser_compareByName);
	assert(Num, index, 0);

	index = Mem_binarySearch(usersSortedByName, usersSortedByNameLen, sizeof(ItemUser), "blue", ItemUser_compareByName);
	assert(Num, index, 5);

	index = Mem_binarySearch(usersSortedByName, usersSortedByNameLen, sizeof(ItemUser), "red", ItemUser_compareByName);
	assert(Num, index, 7);

	age = 25;
	index = Mem_binarySearch(usersSortedByAge, usersSortedByAgeLen, sizeof(ItemUser), &age, ItemUser_compareByAge);
	assert(Num, index, 7);

	age = 10;
	index = Mem_binarySearch(usersSortedByAge, usersSortedByAgeLen, sizeof(ItemUser), &age, ItemUser_compareByAge);
	assert(Num, index, 1);

	age = 18;
	index = Mem_binarySearch(usersSortedByAge, usersSortedByAgeLen, sizeof(ItemUser), &age, ItemUser_compareByAge);
	assert(Num, index, 3);

	age = 100;
	index = Mem_binarySearch(usersSortedByAge, usersSortedByAgeLen, sizeof(ItemUser), &age, ItemUser_compareByAge);
	assert(Num, index, -1);

	return (uint32_t) Str_Ok;
}
// -------------------------------------------------------------------------------
uint32_t Test_trim(void) {
	char tempStr[32];

	PRINTLN("Trim:");


	Str_copy(tempStr, "Hello");
	Str_trimLeft(tempStr);
	assert(Str, tempStr, "Hello");

	Str_copy(tempStr, "Booo");
	Str_trimRight(tempStr);
	assert(Str, tempStr, "Booo");

	Str_copy(tempStr, "hi");
	Str_trim(tempStr);
	assert(Str, tempStr, "hi");

	Str_copy(tempStr, "  Hello  ");
	Str_trimLeft(tempStr);
	assert(Str, tempStr, "Hello  ");

	Str_copy(tempStr, "  Hello World ");
	Str_trimLeft(tempStr);
	assert(Str, tempStr, "Hello World ");

	Str_copy(tempStr, " Booo  ");
	Str_trimRight(tempStr);
	assert(Str, tempStr, " Booo");

	Str_copy(tempStr, " Booo Hoo ");
	Str_trimRight(tempStr);
	assert(Str, tempStr, " Booo Hoo");

	Str_copy(tempStr, "  hi  ");
	Str_trim(tempStr);
	assert(Str, tempStr, "hi");

	Str_copy(tempStr, "  Test Case  ");
	Str_trim(tempStr);
	assert(Str, tempStr, "Test Case");

	return (uint32_t) Str_Ok;
}
// -------------------------------------------------------------------------------
uint32_t Assert_Str(const char* str1, const char* str2, uint32_t line) {
	if (Str_compare(str1, str2)) {
		PRINTF("\"%s\"\n", str1);
		return Str_Error | line << 1;
	}
	return (uint32_t) Str_Ok;
}
uint32_t Assert_Num(int num1, int num2, uint32_t line) {
	if (num1 != num2) {
		PRINTF("%d\r\n", (num1));
		return Str_Error | line << 1;
	}
	return (uint32_t) Str_Ok;
}
uint32_t Assert_Float(float num1, float num2, uint32_t line) {
	if (num1 != num2) {
		PRINTF("%f\r\n", (num1));
		return Str_Error | line << 1;
	}
	return (uint32_t) Str_Ok;
}

uint32_t Assert_Strs(const char** strs1, const char** strs2, int len, uint32_t line) {
	int tempLen = len;
	const char** tempStrs = strs1;
	while (len--) {
		if (Str_compare(*strs1++, *strs2++)) {
			printStrs(tempStrs, tempLen);
			return Str_Error | line << 1;
		}
	}
	return (uint32_t) Str_Ok;
}

uint32_t Assert_Ptr(const void* ptr1, const void* ptr2, uint32_t line) {
    if (ptr1 != ptr2) {
        PRINTF("%p\r\n", (ptr1));
		return Str_Error | line << 1;
    }
    return (uint32_t) Str_Ok;
}

uint32_t Assert_ItemUsers(const ItemUser* items1, const ItemUser* items2, int len, uint32_t line) {
	int tempLen = len;
	const char** tempStrs = items1;
	while (len--) {
		if (Mem_compare(items1++, items2++, sizeof(ItemUser))) {
			printItemUsers(tempStrs, tempLen);
			return Str_Error | line << 1;
		}
	}
	return (uint32_t) Str_Ok;
}

void printStrs(const char** strs, int len) {
	while (len--) {
		PRINTLN(*strs++);
	}
}
void printItemUsers(const ItemUser* items, int len) {
	while (len--) {
		PRINTF("{\"%s\", %d, %d}\n", items->Name, items->Age, items->Height);
		items++;
	}
}

