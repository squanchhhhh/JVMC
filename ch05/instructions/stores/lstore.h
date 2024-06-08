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

typedef struct{
    Index8Instruction base;
}ISTORE;
typedef struct{
    NoOperandsInstruction base;
}ISTORE_0;
typedef struct{
    NoOperandsInstruction base;
}ISTORE_1;
typedef struct{
    NoOperandsInstruction base;
}ISTORE_2;
typedef struct{
    NoOperandsInstruction base;
}ISTORE_3;
void _istore(Frame*frame,int index);
void excute_istore(void* self,Frame*frame);
void excute_istore_0(void* self,Frame*frame);
void excute_istore_1(void* self,Frame*frame);
void excute_istore_2(void* self,Frame*frame);
void excute_istore_3(void* self,Frame*frame);
void init_ISTORE(ISTORE* self);
void init_ISTORE_0(ISTORE_0* self);
void init_ISTORE_1(ISTORE_1* self);
void init_ISTORE_2(ISTORE_2* self);
void init_ISTORE_3(ISTORE_3* self);

void _astore(Frame*frame,int index);
typedef struct{
    Index8Instruction base;
}ASTORE;
void excute_astore(void* self,Frame*frame);
void init_ASTORE(ASTORE* self);


typedef struct{
    NoOperandsInstruction base;
}ASTORE_0;
void excute_astore_0(void* self,Frame*frame);
void init_ASTORE_0(ASTORE_0* self);
typedef struct{
    NoOperandsInstruction base;
}ASTORE_1;
void excute_astore_1(void* self,Frame*frame);
void init_ASTORE_1(ASTORE_1* self);

typedef struct{
    NoOperandsInstruction base;
}ASTORE_2;
void excute_astore_2(void* self,Frame*frame);
void init_ASTORE_2(ASTORE_2* self);


typedef struct{
    NoOperandsInstruction base;
}ASTORE_3;
void excute_astore_3(void* self,Frame*frame);
void init_ASTORE_3(ASTORE_3* self);

typedef struct{
    NoOperandsInstruction base;
}DSTORE;
void excute_dstore(void* self,Frame*frame);
void init_DSTORE(DSTORE* self);

typedef struct{
    NoOperandsInstruction base;
}FSTORE;
void excute_fstore(void* self,Frame*frame);
void init_FSTORE(FSTORE* self);




#endif //JVMC_LSTORE_H
