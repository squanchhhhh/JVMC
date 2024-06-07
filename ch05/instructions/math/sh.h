//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_SH_H
#define JVMC_SH_H
#include "../base/instruction.h"
typedef struct{
    NoOperandsInstruction base;
}ISHL;
typedef struct{
    NoOperandsInstruction base;
}ISHR;
typedef struct{
    NoOperandsInstruction base;
}IUSHR;
typedef struct{
    NoOperandsInstruction base;
}LSHL;
typedef struct{
    NoOperandsInstruction base;
}LSHR;
typedef struct{
    NoOperandsInstruction base;
}LUSHR;
void init_ISHL(ISHL*self);
void init_ISHR(ISHR*self);
void init_IUSHR(IUSHR*self);
void init_LSHL(LSHL*self);
void init_LSHR(LSHR*self);
void init_LUSHR(LUSHR*self);
void execute_ISHR(void*self,Frame* frame);
void execute_ISHL(void*self,Frame* frame);
void execute_IUSHR(void*self,Frame* frame);
void execute_LSHR(void*self,Frame* frame);
void execute_LSHL(void*self,Frame* frame);
void execute_LUSHR(void*self,Frame* frame);

#endif //JVMC_SH_H
