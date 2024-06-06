//
// Created by Squanch on 2024/6/3.
//

#ifndef JVMC_IF_ICMP_H
#define JVMC_IF_ICMP_H
#include "../base/instruction.h"
typedef struct{
    BranchInstruction * base;
}IF_ICMPEQ;
typedef struct{
    BranchInstruction * base;
}IF_ICMPNE;
typedef struct{
    BranchInstruction * base;
}IF_ICMPLT;
typedef struct{
    BranchInstruction * base;
}IF_ICMPLE;
typedef struct{
    BranchInstruction * base;
}IF_ICMPGT;
typedef struct{
    BranchInstruction * base;
}IF_ICMPGE;
void init_IF_ICMPEQ(IF_ICMPEQ*self);
void init_IF_ICMPNE(IF_ICMPNE*self);
void init_IF_ICMPLT(IF_ICMPLT*self);
void init_IF_ICMPLE(IF_ICMPLE*self);
void init_IF_ICMPGT(IF_ICMPGT*self);
void init_IF_ICMPGE(IF_ICMPGE*self);
void execute_IF_ICMPEQ(void * self,Frame*frame);
void execute_IF_ICMPNE(void * self,Frame*frame);
void execute_IF_ICMPLT(void * self,Frame*frame);
void execute_IF_ICMPLE(void * self,Frame*frame);
void execute_IF_ICMPGT(void * self,Frame*frame);
void execute_IF_ICMPGE(void * self,Frame*frame);

#endif //JVMC_IF_ICMP_H
