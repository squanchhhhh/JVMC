//
// Created by Squanch on 2024/6/5.
//

#ifndef JVMC_MEMBER_INFO_H
#define JVMC_MEMBER_INFO_H
#include "common_classfile_struct.h"
typedef struct ClassFile ClassFile;
typedef struct ConstantPool ConstantPool;
typedef struct ClassReader ClassReader;
typedef struct AttributeInfo AttributeInfo;
typedef struct CodeAttribute CodeAttribute;
typedef struct ConstantValueAttribute ConstantValueAttribute;
typedef struct MemberInfo MemberInfo;

MemberInfo **read_members(ClassReader *reader, ConstantPool *pool, ClassFile *cf, int flag);
MemberInfo *read_member(ClassReader*reader,ConstantPool*pool);
char* read_member_name(MemberInfo *self,ConstantPool*pool);
CodeAttribute * get_code_attribute(MemberInfo *self);
ConstantValueAttribute *get_constant_value_attribute(MemberInfo *self);
#endif //JVMC_MEMBER_INFO_H
