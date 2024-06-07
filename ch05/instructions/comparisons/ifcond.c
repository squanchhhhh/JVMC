//
// Created by Squanch on 2024/6/3.
//

#include "ifcond.h"
void init_IFEQ(IFEQ*self){
    Branch_instruction_init(self->base);
    self->base.base.Execute = execute_IFEQ;
}
void init_IFNE(IFNE*self){
    Branch_instruction_init(self->base);
    self->base.base.Execute = execute_IFNE;
}
void init_IFLT(IFLT*self){
    Branch_instruction_init(self->base);
    self->base.base.Execute = execute_IFLT;
}
void init_IFLE(IFLE*self){
    Branch_instruction_init(self->base);
    self->base.base.Execute = execute_IFLE;
}
void init_IFGT(IFGT*self){
    Branch_instruction_init(self->base);
    self->base.base.Execute = execute_IFGT;
}
void init_IFGE(IFGE*self){
    Branch_instruction_init(self->base);
    self->base.base.Execute = execute_IFGE;
}
void execute_IFEQ(void * self,Frame*frame){
    IFEQ*self_ = (IFEQ*)self;
    int v = pop_int(frame->operand_stack);
    if (v==0){
        branch(frame,self_->base.offset);
    }
}
void execute_IFNE(void * self,Frame*frame){
    IFNE*self_ = (IFNE*)self;
    int v = pop_int(frame->operand_stack);
    if (v!=0){
        branch(frame,self_->base.offset);
    }
}
void execute_IFLT(void * self,Frame*frame){
    IFLT*self_ = (IFLT*)self;
    int v = pop_int(frame->operand_stack);
    if (v<0){
        branch(frame,self_->base.offset);
    }
}
void execute_IFLE(void * self,Frame*frame){
    IFLE*self_ = (IFLE*)self;
    int v = pop_int(frame->operand_stack);
    if (v<=0){
        branch(frame,self_->base.offset);
    }
}
void execute_IFGT(void * self,Frame*frame){
    IFGT*self_ = (IFGT*)self;
    int v = pop_int(frame->operand_stack);
    if (v>0){
        branch(frame,self_->base.offset);
    }
}
void execute_IFGE(void * self,Frame*frame){
    IFGE*self_ = (IFGE*)self;
    int v = pop_int(frame->operand_stack);
    if (v>=0){
        branch(frame,self_->base.offset);
    }
}