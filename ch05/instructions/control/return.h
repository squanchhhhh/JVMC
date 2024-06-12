//
// Created by Squanch on 2024/6/12.
//

#ifndef JVMC_RETURN_H
#define JVMC_RETURN_H
#include "../base/instruction.h"
typedef struct{
    NoOperandsInstruction base;
}RETURN;
typedef struct{
    NoOperandsInstruction base;
}ARETURN;
typedef struct {
    NoOperandsInstruction base;
}DRETURN;
typedef struct {
    NoOperandsInstruction base;
}FRETURN;
typedef struct {
    NoOperandsInstruction base;
}LRETURN;
typedef struct {
    NoOperandsInstruction base;
}IRETURN;

void init_RETURN(RETURN* self);
void init_ARETURN(ARETURN* self);
void init_DRETURN(DRETURN* self);
void init_FRETURN(FRETURN* self);
void init_LRETURN(LRETURN* self);
void init_IRETURN(IRETURN* self);

void execute_RETURN(void *self,Frame*frame);
void execute_ARETURN(void *self,Frame*frame);
void execute_DRETURN(void *self,Frame*frame);
void execute_FRETURN(void *self,Frame*frame);
void execute_LRETURN(void *self,Frame*frame);
void execute_IRETURN(void *self,Frame*frame);

#endif //JVMC_RETURN_H
