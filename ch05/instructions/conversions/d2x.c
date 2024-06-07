//
// Created by Squanch on 2024/6/3.
//

#include "d2x.h"
void init_D2F(D2F *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_D2F;
}
void init_D2I(D2I *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_D2I;
}
void init_D2L(D2L *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_D2L;
}
void init_F2D(F2D *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_F2D;
}
void init_F2I(F2I *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_F2I;
}
void init_F2L(F2L *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_F2L;
}
void execute_D2F(void * self,Frame*frame){
    double v = pop_double(frame->operand_stack);
    push_float(frame->operand_stack,(float)v);
}
void execute_D2I(void * self,Frame*frame){
    double v = pop_double(frame->operand_stack);
    push_int(frame->operand_stack,(int)v);
}
void execute_D2L(void * self,Frame*frame){
    double v = pop_double(frame->operand_stack);
    push_long(frame->operand_stack,(long)v);
}
void execute_F2D(void * self,Frame*frame){
    float v = pop_float(frame->operand_stack);
    push_double(frame->operand_stack,(double)v);
}
void execute_F2I(void * self,Frame*frame){
    float v = pop_float(frame->operand_stack);
    push_int(frame->operand_stack,(int)v);
}
void execute_F2L(void * self,Frame*frame){
    float v = pop_float(frame->operand_stack);
    push_long(frame->operand_stack,(long)v);
}