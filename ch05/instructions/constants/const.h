//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_CONST_H
#define JVMC_CONST_H
#include "../base/instruction.h"
typedef struct {
    NoOperandsInstruction* base;
} ACONST_NULL;
void excute_aconst_null(void * self,Frame *frame);

typedef struct {
    NoOperandsInstruction* base;
} DCONST_0;
void excute_dconst_0(void * self,Frame *frame);

typedef struct {
    NoOperandsInstruction* base;
} DCONST_1;
void excute_dconst_1(void * self,Frame *frame);

typedef struct {
    NoOperandsInstruction* base;
} FCONST_0;
void excute_fconst_0(void * self,Frame *frame);

typedef struct {
    NoOperandsInstruction* base;
} FCONST_1;
void excute_fconst_1(void * self,Frame *frame);

typedef struct {
    NoOperandsInstruction* base;
} FCONST_2;
void excute_fconst_2(void * self,Frame *frame);

typedef struct {
    NoOperandsInstruction* base;
} ICONST_M1;
void excute_iconst_m1(void * self,Frame *frame);

typedef struct {
    NoOperandsInstruction* base;
} ICONST_0;
void excute_iconst_0(void * self,Frame *frame);

typedef struct {
    NoOperandsInstruction* base;
} ICONST_1;
void excute_iconst_1(void * self,Frame *frame);

typedef struct {
    NoOperandsInstruction* base;
} ICONST_2;
void excute_iconst_2(void * self,Frame *frame);

typedef struct {
    NoOperandsInstruction* base;
} ICONST_3;
void excute_iconst_3(void * self,Frame *frame);

typedef struct {
    NoOperandsInstruction* base;
} ICONST_4;
void excute_iconst_4(void * self,Frame *frame);

typedef struct {
    NoOperandsInstruction* base;
} ICONST_5;
void excute_iconst_5(void * self,Frame *frame);

typedef struct {
    NoOperandsInstruction* base;
} LCONST_0;
void excute_lconst_0(void * self,Frame *frame);

typedef struct {
    NoOperandsInstruction* base;
} LCONST_1;
void excute_lconst_1(void * self,Frame *frame);

void init_ACONST_NULL(ACONST_NULL * self);
void init_DCONST_0(DCONST_0 * self);
void init_DCONST_1(DCONST_1 * self);
void init_FCONST_0(FCONST_0 * self);
void init_FCONST_1(FCONST_1 * self);
void init_FCONST_2(FCONST_2 * self);
void init_ICONST_M1(ICONST_M1 * self);
void init_ICONST_0(ICONST_0 * self);
void init_ICONST_1(ICONST_1 * self);
void init_ICONST_2(ICONST_2 * self);
void init_ICONST_3(ICONST_3 * self);
void init_ICONST_4(ICONST_4 * self);
void init_ICONST_5(ICONST_5 * self);
void init_LCONST_0(LCONST_0 * self);
void init_LCONST_1(LCONST_1 * self);

#endif //JVMC_CONST_H
