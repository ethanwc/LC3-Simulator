/*
 * TCSS 371 hw 4
 * Ethan Cheatham
 * Carl Argabright
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


void testNot() {/* NOT test */
    printf("\n\n\t\t####  Starting NOT test  ####\n");

    /* Initialize computer */
    Computer comp;
    COMP_Init(&comp);

    /* Create desired instructions */
    BitString notInstr;
    BSTR_SetBits(&notInstr, "1001100101111111"); // NOT Dest: R4, Source: R5

    /* Load desired instructions */
    COMP_LoadWord(&comp,0,notInstr);

    /* Display initialized computer and loaded instructions */
    printf("\t####  Displaying computers initial state  ####\n");
    COMP_Display(comp);

    /* Execute all loaded instructions */
    COMP_Execute(&comp);

    /* Display state of computer after execution */
    printf("\n\n\t####  Displaying computers state after execution ####\n");
    COMP_Display(comp);

    printf("\n\t\t####  Finished NOT test  ####\n\n");
    printf("Verify R4 <-- NOT(R5)\n");
    printf("R4 Value = %d\n", BSTR_GetValueTwosComp(comp.reg[4]));
    printf("Verify CC n,z,p = 100");
}

/**
 * Tests register mode of the ADD instruction using the following
 * formula for the given values a and b stored respectively in R0 and R1.
 *
 * c = a + b
 * R2 <- R0 + R1
 *
 * @param a 16 bit signed integer value to be added
 * @param b 16 bit signed integer value to be added
 */
void testAddRegisterMode(int a, int b) {
    printf("\n\n\t\t####  Starting ADD - Register Mode test  ####\n");

    /* Initialize computer */
    Computer comp;
    COMP_Init(&comp);

    /* Create desired instructions */
    BitString addInstr;                         // R2 <-- R0 + R1
    BSTR_SetBits(&addInstr, "0001010000000001"); // ADD Dest: R2, Src1: R0 Src2: R1

    /* Load desired instructions */
    COMP_LoadWord(&comp, 0, addInstr);

    /* Setup R0 and R1 with the given value of a */
    BSTR_SetValueTwosComp(&(comp.reg[0]), a, 16); // R0 <-- a
    BSTR_SetValueTwosComp(&(comp.reg[1]), b, 16); // R1 <-- b

    /* Display initialized computer and loaded instructions */
    printf("\t####  Displaying computers initial state  ####\n");
    COMP_Display(comp);

    /* Execute all loaded instructions */
    COMP_Execute(&comp);

    /* Display state of computer after execution */
    printf("\n\n\t####  Displaying computers state after execution ####\n");
    COMP_Display(comp);

    printf("\n\t\t####  Finished ADD - Register Mode test  ####\n\n");
    printf("Verify R2 <-- R0 + R1)\n");
    printf("Verify R2 <-- %d + %d)\n", a, b);
    printf("R2 Value = %d\n", BSTR_GetValueTwosComp(comp.reg[2]));
    printf("Verify CC n,z,p for the given stored result\n");
}

/***
 * Tests immediate mode of the ADD instruction using the following
 * formula for the given values a and b stored respectively in R0 and b
 * where b is a literal value to be added to a and stored in R1
 *
 * c = a + b
 * R1 <- R0 + b
 *
 * @param a 16 bit signed integer value to be added
 * @param b 5 bit signed integer value to be added
 */
