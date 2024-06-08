//
// Created by Squanch on 2024/6/5.
//

#ifndef JVMC_CONSTANT_POOL_H
#define JVMC_CONSTANT_POOL_H

#include "common_classfile_struct.h"
typedef struct ClassReader ClassReader;
typedef struct ConstantPool ConstantPool;
typedef struct ConstantInfo ConstantInfo;
typedef struct ConstantFloatInfo ConstantFloatInfo;
typedef struct ConstantIntegerInfo ConstantIntegerInfo;
typedef struct ConstantLongInfo ConstantLongInfo;
typedef struct ConstantDoubleInfo ConstantDoubleInfo;
typedef struct ConstantUtf8Info ConstantUtf8Info;
typedef struct ConstantNameAndTypeInfo ConstantNameAndTypeInfo;
typedef struct ConstantMethodHandleInfo ConstantMethodHandleInfo;
typedef struct ConstantMethodTypeInfo ConstantMethodTypeInfo;
typedef struct ConstantStringInfo ConstantStringInfo;
typedef struct ConstantMethodRefInfo ConstantMethodRefInfo;
typedef struct ConstantFieldRefInfo ConstantFieldRefInfo;
typedef struct ConstantInterfaceMethodRefInfo ConstantInterfaceMethodRefInfo;
typedef struct ConstantInvokeDynamicInfo ConstantInvokeDynamicInfo;
typedef struct ConstantClassInfo ConstantClassInfo;
// 常量池标签
#define CONSTANT_Class              7
#define CONSTANT_Fieldref           9
#define CONSTANT_Methodref          10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String             8
#define CONSTANT_Integer            3
#define CONSTANT_Float              4
#define CONSTANT_Long               5
#define CONSTANT_Double             6
#define CONSTANT_NameAndType        12
#define CONSTANT_Utf8               1
#define CONSTANT_MethodHandle       15
#define CONSTANT_MethodType         16
#define CONSTANT_InvokeDynamic      18


ConstantInfo *new_constant_info(uint8_t tag, ConstantPool *pool, ClassReader *reader);

ConstantInfo *read_constant_info(ClassReader *reader, ConstantPool *pool);

ConstantPool *read_constant_pool(ClassReader *reader);

char *get_utf8_string(ConstantPool *pool, uint16_t index);

void read_integer(void *self, ClassReader *reader);

void init_read_integer(ConstantIntegerInfo *self, ClassReader *reader);

void read_float(void *self, ClassReader *reader);

void init_read_float(ConstantFloatInfo *self, ClassReader *reader);


void read_long(void *self, ClassReader *reader);

void init_read_long(ConstantLongInfo *self, ClassReader *reader);


void read_double(void *self, ClassReader *reader);

void init_read_double(ConstantDoubleInfo *self, ClassReader *reader);


char *decode_mutf8(const uint8_t *bytearr, size_t length);

void read_utf8(void *info, ClassReader *reader);

void init_read_utf8(ConstantUtf8Info *info, ClassReader *reader);


void read_string(void *info, ClassReader *reader);

void init_read_string(ConstantStringInfo *info, ClassReader *reader);


void read_class(void *info, ClassReader *reader);

void init_read_class(ConstantClassInfo *info, ClassReader *reader, ConstantPool *pool);


void read_name(void *info, ClassReader *reader);

void init_read_name(ConstantNameAndTypeInfo *info, ClassReader *reader);


void read_methodref(void *info, ClassReader *reader);

void init_read_methodref(ConstantMethodRefInfo *info, ClassReader *reader, uint8_t tag, ConstantPool *pool);


void read_fieldref(void *info, ClassReader *reader);

void init_read_fieldref(ConstantFieldRefInfo *info, ClassReader *reader, uint8_t tag, ConstantPool *pool);


void read_interface_methodref(void *info, ClassReader *reader);

void init_read_interface_methodref(ConstantInterfaceMethodRefInfo *info, ClassReader *reader, uint8_t tag,
                                   ConstantPool *pool);


#endif //JVMC_CONSTANT_POOL_H
