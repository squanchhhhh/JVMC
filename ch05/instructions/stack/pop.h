//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_POP_H
#define JVMC_POP_H
#include "../base/instruction.h"
typedef struct{
    NoOperandsInstruction base;
}POP;
typedef struct{
    NoOperandsInstruction base;
}POP2;
void init_POP(POP*self);
void init_POP2(POP2*self);
void excute_POP(void * self,Frame*frame);
void excute_POP2(void * self,Frame*frame);
#endif //JVMC_POP_H
