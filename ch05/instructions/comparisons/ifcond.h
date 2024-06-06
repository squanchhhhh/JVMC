//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_IFCOND_H
#define JVMC_IFCOND_H
#include "../base/instruction.h"
typedef struct{
    BranchInstruction *base;
}IFEQ;
typedef struct{
    BranchInstruction *base;
}IFNE;
typedef struct{
    BranchInstruction *base;
}IFLT;
typedef struct{
    BranchInstruction *base;
}IFLE;
typedef struct{
    BranchInstruction *base;
}IFGT;
typedef struct{
    BranchInstruction *base;
}IFGE;
void init_IFEQ(IFEQ*self);
void init_IFNE(IFNE*self);
void init_IFLT(IFLT*self);
void init_IFLE(IFLE*self);
void init_IFGT(IFGT*self);
void init_IFGE(IFGE*self);
void execute_IFEQ(void * self,Frame*frame);
void execute_IFNE(void * self,Frame*frame);
void execute_IFLT(void * self,Frame*frame);
void execute_IFLE(void * self,Frame*frame);
void execute_IFGT(void * self,Frame*frame);
void execute_IFGE(void * self,Frame*frame);
#endif //JVMC_IFCOND_H
