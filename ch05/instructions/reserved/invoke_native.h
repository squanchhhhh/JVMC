//
// Created by Squanch on 2024/6/13.
//

#ifndef JVMC_INVOKE_NATIVE_H
#define JVMC_INVOKE_NATIVE_H
#include "../base/instruction.h"
#include "../../native/register.h"

typedef struct{
    NoOperandsInstruction base;
}INVOKE_NATIVE;
void init_INVOKE_NATIVE(INVOKE_NATIVE*self);
void execute_INVOKE_NATIVE(void*self,Frame*frame);

#endif //JVMC_INVOKE_NATIVE_H
