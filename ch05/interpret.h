//
// Created by Squanch on 2024/6/4.
//

#ifndef JVMC_INTERPRET_H
#define JVMC_INTERPRET_H
#include "rtda/thread.h"
#include "instructions/base/instruction.h"
#include "instructions/factory.h"
#include "classfile/common_classfile_struct.h"
#include "classfile/member_info.h"

void loop(Thread *thread, unsigned char *bytecode);
void interpret(RtMethods*methods);
#endif //JVMC_INTERPRET_H
