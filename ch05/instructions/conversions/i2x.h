//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_I2X_H
#define JVMC_I2X_H
#include "../base/instruction.h"
typedef struct{
    NoOperandsInstruction base;
}I2L;
typedef struct{
    NoOperandsInstruction base;
}I2F;
typedef struct{
    NoOperandsInstruction base;
}I2D;
typedef struct{
    NoOperandsInstruction base;
}L2I;
typedef struct{
    NoOperandsInstruction base;
}L2F;
typedef struct{
    NoOperandsInstruction base;
}L2D;
typedef struct{
    NoOperandsInstruction base;
}I2B;
typedef struct{
    NoOperandsInstruction base;
}I2C;
typedef struct{
    NoOperandsInstruction base;
}I2S;
void init_I2L(I2L *self);
void init_I2F(I2F *self);
void init_I2D(I2D *self);
void init_L2I(L2I *self);
void init_L2F(L2F *self);
void init_L2D(L2D *self);
void init_I2B(I2B *self);
void init_I2C(I2C *self);
void init_I2S(I2S *self);

void execute_I2L(void*self,Frame*frame);
void execute_I2F(void*self,Frame*frame);
void execute_I2D(void*self,Frame*frame);
void execute_L2I(void*self,Frame*frame);
void execute_L2F(void*self,Frame*frame);
void execute_L2D(void*self,Frame*frame);
void execute_I2B(void*self,Frame*frame);
void execute_I2C(void*self,Frame*frame);
void execute_I2S(void*self,Frame*frame);

#endif //JVMC_I2X_H
