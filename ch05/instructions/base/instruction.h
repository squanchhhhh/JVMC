//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_INSTRUCTION_H
#define JVMC_INSTRUCTION_H

#include "../../rtda/thread.h"
#include "bytecode_reader.h"
void branch(Frame*frame,int offset);
// 定义接口
typedef struct Instruction {
    void (*FetchOperands)(void* self,BytecodeReader *reader);
    void (*Execute)(void * self,Frame *frame);
} Instruction;

typedef struct {
    Instruction base;
}NoOperandsInstruction;
void NoOperands_instruction_init(NoOperandsInstruction * self);
void NoOperands_instruction_fetch();

typedef struct{
    NoOperandsInstruction * base;
}NOP;

typedef struct {
    Instruction base;
    int offset;
}BranchInstruction;
void Branch_instruction_init(BranchInstruction self);
void Branch_instruction_fetch(void *self,BytecodeReader *reader);

typedef struct {
    Instruction base;
    int index;
}Index8Instruction;
void Index8_instruction_init(Index8Instruction self);
void Index8_instruction_fetch(void *self,BytecodeReader *reader);

typedef struct {
    Instruction base;
    int index;
}Index16Instruction;
void Index16_instruction_init(Index16Instruction self);
void Index16_instruction_fetch(void *self,BytecodeReader *reader);



#endif //JVMC_INSTRUCTION_H
