//
// Created by Squanch on 2024/6/3.
//

#include <math.h>
#include "rem.h"
void init_DREM(DREM*self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_DREM;
}
void init_FREM(FREM*self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_FREM;
}
void init_IREM(IREM*self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_IREM;
}
void init_LREM(LREM*self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = excute_LREM;
}
void excute_DREM(void*self,Frame*frame){
    double v2 = pop_double(frame->operand_stack);
    double v1 = pop_double(frame->operand_stack);
    if (v2 == 0){
        printf("java.lang.ArithmeticException: / by zero");
        exit(-1);
    }
    double result = fmod(v1, v2);
    push_double(frame->operand_stack,result);
}
void excute_FREM(void*self,Frame*frame){
    float v2 = pop_float(frame->operand_stack);
    float v1 = pop_float(frame->operand_stack);
    if (v2 == 0){
        printf("java.lang.ArithmeticException: / by zero");
        exit(-1);
    }
    float result = fmodf(v1, v2);
    push_float(frame->operand_stack,result);
}
void excute_IREM(void*self,Frame*frame){
    int v2 = pop_int(frame->operand_stack);
    int v1 = pop_int(frame->operand_stack);
    if (v2 == 0){
        printf("java.lang.ArithmeticException: / by zero");
        exit(-1);
    }
    int result = v1&v2;
    push_int(frame->operand_stack,result);
}
void excute_LREM(void*self,Frame*frame){
    long v2 = pop_long(frame->operand_stack);
    long v1 = pop_long(frame->operand_stack);
    if (v2 == 0){
        printf("java.lang.ArithmeticException: / by zero");
        exit(-1);
    }
    long result = v1&v2;
    push_long(frame->operand_stack,result);
}