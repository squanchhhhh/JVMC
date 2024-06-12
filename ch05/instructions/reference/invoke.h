//
// Created by Squanch on 2024/6/12.
//

#ifndef JVMC_INVOKE_METHOD_H
#define JVMC_INVOKE_H
#include "../base/instruction.h"
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

typedef struct {
    Index16Instruction base;
}INVOKE_STATIC;

void init_INVOKE_STATIC(INVOKE_STATIC *self);

void execute_INVOKE_STATIC(void *self, Frame *frame);

typedef struct {
    Instruction base;
    uint index;
}INVOKE_INTERFACE;

void init_INVOKE_INTERFACE(INVOKE_INTERFACE *self);
void fetch_INVOKE_INTERFACE(void * self,BytecodeReader*reader);
void execute_INVOKE_INTERFACE(void *self, Frame *frame);
#endif //JVMC_INVOKE_METHOD_H
