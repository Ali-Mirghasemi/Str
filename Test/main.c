#include <stdio.h>
#include "StrUtils.h"

int Assert_Str(const char* str1, const char* str2, int line);
int Assert_Num(int num1, int num2, int line);
int Assert_Float(float num1, float num2, int line);
int Assert_Strs(const char** strs1, const char** strs2, int len, int line);

int assertResult = 0;
#define assert(TYPE, ...)			if((assertResult = Assert_ ##TYPE (__VA_ARGS__, __LINE__)) != Str_Ok) return assertResult

void Print_Strs(const char** strs, int len);

typedef int (*TestFunc)(void);

int Test_Parse(void);
int Test_Convert(void);
int Test_Get(void);
int Test_Replace(void);
int Test_Sort(void);
int Test_QuickSort(void);
int Test_MultiCompare(void);
int Test_MultiCompareSorted(void);
int Test_FindStrs(void);
int Test_FindStrsSorted(void);

const TestFunc Tests[] = {
	Test_Parse,
	Test_Convert,
	Test_Get,
	Test_Replace,
	Test_Sort,
	Test_QuickSort,
	Test_MultiCompare,
	Test_MultiCompareSorted,
	Test_FindStrs,
	Test_FindStrsSorted,
};
const int Tests_Length = sizeof(Tests) / sizeof(Tests[0]);

int main(void) {
	int testIndex;
	int countTestError = 0;
	Str_Result res;

	for (testIndex = 0; testIndex < Tests_Length; testIndex++) {
		printf("---------------- Begining Test[%d]------------ \r\n", testIndex);
		res = Tests[testIndex]();
		printf("Test Result: %s\r\n", res & 0x01 ? "Error" : "Ok");
		if (res & 1) {
			printf("Error in Line: %d\r\n", res >> 1);
		}
		countTestError += (int) res & 1;
		printf("---------------------------------------------- \r\n", testIndex);
	}
	puts("Test Done\r\n");
	printf("Tests Errors: %d\r\n", countTestError);
}

int Test_Parse(void) {
	char tempStr[32];
	puts("Parse:");

	Str_ParseNum(5, Str_Decimal, STR_NORMAL_LEN, tempStr);
	assert(Str, tempStr, "5");

	Str_ParseNum(10, Str_Decimal, STR_NORMAL_LEN, tempStr);
	assert(Str, tempStr, "10");

	Str_ParseNum(1234, Str_Decimal, 2, tempStr);
	assert(Str, tempStr, "1234");

	Str_ParseNum(12, Str_Binary, 4, tempStr);
	assert(Str, tempStr, "1100");

	Str_ParseNum(255, Str_Hex, 4, tempStr);
	assert(Str, tempStr, "00FF");

	Str_ParseFloatFix(2.45f, tempStr, 2);
	assert(Str, tempStr, "2.45");

	Str_ParseFloatFix(5.75f, tempStr, 1);
	assert(Str, tempStr, "5.7");

	Str_ParseFloatFix(-5.75f, tempStr, 1);
	assert(Str, tempStr, "-5.7");

	Str_ParseFloatFix(5.75f, tempStr, 3);
	assert(Str, tempStr, "5.750");

	Str_ParseFloatFix(5.754f, tempStr, 0);
	assert(Str, tempStr, "5");

	Str_ParseFloatFix(-5.754f, tempStr, 0);
	assert(Str, tempStr, "-5");

	Str_ParseFloatFix(10.456f, tempStr, 3);
	assert(Str, tempStr, "10.456");

	Str_ParseFloat(10.5f, tempStr);
	assert(Str, tempStr, "10.5");

	Str_ParseFloat(10.75f, tempStr);
	assert(Str, tempStr, "10.75");

	Str_ParseFloat(10.125f, tempStr);
	assert(Str, tempStr, "10.125");

	return Str_Ok;
}

