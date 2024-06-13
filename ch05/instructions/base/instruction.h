//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_INSTRUCTION_H
#define JVMC_INSTRUCTION_H

#include "../../rtda/thread.h"
#include "../../rtda/heap/string_pool.h"
#include "../../rtda/heap/object.h"
#include "bytecode_reader.h"

typedef struct Frame Frame;
typedef struct BranchInstruction BranchInstruction;
typedef struct Index8Instruction Index8Instruction;
typedef struct NoOperandsInstruction NoOperandsInstruction;
typedef struct Index16Instruction Index16Instruction;
typedef struct Instruction Instruction;
typedef struct NOP NOP;
void branch(Frame*frame,int offset);
// 定义接口
struct Instruction {
    void (*FetchOperands)(void* self,BytecodeReader *reader);
    void (*Execute)(void * self,Frame *frame);
};

struct NoOperandsInstruction{
    Instruction base;
};
void NoOperands_instruction_init(NoOperandsInstruction * self);
void NoOperands_instruction_fetch();


struct BranchInstruction{
    Instruction base;
    int offset;
};
void Branch_instruction_init(BranchInstruction *self);
void Branch_instruction_fetch(void *self,BytecodeReader *reader);

struct Index8Instruction{
    Instruction base;
    int index;
};
void Index8_instruction_init(Index8Instruction *self);
void Index8_instruction_fetch(void *self,BytecodeReader *reader);

struct Index16Instruction{
    Instruction base;
    int index;
};
void Index16_instruction_init(Index16Instruction *self);
void Index16_instruction_fetch(void *self,BytecodeReader *reader);

struct NOP {
    NoOperandsInstruction *base;
};
void init_NOP(NoOperandsInstruction * self);
void fetch_NOP(void * self,BytecodeReader *reader);
void execute_NOP(void * self,Frame*frame);


void invoke_method(Frame*frame,RtMethods*methods);
void init_class(Thread *thread,Class* class);
void schedule_clinit(Thread*thread,Class*class);
void init_super_class(Thread*thread,Class*class);
Class * arr_class(Class * class);
Class* ComponentClass(Class *self);;
#endif //JVMC_INSTRUCTION_H
