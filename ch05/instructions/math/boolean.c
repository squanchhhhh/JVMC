//
// Created by Squanch on 2024/6/3.
//

#include "boolean.h"
void init_IAND(IAND * self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute=execute_IAND;
}
void init_IOR(IOR * self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute=execute_IOR;
}
void init_IXOR(IXOR * self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute=execute_IXOR;
}
void init_LAND(LAND * self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute=execute_LAND;
}
void init_LOR(LOR * self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute=execute_LOR;
}
void init_LXOR(LXOR * self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute=execute_LXOR;
}
void execute_IAND(void*self,Frame*frame){
    int v2 = pop_int(frame->operand_stack);
    int v1 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack,v1&v2);
}
void execute_IOR(void*self,Frame*frame){
    int v2 = pop_int(frame->operand_stack);
    int v1 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack,v1|v2);
}
void execute_IXOR(void*self,Frame*frame){
    int v2 = pop_int(frame->operand_stack);
    int v1 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack,v1^v2);
}
void execute_LAND(void*self,Frame*frame){
    long v2 = pop_long(frame->operand_stack);
    long v1 = pop_long(frame->operand_stack);
    push_long(frame->operand_stack,v1&v2);
}
void execute_LOR(void*self,Frame*frame){
    long v2 = pop_long(frame->operand_stack);
    long v1 = pop_long(frame->operand_stack);
    push_long(frame->operand_stack,v1|v2);
}
void execute_LXOR(void*self,Frame*frame){
    long v2 = pop_long(frame->operand_stack);
    long v1 = pop_long(frame->operand_stack);
    push_long(frame->operand_stack,v1^v2);
}

