//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_WIDE_H
#define JVMC_WIDE_H
//todo wide
#include "../base/instruction.h"
typedef struct{
    Instruction * base;
}WIDE;
void init_WIDE(WIDE*self);
void execute_WIDE(void*self,Frame*frame);
#endif //JVMC_WIDE_H
