//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_IFNULL_H
#define JVMC_IFNULL_H
//todo ifnull
#include "../base/instruction.h"
typedef struct{
    BranchInstruction * base;
}IFNULL;
typedef struct{
    BranchInstruction * base;
}IFNONNULL;
typedef struct{
    Instruction * base;
    int32_t offset;
}GOTO_W;
#endif //JVMC_IFNULL_H