void testAddImmediateMode(int a, int b) {
    printf("\n\n\t\t####  Starting ADD - Immediate Mode test  ####\n");

    /* Initialize computer */
    Computer comp;
    COMP_Init(&comp);

    /* Create desired instructions */
    BitString addInstrComplete; // R1 <-- R0 + b
    BitString addInstr;         // R1 <-- R0 + imm5
    BitString imm5BS;           // 5 bit 2's comp binary number
    BSTR_SetValueTwosComp(&imm5BS, b, 5);
    BSTR_SetBits(&addInstr, "00010010001"); // ADD Dest: R1, Src1: R0 Imm5: b
    BSTR_Append(&addInstrComplete, addInstr, imm5BS);

    /* Load desired instructions */
    COMP_LoadWord(&comp, 0, addInstrComplete);

    /* Setup R0 with the given value of a */
    BSTR_SetValueTwosComp(&(comp.reg[0]), a, 16); // R0 <-- a

    /* Display initialized computer and loaded instructions */
    printf("\t####  Displaying computers initial state  ####\n");
    COMP_Display(comp);

    /* Execute all loaded instructions */
    COMP_Execute(&comp);

    /* Display state of computer after execution */
    printf("\n\n\t####  Displaying computers state after execution ####\n");
    COMP_Display(comp);

    printf("\n\t\t####  Finished ADD - Immediate Mode test  ####\n\n");
    printf("Verify R1 <-- R0 + b)\n");
    printf("Verify R1 <-- %d + %d)\n", a, b);
    printf("R1 Value = %d\n", BSTR_GetValueTwosComp(comp.reg[1]));
    printf("Verify CC n,z,p for the given stored result\n");
}


/***
 * Tests the load instruction
 * given a destination register and a 9bit signed PCoffset
 *
 * @param a 3 bit int in the range of 1-7 representing the Destination
 * @param b 9 bit int representing the memory address to fetch the data to be loaded.
 */
void testLdMode(int a, int b) {
    printf("\n\n\t\t####  Starting LD test  ####\n");

    /* Initialize computer */
    Computer comp;
    COMP_Init(&comp);

    /* Create desired instruction set */
    BitString ldInstr;
    BSTR_SetBits(&ldInstr, "0001");         // LD Dest: R0
    /* Create a bitstring for the desired storage address */
    BitString address;
    BSTR_SetValue(&address, a, 3);
    /* Create the offset from b */
    BitString pcOffset;                     // 9 bit 2's comp binary number
    BSTR_SetValueTwosComp(&pcOffset, b, 9);
    /* Create the full instruction needed for LD operation */
    BitString ldInstrComplete;              // a <-- M[PC + PCoffset9]
    BSTR_Append(&ldInstrComplete, ldInstr, address);
    BSTR_Append(&ldInstrComplete, ldInstrComplete, pcOffset);

    BSTR_Display(ldInstrComplete, 0);

    /* Load desired instruction */
    COMP_LoadWord(&comp, 0, ldInstrComplete);

    /* Load some interesting things in the following 10 registers */
    int i;
    for (i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            BSTR_SetValueTwosComp(&(comp.mem[i]), i, 16);
        } else {
            BSTR_SetValueTwosComp(&(comp.mem[i]), i * -1, 16);
        }
    }

    /* Display initialized computer and loaded instructions */
    printf("\t####  Displaying computers initial state  ####\n");
    COMP_Display(comp);

    /* Execute all loaded instructions */
    COMP_Execute(&comp);

    /* Display state of computer after execution */
    printf("\n\n\t####  Displaying computers state after execution ####\n");
    COMP_Display(comp);

    printf("\n\t\t####  Finished LD test  ####\n\n");
    printf("Verify Ra <-- PC + b)\n");
    printf("Verify R%d <-- ", a); //%d + %d)\n", b);
    printf("1 + %d\n", b);
}

void testOutput() {
    printf("Testing Output Operation\n");
    int a = 5, b = 7;

    /* Initialize computer */
    Computer comp;
    COMP_Init(&comp);

    /* Create desired instructions */
    BitString addInstrComplete; // R1 <-- R0 + b
    BitString addInstr;         // R1 <-- R0 + imm5
    BitString imm5BS;           // 5 bit 2's comp binary number
    BitString haltInstr;
    BitString outputInstr;
    BSTR_SetValueTwosComp(&imm5BS, b, 5);

    BSTR_SetBits(&addInstr, "00010010001"); // ADD Dest: R1, Src1: R0 Imm5: b
    BSTR_Append(&addInstrComplete, addInstr, imm5BS);

    COMP_LoadWord(&comp, 0, addInstrComplete);

    BSTR_SetBits(&outputInstr, "1111000000100001");
    COMP_LoadWord(&comp, 1, outputInstr);

    BSTR_SetBits(&haltInstr, "1111000000100101");
    COMP_LoadWord(&comp, 2, haltInstr);

    /* Setup R0 with the given value of a */
    BSTR_SetValueTwosComp(&(comp.reg[0]), a, 16); // R0 <-- a

    /* Execute all loaded instructions */
    COMP_Execute(&comp);

    printf("Finished output test\n");
}

