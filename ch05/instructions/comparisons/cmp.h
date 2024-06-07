//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_CMP_H
#define JVMC_CMP_H
#include "../base/instruction.h"
typedef struct{
    NoOperandsInstruction base;
}LCMP;
typedef struct{
    NoOperandsInstruction base;
}FCMPG;
typedef struct{
    NoOperandsInstruction base;
}FCMPL;
typedef struct{
    NoOperandsInstruction base;
}DCMPL;
typedef struct{
    NoOperandsInstruction base;
}DCMPG;
void init_LCMP(LCMP*self);
void init_FCMPG(FCMPG*self);
void init_FCMPL(FCMPL*self);
void init_DCMPL(DCMPL*self);
void init_DCMPG(DCMPG*self);
void _FCMP(Frame*frame,int flag);
void execute_LCMP(void*self,Frame*frame);
void execute_FCMPG(void*self,Frame*frame);
void execute_FCMPL(void*self,Frame*frame);
void execute_DCMPL(void*self,Frame*frame);
void execute_DCMPG(void*self,Frame*frame);
#endif //JVMC_CMP_H
