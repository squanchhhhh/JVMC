//
// Created by Squanch on 2024/6/3.
//

#include "cmp.h"
void init_LCMP(LCMP*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_LCMP;
}
void init_FCMPG(FCMPG*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_FCMPG;
}
void init_FCMPL(FCMPL*self) {
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_FCMPL;
}
void init_DCMPL(DCMPL*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_DCMPL;
}
void init_DCMPG(DCMPG*self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_DCMPG;
}
void _FCMP(Frame*frame,int flag){
    float v2 = pop_float(frame->operand_stack);
    float v1 = pop_float(frame->operand_stack);
    if (v1>v2){
        push_int(frame->operand_stack,1);
    }else if(v1==v2){
        push_int(frame->operand_stack,0);
    }else if(v1<v2){
        push_int(frame->operand_stack,-1);
    }else if (flag){
        push_int(frame->operand_stack,1);
    }else {
        push_int(frame->operand_stack, -1);
    }
}
void _DCMP(Frame*frame,int flag){
    double v2 = pop_double(frame->operand_stack);
    double v1 = pop_double(frame->operand_stack);
    if (v1>v2){
        push_int(frame->operand_stack,1);
    }else if(v1==v2){
        push_int(frame->operand_stack,0);
    }else if(v1<v2){
        push_int(frame->operand_stack,-1);
    }else if (flag){
        push_int(frame->operand_stack,1);
    }else {
        push_int(frame->operand_stack, -1);
    }
}
void execute_LCMP(void*self,Frame*frame){
    long v2 = pop_long(frame->operand_stack);
    long v1 = pop_long(frame->operand_stack);
    if (v1>v2){
        push_int(frame->operand_stack,1);
    }else if (v1 == v2){
        push_int(frame->operand_stack,0);
    }else{
        push_int(frame->operand_stack,-1);
    }


}
void execute_FCMPG(void*self,Frame*frame){
    _FCMP(frame,1);
}
void execute_FCMPL(void*self,Frame*frame){
    _FCMP(frame,0);
}
void execute_DCMPL(void*self,Frame*frame){
    _DCMP(frame,0);
}
void execute_DCMPG(void*self,Frame*frame){
    _DCMP(frame,1);
}