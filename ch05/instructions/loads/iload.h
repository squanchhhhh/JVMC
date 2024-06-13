//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_ILOAD_H
#define JVMC_ILOAD_H
#include "../base/instruction.h"
// todo other loads
typedef struct {
    Index8Instruction base;
}ILOAD;
typedef struct {
    NoOperandsInstruction base;
}ILOAD_0;
typedef struct {
    NoOperandsInstruction base;
}ILOAD_1;
typedef struct {
    NoOperandsInstruction base;
}ILOAD_2;
typedef struct {
    NoOperandsInstruction base;
}ILOAD_3;
void excute_iload(void * self,Frame *frame);
void excute_iload_0(void * self,Frame *frame);
void excute_iload_1(void * self,Frame *frame);
void excute_iload_2(void * self,Frame *frame);
void excute_iload_3(void * self,Frame *frame);
void init_ILOAD(ILOAD*self);
void init_ILOAD_0(ILOAD_0*self);
void init_ILOAD_1(ILOAD_1*self);
void init_ILOAD_2(ILOAD_2*self);
void init_ILOAD_3(ILOAD_3*self);
void _iload(Frame*frame,int index);

typedef struct{
    Index8Instruction base;
}FLOAD;
typedef struct{
    NoOperandsInstruction base;
}FLOAD_0;
typedef struct{
    NoOperandsInstruction base;
}FLOAD_1;
typedef struct{
    NoOperandsInstruction base;
}FLOAD_2;
typedef struct{
    NoOperandsInstruction base;
}FLOAD_3;
void excute_fload(void * self,Frame *frame);
void excute_fload_0(void * self,Frame *frame);
void excute_fload_1(void * self,Frame *frame);
void excute_fload_2(void * self,Frame *frame);
void excute_fload_3(void * self,Frame *frame);

void init_FLOAD(FLOAD*self);
void init_FLOAD_0(FLOAD_0*self);
void init_FLOAD_1(FLOAD_1*self);
void init_FLOAD_2(FLOAD_2*self);
void init_FLOAD_3(FLOAD_3*self);
void _fload(Frame*frame,int index);


typedef struct{
    Index8Instruction base;
}DLOAD;
typedef struct{
    NoOperandsInstruction base;
}DLOAD_0;
typedef struct{
    NoOperandsInstruction base;
}DLOAD_1;
typedef struct{
    NoOperandsInstruction base;
}DLOAD_2;
typedef struct{
    NoOperandsInstruction base;
}DLOAD_3;
void excute_dload(void * self,Frame *frame);
void excute_dload_0(void * self,Frame *frame);
void excute_dload_1(void * self,Frame *frame);
void excute_dload_2(void * self,Frame *frame);
void excute_dload_3(void * self,Frame *frame);

void init_DLOAD(DLOAD*self);
void init_DLOAD_0(DLOAD_0*self);
void init_DLOAD_1(DLOAD_1*self);
void init_DLOAD_2(DLOAD_2*self);
void init_DLOAD_3(DLOAD_3*self);
void _dload(Frame*frame,int index);

typedef struct{
    Index8Instruction base;
}ALOAD;
typedef struct{
    NoOperandsInstruction base;
}ALOAD_0;
typedef struct{
    NoOperandsInstruction base;
}ALOAD_1;
typedef struct{
    NoOperandsInstruction base;
}ALOAD_2;
typedef struct{
    NoOperandsInstruction base;
}ALOAD_3;
void excute_aload(void * self,Frame *frame);
void excute_aload_0(void * self,Frame *frame);
void excute_aload_1(void * self,Frame *frame);
void excute_aload_2(void * self,Frame *frame);
void excute_aload_3(void * self,Frame *frame);

void init_ALOAD(ALOAD*self);
void init_ALOAD_0(ALOAD_0*self);
void init_ALOAD_1(ALOAD_1*self);
void init_ALOAD_2(ALOAD_2*self);
void init_ALOAD_3(ALOAD_3*self);
void _aload(Frame*frame,int index);


typedef struct{
    Index8Instruction base;
}LLOAD;
typedef struct{
    NoOperandsInstruction base;
}LLOAD_0;
typedef struct{
    NoOperandsInstruction base;
}LLOAD_1;
typedef struct{
    NoOperandsInstruction base;
}LLOAD_2;
typedef struct{
    NoOperandsInstruction base;
}LLOAD_3;
void excute_lload(void * self,Frame *frame);
void excute_lload_0(void * self,Frame *frame);
void excute_lload_1(void * self,Frame *frame);
void excute_lload_2(void * self,Frame *frame);
void excute_lload_3(void * self,Frame *frame);

void init_LLOAD(LLOAD*self);
void init_LLOAD_0(LLOAD_0*self);
void init_LLOAD_1(LLOAD_1*self);
void init_LLOAD_2(LLOAD_2*self);
void init_LLOAD_3(LLOAD_3*self);
void _lload(Frame*frame,int index);

typedef struct{
    NoOperandsInstruction base;
}AALOAD;
typedef struct {
    NoOperandsInstruction base;
}BALOAD;
typedef struct{
    NoOperandsInstruction base;
}CALOAD;
typedef struct{
    NoOperandsInstruction base;
}DALOAD;
typedef struct{
    NoOperandsInstruction base;
}FALOAD;
typedef struct{
    NoOperandsInstruction base;
}IALOAD;
typedef struct{
    NoOperandsInstruction base;
}LALOAD;
typedef struct{
    NoOperandsInstruction base;
}SALOAD;

void init_AALOAD(AALOAD*self);
void init_BALOAD(BALOAD*self);
void init_CALOAD(CALOAD*self);
void init_DALOAD(DALOAD*self);
void init_FALOAD(FALOAD*self);
void init_IALOAD(IALOAD*self);
void init_LALOAD(LALOAD*self);
void init_SALOAD(SALOAD*self);

void excute_aaload(void * self,Frame *frame);
void excute_baload(void * self,Frame *frame);
void excute_caload(void * self,Frame *frame);
void excute_daload(void * self,Frame *frame);
void excute_faload(void * self,Frame *frame);
void excute_iaload(void * self,Frame *frame);
void excute_laload(void * self,Frame *frame);
void excute_saload(void * self,Frame *frame);


#endif //JVMC_ILOAD_H
