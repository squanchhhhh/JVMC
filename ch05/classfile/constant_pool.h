//
// Created by Squanch on 2024/6/5.
//

#ifndef JVMC_CONSTANT_POOL_H
#define JVMC_CONSTANT_POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "class_reader.h"
#include "common_classfile_struct.h"
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
char* get_utf8_string(ConstantPool *pool,uint16_t index);



void read_integer(void *self, ClassReader *reader);
void init_read_integer(ConstantIntegerInfo *self, ClassReader *reader);


void read_float(void *self, ClassReader *reader);
void init_read_float(ConstantFloatInfo *self, ClassReader *reader);

typedef struct {
    ConstantInfo base;
    int64_t value;
}ConstantLongInfo;
void read_long(void *self, ClassReader *reader);
void init_read_long(ConstantLongInfo *self, ClassReader *reader);

typedef struct {
    ConstantInfo base;
    double value;
}ConstantDoubleInfo;
void read_double(void *self, ClassReader *reader);
void init_read_double(ConstantDoubleInfo *self, ClassReader *reader);

typedef struct {
    ConstantInfo base;
    char * str;
}ConstantUtf8Info;
char *decode_mutf8(const uint8_t *bytearr, size_t length);
void read_utf8(void *info, ClassReader *reader);
void init_read_utf8(ConstantUtf8Info *info, ClassReader *reader);

typedef struct {
    ConstantInfo base;
    ConstantPool * pool;
    uint16_t string_index;
}ConstantStringInfo;
void read_string(void *info, ClassReader *reader);
void init_read_string(ConstantStringInfo *info, ClassReader *reader);

typedef struct {
    ConstantInfo base;
    ConstantPool * pool;
    uint16_t name_index;
}ConstantClassInfo;
void read_class(void *info, ClassReader *reader);
void init_read_class(ConstantClassInfo *info, ClassReader *reader);

typedef struct {
    ConstantInfo base;
    uint16_t name_index;
    uint16_t descriptor_index;
}ConstantNameAndTypeInfo;
void read_name(void *info, ClassReader *reader);
void init_read_name(ConstantNameAndTypeInfo *info, ClassReader *reader);


/**
 * 为了保证实现多态的效果，这里的ConstantInfo不能使用指针
 * 如果使用指针会导致类型强转时无法读取到base的信息
 */
typedef struct {
    ConstantInfo base;
    ConstantPool * pool;
    uint16_t class_index;
    uint16_t name_and_type_index;
}ConstantMethodrefInfo;
void read_methodref(void *info, ClassReader *reader);
void init_read_methodref(ConstantMethodrefInfo *info, ClassReader *reader,uint8_t tag);

typedef struct {
    ConstantInfo base;
    ConstantPool * pool;
    uint16_t class_index;
    uint16_t name_and_type_index;
}ConstantFieldrefInfo;
void read_fieldref(void *info, ClassReader *reader);
void init_read_fieldref(ConstantFieldrefInfo *info, ClassReader *reader,uint8_t tag);
typedef struct {
    ConstantInfo base;
    ConstantPool * pool;
    uint16_t class_index;
    uint16_t name_and_type_index;
}ConstantInterfaceMethodrefInfo;
void read_interface_methodref(void *info, ClassReader *reader);
void init_read_interface_methodref(ConstantInterfaceMethodrefInfo *info, ClassReader *reader,uint8_t tag);







#endif //JVMC_CONSTANT_POOL_H
