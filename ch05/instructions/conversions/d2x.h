//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_D2X_H
#define JVMC_D2X_H
#include "../base/instruction.h"
typedef struct{
    NoOperandsInstruction *base;
}D2F;
typedef struct{
    NoOperandsInstruction *base;
}D2I;
typedef struct{
    NoOperandsInstruction *base;
}D2L;
typedef struct{
    NoOperandsInstruction *base;
}F2D;
typedef struct{
    NoOperandsInstruction *base;
}F2I;
typedef struct{
    NoOperandsInstruction *base;
}F2L;
void init_D2F(D2F *self);
void init_D2I(D2I *self);
void init_D2L(D2L *self);
void init_F2D(F2D *self);
void init_F2I(F2I *self);
void init_F2L(F2L *self);
void execute_D2F(void * self,Frame*frame);
void execute_D2I(void * self,Frame*frame);
void execute_D2L(void * self,Frame*frame);
void execute_F2D(void * self,Frame*frame);
void execute_F2I(void * self,Frame*frame);
void execute_F2L(void * self,Frame*frame);

#endif //JVMC_D2X_H
