//
// Created by Squanch on 2024/6/3.
//

#include "lstore.h"
void _lstore(Frame*frame,int index){
    long var = pop_long(frame->operand_stack);
    set_long(frame->local_vars,index,var);
}
void excute_lstore(void* self,Frame*frame){
    LSTORE * inst = (LSTORE*)self;
    _lstore(frame,inst->base.index);
}
void excute_lstore_0(void* self,Frame*frame){
    _lstore(frame,0);
}
void excute_lstore_1(void* self,Frame*frame){
    _lstore(frame,1);
}
void excute_lstore_2(void* self,Frame*frame){
    _lstore(frame,2);
}
void excute_lstore_3(void* self,Frame*frame){
    _lstore(frame,3);
}
void init_LSTORE(LSTORE* self){
    Index8_instruction_init(self->base);
    self->base.base.Execute = excute_lstore;
}
void init_LSTORE_0(LSTORE_0* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_lstore_0;
}
void init_LSTORE_1(LSTORE_1* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_lstore_1;
}
void init_LSTORE_2(LSTORE_2* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_lstore_2;
}
void init_LSTORE_3(LSTORE_3* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_lstore_3;
}

void _istore(Frame*frame,int index){
    int var = pop_int(frame->operand_stack);
    set_int(frame->local_vars,index,var);
}
void excute_istore(void* self,Frame*frame){
    ISTORE * inst = (ISTORE*)self;
    _istore(frame,inst->base.index);
}
void excute_istore_0(void* self,Frame*frame){
    _istore(frame,0);
}
void excute_istore_1(void* self,Frame*frame){
    _istore(frame,1);
}
void excute_istore_2(void* self,Frame*frame){
    _istore(frame,2);
}
void excute_istore_3(void* self,Frame*frame){
    _istore(frame,3);
}
void init_ISTORE(ISTORE* self){
    Index8_instruction_init(self->base);
    self->base.base.Execute = excute_istore;
}
void init_ISTORE_0(ISTORE_0* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_istore_0;
}
void init_ISTORE_1(ISTORE_1* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_istore_1;
}
void init_ISTORE_2(ISTORE_2* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_istore_2;
}
void init_ISTORE_3(ISTORE_3* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_istore_3;
}
//todo other store