//
// Created by Squanch on 2024/6/5.
//

#ifndef JVMC_MEMBER_INFO_H
#define JVMC_MEMBER_INFO_H
#include "constant_pool.h"
#include "attr_info.h"
typedef struct{
    ConstantPool * pool;
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    AttributeInfo ** attributes;
}MemberInfo;

MemberInfo **read_members(ClassReader*reader,ConstantPool*pool);
MemberInfo *read_member(ClassReader*reader,ConstantPool*pool);
char* read_member_name(MemberInfo *self,ConstantPool*pool);
#endif //JVMC_MEMBER_INFO_H
