//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_GOTO_H
#define JVMC_GOTO_H
#include "../base/instruction.h"

typedef struct{
    BranchInstruction base;
}GOTO;
void init_GOTO(GOTO *self);
void execute_GOTO(void * self,Frame*frame);
#endif //JVMC_GOTO_H
