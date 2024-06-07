//
// Created by Squanch on 2024/6/3.
//

#include "instruction.h"
void NoOperands_instruction_fetch(){
    //do nothing
}
void NoOperands_instruction_init(NoOperandsInstruction *self){
    self->base = *(Instruction*)malloc(sizeof(Instruction));
    self->base.FetchOperands = NoOperands_instruction_fetch;
}
void Branch_instruction_fetch(void *self,BytecodeReader*reader){
    BranchInstruction* branchInstr = (BranchInstruction*)self;
    branchInstr->offset = (int)read_int16(reader);
}
void Branch_instruction_init(BranchInstruction *self){
    self->base.FetchOperands = Branch_instruction_fetch;
}
void Index8_instruction_fetch(void *self,BytecodeReader *reader){
    Index8Instruction* indexInstr = (Index8Instruction*)self;
    indexInstr->index = (int)read_int8(reader);
}
void Index8_instruction_init(Index8Instruction *self){
    self->base.FetchOperands = Index8_instruction_fetch;
}
void Index16_instruction_fetch(void *self,BytecodeReader *reader){
    Index16Instruction* indexInstr = (Index16Instruction*)self;
    indexInstr->index = (int)read_int16(reader);
}
void Index16_instruction_init(Index16Instruction *self){
    self->base.FetchOperands = Index16_instruction_fetch;
}
void branch(Frame*frame,int offset){
    int pc = frame->thread->pc;
    int next_pc = pc+offset;
    frame->next_pc = next_pc;
}