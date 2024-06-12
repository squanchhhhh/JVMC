//
// Created by Squanch on 2024/6/12.
//

#include "return.h"
void init_RETURN(RETURN* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_RETURN;
}
void init_ARETURN(ARETURN* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_ARETURN;
}
void init_DRETURN(DRETURN* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_DRETURN;
}
void init_FRETURN(FRETURN* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_FRETURN;
}
void init_LRETURN(LRETURN* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_LRETURN;
}
void init_IRETURN(IRETURN* self){
    NoOperands_instruction_init(&self->base);
    self->base.base.Execute = execute_IRETURN;
}

void execute_RETURN(void *self,Frame*frame){
    pop_frame(frame->thread);
}
void execute_ARETURN(void *self,Frame*frame){
    Thread * thread = frame->thread;
    Frame * current = pop_frame(thread);
    Frame * caller_frame = top_frame(thread);
    Object * ret = pop_ref(current->operand_stack);
    push_ref(caller_frame->operand_stack,ret);
}

void execute_DRETURN(void *self,Frame*frame){
    Thread * thread = frame->thread;
    Frame * current = pop_frame(thread);
    Frame * caller_frame = top_frame(thread);
    double ret = pop_double(current->operand_stack);
    push_double(caller_frame->operand_stack,ret);
}
void execute_FRETURN(void *self,Frame*frame){
    Thread * thread = frame->thread;
    Frame * current = pop_frame(thread);
    Frame * caller_frame = top_frame(thread);
    float ret = pop_float(current->operand_stack);
    push_float(caller_frame->operand_stack,ret);
}
void execute_LRETURN(void *self,Frame*frame){
    Thread * thread = frame->thread;
    Frame * current = pop_frame(thread);
    Frame * caller_frame = top_frame(thread);
    long ret = pop_long(current->operand_stack);
    push_long(caller_frame->operand_stack,ret);
}
void execute_IRETURN(void *self,Frame*frame){
    Thread * thread = frame->thread;
    Frame * current = pop_frame(thread);
    Frame * caller_frame = top_frame(thread);
    int ret = pop_int(current->operand_stack);
    push_int(caller_frame->operand_stack,ret);
}