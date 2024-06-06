//
// Created by Squanch on 2024/6/3.
//

#include "pop.h"
void init_POP(POP*self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_POP;
}
void init_POP2(POP2*self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_POP2;
}
void excute_POP(void * self,Frame*frame){
    pop_slot(frame->operand_stack);
}
void excute_POP2(void * self,Frame*frame){
    pop_slot(frame->operand_stack);
    pop_slot(frame->operand_stack);
}