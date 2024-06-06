//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_REM_H
#define JVMC_REM_H
#include "../base/instruction.h"
typedef struct{
    NoOperandsInstruction * base;
}DREM;
typedef struct{
    NoOperandsInstruction * base;
}FREM;
typedef struct{
    NoOperandsInstruction * base;
}IREM;
typedef struct{
    NoOperandsInstruction * base;
}LREM;
void init_DREM(DREM*self);
void init_FREM(FREM*self);
void init_IREM(IREM*self);
void init_LREM(LREM*self);
void excute_DREM(void*self,Frame*frame);
void excute_FREM(void*self,Frame*frame);
void excute_IREM(void*self,Frame*frame);
void excute_LREM(void*self,Frame*frame);
#endif //JVMC_REM_H
