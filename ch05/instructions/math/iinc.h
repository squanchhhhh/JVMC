//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_IINC_H
#define JVMC_IINC_H
#include "../base/instruction.h"
typedef struct{
    NoOperandsInstruction base;
    uint index;
    int increment;
}IINC;
void init_IINC(IINC*self);
void execute_IINC(void * self,Frame* frame);
#endif //JVMC_IINC_H
