//
// Created by Squanch on 2024/6/3.
//

#include "if_acmp.h"
void init_IF_ACMPEQ(IF_ACMPEQ * self){
    Branch_instruction_init(&self->base);
    self->base.base.Execute = execute_IF_ACMPEQ;
}
void init_IF_ACMPNE(IF_ACMPNE * self){
    Branch_instruction_init(&self->base);
    self->base.base.Execute = execute_IF_ACMPNE;
}
void execute_IF_ACMPEQ(void * self,Frame*frame){
    IF_ACMPEQ * self_ = (IF_ACMPEQ*)self;
    int offset = self_->base.offset;
    Object *ref2 = pop_ref(frame->operand_stack);
    Object *ref1 = pop_ref(frame->operand_stack);
    if (ref1 == ref2){
        branch(frame,offset);
    }
}
void execute_IF_ACMPNE(void * self,Frame* frame){
    IF_ACMPNE * self_ = (IF_ACMPNE*)self;
    int offset = self_->base.offset;
    Object *ref2 = pop_ref(frame->operand_stack);
    Object *ref1 = pop_ref(frame->operand_stack);
    if (ref1!= ref2){
        branch(frame,offset);
    }
}