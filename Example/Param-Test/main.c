#include <stdio.h>

#include "Param.h"

#define PRINTLN						puts
#define PRINTF						printf

uint32_t assertResult = 0;
#define assert(TYPE, ...)			if((assertResult = Assert_ ##TYPE (__VA_ARGS__, __LINE__)) != Str_Ok) return assertResult

#define ARRAY_LEN(ARR)			    (sizeof(ARR) / sizeof(ARR[0]))

#define setValue(IDX, TYPE, VAL)    values[IDX].Type = Param_ValueType_ ##TYPE;\
                                    values[IDX].TYPE = VAL

typedef uint32_t Param_Result;
typedef Param_Result (*Test_Fn)(void);

Param_Result Assert_Param(char* buff, Param_Value* values, int len, uint16_t cLine);
Param_Result Assert_Str(const char* str1, const char* str2, uint16_t line);
void Result_print(Param_Result result);
void Param_print(Param* param);

Param_Result Test_1(void);
Param_Result Test_2(void);

const Test_Fn Tests[] = {
    Test_1,
    Test_2,
};
const uint32_t Tests_Len = sizeof(Tests) / sizeof(Tests[0]);

int main()
{
    int testIndex;
	int countTestError = 0;
	Param_Result res;

	for (testIndex = 0; testIndex < Tests_Len; testIndex++) {
		PRINTF("---------------- Beginning Test[%d]------------ \r\n", testIndex);
		res = Tests[testIndex]();
		PRINTF("Test Result: %s\r\n", res ? "Error" : "Ok");
		if (res) {
			Result_print(res);
			countTestError++;
		}
		PRINTF("---------------------------------------------- \r\n", testIndex);
	}
	PRINTLN("Test Done\r\n");
	PRINTF("Tests Errors: %d\r\n", countTestError);
}

Param_Result Test_1(void) {
    char TEMP1[20];
    char TEMP2[20];
    char TEMP3[20];
    char TEMP4[20];
    char BUFF[100] = "";
    Param_Value values[10];
    char str[100];

    Str_copy(BUFF, "12, 13, 14, 15");
    values[0].Type = Param_ValueType_Number;
    values[0].Number = 12;
    values[1].Type = Param_ValueType_Number;
    values[1].Number = 13;
    values[2].Type = Param_ValueType_Number;
    values[2].Number = 14;
    values[3].Type = Param_ValueType_Number;
    values[3].Number = 15;
    Param_toStr(str, values, 4, ", ");
    assert(Str, str, BUFF);

    Str_copy(BUFF, "2.5,123,\"Ali\",Off");
    Str_copy(TEMP1, "Ali");
    values[0].Type = Param_ValueType_Float;
    values[0].Float = 2.5f;
    values[1].Type = Param_ValueType_Number;
    values[1].Number = 123;
    values[2].Type = Param_ValueType_String;
    values[2].String = TEMP1;
    values[3].Type = Param_ValueType_StateKey;
    values[3].StateKey = 0;
    Param_toStr(str, values, 4, ",");
    assert(Str, str, BUFF);

    Str_copy(BUFF, "Null,ABC,0xAA,0b1010");
    Str_copy(TEMP1, "Null");
    Str_copy(TEMP2, "ABC");
    values[0].Type = Param_ValueType_Null;
    values[0].Null = TEMP1;
    values[1].Type = Param_ValueType_Unknown;
    values[1].Unknown = TEMP2;
    values[2].Type = Param_ValueType_NumberHex;
    values[2].NumberHex = 0xAA;
    values[3].Type = Param_ValueType_NumberBinary;
    values[3].NumberBinary = 10;
    Param_toStr(str, values, 4, ",");
    assert(Str, str, BUFF);

    Str_copy(BUFF, "\"LOL\",1.125,High,Null");
    Str_copy(TEMP1, "LOL");
    Str_copy(TEMP2, "Null");
    values[0].Type = Param_ValueType_String;
    values[0].String = TEMP1;
    values[1].Type = Param_ValueType_Float;
    values[1].Float = 1.125f;
    values[2].Type = Param_ValueType_State;
    values[2].State = 1;
    values[3].Type = Param_ValueType_Null;
    values[3].Null = 0;
    Param_toStr(str, values, 4, ",");
    assert(Str, str, BUFF);

    Str_copy(BUFF, "\"oOo\",AAAAA,Boo,Ok");
    Str_copy(TEMP1, "oOo");
    Str_copy(TEMP2, "AAAAA");
    Str_copy(TEMP3, "Boo");
    Str_copy(TEMP4, "Ok");
    values[0].Type = Param_ValueType_String;
    values[0].String = TEMP1;
    values[1].Type = Param_ValueType_Unknown;
    values[1].Unknown = TEMP2;
    values[2].Type = Param_ValueType_Unknown;
    values[2].Unknown = TEMP3;
    values[3].Type = Param_ValueType_Unknown;
    values[3].Unknown = TEMP4;
    Param_toStr(str, values, 4, ",");
    assert(Str, str, BUFF);

    Str_copy(BUFF, "?, 145, 5.5, Null");
    Str_copy(TEMP1, "?");
    Str_copy(TEMP2, "Null");
    values[0].Type = Param_ValueType_Unknown;
    values[0].String = TEMP1;
    values[1].Type = Param_ValueType_Number;
    values[1].Number = 145;
    values[2].Type = Param_ValueType_Float;
    values[2].Float = 5.5f;
    values[3].Type = Param_ValueType_Null;
    values[3].Null = TEMP2;
    Param_toStr(str, values, 4, ", ");
    assert(Str, str, BUFF);

    return 0;
}

