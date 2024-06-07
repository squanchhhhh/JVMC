//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_LSTORE_H
#define JVMC_LSTORE_H
#include "../base/instruction.h"
typedef struct{
    Index8Instruction base;
}  LSTORE;
typedef struct{
    NoOperandsInstruction base;
}  LSTORE_0;
typedef struct{
    NoOperandsInstruction base;
}  LSTORE_1;
typedef struct{
    NoOperandsInstruction base;
}  LSTORE_2;
typedef struct{
    NoOperandsInstruction base;
}  LSTORE_3;
void _lstore(Frame*frame,int index);
void excute_lstore(void* self,Frame*frame);
void excute_lstore_0(void* self,Frame*frame);
void excute_lstore_1(void* self,Frame*frame);
void excute_lstore_2(void* self,Frame*frame);
void excute_lstore_3(void* self,Frame*frame);
void init_LSTORE(LSTORE* self);
void init_LSTORE_0(LSTORE_0* self);
void init_LSTORE_1(LSTORE_1* self);
void init_LSTORE_2(LSTORE_2* self);
void init_LSTORE_3(LSTORE_3* self);

#endif //JVMC_LSTORE_H
