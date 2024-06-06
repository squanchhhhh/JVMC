//
// Created by Squanch on 2024/6/3.
//

#include "iinc.h"
void init_IINC(IINC*self){
    NoOperands_instruction_init(self->base);
    self->base->base.Execute = execute_IINC;
}
void execute_IINC(void * self,Frame* frame){
    IINC* iinc = (IINC*)self;
    int32_t index = iinc->index;
    int32_t increment = iinc->increment;
    int32_t value = get_int(frame->local_vars,index);
    value += increment;
    set_int(frame->local_vars,index,value);
}