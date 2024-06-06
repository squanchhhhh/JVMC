//
// Created by Squanch on 2024/6/3.
//

#include "goto.h"
void init_GOTO(GOTO *self){
    Branch_instruction_init(self->base);
    self->base->base.Execute = execute_GOTO;
}
void execute_GOTO(void * self,Frame*frame){
    GOTO *self_ = (GOTO*)self;
    branch(frame,self_->base->offset);
}