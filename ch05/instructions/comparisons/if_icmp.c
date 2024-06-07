//
// Created by Squanch on 2024/6/3.
//

#include "if_icmp.h"
void init_IF_ICMPEQ(IF_ICMPEQ*self){
    Branch_instruction_init(&self->base);
    self->base.base.Execute = execute_IF_ICMPEQ;
}
void init_IF_ICMPNE(IF_ICMPNE*self){
    Branch_instruction_init(&self->base);
    self->base.base.Execute = execute_IF_ICMPNE;
}
void init_IF_ICMPLT(IF_ICMPLT*self){
    Branch_instruction_init(&self->base);
    self->base.base.Execute = execute_IF_ICMPLT;
}
void init_IF_ICMPLE(IF_ICMPLE*self){
    Branch_instruction_init(&self->base);
    self->base.base.Execute = execute_IF_ICMPLE;
}
void init_IF_ICMPGT(IF_ICMPGT*self){
    Branch_instruction_init(&self->base);
    self->base.base.Execute = execute_IF_ICMPGT;
}
void init_IF_ICMPGE(IF_ICMPGE*self){
    Branch_instruction_init(&self->base);
    self->base.base.Execute = execute_IF_ICMPGE;
}
void execute_IF_ICMPEQ(void * self,Frame*frame){
    IF_ICMPEQ*self_ = (IF_ICMPEQ*)self;
    int offset = self_->base.offset;
    int v2 = pop_int(frame->operand_stack);
    int v1 = pop_int(frame->operand_stack);
    if(v1 == v2){
       branch(frame,offset);
    }
}
void execute_IF_ICMPNE(void * self,Frame*frame){
    IF_ICMPNE*self_ = (IF_ICMPNE*)self;
    int offset = self_->base.offset;
    int v2 = pop_int(frame->operand_stack);
    int v1 = pop_int(frame->operand_stack);
    if(v1!= v2){
        branch(frame,offset);
    }
}
void execute_IF_ICMPLT(void * self,Frame*frame){
    IF_ICMPLT*self_ = (IF_ICMPLT*)self;
    int offset = self_->base.offset;
    int v2 = pop_int(frame->operand_stack);
    int v1 = pop_int(frame->operand_stack);
    if(v1 < v2){
        branch(frame,offset);
    }
}
void execute_IF_ICMPLE(void * self,Frame*frame){
    IF_ICMPLE*self_ = (IF_ICMPLE*)self;
    int offset = self_->base.offset;
    int v2 = pop_int(frame->operand_stack);
    int v1 = pop_int(frame->operand_stack);
    if(v1 <= v2){
        branch(frame,offset);
    }
}
void execute_IF_ICMPGT(void * self,Frame*frame){
    IF_ICMPGT*self_ = (IF_ICMPGT*)self;
    int offset = self_->base.offset;
    int v2 = pop_int(frame->operand_stack);
    int v1 = pop_int(frame->operand_stack);
    if(v1 > v2){
        branch(frame,offset);
    }
}
void execute_IF_ICMPGE(void * self,Frame*frame){
    IF_ICMPGE*self_ = (IF_ICMPGE*)self;
    int offset = self_->base.offset;
    int v2 = pop_int(frame->operand_stack);
    int v1 = pop_int(frame->operand_stack);
    if(v1 >= v2){
        branch(frame,offset);
    }
}