Param_Result Test_2(void) {
    char TEMP1[20];
    char TEMP2[20];
    char TEMP3[20];
    char TEMP4[20];
    char BUFF[100] = "";
    Param_Value values[10];
    char str[100];

    Str_copy(BUFF, "12, 13, 14, 15");
    setValue(0, Number, 12);
    setValue(1, Number, 13);
    setValue(2, Number, 14);
    setValue(3, Number, 15);
    assert(Param, BUFF, values, 4);

    Str_copy(BUFF, "2.5,123,\"Ali\",Off");
    Str_copy(TEMP1, "Ali");
    setValue(0, Float, 2.5f);
    setValue(1, Number, 123);
    setValue(2, String, TEMP1);
    setValue(3, StateKey, 0);
    assert(Param, BUFF, values, 4);

    Str_copy(BUFF, "Null,ABC,0xAA,0b1010");
    Str_copy(TEMP1, "Null");
    Str_copy(TEMP2, "ABC");
    setValue(0, Null, TEMP1);
    setValue(1, Unknown, TEMP2);
    setValue(2, NumberHex, 0xAA);
    setValue(3, NumberBinary, 10);
    assert(Param, BUFF, values, 4);

    Str_copy(BUFF, "\"LOL\",1.125,High,Null");
    Str_copy(TEMP1, "LOL");
    Str_copy(TEMP2, "Null");
    setValue(0, String, TEMP1);
    setValue(1, Float, 1.125f);
    setValue(2, State, 1);
    setValue(3, Null, TEMP2);
    assert(Param, BUFF, values, 4);

    Str_copy(BUFF, "\"oOo\",AAAAA,Boo,Ok");
    Str_copy(TEMP1, "oOo");
    Str_copy(TEMP2, "AAAAA");
    Str_copy(TEMP3, "Boo");
    Str_copy(TEMP4, "Ok");
    setValue(0, String, TEMP1);
    setValue(1, Unknown, TEMP2);
    setValue(2, Unknown, TEMP3);
    setValue(3, Unknown, TEMP4);
    assert(Param, BUFF, values, 4);

    Str_copy(BUFF, "?, 145, 5.5, Null");
    Str_copy(TEMP1, "?");
    Str_copy(TEMP2, "Null");
    setValue(0, Unknown, TEMP1);
    setValue(1, Number, 145);
    setValue(2, Float, 5.5f);
    setValue(3, Null, TEMP2);
    assert(Param, BUFF, values, 4);

    Str_copy(BUFF, "as,0b0111,ok,boo,null,0x10");
    Str_copy(TEMP1, "as");
    Str_copy(TEMP2, "ok");
    Str_copy(TEMP3, "boo");
    Str_copy(TEMP4, "null");
    setValue(0, Unknown, TEMP1);
    setValue(1, NumberBinary, 7);
    setValue(2, Unknown, TEMP2);
    setValue(3, Unknown, TEMP3);
    setValue(4, Null, TEMP4);
    setValue(5, NumberHex, 0x10);
    assert(Param, BUFF, values, 6);

    Str_copy(BUFF, "14, \"Test\",0b0111 , ooo , low,high,0x10, sss,null");
    Str_copy(TEMP1, "Test");
    Str_copy(TEMP2, "ooo");
    Str_copy(TEMP3, "sss");
    Str_copy(TEMP4, "null");
    setValue(0, Number, 14);
    setValue(1, String, TEMP1);
    setValue(2, NumberBinary, 7);
    setValue(3, Unknown, TEMP2);
    setValue(4, State, 0);
    setValue(5, State, 1);
    setValue(6, NumberHex, 0x10);
    setValue(7, Unknown, TEMP3);
    setValue(8, Null, TEMP4);
    assert(Param, BUFF, values, 9);

    Str_copy(BUFF, "\"your-SSID\", \"your-pass\"");
    Str_copy(TEMP1, "your-SSID");
    Str_copy(TEMP2, "your-pass");
    setValue(0, String, TEMP1);
    setValue(1, String, TEMP2);
    assert(Param, BUFF, values, 2);

    Str_copy(BUFF, "12x8, null p");
    Str_copy(TEMP1, "12x8");
    Str_copy(TEMP2, "null p");
    setValue(0, Unknown, TEMP1);
    setValue(1, Unknown, TEMP2);
    assert(Param, BUFF, values, 2);

    return 0;
}