int Test_Convert(void) {
	int tempNum;
	float tempFloat;
	puts("Convert:");

	Str_ConvertNum("123", &tempNum, Str_Decimal);
	assert(Num, tempNum, 123);

	Str_ConvertNum("-431", &tempNum, Str_Decimal);
	assert(Num, tempNum, -431);

	Str_ConvertNum("1", &tempNum, Str_Decimal);
	assert(Num, tempNum, 1);

	Str_ConvertNumFix("1234", &tempNum, Str_Decimal, 2);
	assert(Num, tempNum, 12);

	Str_ConvertNum("4756", &tempNum, Str_Decimal);
	assert(Num, tempNum, 4756);

	Str_ConvertFloat("5.5", &tempFloat);
	assert(Float, tempFloat, 5.5f);

	Str_ConvertFloat("-5.5", &tempFloat);
	assert(Float, tempFloat, -5.5f);

	Str_ConvertFloat("-5", &tempFloat);
	assert(Float, tempFloat, -5.0f);

	Str_ConvertFloat("3.", &tempFloat);
	assert(Float, tempFloat, 3.0f);

	Str_ConvertFloatFix("5.575", &tempFloat, 3);
	assert(Float, tempFloat, 5.5f);

	return Str_Ok;
}

int Test_Get(void) {
	int tempNum;
	float tempFloat;
	const char* numPos;
	puts("Get:");

	Str_GetNum("This is my number: 1234", &tempNum, &numPos);
	assert(Num, tempNum, 1234);

	Str_GetNum("34 is Number", &tempNum, &numPos);
	assert(Num, tempNum, 34);

	Str_GetNum("ABC,-47,25", &tempNum, &numPos);
	assert(Num, tempNum, -47);

	Str_GetNum("-- 88 --", &tempNum, &numPos);
	assert(Num, tempNum, 88);

	Str_GetFloat("-- 2. --", &tempFloat, &numPos);
	assert(Float, tempFloat, 2.0f);

	Str_GetFloat("-- 3.5 --", &tempFloat, &numPos);
	assert(Float, tempFloat, 3.5f);

	return Str_Ok;
}

int Test_Replace(void) {
	char tempStr[32];
	puts("Replace:");

	Str_Copy("Hello my name is Ali", tempStr);
	Str_Replace(tempStr, "Ali", "Reza");
	assert(Str, tempStr, "Hello my name is Reza");

	Str_Copy("I Lost", tempStr);
	Str_Replace(tempStr, "I", "We");
	assert(Str, tempStr, "We Lost");

	Str_Copy("AAA BBB CCC", tempStr);
	Str_Replace(tempStr, "BBB", "X");
	assert(Str, tempStr, "AAA X CCC");

	Str_Copy("111 2 333", tempStr);
	Str_Replace(tempStr, "2", "222");
	assert(Str, tempStr, "111 222 333");

	Str_Copy("This is My life", tempStr);
	Str_Replace(tempStr, "This ", "");
	assert(Str, tempStr, "is My life");

	return Str_Ok;
}

int Test_Sort(void) {
	const char* tempStrs[] = {
		"ABCD",
		"123",
		"abcd",
		"9876",
		"-w-",
	};
	const int tempStrs_Length = sizeof(tempStrs) / sizeof(tempStrs[0]);

	const char* sortedStrs[] = {
		"-w-",
		"123",
		"9876",
		"ABCD",
		"abcd",
	};
	puts("Sort:");

	Str_Sort(tempStrs, tempStrs_Length);
	assert(Strs, tempStrs, sortedStrs, tempStrs_Length);

	return (int) Str_Ok;
}

int Test_QuickSort(void) {
	const char* tempStrs[] = {
		"red",
		"blue",
		"yellow",
		"mine",
		"your",
		"Here"
	};
	const int tempStrs_Length = sizeof(tempStrs) / sizeof(tempStrs[0]);

	const char* sortedStrs[] = {
		"Here",
		"blue",
		"mine",
		"red",
		"yellow",
		"your",
	};
	const int sortedStrs_Length = sizeof(tempStrs) / sizeof(tempStrs[0]);

	puts("Quick Sort:");

	Str_QuickSort(tempStrs, tempStrs_Length);
	assert(Strs, tempStrs, sortedStrs, tempStrs_Length);

	return (int) Str_Ok;
}

