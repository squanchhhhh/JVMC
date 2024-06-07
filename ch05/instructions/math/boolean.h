//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_BOOLEAN_H
#define JVMC_BOOLEAN_H
#include "../base/instruction.h"
typedef struct {
    NoOperandsInstruction base;
}IAND;
typedef struct {
    NoOperandsInstruction base;
}IOR;
typedef struct {
    NoOperandsInstruction base;
}IXOR;
typedef struct {
    NoOperandsInstruction base;
}LAND;
typedef struct {
    NoOperandsInstruction base;
}LOR;
typedef struct {
    NoOperandsInstruction base;
}LXOR;
void init_IAND(IAND * self);
void init_IOR(IOR * self);
void init_IXOR(IXOR * self);
void init_LAND(LAND * self);
void init_LOR(LOR * self);
void init_LXOR(LXOR * self);
void execute_IAND(void*self,Frame*frame);
void execute_IOR(void*self,Frame*frame);
void execute_IXOR(void*self,Frame*frame);
void execute_LAND(void*self,Frame*frame);
void execute_LOR(void*self,Frame*frame);
void execute_LXOR(void*self,Frame*frame);

#endif //JVMC_BOOLEAN_H
