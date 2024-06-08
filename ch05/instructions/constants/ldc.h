//
// Created by Squanch on 2024/6/8.
//

#ifndef JVMC_LDC_H
#define JVMC_LDC_H
#include "../base/instruction.h"
void _ldc(Frame*frame,uint32_t index);
typedef struct{
    Index8Instruction base;
}LDC;
void init_LDC(LDC*self);
void execute_LDC(void *self,Frame* frame);


typedef struct{
    Index16Instruction base;
}LDC_W;
void init_LDC_W(LDC_W*self);
void execute_LDC_W(void *self,Frame* frame);


typedef struct{
    Index16Instruction base;
}LDC2_W;
void init_LDC2_W(LDC2_W*self);
void execute_LDC2_W(void *self,Frame* frame);
#endif //JVMC_LDC_H
