//
// Created by Squanch on 2024/6/8.
//

#ifndef JVMC_NEW_H
#define JVMC_NEW_H

#include "../base/instruction.h"

typedef struct {
    Index16Instruction base;
} NEW;

void init_NEW(NEW *self);

void execute_NEW(void *self, Frame *frame);

typedef struct {
    Index16Instruction base;
} PUT_STATIC;

void init_PUT_STATIC(PUT_STATIC *self);

void execute_PUT_STATIC(void *self, Frame *frame);

typedef struct {
    Index16Instruction base;
} GET_STATIC;

void init_GET_STATIC(GET_STATIC *self);

void execute_GET_STATIC(void *self, Frame *frame);

typedef struct {
    Index16Instruction base;
} PUT_FIELD;

void init_PUT_FIELD(PUT_FIELD *self);

void execute_PUT_FIELD(void *self, Frame *frame);

typedef struct {
    Index16Instruction base;
} GET_FIELD;

void init_GET_FIELD(GET_FIELD *self);

void execute_GET_FIELD(void *self, Frame *frame);

typedef struct {
    Index16Instruction base;
}INSTANCE_OF;

void init_INSTANCE_OF(INSTANCE_OF *self);

void execute_INSTANCE_OF(void *self, Frame *frame);


typedef struct {
    Index16Instruction base;
}CHECK_CAST;

void init_CHECK_CAST(CHECK_CAST *self);

void execute_CHECK_CAST(void *self, Frame *frame);

typedef struct {
    Index16Instruction base;
}INVOKE_SPECIAL;

void init_INVOKE_SPECIAL(INVOKE_SPECIAL *self);

void execute_INVOKE_SPECIAL(void *self, Frame *frame);

typedef struct {
    Index16Instruction base;
}INVOKE_VIRTUAL;

void init_INVOKE_VIRTUAL(INVOKE_VIRTUAL *self);

void execute_INVOKE_VIRTUAL(void *self, Frame *frame);

#endif //JVMC_NEW_H
