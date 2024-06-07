//
// Created by Squanch on 2024/6/3.
//

#include "i2x.h"
void init_I2L(I2L *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_I2L;
}
void init_I2F(I2F *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_I2F;
}
void init_I2D(I2D *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_I2D;
}
void init_L2I(L2I *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_L2I;
}
void init_L2F(L2F *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_L2F;
}
void init_L2D(L2D *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_L2D;
}
void init_I2B(I2B *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_I2B;
}
void init_I2C(I2C *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_I2C;
}
void init_I2S(I2S *self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_I2S;
}
void execute_I2L(void*self,Frame*frame){
    int v = pop_int(frame->operand_stack);
    push_long(frame->operand_stack,v);
}
void execute_I2F(void*self,Frame*frame){
    int v = pop_int(frame->operand_stack);
    push_float(frame->operand_stack,(float)v);
}
void execute_I2D(void*self,Frame*frame){
    int v = pop_int(frame->operand_stack);
    push_double(frame->operand_stack,(double)v);
}
void execute_L2I(void*self,Frame*frame) {
    long v = pop_long(frame->operand_stack);
    push_int(frame->operand_stack, (int) v);
}
void execute_L2F(void*self,Frame*frame){
    long v = pop_long(frame->operand_stack);
    push_float(frame->operand_stack,(float)v);
}
void execute_L2D(void*self,Frame*frame){
    long v = pop_long(frame->operand_stack);
    push_double(frame->operand_stack,(double)v);
}
// todo i2b
void execute_I2B(void*self,Frame*frame){
    int v = pop_int(frame->operand_stack);
    push_int(frame->operand_stack,(uint8_t)v);
}
void execute_I2C(void*self,Frame*frame){
    int v = pop_int(frame->operand_stack);
    push_int(frame->operand_stack,(uint16_t)v);
}
void execute_I2S(void*self,Frame*frame){
    int v = pop_int(frame->operand_stack);
    push_int(frame->operand_stack,(uint16_t)v);
}