//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_SWAP_H
#define JVMC_SWAP_H
#include "../base/instruction.h"
typedef struct{
    NoOperandsInstruction * base;
}SWAP;
void init_SWAP(SWAP * swap);
void excute_SWAP(void * self,Frame*frame);

#endif //JVMC_SWAP_H
