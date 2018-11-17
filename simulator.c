/*
 * TCSS 371 HW 4
 * Ethan Cheatham
 *
 *
 */
#include <stdio.h>

#include "bstr.h"

#include "comp.h"


void bitStringTest(void) {

	BitString bStr;
	BitString bStr1;
	BitString bStr2;
	BitString bStr3;
	BitString bStr4;

	int testValues[] = { 255, -255, -83, 83 };
	int i;
	for (i = 0; i < 4; i++) {

   	    BSTR_SetValueTwosComp(&bStr, testValues[i], 16);
	    BSTR_Display(bStr, 1);
	    printf("\n");
        printf("Value = %d\n", BSTR_GetValueTwosComp(bStr));
    }


    BSTR_SetValue(&bStr1, 4, 8);
	BSTR_SetValue(&bStr2, 10, 8);
	BSTR_Display(bStr1, 1);
	printf("\n");
	BSTR_Display(bStr2, 1);
	printf("\n");
	printf("Length = %d\n", BSTR_Length(bStr1));
	printf("Length = %d\n", BSTR_Length(bStr2));
	BSTR_Append(&bStr3, bStr1, bStr2);
    printf("Length = %d\n", BSTR_Length(bStr3));
	BSTR_Display(bStr3, 1);
	printf("\n");

	BSTR_Substring(&bStr4,bStr3,4,8);
	BSTR_Display(bStr4, 1);
	printf("\n");
}

int main(int argc, const char * argv[]) {

    Computer comp;
    int programSize = 10;
    BitString instruction;

    char* program[] =
    {
     "0010000000000111",
     "0010001000000111",
     "0001010000000001",
     "0000010000000011",
     "1111000000100001",
     "0001000000111111",
     "0000111111111011",
     "1111000000100101",
     "0000000000111001",
     "1111111111010000"
	 };


    //initial state
	COMP_Init(&comp);

	//load instructions (bits) into computer
	for (int i = 0; i < programSize; i++) {
	    BSTR_SetBits(&instruction, program[i]);
	    COMP_LoadWord(&comp, i, instruction);
//	    COMP_Display(comp);
	}

	//execute the program
	COMP_Execute(&comp);
	//shows final configuration
	COMP_Display(comp);
}