//
// Created by Squanch on 2024/6/3.
//

#include "sh.h"
void init_ISHL(ISHL*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_ISHL;
}
void init_ISHR(ISHR*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_ISHR;
}
void init_IUSHR(IUSHR*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_IUSHR;
}
void init_LSHL(LSHL*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_LSHL;
}
void init_LSHR(LSHR*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_LSHR;
}
void init_LUSHR(LUSHR*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_LUSHR;
}
void execute_ISHR(void*self,Frame* frame){
    int v2 = pop_int(frame->operand_stack);
    int v1 = pop_int(frame->operand_stack);
    int s = v2&0x1f;
    int result = v1>>s;
    push_int(frame->operand_stack,result);
}
void execute_ISHL(void*self,Frame* frame){
    int v2 = pop_int(frame->operand_stack);
    int v1 = pop_int(frame->operand_stack);
    int s = v2&0x1f;
    int result = v1<<s;
    push_int(frame->operand_stack,result);
}
void execute_IUSHR(void*self,Frame* frame){
    int v2 = pop_int(frame->operand_stack);
    int v1 = pop_int(frame->operand_stack);
    int s = v2&0x1f;
    int result = (uint)v1>>s;
    push_int(frame->operand_stack,result);
}
void execute_LSHR(void*self,Frame* frame){
    int v2 = pop_int(frame->operand_stack);
    long v1 = pop_long(frame->operand_stack);
    int s = v2&0x3f;
    long result = v1>>s;
    push_long(frame->operand_stack,result);
}
void execute_LSHL(void*self,Frame* frame){
    int v2 = pop_int(frame->operand_stack);
    long v1 = pop_long(frame->operand_stack);
    int s = v2&0x3f;
    long result = v1<<s;
    push_long(frame->operand_stack,result);
}
void execute_LUSHR(void*self,Frame* frame){
    int v2 = pop_int(frame->operand_stack);
    long v1 = pop_long(frame->operand_stack);
    int s = v2&0x3f;
    long result =  (unsigned long)v1>>s;
    push_long(frame->operand_stack,result);
}