void Result_print(Param_Result result) {
    PRINTF("Line: %u, Index: %u\r\n", result >> 16, result & 0xFFFF);
}
void Param_print(Param* param) {
    static const char* TYPES[] = {
        "Unknown",
        "Number",
        "NumberHex",
        "NumberBinary",
        "Float",
        "State",
        "StateKey",
        "Boolean",
        "String",
        "Null",
    };

    PRINTF("{%u, %s, ", param->Index, TYPES[(int) param->Value.Type]);
    switch (param->Value.Type) {
        case Param_ValueType_Unknown:
            PRINTF("\"%s\"", param->Value.Unknown);
            break;
        case Param_ValueType_Number:
            PRINTF("%d", param->Value.Number);
            break;
        case Param_ValueType_NumberHex:
            PRINTF("%X", param->Value.NumberHex);
            break;
        case Param_ValueType_NumberBinary:
            PRINTF("%u", param->Value.NumberBinary);
            break;
        case Param_ValueType_Float:
            PRINTF("%g", param->Value.Float);
            break;
        case Param_ValueType_State:
            PRINTF("%s", param->Value.State ? "HIGH" : "LOW");
            break;
        case Param_ValueType_StateKey:
            PRINTF("%s", param->Value.StateKey ? "ON" : "OFF");
            break;
        case Param_ValueType_Boolean:
            PRINTF("%s", param->Value.Boolean ? "true" : "false");
            break;
        case Param_ValueType_String:
            PRINTF("\"%s\"", param->Value.String);
            break;
        case Param_ValueType_Null:
            PRINTF("\"%s\"", param->Value.Null);
            break;
    }
    PRINTLN("}");
}

Param_Result Assert_Param(char* buff, Param_Value* values, int len, uint16_t cLine) {
    Param param;
    Param_Cursor cursor;
    cursor.Index = 0;
    cursor.Len = Str_len(buff);
    cursor.ParamSeperator = ',';
    cursor.Ptr = buff;

    while (Param_next(&cursor, &param)) {
        if (Param_compareValue(&param.Value, values) == 0) {
            Param_print(&param);
            return cLine << 16 | param.Index;
        }
        values++;
        len--;
    }
    if (len > 0) {
        return cLine << 16 | param.Index;
    }
    else {
        return 0;
    }
}
Param_Result Assert_Str(const char* str1, const char* str2, uint16_t line) {
	if (Str_compare(str1, str2)) {
		PRINTF("\"%s\"\n", str1);
		return Str_Error | line << 16;
	}
	return (uint32_t) Str_Ok;
}