void testHalt() {

    printf("Testing Halt Operation\n");
    int a = 5, b = 7;

    /* Initialize computer */
    Computer comp;
    COMP_Init(&comp);

    /* Create desired instructions */
    BitString addInstrComplete; // R1 <-- R0 + b
    BitString addInstr;         // R1 <-- R0 + imm5
    BitString imm5BS;           // 5 bit 2's comp binary number
    BitString haltInstr;
    BitString outputInstr;
    BSTR_SetValueTwosComp(&imm5BS, b, 5);

    BSTR_SetBits(&haltInstr, "1111000000100101");
    COMP_LoadWord(&comp, 0, haltInstr);

    BSTR_SetBits(&addInstr, "00010010001"); // ADD Dest: R1, Src1: R0 Imm5: b
    BSTR_Append(&addInstrComplete, addInstr, imm5BS);

    COMP_LoadWord(&comp, 1, addInstrComplete);

    BSTR_SetBits(&outputInstr, "1111000000100001");
    COMP_LoadWord(&comp, 2, outputInstr);


    /* Setup R0 with the given value of a */
    BSTR_SetValueTwosComp(&(comp.reg[0]), a, 16); // R0 <-- a

    /* Display initialized computer and loaded instructions */
    printf("\t####  Displaying computers initial state  ####\n");
    COMP_Display(comp);

    /* Execute all loaded instructions */
    COMP_Execute(&comp);

    /* Display state of computer after execution */
    printf("\n\n\t####  Displaying computers state after execution ####\n");
    COMP_Display(comp);

    printf("\n\t\t####  Finished Halt Before Add test. Should be no output or addition occurring.  ####\n\n");
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
    int i;
    for (i = 0; i < programSize; i++) {
        BSTR_SetBits(&instruction, program[i]);
        COMP_LoadWord(&comp, i, instruction);
    }

    //execute the program
    COMP_Execute(&comp);
    //shows final configuration
    COMP_Display(comp);

    /* Tests the NOT instruction */
    //    testNot();

    /* Test halt operation, prevent program from outputting...*/
    //    testHalt();

    /* Test output operation */
    //    testOutput();

    /* Test the ADD instruction in Register mode with two positive numbers */
//    testAddRegisterMode(5, 5);

    /* Test the ADD instruction in Register mode with two negative numbers */
//    testAddRegisterMode(-5, -5);

    /* Test the ADD instruction in Register mode with a negative and positive number
     * result is negative  */
//    testAddRegisterMode(-5, 2);

    /* Test the ADD instruction in Register mode with a negative and positive number
     * result is positive  */
//    testAddRegisterMode(-5, 10);

    /* Test the ADD instruction in Register mode with a negative and positive number
     * result is zero  */
//    testAddRegisterMode(-5, 5);

    /* Test the ADD instruction in Immediate mode with two positive numbers */
//    testAddImmediateMode(5, 5);

    /* Test the ADD instruction in Immediate mode with two negative numbers */
//    testAddImmediateMode(-5, -5);

    /* Test the ADD instruction in Immediate mode with a negative and positive number
     * result is negative  */
//    testAddImmediateMode(-5, 2);

    /* Test the ADD instruction in Immediate mode with a negative and positive number
     * result is positive  */
//    testAddImmediateMode(-5, 10);

    /* Test the ADD instruction in Immediate mode with a negative and positive number
     * result is zero  */
//    testAddImmediateMode(-5, 5);


//    testLdMode(1, 6);

//     bitStringTest();

}