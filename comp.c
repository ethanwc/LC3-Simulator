/**
 * TCSS 371 HW $
 * Ethan Cheatham
 */
#include <stdio.h>
#include "bstr.h"
#include "comp.h"

void COMP_Init(Computer *cmp) {
    int r, m;
    BSTR_SetValue(&(cmp->pc),0,16);
    BSTR_SetValue(&(cmp->ir),0,16);
    BSTR_SetValue(&(cmp->cc),0,3);
    for (r = 0; r < 8; r++) {
        BSTR_SetValue(&(cmp->reg[r]),r,16);  /* put some interesting data in registers */
    }
    for (m = 0; m < MAXMEM; m++) {
        BSTR_SetValue(&(cmp->mem[m]),0,16);
    }
}



void COMP_LoadWord(Computer* comp, int addr, BitString word) {
    comp->mem[addr] = word;
}


void COMP_ExecuteNot(Computer *comp) {
    int value;
    BitString drBS, srBS;
    BSTR_Substring(&drBS,comp->ir,4,3);
    BSTR_Substring(&srBS,comp->ir,7,3);
    comp->reg[ BSTR_GetValue(drBS) ] = comp->reg[ BSTR_GetValue(srBS) ];
    BSTR_Invert( & comp->reg[ BSTR_GetValue(drBS)  ]  );
    value = BSTR_GetValueTwosComp(comp->reg[BSTR_GetValue(drBS)]);

    //set value for condition
    if (value > 0) BSTR_SetValue(&(comp->cc), 1, 3);
    if (value < 0) BSTR_SetValue(&(comp->cc), 4, 3);
    if (!value) BSTR_SetValue(&(comp->cc), 2, 3);

}
void COMP_ExecuteAdd(Computer *comp) {
    BitString immediate, drBS, srBS0, srBS1, srBS2;
    int value, sr1Value, status;

    //Access the 'immediate' part of instruction
    BSTR_Substring(&immediate, comp->ir, 10, 1);

    value = BSTR_GetValue(immediate);

    BSTR_Substring(&drBS, comp->ir, 4, 3);  // Fetch the destination register index
    BSTR_Substring(&srBS1, comp->ir, 7, 3); // Fetch the SR1 register index
    sr1Value = BSTR_GetValueTwosComp(comp->reg[BSTR_GetValue(srBS1)]); // Fetch the SR1 register value

    //if immediate mode
    if (value) {
        BSTR_Substring(&srBS2, comp->ir, 11, 5);
        int immediate = BSTR_GetValueTwosComp(srBS2);
        //adds register and immediate value
        BSTR_SetValueTwosComp(&comp->reg[BSTR_GetValue(drBS)], sr1Value + immediate, 16);
        //not immediate
    } else {
        BSTR_Substring(&srBS2, comp->ir, 13, 3); // Fetch the SR2 register index
        //add two registers
        int sr2Value = BSTR_GetValueTwosComp(comp->reg[BSTR_GetValue(srBS2)]);// Fetch the SR2 register value
        BSTR_SetValueTwosComp(&comp->reg[BSTR_GetValue(drBS)], sr1Value + sr2Value, 16);
    }

    //get the 'operator value'
//    status = BSTR_GetValue(comp->reg[BSTR_GetValue(drBS)]);

//    if (status > 0) BSTR_SetValue(&(comp->cc), 1, 3);
//    if (status < 0) BSTR_SetValue(&(comp->cc), 4, 3);
//    if (!status) BSTR_SetValue(&(comp->cc), 2, 3);

    /* Update the CC flag */
    COMP_ExecuteSetCC(comp, comp->reg[ BSTR_GetValue(drBS)]);
}

