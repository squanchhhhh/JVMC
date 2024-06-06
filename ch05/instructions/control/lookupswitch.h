//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_LOOKUPSWITCH_H
#define JVMC_LOOKUPSWITCH_H
#include "../base/instruction.h"
typedef struct{
    Instruction *base;
    int32_t default_offset;
    int32_t npairs;
    int32_t* match;
}LOOKUP_SWITCH;
void init_LOOKUP_SWITCH(LOOKUP_SWITCH*self);
void fetch_LOOKUP_SWITCH(void* self,BytecodeReader*reader);
void execute_LOOKUP_SWITCH(void* self,Frame*frame);
#endif //JVMC_LOOKUPSWITCH_H
