//
// Created by Squanch on 2024/6/5.
//

#ifndef JVMC_MEMBER_INFO_H
#define JVMC_MEMBER_INFO_H
#include "constant_pool.h"
#include "common_classfile_struct.h"
MemberInfo **read_members(ClassReader *reader, ConstantPool *pool, ClassFile *cf, int flag);
MemberInfo *read_member(ClassReader*reader,ConstantPool*pool);
char* read_member_name(MemberInfo *self,ConstantPool*pool);
CodeAttribute * get_code_attribute(MemberInfo *self);
ConstantValueAttribute *get_constant_value_attribute(MemberInfo *self);
#endif //JVMC_MEMBER_INFO_H
