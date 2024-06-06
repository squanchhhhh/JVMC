//
// Created by Squanch on 2024/6/3.
//

#include "tableswitch.h"
void init_TABLE_SWITCH(TABLE_SWITCH*self){
    self->base->Execute = execute_TABLE_SWITCH;
    self->base->FetchOperands = fetch_TABLE_SWITCH;
}
void fetch_TABLE_SWITCH(void *self,BytecodeReader *reader){
    skip_padding(reader);
    TABLE_SWITCH*table_switch = (TABLE_SWITCH*)self;
    table_switch->default_offset = read_int32(reader);
    table_switch->low = read_int32(reader);
    table_switch->high = read_int32(reader);
    table_switch->offsets = malloc(sizeof(int32_t)*(table_switch->high-table_switch->low+1));
}
void execute_TABLE_SWITCH(void *self,Frame*frame){
    int index = pop_int(frame->operand_stack);
    TABLE_SWITCH*table_switch = (TABLE_SWITCH*)self;
    int offset;
    if (index>=table_switch->low && index<=table_switch->high){
         offset = table_switch->offsets[index-table_switch->low];
    }else{
         offset = table_switch->default_offset;
    }
    branch(frame,offset);
}
