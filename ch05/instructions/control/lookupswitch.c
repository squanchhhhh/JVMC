//
// Created by Squanch on 2024/6/3.
//

#include "lookupswitch.h"
void init_LOOKUP_SWITCH(LOOKUP_SWITCH*self){
    self->base->FetchOperands = fetch_LOOKUP_SWITCH;
    self->base->Execute = execute_LOOKUP_SWITCH;
}
void fetch_LOOKUP_SWITCH(void* self,BytecodeReader*reader){
    skip_padding(reader);
    LOOKUP_SWITCH*lookup_switch = (LOOKUP_SWITCH*)self;
    lookup_switch->default_offset = read_int32(reader);
    lookup_switch->npairs = read_int32(reader);
    lookup_switch->match = malloc(sizeof(int32_t)*lookup_switch->npairs*2);
}
void execute_LOOKUP_SWITCH(void* self,Frame*frame){
    int key = pop_int(frame->operand_stack);
    LOOKUP_SWITCH*lookup_switch = (LOOKUP_SWITCH*)self;
    for (int i = 0;i<lookup_switch->npairs*2;i+=2){
        if (lookup_switch->match[i] == key){
            int offset = lookup_switch->match[i+1];
            branch(frame,offset);
            return;
        }
    }
    branch(frame,lookup_switch->default_offset);
}