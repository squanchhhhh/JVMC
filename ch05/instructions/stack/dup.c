//
// Created by Squanch on 2024/6/3.
//

#include "dup.h"
//todo other dup
void init_DUP(DUP*self){
    self = (DUP*)malloc(sizeof(DUP));
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_DUP;
}
void init_DUP_X1(DUP_X1*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_DUP_X1;
}
void init_DUP_X2(DUP_X2*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_DUP_X2;
}
void init_DUP2(DUP2*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_DUP2;
}
void init_DUP2_X1(DUP2_X1*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_DUP2_X1;
}
void init_DUP2_X2(DUP2_X2*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_DUP2_X2;
}
void excute_DUP(void*self,Frame*frame){
    Slot slot = pop_slot(frame->operand_stack);
    push_slot(frame->operand_stack,slot);
    push_slot(frame->operand_stack,slot);
}
void excute_DUP_X1(void*self,Frame*frame){
    Slot slot1 = pop_slot(frame->operand_stack);
    Slot slot2 = pop_slot(frame->operand_stack);
    push_slot(frame->operand_stack,slot1);
    push_slot(frame->operand_stack,slot2);
    push_slot(frame->operand_stack,slot1);
}
void excute_DUP_X2(void*self,Frame*frame){
    Slot slot1 = pop_slot(frame->operand_stack);
    Slot slot2 = pop_slot(frame->operand_stack);
    Slot slot3 = pop_slot(frame->operand_stack);
    push_slot(frame->operand_stack,slot1);
    push_slot(frame->operand_stack,slot3);
    push_slot(frame->operand_stack,slot2);
    push_slot(frame->operand_stack,slot1);
}
void excute_DUP2(void*self,Frame*frame){
    Slot slot1 = pop_slot(frame->operand_stack);
    Slot slot2 = pop_slot(frame->operand_stack);
    push_slot(frame->operand_stack,slot2);
    push_slot(frame->operand_stack,slot1);
    push_slot(frame->operand_stack,slot2);
    push_slot(frame->operand_stack,slot1);
}
void excute_DUP2_X1(void*self,Frame*frame){
    Slot slot1 = pop_slot(frame->operand_stack);
    Slot slot2 = pop_slot(frame->operand_stack);
    Slot slot3 = pop_slot(frame->operand_stack);
    push_slot(frame->operand_stack,slot2);
    push_slot(frame->operand_stack,slot1);
    push_slot(frame->operand_stack,slot3);
    push_slot(frame->operand_stack,slot2);
    push_slot(frame->operand_stack,slot1);
}
void excute_DUP2_X2(void*self,Frame*frame){
    Slot slot1 = pop_slot(frame->operand_stack);
    Slot slot2 = pop_slot(frame->operand_stack);
    Slot slot3 = pop_slot(frame->operand_stack);
    Slot slot4 = pop_slot(frame->operand_stack);
    push_slot(frame->operand_stack,slot2);
    push_slot(frame->operand_stack,slot1);
    push_slot(frame->operand_stack,slot4);
    push_slot(frame->operand_stack,slot3);
    push_slot(frame->operand_stack,slot2);
    push_slot(frame->operand_stack,slot1);
}