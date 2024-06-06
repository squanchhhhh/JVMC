//
// Created by Squanch on 2024/6/4.
//

#ifndef JVMC_INTERPRET_H
#define JVMC_INTERPRET_H
#include "rtda/thread.h"
#include "instructions/base/instruction.h"
#include "instructions/factory.h"
void loop(Thread *thread, unsigned char *bytecode);
#endif //JVMC_INTERPRET_H
