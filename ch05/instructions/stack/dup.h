//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_DUP_H
#define JVMC_DUP_H
#include "../base/instruction.h"
typedef struct {
    NoOperandsInstruction *base;
}DUP;
typedef struct {
    NoOperandsInstruction *base;
}DUP_X1;
typedef struct {
    NoOperandsInstruction *base;
}DUP_X2;
typedef struct {
    NoOperandsInstruction *base;
}DUP2;
typedef struct {
    NoOperandsInstruction *base;
}DUP2_X1;
typedef struct {
    NoOperandsInstruction *base;
}DUP2_X2;

void init_DUP(DUP*self);
void init_DUP_X1(DUP_X1*self);
void init_DUP_X2(DUP_X2*self);
void init_DUP2(DUP2*self);
void init_DUP2_X1(DUP2_X1*self);
void init_DUP2_X2(DUP2_X2*self);
void excute_DUP(void*self,Frame*frame);
void excute_DUP_X1(void*self,Frame*frame);
void excute_DUP_X2(void*self,Frame*frame);
void excute_DUP2(void*self,Frame*frame);
void excute_DUP2_X1(void*self,Frame*frame);
void excute_DUP2_X2(void*self,Frame*frame);

#endif //JVMC_DUP_H
