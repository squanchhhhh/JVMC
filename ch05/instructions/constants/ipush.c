//
// Created by Squanch on 2024/6/3.
//

#include "ipush.h"
void init_BIPUSH(BIPUSH*self){
    self->base->Execute = excute_bipush;
    self->base->FetchOperands = fetch_bipush;
}
void fetch_bipush(void *bipush,BytecodeReader * reader){
    BIPUSH * self = (BIPUSH *)bipush;
    self->val = read_int8(reader);
}
void excute_bipush(void *bipush,Frame * frame){
    BIPUSH * self = (BIPUSH *)bipush;
    push_int(frame->operand_stack,(int)self->val);
}

void init_SIPUSH(SIPUSH*self){
    self->base->FetchOperands = fetch_bipush;
    self->base->Execute = excute_bipush;
}
void fetch_sipush(void *sipush,BytecodeReader * reader){
    SIPUSH * self = (SIPUSH *)sipush;
    self->val = read_int16(reader);
}

void excute_sipush(void *sipush,Frame * frame){
    SIPUSH * self = (SIPUSH *)sipush;
    push_int(frame->operand_stack,(int)self->val);
}