void COMP_ExecuteLoad(Computer *comp) {
    BitString drBS, pc;
    int offset, status;

    BSTR_Substring(&pc, comp->ir, 7, 9);
    BSTR_Substring(&drBS, comp->ir, 4, 3);
    //determine offset 'location' in memory of where to operate.
    offset = BSTR_GetValueTwosComp(pc) + BSTR_GetValue(comp->pc);
    //load into register
    BSTR_SetValue(&(comp->reg[BSTR_GetValue(drBS)]), BSTR_GetValueTwosComp(comp->mem[offset]), 16);


    status = BSTR_GetValueTwosComp(comp->reg[BSTR_GetValue(drBS)]);

    if (status > 0) BSTR_SetValue(&(comp->cc), 1, 3);
    if (status < 0) BSTR_SetValue(&(comp->cc), 4, 3);
    if (!status) BSTR_SetValue(&(comp->cc), 2, 3);

}

void COMP_ExecuteTrap(Computer *comp, int* isRunning) {
    BitString trap;
    int id;
    //get trap op code 'id'
    BSTR_Substring(&trap, comp->ir, 8, 8);
    id = BSTR_GetValue(trap);

    if (id == 33) printf("%c\n", BSTR_GetValue(comp->reg[0])); // OUTPUT
    if (id == 37) *isRunning = 0; // HALT
}

void COMP_Execute(Computer* comp) {
    BitString opCode;
    //start off running
    int opCodeInt, isRunning = 1, *run = &isRunning;

    //only 50 memory locations pre defined, program not halted
    while (isRunning && BSTR_GetValue(comp->pc) < 50) {

        /* use the PC to load current instruction from memory into IR */
        comp->ir = comp->mem[BSTR_GetValue(comp->pc)];

        BSTR_AddOne(&comp->pc);

        BSTR_Substring(&opCode, comp->ir, 0, 4);  /* isolate op code */
        opCodeInt = BSTR_GetValue(opCode); /* get its value */

        if (opCodeInt == 9) COMP_ExecuteNot(comp); //NOT
        if (opCodeInt == 0) COMP_ExecuteBranch(comp); //BRANCH
        if (opCodeInt == 1) COMP_ExecuteAdd(comp); //ADD
        if (opCodeInt == 2) COMP_ExecuteLoad(comp); //LOAD
        if (opCodeInt == 15) COMP_ExecuteTrap(comp, run); //TRAP (output/halt)
    }
}


void COMP_ExecuteBranch(Computer *comp) {
    BitString cond, state, pc;
    int offset, state_int, condition;

    //break apart instruction
    BSTR_Substring(&pc,comp->ir,7,9);
    BSTR_Substring(&state,comp->ir,4,3);
    BSTR_Substring(&cond,comp->cc,0,3);

    //determine jump offset
    offset = BSTR_GetValueTwosComp(pc) + BSTR_GetValue(comp->pc);
    condition = BSTR_GetValue(cond);
    state_int = BSTR_GetValue(state);

    //sets pc based on offset from branch (if conditions met)
    if ((condition & state_int)) BSTR_SetValue(&comp->pc, offset, 16);
}



void COMP_Display(Computer cmp) {
    int r, m;
    printf("\n");

    printf("PC ");
    BSTR_Display(cmp.pc,1);
    printf("   ");


    printf("IR ");
    BSTR_Display(cmp.ir,1);
    printf("   ");


    printf("CC ");
    BSTR_Display(cmp.cc,1);
    printf("\n");


    for (r = 0; r < 8; r++) {
        printf("R%d ",r);
        BSTR_Display(cmp.reg[r], 1);
        if (r % 3 == 2)
            printf("\n");
        else
            printf("   ");
    }
    printf("\n");
    for (m = 0; m < MAXMEM; m++) {
        printf("%3d ",m);
        BSTR_Display(cmp.mem[m], 1);

        if (m % 3 == 2)
            printf("\n");
        else
            printf("    ");
    }
    printf("\n");
}

void COMP_ExecuteSetCC(Computer *comp, BitString bs) {

    int result = BSTR_GetValueTwosComp(bs);

    if (result < 0) {
        BSTR_SetValue(&(comp->cc),4,3);
    } /* If resulting bitstring is negative set CC <- 100 */
    else if (result > 0) {
        BSTR_SetValue(&(comp->cc),1,3);
    } /* If resulting bitstring is positive set CC <- 001 */
    else {
        BSTR_SetValue(&(comp->cc),2,3);
    } /* If resulting bitstring is zero set CC <- 010 */
}

