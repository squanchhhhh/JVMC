//
// Created by Squanch on 2024/6/3.
//

#include "swap.h"
void init_SWAP(SWAP * swap){
    NoOperands_instruction_init(swap->base);
    swap->base->base.Execute = excute_SWAP;
}
void excute_SWAP(void * self,Frame*frame){
    Slot slot1 = pop_slot(frame->operand_stack);
    Slot slot2 = pop_slot(frame->operand_stack);
    push_slot(frame->operand_stack,slot1);
    push_slot(frame->operand_stack,slot2);
}