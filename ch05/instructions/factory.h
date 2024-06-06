//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_FACTORY_H
#define JVMC_FACTORY_H
#include "base/instruction.h"
#include "../all_headers.h"


// 工厂函数，根据操作码创建指令
Instruction * new_instruction(unsigned char * opcode);
#endif //JVMC_FACTORY_H
