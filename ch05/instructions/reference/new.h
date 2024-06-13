//
// Created by Squanch on 2024/6/8.
//

#ifndef JVMC_NEW_H
#define JVMC_NEW_H

#include "../base/instruction.h"

#define AT_BOOLEAN  4
#define AT_CHAR     5
#define AT_FLOAT    6
#define AT_DOUBLE   7
#define AT_BYTE     8
#define AT_SHORT    9
#define AT_INT      10
#define AT_LONG     11
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
} INSTANCE_OF;

void init_INSTANCE_OF(INSTANCE_OF *self);

void execute_INSTANCE_OF(void *self, Frame *frame);


typedef struct {
    Index16Instruction base;
} CHECK_CAST;

void init_CHECK_CAST(CHECK_CAST *self);

void execute_CHECK_CAST(void *self, Frame *frame);


typedef struct {
    Instruction base;
    uint8_t atype;
} NEW_ARRAY;

void init_NEW_ARRAY(NEW_ARRAY *self);

Class *get_primitive_array_class(ClassLoader *loader, uint8_t atype);

void execute_NEW_ARRAY(void *self, Frame *frame);

void fetch_NEW_ARRAY(void *self, BytecodeReader *reader);

typedef struct {
    Index16Instruction base;
} ANEW_ARRAY;

void init_ANEW_ARRAY(ANEW_ARRAY *self);

void execute_ANEW_ARRAY(void *self, Frame *frame);


typedef struct {
    NoOperandsInstruction base;
} ARRAY_LENGTH;

void init_ARRAY_LENGTH(ARRAY_LENGTH *self);

void execute_ARRAY_LENGTH(void *self, Frame *frame);


typedef struct {
    Instruction base;
    uint16_t index;
    uint8_t dimensions;
} MULTI_ANEW_ARRAY;

void init_MULTI_ANEW_ARRAY(MULTI_ANEW_ARRAY *self);

void execute_MULTI_ANEW_ARRAY(void *self, Frame *frame);

void fetch_MULTI_ANEW_ARRAY(void *self, BytecodeReader *reader);



#endif //JVMC_NEW_H