int Test_MultiCompare(void) {
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
	const Str_LenType tempStrs_Length = sizeof(tempStrs) / sizeof(tempStrs[0]);
	Str_LenType result;

	puts("MultiCompare:");

	result = Str_MultiCompare(tempStrs, tempStrs_Length, "AAA");
	assert(Num, result, 0);

	result = Str_MultiCompare(tempStrs, tempStrs_Length, "ddd");
	assert(Num, result, 7);

	result = Str_MultiCompare(tempStrs, tempStrs_Length, "CCC");
	assert(Num, result, 2);

	result = Str_MultiCompare(tempStrs, tempStrs_Length, "bbb");
	assert(Num, result, 5);

	result = Str_MultiCompare(tempStrs, tempStrs_Length, "XXX");
	assert(Num, result, -1);

	return (int) Str_Ok;
}

int Test_MultiCompareSorted(void) {
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
	const Str_LenType sortedStrs_Length = sizeof(sortedStrs) / sizeof(sortedStrs[0]);
	Str_LenType result;

	puts("MultiCompare Sorted:");

	result = Str_MultiCompareSorted(sortedStrs, sortedStrs_Length, "AAA");
	assert(Num, result, 0);

	result = Str_MultiCompareSorted(sortedStrs, sortedStrs_Length, "ddd");
	assert(Num, result, 7);

	result = Str_MultiCompareSorted(sortedStrs, sortedStrs_Length, "CCC");
	assert(Num, result, 2);

	result = Str_MultiCompareSorted(sortedStrs, sortedStrs_Length, "bbb");
	assert(Num, result, 5);

	result = Str_MultiCompareSorted(sortedStrs, sortedStrs_Length, "XXX");
	assert(Num, result, -1);

	return (int) Str_Ok;
}

int Test_FindStrs(void) {
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
	const Str_LenType tempStrs_Length = sizeof(tempStrs) / sizeof(tempStrs[0]);
	Str_MultiResult result;

	puts("Find Strs:");

	Str_FindStrs(Text1, tempStrs, tempStrs_Length, &result);
	assert(Num, result.Position, 0);
	assert(Num, result.IndexOf, &Text1[0]);

	Str_FindStrs(Text2, tempStrs, tempStrs_Length, &result);
	assert(Num, result.Position, 3);
	assert(Num, result.IndexOf, &Text2[12]);

	Str_FindStrs(Text3, tempStrs, tempStrs_Length, &result);
	assert(Num, result.Position, 4);
	assert(Num, result.IndexOf, &Text3[24]);

	return (int) Str_Ok;
}

int Test_FindStrsSorted(void) {
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
	const Str_LenType tempStrs_Length = sizeof(tempStrs) / sizeof(tempStrs[0]);
	Str_MultiResult result;

	puts("Find Strs Sorted:");

	Str_FindStrsSorted(Text1, tempStrs, tempStrs_Length, &result);
	assert(Num, result.Position, 0);
	assert(Num, result.IndexOf, &Text1[0]);

	Str_FindStrsSorted(Text2, tempStrs, tempStrs_Length, &result);
	assert(Num, result.Position, 3);
	assert(Num, result.IndexOf, &Text2[12]);

	Str_FindStrsSorted(Text3, tempStrs, tempStrs_Length, &result);
	assert(Num, result.Position, 4);
	assert(Num, result.IndexOf, &Text3[24]);

	return (int) Str_Ok;
}

int Assert_Str(const char* str1, const char* str2, int line) {
	if (Str_Compare((str1), (str2))) {
		puts((str1));
		return Str_Error | line << 1;
	}
	return (int) Str_Ok;
}
int Assert_Num(int num1, int num2, int line) {
	if (num1 != num2) {
		printf("%d\r\n", (num1));
		return Str_Error | line << 1;
	}
	return (int) Str_Ok;
}
int Assert_Float(float num1, float num2, int line) {
	if (num1 != num2) {
		printf("%f\r\n", (num1));
		return Str_Error | line << 1;
	}
	return (int) Str_Ok;
}

int Assert_Strs(const char** strs1, const char** strs2, int len, int line) {
	int tempLen = len;
	const char** tempStrs = strs1;
	while (len--) {
		if (Str_Compare(*strs1++, *strs2++)) {
			Print_Strs(tempStrs, tempLen);
			return Str_Error | line << 1;
		}
	}
	return (int) Str_Ok;
}

void Print_Strs(const char** strs, int len) {
	while (len--) {
		puts(*strs++);
	}
}

