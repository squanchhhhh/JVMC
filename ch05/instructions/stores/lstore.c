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
    Index8_instruction_init(&self->base);
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
    Index8_instruction_init(&self->base);
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

void _astore(Frame*frame,int index){
    Object* var = pop_ref(frame->operand_stack);
    set_ref(frame->local_vars,index,var);
}
void excute_astore(void* self,Frame*frame){
    ASTORE * inst = (ASTORE*)self;
    _astore(frame,inst->base.index);
}

void init_ASTORE(ASTORE* self){
    Index8_instruction_init(&self->base);
    self->base.base.Execute = excute_astore;
}

void execute_astore(void* self,Frame* frame){
    ASTORE * inst = (ASTORE*)self;
    _astore(frame,inst->base.index);
}
void excute_astore_0(void* self,Frame*frame){
    _astore(frame,0);
}
void excute_astore_1(void* self,Frame*frame){
    _astore(frame,1);
}
void excute_astore_2(void* self,Frame*frame){
    _astore(frame,2);
}
void excute_astore_3(void* self,Frame*frame){
    _astore(frame,3);
}
void init_ASTORE_0(ASTORE_0* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_astore_0;
}
void init_ASTORE_1(ASTORE_1* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_astore_1;
}
void init_ASTORE_2(ASTORE_2* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_astore_2;
}
void init_ASTORE_3(ASTORE_3* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_astore_3;
}



void init_AASTORE(AASTORE*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_aastore;
}
void init_BASTORE(BASTORE*self);
void init_CASTORE(CASTORE*self);
void init_DASTORE(DASTORE*self);
void init_FASTORE(FASTORE*self);
void init_IASTORE(IASTORE*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = excute_iastore;
}
void init_LASTORE(LASTORE*self);
void init_SASTORE(SASTORE*self);
void excute_aastore(void* self,Frame*frame){

}
void excute_bastore(void* self,Frame*frame);
void excute_castore(void* self,Frame*frame);
void excute_dastore(void* self,Frame*frame);
void excute_fastore(void* self,Frame*frame);
void excute_iastore(void* self,Frame*frame){
    OperandStack *stack = frame->operand_stack;
    int val = pop_int(stack);
    int index = pop_int(stack);
    Object * arr_ref = pop_ref(stack);
    if(arr_ref == NULL){
        printf("java.lang.NullPointerException\n");
        exit(1);
    }
    int32_t* int_arr = ints(arr_ref);
    if (index >= arrayLength(arr_ref) || index <0){
        printf("java.lang.ArrayIndexOutOfBoundsException\n");
        exit(1);
    }
    int_arr[index] = val;
}
void excute_lastore(void* self,Frame*frame);
void excute_sastore(void* self,Frame*frame);
