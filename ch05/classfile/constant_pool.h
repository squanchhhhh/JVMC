//
// Created by Squanch on 2024/6/5.
//

#ifndef JVMC_CONSTANT_POOL_H
#define JVMC_CONSTANT_POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "class_reader.h"

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

typedef struct ConstantPool ConstantPool;
typedef struct ConstantInfo ConstantInfo;
ConstantInfo *new_constant_info(uint8_t tag, ConstantPool *pool, ClassReader *reader);
ConstantInfo *read_constant_info(ClassReader *reader, ConstantPool *pool);
struct ConstantInfo {
    uint8_t tag;
    void (*read_info)(void *self, ClassReader *reader);
};

struct ConstantPool {
    int index;
    int count;
    ConstantInfo **constants;  // Pointer to an array of pointers
};
ConstantPool *read_constant_pool(ClassReader *reader);
char* get_utf8_string(ConstantPool *pool,uint16_t index);


typedef struct {
    int32_t value;
    ConstantInfo *base;
} ConstantIntegerInfo;
void read_integer(void *self, ClassReader *reader);
void init_read_integer(ConstantIntegerInfo *self, ClassReader *reader);

typedef struct {
    float value;
    ConstantInfo *base;
}ConstantFloatInfo;
void read_float(void *self, ClassReader *reader);
void init_read_float(ConstantFloatInfo *self, ClassReader *reader);

typedef struct {
    int64_t value;
    ConstantInfo *base;
}ConstantLongInfo;
void read_long(void *self, ClassReader *reader);
void init_read_long(ConstantLongInfo *self, ClassReader *reader);

typedef struct {
    double value;
    ConstantInfo *base;
}ConstantDoubleInfo;
void read_double(void *self, ClassReader *reader);
void init_read_double(ConstantDoubleInfo *self, ClassReader *reader);

typedef struct {
    char * str;
    ConstantInfo *base;
}ConstantUtf8Info;
char *decode_mutf8(const uint8_t *bytearr, size_t length);
void read_utf8(void *info, ClassReader *reader);
void init_read_utf8(ConstantUtf8Info *info, ClassReader *reader);

typedef struct {
    ConstantPool * pool;
    uint16_t string_index;
    ConstantInfo *base;
}ConstantStringInfo;
void read_string(void *info, ClassReader *reader);
void init_read_string(ConstantStringInfo *info, ClassReader *reader);

typedef struct {
    ConstantPool * pool;
    uint16_t name_index;
    ConstantInfo *base;
}ConstantClassInfo;
void read_class(void *info, ClassReader *reader);
void init_read_class(ConstantClassInfo *info, ClassReader *reader);

typedef struct {
    uint16_t name_index;
    uint16_t descriptor_index;
    ConstantInfo * base;
}ConstantNameAndTypeInfo;
void read_name(void *info, ClassReader *reader);
void init_read_name(ConstantNameAndTypeInfo *info, ClassReader *reader);

typedef struct {
    ConstantInfo * base;
    ConstantPool * pool;
    uint16_t class_index;
    uint16_t name_and_type_index;
}ConstantMemberrefInfo;
typedef struct {
    ConstantMemberrefInfo * base;
}ConstantFieldrefInfo;
typedef struct {
    ConstantMemberrefInfo * base;
}ConstantMethodrefInfo;
typedef struct {
    ConstantMemberrefInfo * base;
}ConstantInterfaceMethodrefInfo;
void read_memberref(void *info, ClassReader *reader);
void init_read_memberref(ConstantMemberrefInfo *info, ClassReader *reader,uint8_t tag);






#endif //JVMC_CONSTANT_POOL_H
