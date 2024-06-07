//
// Created by Squanch on 2024/6/3.
//

#include "iload.h"
void _iload(Frame*frame,int index){
    int val = get_int(frame->local_vars,index);
    push_int(frame->operand_stack,val);
}
void excute_iload(void * self,Frame*frame){
    ILOAD*inst = (ILOAD*)self;
    int index = inst->base.index;
    _iload(frame,index);
}
void excute_iload_0(void * self,Frame *frame){
    _iload(frame,0);
}
void excute_iload_1(void * self,Frame *frame){
    _iload(frame,1);
}
void excute_iload_2(void * self,Frame *frame){
    _iload(frame,2);
}
void excute_iload_3(void * self,Frame *frame){
    _iload(frame,3);
}

void init_ILOAD(ILOAD*self){
    Index8_instruction_init(self->base);
    self->base.base.Execute = excute_iload;
}
void init_ILOAD_0(ILOAD_0*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_iload_0;
}
void init_ILOAD_1(ILOAD_1*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_iload_1;
}
void init_ILOAD_2(ILOAD_2*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_iload_2;
}
void init_ILOAD_3(ILOAD_3*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_iload_3;
}


void excute_aload(void * self,Frame *frame){
    ALOAD*inst = (ALOAD*)self;
    int index = inst->base.index;
    _aload(frame,index);
}
void excute_aload_0(void * self,Frame *frame){
    _aload(frame,0);
}
void excute_aload_1(void * self,Frame *frame){
    _aload(frame,1);
}
void excute_aload_2(void * self,Frame *frame){
    _aload(frame,2);
}
void excute_aload_3(void * self,Frame *frame){
    _aload(frame,3);
}

void init_ALOAD(ALOAD*self){
    Index8_instruction_init(self->base);
    self->base.base.Execute = excute_aload;
}
void init_ALOAD_0(ALOAD_0*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_aload_0;
}
void init_ALOAD_1(ALOAD_1*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_aload_1;
}
void init_ALOAD_2(ALOAD_2*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_aload_2;
}
void init_ALOAD_3(ALOAD_3*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_aload_3;
}
void _aload(Frame*frame,int index){
    Object* val = get_ref(frame->local_vars,index);
    push_ref(frame->operand_stack,val);
}

void excute_lload(void * self,Frame *frame){
    LLOAD*inst = (LLOAD*)self;
    int index = inst->base.index;
    _lload(frame,index);
}
void excute_lload_0(void * self,Frame *frame){
    _lload(frame,0);
}
void excute_lload_1(void * self,Frame *frame){
    _lload(frame,1);
}
void excute_lload_2(void * self,Frame *frame){
    _lload(frame,2);
}
void excute_lload_3(void * self,Frame *frame){
    _lload(frame,3);
}

void init_LLOAD(LLOAD*self){
    Index8_instruction_init(self->base);
    self->base.base.Execute = excute_lload;
}
void init_LLOAD_0(LLOAD_0*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_lload_0;
}
void init_LLOAD_1(LLOAD_1*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_lload_1;
}
void init_LLOAD_2(LLOAD_2*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_lload_2;
}
void init_LLOAD_3(LLOAD_3*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_lload_3;
}
void _lload(Frame*frame,int index){
    long val = get_long(frame->local_vars,index);
    push_long(frame->operand_stack,val);
}

void excute_dload(void * self,Frame *frame){
    DLOAD*inst = (DLOAD*)self;
    int index = inst->base.index;
    _dload(frame,index);
}
void excute_dload_0(void * self,Frame *frame){
    _dload(frame,0);
}
void excute_dload_1(void * self,Frame *frame){
    _dload(frame,1);
}
void excute_dload_2(void * self,Frame *frame){
    _dload(frame,2);
}
void excute_dload_3(void * self,Frame *frame){
    _dload(frame,3);
}

void init_DLOAD(DLOAD*self){
    Index8_instruction_init(self->base);
    self->base.base.Execute = excute_dload;
}
void init_DLOAD_0(DLOAD_0*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_dload_0;
}
void init_DLOAD_1(DLOAD_1*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_dload_1;
}
void init_DLOAD_2(DLOAD_2*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_dload_2;
}
void init_DLOAD_3(DLOAD_3*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_dload_3;
}
void _dload(Frame*frame,int index){
    double val = get_double(frame->local_vars,index);
    push_double(frame->operand_stack,val);
}


void excute_fload(void * self,Frame *frame){
    FLOAD*inst = (FLOAD*)self;
    int index = inst->base.index;
    _fload(frame,index);
}

void excute_fload_0(void * self,Frame *frame){
    _fload(frame,0);
}
void excute_fload_1(void * self,Frame *frame){
    _fload(frame,1);
}
void excute_fload_2(void * self,Frame *frame){
    _fload(frame,2);
}
void excute_fload_3(void * self,Frame *frame){
    _fload(frame,3);
}

void init_FLOAD(FLOAD*self){
    Index8_instruction_init(self->base);
    self->base.base.Execute = excute_fload;
}
void init_FLOAD_0(FLOAD_0*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_fload_0;
}
void init_FLOAD_1(FLOAD_1*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_fload_1;
}
void init_FLOAD_2(FLOAD_2*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_fload_2;
}
void init_FLOAD_3(FLOAD_3*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_fload_3;
}
void _fload(Frame*frame,int index){
    float val = get_float(frame->local_vars,index);
    push_float(frame->operand_stack,val);
}