//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_TABLESWITCH_H
#define JVMC_TABLESWITCH_H
#include "../base/instruction.h"
typedef struct{
    Instruction *base;
    int default_offset;
    int low;
    int high;
    int* offsets;
}TABLE_SWITCH;
void init_TABLE_SWITCH(TABLE_SWITCH*self);
void fetch_TABLE_SWITCH(void *self,BytecodeReader *reader);
void execute_TABLE_SWITCH(void *self,Frame*frame);
#endif //JVMC_TABLESWITCH_H
