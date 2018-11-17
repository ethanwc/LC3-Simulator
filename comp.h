#ifndef COMP
#define COMP

#include "bstr.h"

#define MAXMEM 50

struct compType {
    BitString reg[8];
    BitString mem[MAXMEM];
    BitString pc;
    BitString ir;
    BitString cc;  /* condition code */
};

typedef struct compType Computer;

/* initialized the computer  */
void COMP_Init(Computer*);

/* displays its current contents - register and memory */
void COMP_Display(Computer);

/* put a word (either data or instruction) into the computer's */
/* memory at address addr */
void COMP_LoadWord(Computer* comp, int addr, BitString word);

/* execute the computer's stored program */
/* starting at PC = 0 */
/* and until the program executes a HALT */
void COMP_Execute(Computer* comp);

/* Performs Not operation */
void COMP_ExecuteNot(Computer *comp);

/* Performs Add operation */
void COMP_ExecuteAdd(Computer *comp);

/* Performs BR operation */
void COMP_ExecuteBranch(Computer *comp);

/* Performs LD operation */
void COMP_ExecuteLoad(Computer *comp);

void COMP_ExecuteTrap(Computer *comp, int* running);

/* Performs Set Condition Code operation */
/* Sets condition code based on the given bit strings value
   interpreted as 2's complement being n, z, or p */
void COMP_ExecuteSetCC(Computer *comp, BitString bs);

#endif

