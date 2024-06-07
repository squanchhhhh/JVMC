//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_IPUSH_H
#define JVMC_IPUSH_H
#include "../base/instruction.h"
typedef struct{
    Instruction base;
    int8_t val;
}BIPUSH;
void init_BIPUSH(BIPUSH*self);
void fetch_bipush(void *bipush,BytecodeReader * reader);
void excute_bipush(void *bipush,Frame * frame);
typedef struct{
    Instruction base;
    int16_t val;
}SIPUSH;
void init_SIPUSH(SIPUSH*self);
void fetch_sipush(void *sipush,BytecodeReader * reader);
void excute_sipush(void *sipush,Frame * frame);
#endif //JVMC_IPUSH_H
