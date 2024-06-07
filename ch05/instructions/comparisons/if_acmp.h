//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_IF_ACMP_H
#define JVMC_IF_ACMP_H
#include "../base/instruction.h"
typedef struct{
    BranchInstruction base;
}IF_ACMPEQ;
typedef struct{
    BranchInstruction base;
}IF_ACMPNE;
void init_IF_ACMPEQ(IF_ACMPEQ * self);
void init_IF_ACMPNE(IF_ACMPNE * self);
void execute_IF_ACMPEQ(void * self,Frame*frame);
void execute_IF_ACMPNE(void * self,Frame* frame);
#endif //JVMC_IF_ACMP_H
