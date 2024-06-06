//
// Created by Squanch on 2024/6/3.
//

#include "const.h"
void init_ACONST_NULL(ACONST_NULL * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_aconst_null;
}
void init_DCONST_0(DCONST_0 * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_dconst_0;
}
void init_DCONST_1(DCONST_1 * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_dconst_1;
}
void init_FCONST_0(FCONST_0 * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_fconst_0;
}
void init_FCONST_1(FCONST_1 * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_fconst_1;
}
void init_FCONST_2(FCONST_2 * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_fconst_2;
}
void init_ICONST_M1(ICONST_M1 * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_iconst_m1;
}
void init_ICONST_0(ICONST_0 * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_iconst_0;
}
void init_ICONST_1(ICONST_1 * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_iconst_1;
}
void init_ICONST_2(ICONST_2 * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_iconst_2;
}
void init_ICONST_3(ICONST_3 * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_iconst_3;
}
void init_ICONST_4(ICONST_4 * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_iconst_4;
}
void init_ICONST_5(ICONST_5 * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_iconst_5;
}
void init_LCONST_0(LCONST_0 * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_lconst_0;
}
void init_LCONST_1(LCONST_1 * self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_lconst_1;
}

void excute_aconst_null(void * self,Frame *frame){
    push_ref(frame->operand_stack,NULL);
}
void excute_dconst_0(void * self,Frame *frame){
    push_double(frame->operand_stack,0.0);
}
void excute_dconst_1(void * self,Frame *frame){
    push_double(frame->operand_stack,1.0);
}
void excute_fconst_0(void * self,Frame *frame){
    push_float(frame->operand_stack,0.0);
}
void excute_fconst_1(void * self,Frame *frame){
    push_float(frame->operand_stack,1.0);
}
void excute_fconst_2(void * self,Frame *frame){
    push_float(frame->operand_stack,2.0);
}
void excute_iconst_m1(void * self,Frame *frame){
    push_int(frame->operand_stack,-1);
}
void excute_iconst_0(void * self,Frame *frame){
    push_int(frame->operand_stack,0);
}
void excute_iconst_1(void * self,Frame *frame){
    push_int(frame->operand_stack,1);
}
void excute_iconst_2(void * self,Frame *frame){
    push_int(frame->operand_stack,2);
}
void excute_iconst_3(void * self,Frame *frame){
    push_int(frame->operand_stack,3);
}
void excute_iconst_4(void * self,Frame *frame){
    push_int(frame->operand_stack,4);
}
void excute_iconst_5(void * self,Frame *frame){
    push_int(frame->operand_stack,5);
}
void excute_lconst_0(void * self,Frame *frame){
    push_long(frame->operand_stack,0);
}
void excute_lconst_1(void * self,Frame *frame){
    push_long(frame->operand_stack,1);
}
